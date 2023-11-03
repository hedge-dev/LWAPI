#pragma once

namespace app
{
	class ObjYoshiCoin : public CSetObjectListener
	{
	private:
		inline static const char* ms_pEffectName = "ef_dl2_coin_get";
		inline static const char* ms_pSoundName = "obj_yossycoin_get";
		inline static const char* ms_pScoreName = "GET_YOSHICOIN";
		inline static const csl::math::Vector3 ms_PositionOffset = { 0.0f, 5.0f, 0.0f };
		inline static const size_t ms_ShapeCount = 1;
		inline static const float ms_CollisionRadius = 3.0f;
		inline static const float ms_ShadowRadius = 3.0f;

	public:
		Gimmick::CRingManager* pRingManager{ nullptr };
		float ResetTime{ 0.0f };
		csl::ut::Bitset<uint8> IsReset{};

	public:
		ObjYoshiCoin() : CSetObjectListener()
		{
			SetUpdateFlag(0, false);
		}

	protected:
		void AddCallback(GameDocument* in_pDocument) override
		{
			fnd::GOComponent::Create<fnd::GOCVisualModel>(*this);
			fnd::GOComponent::Create<game::GOCCollider>(*this);
			fnd::GOComponent::Create<game::GOCEffect>(*this);
			fnd::GOComponent::Create<game::GOCSound>(*this);

			fnd::GOComponent::BeginSetup(*this);

			auto* parentObject = GetParentObject();
			auto* pParam = GetAdapter()->GetData<SYoshiCoinParam>();

			ResetTime = pParam->ResetTime;
			IsReset.set(0, pParam->IsReset);
			
			auto* pInfo = ObjUtil::GetObjectInfo<ObjYoshiCoinInfo>(*in_pDocument);
			
			pRingManager = in_pDocument->GetService<Gimmick::CRingManager>();
			pRingManager->RegisterRotateRing(this);

			if (auto* pVisualModel = GetComponent<fnd::GOCVisualModel>())
			{
				fnd::GOCVisualModel::Description description{};
				description.Model = pInfo->Model;
				description.Unk2 |= 0x400000u;
				description.LightQualityType = 1;
				description.Unk8 = 0x60000000;
				
				pVisualModel->Setup(description);
				pVisualModel->SetLocalTranslation(ms_PositionOffset);
			}

			if (auto* pCollider = GetComponent<game::GOCCollider>())
			{
				pCollider->Setup({ ms_ShapeCount });
				game::ColliSphereShapeCInfo collisionInfo{};
				collisionInfo.ShapeType = game::CollisionShapeType::ShapeType::eShapeType_Sphere;
				collisionInfo.MotionType = game::PhysicsMotionType::MotionType::eMotionType_Value0;
				collisionInfo.Unk2 = 1;
				collisionInfo.Radius = ms_CollisionRadius;
				collisionInfo.SetLocalPosition({ ms_PositionOffset });
				ObjUtil::SetupCollisionFilter(ObjUtil::eFilter_Unk12, collisionInfo);
				
				if (parentObject) collisionInfo.MotionType = game::PhysicsMotionType::MotionType::eMotionType_Value2;

				pCollider->CreateShape(collisionInfo);
			}

			if (GetComponent<game::GOCEffect>()) game::GOCEffect::SimpleSetup(this, 0, false);
			game::GOCSound::SimpleSetup(this, 0, 0);

			if (auto* pShadowSimple = GetComponent<game::GOCShadowSimple>())
			{
				game::ShadowHemisphereShapeCInfo shadowInfo{ ms_ShadowRadius };
				shadowInfo.Unk2 = 6;
				
				if (parentObject || pParam->SetPlaceType == SYoshiCoinParam::SetPlaceType::PLACETYPE_MOVEABLE)
					shadowInfo.Unk2 = 5;
				
				game::GOCShadowSimple::Description description{ &shadowInfo };
				pShadowSimple->Setup(description);
				pShadowSimple->SetLocalOffsetPosition(ms_PositionOffset);
			}

			uint extUserData = GetExtUserData(eExtUserDataType_High);
			if (extUserData == 1 || pParam->EventType == SYoshiCoinParam::EventType::EVENT_INVISIBLE)
				SetActivate(false);
			
			fnd::GOComponent::EndSetup(*this);
		}

		bool ProcessMessage(fnd::Message& in_rMessage) override
		{
			if (PreProcessMessage(in_rMessage))
				return true;

			switch (in_rMessage.GetType())
			{
			case xgame::MsgNotifyObjectEvent::MessageID:				return ProcMsgNotifyObjectEvent(static_cast<xgame::MsgNotifyObjectEvent&>(in_rMessage));
			case xgame::MsgRingGetSuckedInto::MessageID:				return ProcMsgRingGetSuckedInto(static_cast<xgame::MsgRingGetSuckedInto&>(in_rMessage));
			case xgame::MsgHitEventCollision::MessageID:				return ProcMsgHitEventCollision(static_cast<xgame::MsgHitEventCollision&>(in_rMessage));
			default:													return CSetObjectListener::ProcessMessage(in_rMessage);
			}
		}

		bool ProcMsgHitEventCollision(xgame::MsgHitEventCollision& in_rMessage)
		{
			xgame::MsgTakeObject msg{ xgame::MsgTakeObject::EType::eType_YoshiCoin };
			msg.SetShapeUserID(in_rMessage.pOther->ID);
			if (!SendMessageImm(in_rMessage.Sender, msg) || !msg.Taken)
				return true;
			
			if (auto* pEffect = GetComponent<game::GOCEffect>())
			{
				game::EffectCreateInfo effectInfo{};
				effectInfo.pName = ms_pEffectName;
				effectInfo.Unk1 = 1.0f;
				effectInfo.Position = ms_PositionOffset;
				effectInfo.Unk10 = true;

				pEffect->CreateEffectEx(effectInfo);
			}
			
			if (auto* pSound = GetComponent<game::GOCSound>()) pSound->Play(ms_pSoundName, 0.0f);
			
			ObjUtil::AddScorePlayerAction(*this, ms_pScoreName, ObjUtil::GetPlayerNo(*GetDocument(), in_rMessage.Sender));
			SetStatusToKill();
		}

		bool ProcMsgNotifyObjectEvent(xgame::MsgNotifyObjectEvent& in_rMessage)
		{
			auto* pParam = GetAdapter()->GetData<SYoshiCoinParam>();
			if (pParam->EventType == SYoshiCoinParam::EventType::EVENT_NONE)
				return true;

			if (in_rMessage.GetEventType() == 1)
			{
				SetActivate(true);
				SetExtUserData(eExtUserDataType_High, 2);
			}
			else if (in_rMessage.GetEventType() == 2)
			{
				SetActivate(true);
				SetExtUserData(eExtUserDataType_High, 1);
			}

			return true;
		}

		bool ProcMsgRingGetSuckedInto(xgame::MsgRingGetSuckedInto& in_rMessage)
		{
			if (auto* pVisualModel = GetComponent<fnd::GOCVisualModel>())
			{
				csl::math::Matrix34 visualMatrix{};
				csl::math::Matrix34 transformMatrix{};
				
				pVisualModel->GetMatrix(&visualMatrix);
				
				auto* pTransform = GetComponent<fnd::GOCTransform>();
				transformMatrix = pTransform->Frame.Unk3.Mtx;

				transformMatrix.SetTransVector(visualMatrix.GetTransVector());
				
				sucked_yoshi_coin::CreateInfo createInfo{ transformMatrix, in_rMessage.PlayerNo };
				if (sucked_yoshi_coin::Create(*GetDocument(), createInfo))
					SetStatusToKill();
			}
			
			return true;
		}

		void SetActivate(bool in_activate)
		{
			if (auto* pCollider = GetComponent<game::GOCCollider>()) pCollider->SetEnable(in_activate);
			if (auto* pVisualModel = GetComponent<fnd::GOCVisualModel>()) pVisualModel->SetVisible(in_activate);
			if (auto* pShadowSimple = GetComponent<game::GOCShadowSimple>()) pShadowSimple->SetVisible(in_activate);
		}

		void SetStatusToKill()
		{
			if (IsReset.test(0))
				SetStatusTemporaryRetire(ResetTime);
			else
				SetStatusRetire();

			Kill();
		}
	};
}