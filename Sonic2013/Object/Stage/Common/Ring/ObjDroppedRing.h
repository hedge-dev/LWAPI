#pragma once

namespace app
{
	class CSharedObjInfo;

	class CObjDroppedRing : public GameObject3D
	{
	public:
		inline static constexpr int FLAG_DROPPED_BY_PLAYER = 2;
		inline static constexpr int FLAG_IS_YOSHI_LEVEL = 5;

	private:
		inline static const char* ms_pRingEffectName = "ef_ob_com_yh1_ringget";
		inline static const char* ms_pYoshiCoinEffectName = "ef_dl2_coin_get";
		inline static const char* ms_pRingSoundName = "obj_ring";
		inline static const char* ms_pYoshiCoinSoundName = "obj_yossycoin_get";
		inline static const char* ms_pRingScoreName = "GET_RING";
		inline static const char* ms_pDroppedRingScoreName = "GET_DROPPED_RING";
		inline static const char* ms_pYoshiCoinScoreName = "GET_RING";
		inline static const char* ms_pDroppedYoshiScoreName = "GET_DROPPED_RING";
		inline static const size_t ms_ShapeCount = 1;
		inline static const float ms_CollisionRadius = 3.0f;
		inline static const float ms_ShadowRadius = 3.0f;
		
	public:
		struct SUniqueInfo
		{
			inline static constexpr int FLAG_IS_2D = 0;
			inline static constexpr int FLAG_DROPPED_BY_PLAYER = 2;
			inline static constexpr int FLAG_IS_YOSHI_LEVEL = 5;

			csl::math::Vector3 Position{};
			csl::math::Vector3 Unk1{};
			float Unk2{};
			float Unk3{};
			float LifeSpan{};
			int Counter{};
			game::PathEvaluator PathEvaluator{};
			csl::ut::Bitset<uint32> Flags{};
		};

		const SUniqueInfo* pUniqueInfo{};
		fnd::GOCVisualModel* pVisualModel{};
		game::GOCEffect* pEffect{};
		game::GOCCollider* pCollider{};
		game::GOCGravity* pGravity{};
		game::GOCMovementComplex* pMovementComplex{};
		game::MoveBound* pMoveBound{};
		Gimmick::CRingManager* pRingManager{};
		float ElapsedTime{};
		float LifeSpan{ 1.0f };
		csl::ut::Bitset<uint32> Flags{};
		char Counter{};
		
		CObjDroppedRing(const SUniqueInfo& in_rUniqueInfo) : GameObject3D()
		{
			pUniqueInfo = &in_rUniqueInfo;

			GetComponent<fnd::GOCTransform>()->SetLocalTranslation(in_rUniqueInfo.Position);
			AddProperty(0x4002, 2);
		}

	public:
		void AddCallback(GameDocument* in_pDocument) override
		{
			fnd::GOComponent::Create<fnd::GOCVisualModel>(*this);
			fnd::GOComponent::Create<game::GOCEffect>(*this);
			fnd::GOComponent::Create<game::GOCCollider>(*this);
			fnd::GOComponent::Create<game::GOCGravity>(*this);
			fnd::GOComponent::Create<game::GOCShadowSimple>(*this);
			fnd::GOComponent::Create<game::GOCSound>(*this);
			fnd::GOComponent::Create<game::GOCMovementComplex>(*this);

			fnd::GOComponent::BeginSetup(*this);

			Flags.set(FLAG_IS_YOSHI_LEVEL, pUniqueInfo->Flags.test(SUniqueInfo::FLAG_IS_YOSHI_LEVEL));

			if (pVisualModel = GetComponent<fnd::GOCVisualModel>())
			{
				fnd::GOCVisualModel::Description description{};
				if (Flags.test(FLAG_IS_YOSHI_LEVEL))
				{
					if (auto* pInfo = ObjUtil::GetObjectInfo<ObjYoshiCoinInfo>(*in_pDocument))
						description.Model = pInfo->Model;
				}
				else
				{
					if (auto* pInfo = ObjUtil::GetObjectInfo<CSharedObjInfo>(*in_pDocument))
						description.Model = pInfo->RingModel;
				}

				pVisualModel->Setup(description);
			}

			if (GetComponent<game::GOCEffect>()) game::GOCEffect::SimpleSetup(this, 0, false);

			if (pCollider = GetComponent<game::GOCCollider>())
			{
				pCollider->Setup({ ms_ShapeCount });
				game::ColliSphereShapeCInfo collisionInfo{};
				collisionInfo.ShapeType = game::CollisionShapeType::ShapeType::eShapeType_Sphere;
				collisionInfo.MotionType = game::PhysicsMotionType::MotionType::eMotionType_Value2;
				collisionInfo.Unk2 = 1;
				collisionInfo.ShapeID = 0;
				collisionInfo.Radius = ms_CollisionRadius;
				ObjUtil::SetupCollisionFilter(ObjUtil::eFilter_Unk12, collisionInfo);

				auto pShape = pCollider->CreateShape(collisionInfo);
				ObjUtil::SetEnableColliShape(pShape, false);
			}

			if (pGravity = GetComponent<game::GOCGravity>())
			{
				game::GOCGravity::Description description{};
				if (pUniqueInfo->Flags.test(4))
				{
					description.Unk4 = true;
				}
				else
				{
					description.Type = 1;
					description.Unk2 = 10.0f;
				}

				pGravity->Setup(description);
			}

			if (auto* pShadowSimple = GetComponent<game::GOCShadowSimple>())
			{
				game::ShadowHemisphereShapeCInfo shadowInfo{ ms_ShadowRadius };
				shadowInfo.Unk2 = 5;
				shadowInfo.ShadowQuality = 2;

				game::GOCShadowSimple::Description description{ &shadowInfo };
				pShadowSimple->Setup(description);
			}

			if (pEffect = GetComponent<game::GOCEffect>())
				game::GOCEffect::SimpleSetup(this, 0, 0);

			game::GOCSound::SimpleSetup(this, 0, 0);

			if (pMovementComplex = GetComponent<game::GOCMovementComplex>())
			{
				if (pMoveBound = pMovementComplex->SetMoveController<game::MoveBound>())
				{
					game::MoveBound::Desc description{};
					description.Velocity = pUniqueInfo->Unk1;
					
					if (pUniqueInfo->PathEvaluator.Component.IsValid())
					{
						description.PathEvaluator.SetPathObject(pUniqueInfo->PathEvaluator.GetPathObject());
						description.PathEvaluator.SetDistance(pUniqueInfo->PathEvaluator.Distance);
					}

					if (pUniqueInfo->Flags.test(SUniqueInfo::FLAG_IS_2D))
						description.Unk3 = 240.0f;
					else
						description.Unk3 = 350.0f;
					
					description.Unk4 = pUniqueInfo->Unk2;
					description.Unk5 = pUniqueInfo->Unk3;
					description.Unk6 = 167.332f;
					description.Unk7 = pUniqueInfo->Counter;
					description.Unk8 = 3;

					if (pUniqueInfo->Flags.test(SUniqueInfo::FLAG_DROPPED_BY_PLAYER))
					{
						description.Flags.set(1);
						Flags.set(FLAG_DROPPED_BY_PLAYER);
					}
					
					if (pUniqueInfo->Flags.test(1))
					{
						description.Flags.set(2);
						pMoveBound->RegisterSearchFunction(&app::game::SerachPlaneAndGrindPath);
					}
					
					pMoveBound->Setup(description);
				}
			}
			
			fnd::GOComponent::EndSetup(*this);

			pRingManager = in_pDocument->GetService<Gimmick::CRingManager>();
			LifeSpan = pUniqueInfo->LifeSpan;

			pUniqueInfo = NULL;
		}

		bool ProcessMessage(fnd::Message& in_rMessage) override
		{
			if (PreProcessMessage(in_rMessage))
				return true;

			switch (in_rMessage.GetType())
			{
			case xgame::MsgBeltConveyorControlEnd::MessageID:			return ProcMsgBeltConveyorControlEnd(static_cast<xgame::MsgBeltConveyorControlEnd&>(in_rMessage));
			case xgame::MsgBeltConveyorControlStart::MessageID:			return ProcMsgBeltConveyorControlStart(static_cast<xgame::MsgBeltConveyorControlStart&>(in_rMessage));
			case xgame::MsgHitEventCollision::MessageID:				return ProcMsgHitEventCollision(static_cast<xgame::MsgHitEventCollision&>(in_rMessage));
			case xgame::MsgPressedBySnowBall::MessageID:				return ProcMsgPressedBySnowBall(static_cast<xgame::MsgPressedBySnowBall&>(in_rMessage));
			case xgame::MsgRcGetHomingTargetInfo::MessageID:			return ProcMsgRcGetHomingTargetInfo(static_cast<xgame::MsgRcGetHomingTargetInfo&>(in_rMessage));
			case xgame::MsgTornadoControlAction::MessageID:				return ProcMsgTornadoControlAction(static_cast<xgame::MsgTornadoControlAction&>(in_rMessage));
			case xgame::MsgTornadoControlEnd::MessageID:				return ProcMsgTornadoControlEnd(static_cast<xgame::MsgTornadoControlEnd&>(in_rMessage));
			case xgame::MsgTornadoControlStart::MessageID:				return ProcMsgTornadoControlStart(static_cast<xgame::MsgTornadoControlStart&>(in_rMessage));
			default:													return GameObject3D::ProcessMessage(in_rMessage);
			}
		}

		bool ProcMsgBeltConveyorControlEnd(xgame::MsgBeltConveyorControlEnd& in_rMessage)
		{
			pMovementComplex->EnableMovementFlag(0);
			return true;
		}

		bool ProcMsgBeltConveyorControlStart(xgame::MsgBeltConveyorControlStart& in_rMessage)
		{
			if (Flags.test(8))
			{
				pMovementComplex->DisableMovementFlag(0);
				in_rMessage.Unk1 = true;
			}
			else
			{
				in_rMessage.Unk1 = false;
			}

			in_rMessage.Unk5 = 3.0f;
			in_rMessage.Unk6 = this;
			in_rMessage.Unk3 = { 0.0f, 0.0f, 0.0f };
			return true;
		}

		bool ProcMsgHitEventCollision(xgame::MsgHitEventCollision& in_rMessage)
		{
			if (Flags.test(6))
				return true;

			xgame::MsgTakeObject msg{ xgame::MsgTakeObject::EType::eType_DroppedRing };
			msg.SetShapeUserID(in_rMessage.pOther->ID);
			if (!SendMessageImm(in_rMessage.Sender, msg) || !msg.Taken)
				return true;

			const char* pEffectName = !Flags.test(5) ? ms_pRingEffectName : ms_pYoshiCoinEffectName;
			if (pEffect) pEffect->CreateEffect(pEffectName);

			const char* pSoundName = !Flags.test(5) ? ms_pRingSoundName : ms_pYoshiCoinSoundName;
			if (auto* pSound = GetComponent<game::GOCSound>()) pSound->Play(pSoundName, 0.0f);
			
			const char* pScoreName = !Flags.test(5) ? ms_pDroppedRingScoreName : ms_pDroppedYoshiScoreName;
			if (!Flags.test(2))
				pScoreName = !Flags.test(5) ? ms_pRingScoreName : ms_pYoshiCoinScoreName;

			int playerNo = ObjUtil::GetPlayerNo(*GetDocument(), in_rMessage.Sender);
			ObjUtil::AddScorePlayerAction(*this, pScoreName, playerNo);
			Flags.set(6);
			Kill();

			return true;
		}

		bool ProcMsgPressedBySnowBall(xgame::MsgPressedBySnowBall& in_rMessage)
		{
			if (!in_rMessage.pSnowBall)
				return true;

			if (auto* pVisualModel = GetComponent<fnd::GOCVisualModel>())
			{
				StickerObjectCInfoBase createInfo{};
				createInfo.Unk1 = in_rMessage.Mtx;
				pVisualModel->GetMatrix(&createInfo.Unk2);
				createInfo.pParentObject = in_rMessage.pSnowBall;

				if (obj_sticker::CreateStickerObject(GetAllocator(), *GetDocument(), createInfo))
					Kill();
			}

			return true;
		}

		bool ProcMsgRcGetHomingTargetInfo(xgame::MsgRcGetHomingTargetInfo& in_rMessage)
		{
			in_rMessage.Unk1 = GetComponent<fnd::GOCTransform>()->GetLocalPosition();
			in_rMessage.Unk2.reset();
			return true;
		}

		bool ProcMsgTornadoControlAction(xgame::MsgTornadoControlAction& in_rMessage)
		{
			pCollider->SetEnable(false);
			return true;
		}

		bool ProcMsgTornadoControlEnd(xgame::MsgTornadoControlEnd& in_rMessage)
		{
			Kill();
			return true;
		}

		bool ProcMsgTornadoControlStart(xgame::MsgTornadoControlStart& in_rMessage)
		{
			in_rMessage.Unk1 = this;
			in_rMessage.Unk2 = 0;
			in_rMessage.Unk3 = 0;
			pMovementComplex->DisableMovementFlag(0);
			return true;
		}

		void Update(const fnd::SUpdateInfo& in_rUpdateInfo) override
		{
			ElapsedTime += in_rUpdateInfo.DeltaTime;
			if (ElapsedTime >= LifeSpan * 5.0f)
			{
				Kill();
				return;
			}

			if (Flags.test(8))
			{
				if (++Counter >= 3)
				{
					Counter = 0;
					
					auto* pTransform = GetComponent<fnd::GOCTransform>();
					csl::math::Vector3 yAxis{ pTransform->Transform.GetTransformMatrix().GetColumn(1) };
					csl::math::Vector3 rayStartPos{ pTransform->GetLocalPosition() };
					csl::math::Vector3 rayEndPos{ pTransform->GetLocalPosition() - (yAxis * 3.1f)};

					if (ObjUtil::RaycastHitCollision(*GetDocument(), rayStartPos, rayEndPos, 0xC992))
					{
						pMoveBound->SetFlag(game::MoveController::FlagType::eFlagType_1);
						Flags.reset(8);
					}
				}

				UpdateResources(in_rUpdateInfo);
				return;
			}

			if (!pMoveBound->Flags.test(0))
			{
				UpdateResources(in_rUpdateInfo);
				return;
			}

			auto* pContextParam = pMovementComplex->GetContextParam();
			auto gravityDir = pGravity->GetGravityDirection();
			float power = pContextParam->Velocity.dot(gravityDir);
			
			if (fabs(power) * (1.0f / csl::math::Max(pMoveBound->Plane.Normal.dot(-gravityDir), 0.1f)) > 20.0f)
			{
				UpdateResources(in_rUpdateInfo);
				return;
			}

			pMoveBound->ResetFlag(game::MoveController::FlagType::eFlagType_1);
			Flags.set(8);
			UpdateResources(in_rUpdateInfo);
		}

		void UpdateResources(const fnd::SUpdateInfo& in_rUpdateInfo)
		{
			if (!Flags.test(7))
				JudgeEnableCollision();
		
			BlinkRing(in_rUpdateInfo.Frame);
			UpdateModelRotation();
		}

		void JudgeEnableCollision()
		{
			if (Flags.test(2))
			{
				if (ElapsedTime >= 0.8f && pMoveBound->Flags.test(0))
					Flags.set(7);
			}
			else if (pMoveBound->Flags.test(0) || ElapsedTime >= 0.8f)
			{
				Flags.set(7);
			}

			if (!Flags.test(7) || !pCollider)
				return;
		
			ObjUtil::SetEnableColliShape(pCollider, 0, true);
		}

		void BlinkRing(uint in_frame)
		{
			if (!pVisualModel)
				return;
		
			if (ElapsedTime >= -((2.5f * LifeSpan) - (5.0f * LifeSpan)) &&
				(ElapsedTime >= (5.0f * LifeSpan - 1.0f) || (in_frame & 1) == 0))
			{
				pVisualModel->SetVisible(!pVisualModel->IsVisible());
			}
		}

		void UpdateModelRotation()
		{
			if (!pRingManager)
				return;

			auto gravityDir = pGravity->GetGravityDirection();
			csl::math::Quaternion rotNorm{};
			csl::math::QuaternionRotationBetweenNormals(&rotNorm, { 0.0f, -1.0f, 0.0f }, gravityDir);

			csl::math::Quaternion rotAngle(Eigen::AngleAxisf(pRingManager->Unk2, csl::math::Vector3::UnitY()));

			csl::math::Quaternion rotation(rotNorm * rotAngle);
			rotation.normalize();

			GetComponent<fnd::GOCTransform>()->SetLocalRotation(rotation);
		}
	};
}