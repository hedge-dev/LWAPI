#pragma once

namespace app
{
	class EnemyDekunutsShot;

	namespace dekunuts_shot
	{
		class CreateInfo
		{
		public:
			csl::math::Matrix34 TrasnformMtx{};
			hh::gfx::res::ResModel ShotModel{};
			float Speed{};
			float LifeSpan{};
		};

		inline EnemyDekunutsShot* Create(const CreateInfo& in_rCreateInfo, GameDocument* in_pDocument, csl::fnd::IAllocator* in_pAllocator);
	}

	class EnemyDekunutsShot : public GameObject3D
	{
	public:
		inline static constexpr int FLAG_IS_EXPLODING = 0;
		inline static constexpr int FLAG_IS_DAMAGED = 1;

	private:
		inline static const char* ms_pEffectName = "ef_dl3_dekunuts_hit";
		inline static const char* ms_pSoundName = "enm_cmn_bullet_landing";
		inline static const size_t ms_ShapeCount = 2;
		inline static const float ms_ShadowRadius = 1.5f;
		inline static const float ms_CollisionRadius = 1.5f;

	public:
		const dekunuts_shot::CreateInfo* pCreateInfo{};
		csl::math::Vector3 StartingPosition{};
		float LifeSpan{};
		float ElapsedTime{};
		float Roll{};
		csl::ut::Bitset<uint8> Flags{};

		EnemyDekunutsShot(const dekunuts_shot::CreateInfo& in_rCreateInfo) : GameObject3D()
			, pCreateInfo(&in_rCreateInfo)
			, StartingPosition(pCreateInfo->TrasnformMtx.GetTransVector())
			, LifeSpan(pCreateInfo->LifeSpan)
		{
			ObjUtil::SetPropertyLockonTarget(this);
		}

		void AddCallback(GameDocument* in_pDocument) override
		{
			fnd::GOComponent::Create<fnd::GOCVisualModel>(*this);
			fnd::GOComponent::Create<game::GOCCollider>(*this);
			fnd::GOComponent::Create<game::GOCGravity>(*this);
			fnd::GOComponent::Create<game::GOCMovementComplex>(*this);
			fnd::GOComponent::Create<game::GOCShadowSimple>(*this);
			fnd::GOComponent::Create<game::GOCEffect>(*this);
			fnd::GOComponent::Create<game::GOCSound>(*this);

			fnd::GOComponent::BeginSetup(*this);

			auto* pTransformGoc = GetComponent<fnd::GOCTransform>();
			pTransformGoc->SetLocalTranslation(pCreateInfo->TrasnformMtx.GetTransVector());
			pTransformGoc->SetLocalRotation({ pCreateInfo->TrasnformMtx });

			if (auto* pVisualGoc = GetComponent<fnd::GOCVisualModel>())
			{
				fnd::GOCVisualModel::Description description{};
				description.Model = pCreateInfo->ShotModel;
				description.Unk2 |= 0x400000;

				pVisualGoc->Setup(description);
			}

			game::GOCGravity::SimpleSetup(this, 1);

			if (auto* pShadowSimple = GetComponent<game::GOCShadowSimple>())
			{
				game::ShadowSphereShapeCInfo shadowInfo{ ms_ShadowRadius };
				shadowInfo.Unk2 = 5;
				shadowInfo.ShadowQuality = 2;

				game::GOCShadowSimple::Description description{ &shadowInfo };
				pShadowSimple->Setup(description);
			}

			if (auto* pCollider = GetComponent<game::GOCCollider>())
			{
				pCollider->Setup({ ms_ShapeCount });
				game::ColliSphereShapeCInfo collisionInfo{};
				collisionInfo.ShapeType = game::CollisionShapeType::ShapeType::eShapeType_Sphere;
				collisionInfo.MotionType = game::PhysicsMotionType::MotionType::eMotionType_Value2;
				collisionInfo.Unk2 |= 1;
				collisionInfo.Unk3 = 0x20000;
				collisionInfo.ShapeID = 0;
				collisionInfo.Radius = ms_CollisionRadius;
				ObjUtil::SetupCollisionFilter(ObjUtil::EFilter::eFilter_Default, collisionInfo);

				pCollider->CreateShape(collisionInfo);

				collisionInfo = {};
				collisionInfo.ShapeType = game::CollisionShapeType::ShapeType::eShapeType_Sphere;
				collisionInfo.MotionType = game::PhysicsMotionType::MotionType::eMotionType_Value2;
				collisionInfo.Unk2 |= 1;
				collisionInfo.ShapeID = 1;
				collisionInfo.Radius = ms_CollisionRadius;
				ObjUtil::SetupCollisionFilter(ObjUtil::EFilter::eFilter_Unk3, collisionInfo);

				auto* pShape = pCollider->CreateShape(collisionInfo);
				if (pShape)
					ObjUtil::SetEnableColliShape(pShape, false);
			}

			if (auto* pMovement = GetComponent<game::GOCMovementComplex>())
			{
				pMovement->GetContextParam()->Velocity = { pCreateInfo->TrasnformMtx.GetColumn(2) * pCreateInfo->Speed };
				pMovement->SetMoveController<game::MoveVelocityReference>();
			}

			if (GetComponent<game::GOCEffect>())
				game::GOCEffect::SimpleSetup(this, 0, false);
			
			game::GOCSound::SimpleSetup(this, 1, 0);

			fnd::GOComponent::EndSetup(*this);

			pCreateInfo = nullptr;
		}

		bool ProcessMessage(fnd::Message& in_rMessage) override
		{
			if (PreProcessMessage(in_rMessage))
				return true;

			switch (in_rMessage.GetType())
			{
			case xgame::MsgDamage::MessageID:					return ProcMsgDamage(static_cast<xgame::MsgDamage&>(in_rMessage));
			case xgame::MsgKick::MessageID:						return ProcMsgKick(static_cast<xgame::MsgKick&>(in_rMessage));
			case xgame::MsgPLGetHomingTargetInfo::MessageID:	return ProcMsgPLGetHomingTargetInfo(static_cast<xgame::MsgPLGetHomingTargetInfo&>(in_rMessage));
			case xgame::MsgPLKickTargetting::MessageID:			return ProcMsgPLKickTargetting(static_cast<xgame::MsgPLKickTargetting&>(in_rMessage));
			case xgame::MsgHitEventCollision::MessageID:		return ProcMsgHitEventCollision(static_cast<xgame::MsgHitEventCollision&>(in_rMessage));
			default:											return GameObject3D::ProcessMessage(in_rMessage);
			}
		}

		bool ProcMsgDamage(xgame::MsgDamage& in_rMessage)
		{
			in_rMessage.SetReply(GetComponent<fnd::GOCTransform>()->Frame.Unk3.GetTranslation(), true);
			if (ObjUtil::CheckShapeUserID(in_rMessage.SenderShape, 0))
				Damaged(in_rMessage);

			return true;
		}

		bool ProcMsgKick(xgame::MsgKick& in_rMessage)
		{
			if (!ObjUtil::CheckShapeUserID(in_rMessage.SenderShape, 0))
				return false;

			in_rMessage.SetReplyForSucceed();
			Damaged(in_rMessage);

			return true;
		}

		bool ProcMsgPLKickTargetting(xgame::MsgPLKickTargetting& in_rMessage)
		{
			if (!ObjUtil::CheckShapeUserID(in_rMessage.pOther, 0))
				return false;

			if (!Flags.test(FLAG_IS_DAMAGED))
				in_rMessage.Success = true;

			return true;
		}

		bool ProcMsgPLGetHomingTargetInfo(xgame::MsgPLGetHomingTargetInfo& in_rMessage)
		{
			if (!ObjUtil::CheckShapeUserID(in_rMessage.pTargetShape, 0) || Flags.test(FLAG_IS_DAMAGED))
			{
				in_rMessage.Flags.set(0);
				return true;
			}

			in_rMessage.CursorPosition = GetComponent<game::GOCMovementComplex>()->GetContextParam()->Position;
			in_rMessage.Flags.set(3);

			return true;
		}

		bool ProcMsgHitEventCollision(xgame::MsgHitEventCollision& in_rMessage)
		{
			GetComponent<game::GOCEffect>()->CreateEffect(ms_pEffectName);
			Flags.set(FLAG_IS_EXPLODING);

			if (Flags.test(FLAG_IS_DAMAGED))
			{
				if (ObjUtil::CheckShapeUserID(in_rMessage.pSelf, 1))
				{
					xgame::MsgDamage msg{ 2, 8, 2, in_rMessage, GetComponent<game::GOCMovementComplex>()->GetContextParam()->Velocity };
					SendMessageImm(in_rMessage.Sender, msg);
				}

				Flags.reset(FLAG_IS_EXPLODING);
			}

			xgame::MsgDamage msg{ 2, 8, 1, in_rMessage, GetComponent<game::GOCMovementComplex>()->GetContextParam()->Velocity };
			SendMessageImm(in_rMessage.Sender, msg);

			return true;
		}

		void Update(const fnd::SUpdateInfo& in_rUpdateInfo) override
		{
			if (Flags.test(FLAG_IS_DAMAGED))
			{
				Roll = SonicUSA::System::RadianMaskU(540.0f * (MATHF_PI / 180.f) * in_rUpdateInfo.DeltaTime + Roll);
			}
			else
			{
				Roll = SonicUSA::System::RadianMaskU(720.0f * (MATHF_PI / 180.f) * in_rUpdateInfo.DeltaTime + Roll);
			}

			GetComponent<fnd::GOCVisualModel>()->SetLocalRotationXYZ(Roll, 0.0f, 0.0f);

			ElapsedTime += in_rUpdateInfo.DeltaTime;
			if (ElapsedTime > LifeSpan || Flags.test(FLAG_IS_EXPLODING))
			{
				GetComponent<game::GOCSound>()->Play3D(ms_pSoundName, 0.0f);
				GetComponent<game::GOCEffect>()->CreateEffect(ms_pEffectName);
				Kill();
			}
		}

		void Damaged(xgame::MsgDamageBase& in_rMessage)
		{
			if (in_rMessage.SenderType != 1)
				return;

			if (!ObjUtil::GetPlayerInformation(*GetDocument(), in_rMessage.PlayerNo))
				return;

			Flags.reset(FLAG_IS_EXPLODING);
			Flags.set(FLAG_IS_DAMAGED);

			auto* pColliderGoc = GetComponent<game::GOCCollider>();
			ObjUtil::SetEnableColliShape(pColliderGoc, 0, false);

			auto* pContextParam = GetComponent<game::GOCMovementComplex>()->GetContextParam();
			
			csl::math::Vector3 offset{ StartingPosition - pContextParam->Position };
			if (!math::Vector3NormalizeIfNotZero(offset, &offset))
				return;

			csl::math::Quaternion rotation{};
			csl::math::Vector3 direction{ math::Vector3Rotate(pContextParam->Rotation, { csl::math::Vector3::UnitZ() }) };
			csl::math::QuaternionRotationBetweenNormals(&rotation, direction, offset);

			pContextParam->Velocity = { offset * 200.0f };
			pContextParam->Rotation = csl::math::QuaternionNormalize(csl::math::QuaternionMultiply(rotation, pContextParam->Rotation));

			ObjUtil::SetEnableColliShape(pColliderGoc, 1, true);
			ElapsedTime = 0.0f;
		}

		void Explosion()
		{
			Flags.set(FLAG_IS_EXPLODING);
		}
	};
}