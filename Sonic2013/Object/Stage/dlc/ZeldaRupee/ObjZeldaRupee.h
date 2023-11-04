#pragma once

namespace app
{
	class ObjZeldaRupee : public CSetObjectListener, public TTinyFsm<ObjZeldaRupee>
	{
	private:
		inline static const size_t ms_ShapeCount = 1;
		inline static const float ms_CollisionRadius = 4.0f;
		inline static const float ms_ShadowRadius = 2.3f;
		inline static const csl::math::Vector3 ms_VisualOffset = { 0.0f, 3.0f, 0.0f };
		inline static const csl::math::Vector3 ms_CollisionOffset = { 0.0f, 3.0f, 0.0f };

	public:
		int CreateItem{};
		float ElapsedTime{};

	public:
		ObjZeldaRupee() : CSetObjectListener(), TTinyFsm<ObjZeldaRupee>(&ObjZeldaRupee::StateActive)
		{
			
		}

	protected:
		void AddCallback(GameDocument* in_pDocument) override
		{
			auto* pParam = GetAdapter()->GetData<SZeldaRupeeParam>();
			CreateItem = pParam->CreateItem;

			fnd::GOComponent::Create<game::GOCCollider>(*this);
			fnd::GOComponent::Create<fnd::GOCVisualModel>(*this);
			fnd::GOComponent::Create<game::GOCEffect>(*this);
			fnd::GOComponent::Create<game::GOCSound>(*this);

			if (!pParam->IsShadowOff)
				fnd::GOComponent::Create<game::GOCShadowSimple>(*this);

			if (pParam->IsEventOn)
				FSM_SET_INITSTATE(&ObjZeldaRupee::StateInactive);

			fnd::GOComponent::BeginSetup(*this);

			auto* pInfo = ObjUtil::GetObjectInfo<ObjZeldaRupeeInfo>(*in_pDocument);

			if (auto* pVisualModel = GetComponent<fnd::GOCVisualModel>())
			{
				fnd::GOCVisualModel::Description description{};
				description.Model = pInfo->Models[CreateItem];
				description.LightQualityType = 1;
				description.Unk2 |= 0x4000000;

				pVisualModel->Setup(description);
				pVisualModel->SetLocalTranslation(ms_VisualOffset);
			}

			if (auto* pCollider = GetComponent<game::GOCCollider>())
			{
				pCollider->Setup({ ms_ShapeCount });
				game::ColliSphereShapeCInfo collisionInfo{};
				collisionInfo.ShapeType = game::CollisionShapeType::ShapeType::eShapeType_Sphere;
				collisionInfo.MotionType = game::PhysicsMotionType::MotionType::eMotionType_Value0;
				collisionInfo.Unk2 |= 1;
				collisionInfo.Radius = ms_CollisionRadius;
				collisionInfo.SetLocalPosition(ms_CollisionOffset);
				ObjUtil::SetupCollisionFilter(ObjUtil::EFilter::eFilter_Unk6, collisionInfo);

				pCollider->CreateShape(collisionInfo);
			}

			if (GetComponent<game::GOCEffect>())
				game::GOCEffect::SimpleSetup(this, 1, 0);

			game::GOCSound::SimpleSetup(this, 0, 0);

			if (auto* pShadowSimple = GetComponent<game::GOCShadowSimple>())
			{
				game::ShadowSphereShapeCInfo shadowInfo{ ms_ShadowRadius };
				shadowInfo.Unk2 = 6;
				shadowInfo.ShadowQuality = 0;

				game::GOCShadowSimple::Description description{ &shadowInfo };
				pShadowSimple->Setup(description);
				pShadowSimple->SetMaxDownDist(300.0f);
			}

			fnd::GOComponent::EndSetup(*this);

			InitFSM();
		}

		bool ProcessMessage(fnd::Message& in_rMessage) override
		{
			if (PreProcessMessage(in_rMessage))
				return true;

			switch (in_rMessage.GetType())
			{
			case xgame::MsgHitEventCollision::MessageID:				return ProcMsgHitEventCollision(static_cast<xgame::MsgHitEventCollision&>(in_rMessage));
			case xgame::MsgNotifyObjectEvent::MessageID:				return ProcMsgNotifyObjectEvent(static_cast<xgame::MsgNotifyObjectEvent&>(in_rMessage));
			default:													return CSetObjectListener::ProcessMessage(in_rMessage);
			}
		}

		bool ProcMsgHitEventCollision(xgame::MsgHitEventCollision& in_rMessage)
		{
			DispatchFSM(TiFsmEvent_t::CreateMessage(in_rMessage));
			return true;
		}

		bool ProcMsgNotifyObjectEvent(xgame::MsgNotifyObjectEvent& in_rMessage)
		{
			DispatchFSM(TiFsmEvent_t::CreateMessage(in_rMessage));
			return true;
		}

		void Update(const fnd::SUpdateInfo& in_rUpdateInfo) override
		{
			DispatchFSM(TiFsmEvent_t::CreateUpdate(in_rUpdateInfo.DeltaTime));
		}

		void ChangeState(TiFsmState_t in_state)
		{
			FSM_TRAN(in_state);
		}

		TiFsmState_t StateActive(const TiFsmEvent_t& in_rEvent)
		{
			switch (in_rEvent.getSignal())
			{
			case TiFSM_SIGNAL_UPDATE:
			{
				ElapsedTime += in_rEvent.getFloat();
				float angle = MATHF_PI * 130 / 180;
				
				GetComponent<fnd::GOCVisualModel>()->SetLocalRotation({ Eigen::AngleAxisf(fmodf(angle * ElapsedTime, MATHF_PI * 2), csl::math::Vector3::UnitY()) });

				break;
			}
			case TiFSM_SIGNAL_ENTER:
			{
				GetComponent<fnd::GOCVisualModel>()->SetVisible(true);
				GetComponent<game::GOCCollider>()->SetEnable(true);
				if (auto* pShadowSimple = GetComponent<game::GOCShadowSimple>())
					pShadowSimple->SetVisible(true);

				ElapsedTime = 0.0f;
				
				break;
			}
			case TiFSM_SIGNAL_MESSAGE:
			{
				auto& message = in_rEvent.getMessage();

				switch (message.GetType())
				{
				case xgame::MsgNotifyObjectEvent::MessageID:
				{
					if (static_cast<xgame::MsgNotifyObjectEvent&>(message).GetEventType() == 2)
						ChangeState(&ObjZeldaRupee::StateInactive);

					break;
				}
				case xgame::MsgHitEventCollision::MessageID:
				{
					size_t playerNo = ObjUtil::GetPlayerNo(*GetDocument(), static_cast<xgame::MsgHitEventCollision&>(message).Sender);
					if (playerNo >= 0)
					{
						if (auto* pPlayerInfo = ObjUtil::GetPlayerInformation(*GetDocument(), playerNo))
							zelda_popupitem::CreateZeldaPopupItem(GetAllocator(), *GetDocument(), { math::Matrix34AffineTransformation(pPlayerInfo->Position, pPlayerInfo->Rotation), (ZeldaPopupItemType)CreateItem, playerNo });
					}

					Kill();
					SetStatusRetire();

					break;
				}
				default:
					return FSM_TOP();
				}

				message.Handled = true;
				return {};
			}
			}

			return FSM_TOP();
		}

		TiFsmState_t StateInactive(const TiFsmEvent_t& in_rEvent)
		{
			switch (in_rEvent.getSignal())
			{
			case TiFSM_SIGNAL_ENTER:
			{
				GetComponent<fnd::GOCVisualModel>()->SetVisible(false);
				GetComponent<game::GOCCollider>()->SetEnable(false);
				if (auto* pShadowSimple = GetComponent<game::GOCShadowSimple>())
					pShadowSimple->SetVisible(false);

				break;
			}
			case TiFSM_SIGNAL_MESSAGE:
			{
				auto& message = in_rEvent.getMessage();

				if (message.GetType() != xgame::MsgNotifyObjectEvent::MessageID)
					return FSM_TOP();

				if (static_cast<xgame::MsgNotifyObjectEvent&>(message).GetEventType() == 1)
					ChangeState(&ObjZeldaRupee::StateActive);

				message.Handled = true;
				return{};
			}
			}

			return FSM_TOP();
		}
	};
}