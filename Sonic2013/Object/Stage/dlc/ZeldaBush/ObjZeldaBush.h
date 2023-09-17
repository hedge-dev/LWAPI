#pragma once

namespace app
{
	inline bool ConvSpawnerToInfoType(byte in_type)
	{
		return in_type == 1;
	}

	class ObjZeldaBush : public CSetObjectListener
	{
	private:
		inline static const char* ms_pSoundName = "obj_bush";
		inline static const char* ms_pDestructionSoundName = "obj_zeldabush_cut";
		inline static const char* ms_pAnimationName = "Touch";
		inline static const char* ms_pEffectNames[] = { "ef_dl3_bush_break_a", "ef_dl3_bush_break_b" };
		inline static size_t ms_AnimationCount = 1;
		inline static size_t ms_ShapeCount = 1;
		inline static size_t ms_PopupItemChances[] = { 35, 20, 15, 30 };
		inline static ZeldaPopupItemType ms_PopupItemTypes[] = { eZeldaPopupItemType_RupeeGreen, eZeldaPopupItemType_RupeeBlue, eZeldaPopupItemType_RupeeRed, eZeldaPopupItemType_Heart };
		inline static csl::math::Vector3 ms_CollisionSizes[] = { { 7.5f, 7.5f, 7.5f }, { 11.0f, 11.0f, 11.0f } };
		inline static csl::math::Vector3 ms_CollisionOffsets[] = { { 0.0f, 7.5f, 0.0f }, { 0.0f, 11.0f, 0.0f } };

	public:
		int Type{};
		
		ObjZeldaBush() : CSetObjectListener()
		{
			
		}

	protected:
		void AddCallback(GameDocument& in_rDocument) override
		{

			fnd::GOComponent::Create<fnd::GOCVisualModel>(*this);
			fnd::GOComponent::Create<game::GOCAnimationSimple>(*this);
			fnd::GOComponent::Create<game::GOCCollider>(*this);
			fnd::GOComponent::Create<game::GOCShadow>(*this);
			fnd::GOComponent::Create<game::GOCSound>(*this);
			fnd::GOComponent::Create<game::GOCEffect>(*this);

			fnd::GOComponent::BeginSetup(*this);

			auto* pInfo = ObjUtil::GetObjectInfo<ObjZeldaBushInfo>(in_rDocument);
			Type = ConvSpawnerToInfoType(GetAdapter()->GetData<SZeldaBushParam>()->CreateType);

			if (auto* pVisualGoc = GetComponent<fnd::GOCVisualModel>())
			{
				fnd::GOCVisualModel::Description description{};
				description.m_Model = pInfo->ModelContainer.Models[Type];
				description.m_Skeleton = pInfo->SkeletonContainer.Skeletons[Type];
				description.field_0C |= 0x400000u;

				pVisualGoc->Setup(description);

				if (auto* pAnimationGoc = GetComponent<game::GOCAnimationSimple>())
				{
					pAnimationGoc->Setup({ ms_AnimationCount });
					pVisualGoc->AttachAnimation(pAnimationGoc);
					pAnimationGoc->Add(ms_pAnimationName, pInfo->AnimationContainer.Animations[Type], game::PlayPolicy::Once);
				}
			}

			if (auto* pColliderGoc = GetComponent<game::GOCCollider>())
			{
				pColliderGoc->Setup({ ms_ShapeCount });

				game::ColliBoxShapeCInfo collisionInfo{};
				collisionInfo.m_ShapeType = game::CollisionShapeType::ShapeType::ShapeType_Box;
				collisionInfo.m_MotionType = game::PhysicsMotionType::MotionType::MotionType_VALUE2;
				collisionInfo.m_Unk2 |= 1;
				collisionInfo.m_Size = ms_CollisionSizes[Type];
				ObjUtil::SetupCollisionFilter(ObjUtil::EFilter::eFilter_Default, collisionInfo);
				collisionInfo.SetLocalPosition(ms_CollisionOffsets[Type]);
				pColliderGoc->CreateShape(collisionInfo);
			}

			if (auto* pShadowGoc = GetComponent<game::GOCShadowSimple>())
			{
				game::ShadowModelShapeCInfo shadowInfo{ pInfo->ShadowModelContainer.Models[Type] };
				shadowInfo.Unk2 = 6;
				shadowInfo.ShadowQuality = 0;

				pShadowGoc->Setup({ &shadowInfo });
			}

			game::GOCSound::SimpleSetup(this, 0, 0);
			
			if (GetComponent<game::GOCEffect>())
				game::GOCEffect::SimpleSetup(this);

			fnd::GOComponent::EndSetup(*this);

			Sleep();
		}

		void Update(const fnd::SUpdateInfo& in_rUpdateInfo) override
		{
			if (GetComponent<game::GOCAnimationSimple>()->IsFinished())
				Sleep();
		}

		bool ProcessMessage(fnd::Message& in_rMessage) override
		{
			if (PreProcessMessage(in_rMessage))
				return true;

			switch (in_rMessage.GetType())
			{
			case xgame::MsgDamage::MessageID:					return ProcMsgDamage(static_cast<xgame::MsgDamage&>(in_rMessage));
			case xgame::MsgHitEventCollision::MessageID:		return ProcMsgHitEventCollision(static_cast<xgame::MsgHitEventCollision&>(in_rMessage));
			default:											return CSetObjectListener::ProcessMessage(in_rMessage);
			}
		}

		bool ProcMsgDamage(xgame::MsgDamage& in_rMessage)
		{
			if (!AttackType::And(in_rMessage.AttackType, 64))
				return false;

			int itemChance = (int)floorf(SonicUSA::System::Random::GetInstance()->genrand_float32() * 100.0f);
			if (itemChance < 60)
			{
				int typeChance = (int)floorf(SonicUSA::System::Random::GetInstance()->genrand_float32() * 100.0f);

				size_t itemType{};
				size_t chance{};
				for (size_t i = 0; i < ARRAYSIZE(ms_PopupItemChances); i++)
				{
					chance += ms_PopupItemChances[i];
					if (typeChance < chance)
					{
						itemType = i;
						break;
					}
				}

				if (auto* pPlayerInfo = ObjUtil::GetPlayerInformation(*GetDocument(), in_rMessage.PlayerNo))
					zelda_popupitem::CreateZeldaPopupItem(GetAllocator(), *GetDocument(), { math::Matrix34AffineTransformation(pPlayerInfo->Position, pPlayerInfo->Rotation), ms_PopupItemTypes[itemType], in_rMessage.PlayerNo });
			}

			GetComponent<game::GOCEffect>()->CreateEffect(ms_pEffectNames[Type]);
			GetComponent<game::GOCSound>()->Play(ms_pDestructionSoundName, 0.0f);
			SetStatusRetire();
			Kill();

			return true;
		}

		bool ProcMsgHitEventCollision(xgame::MsgHitEventCollision& in_rMessage)
		{
			GetComponent<game::GOCSound>()->Play3D(ms_pSoundName, 0.0f);
			
			auto* pAnimationGoc = GetComponent<game::GOCAnimationSimple>();
			if (pAnimationGoc->IsCurrentAnimation(ms_pAnimationName) && !pAnimationGoc->IsFinished())
				return false;
		
			pAnimationGoc->SetAnimation(ms_pAnimationName);
			Resume();

			return true;
		}
	};
}