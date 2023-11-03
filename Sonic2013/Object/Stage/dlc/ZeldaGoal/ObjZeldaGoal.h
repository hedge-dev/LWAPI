#pragma once

namespace app
{
	class ObjZeldaGoal : public CSetObjectListener, public TTinyFsm<ObjZeldaGoal>
	{
	protected:
		inline static const size_t ms_ShapeCount = 2;
		inline static const size_t ms_PointLightCount = 3;
		inline static const csl::math::Vector3 ms_ModelScale = { 0.9f, 0.9f, 0.9f };
		inline static const char* ms_pAnimationName = "TRIFORCE";
		inline static const char* ms_pResultAnimationName = "TRIFORCE_RESULT";
		inline static const char* ms_pBgmName = "bgm_result_zdlc03";
		inline static const char* ms_pNodeNames[3] = {"power", "courage", "wisdom"};

	public:
		class Listener : public animation::AnimationListener
		{
		public:
			ObjZeldaGoal* pOwner{};
			char IsEventStarted{};
			char DoUpdateLights{};

			void OnEvent(animation::NotifyTiming timing) override
			{
				if (!pOwner)
					return;

				if (IsEventStarted)
				{
					IsEventStarted = false;
					pOwner->CreatePointLights();
				}

				if (DoUpdateLights)
				{
					DoUpdateLights = false;
					pOwner->UpdatePointTransform();
				}

				if (!pOwner)
					return;

				if (!IsEventStarted || (IsEventStarted = 0, pOwner->CreatePointLights(), pOwner != 0))
				{
					if (DoUpdateLights)
					{
						DoUpdateLights = false;
						pOwner->UpdatePointTransform();
					}
				}

			}
		};

		CSetObjectID CameraId{ static_cast<CSetObjectID*>((void*)ASLR(0x00FEF2BC))->get() };
		csl::math::Matrix34 TransformMtx{};
		uint PlayerNo{ static_cast<uint>(-1) };
		float ElapsedTime{};
		bool DoNeedToShowModel{};
		Listener AnimListener{};
		csl::ut::InplaceObjectMoveArray<GameObjectHandle<ObjectPartPointLight>, 3> PointLights{ 3 };
		fnd::SoundHandle SoundHandle{};

		ObjZeldaGoal() : CSetObjectListener(), TTinyFsm<ObjZeldaGoal>(&ObjZeldaGoal::StateIdle)
		{
			AnimListener.Timing = 2;
		}

	public:
		void AddCallback(GameDocument* in_pDocument) override
		{
			fnd::GOComponent::Create<fnd::GOCVisualModel>(*this);
			fnd::GOComponent::Create<game::GOCAnimationScript>(*this);
			fnd::GOComponent::Create<game::GOCCollider>(*this);
			fnd::GOComponent::Create<game::GOCShadowSimple>(*this);

			fnd::GOComponent::BeginSetup(*this);

			auto* pParam = GetAdapter()->GetData<SZeldaGoalParam>();
			auto* pInfo = ObjUtil::GetObjectInfo<ObjZeldaGoalInfo>(*in_pDocument);

			if (auto* pTransformGoc = GetComponent<fnd::GOCTransform>())
				TransformMtx = pTransformGoc->Frame.Unk3.Mtx;

			if (auto* pVisualGoc = GetComponent<fnd::GOCVisualModel>())
			{
				fnd::GOCVisualModel::Description description{};
				description.Model = pInfo->Model;
				description.Skeleton = pInfo->Skeleton;
				description.Unk2 |= 0x400000;

				pVisualGoc->Setup(description);
				pVisualGoc->SetLocalScale(ms_ModelScale);
				pVisualGoc->SetVisible(false);

				if (auto* pAnimationScriptGoc = GetComponent<game::GOCAnimationScript>())
				{
					pAnimationScriptGoc->Setup({ &pInfo->AnimationContainer });
					pVisualGoc->AttachAnimation(pAnimationScriptGoc);

					pAnimationScriptGoc->RegisterCallback(0, animation::CreateAnimCallback<ObjZeldaGoal>(this, &app::ObjZeldaGoal::AnimationCallback, GetAllocator()));

					AnimListener.pOwner = this;
					pAnimationScriptGoc->AddListener(&AnimListener);
				}
			}

			if (auto* pColliderGoc = GetComponent<game::GOCCollider>())
			{
				pColliderGoc->Setup({ ms_ShapeCount });

				game::ColliBoxShapeCInfo collisionInfo{};
				collisionInfo.ShapeType = game::CollisionShapeType::ShapeType::ShapeType_Box;
				collisionInfo.MotionType = game::PhysicsMotionType::MotionType::MotionType_VALUE2;
				collisionInfo.Unk2 |= 1;
				collisionInfo.Size = { pParam->CollisionWidth / 2.0f, pParam->CollisionHeight / 2.0f, pParam->CollisionDepth / 2.0f };
				ObjUtil::SetupCollisionFilter(ObjUtil::EFilter::eFilter_Unk6, collisionInfo);
				collisionInfo.SetLocalPosition({ csl::math::Vector3(0.0f, pParam->CollisionHeight / 2.0f, 0.0f) + csl::math::Vector3(pParam->OffsetWidth, pParam->OffsetHeight, pParam->OffsetDepth) });
				pColliderGoc->CreateShape(collisionInfo);
			}

			if (auto* pShadowGoc = GetComponent<game::GOCShadowSimple>())
			{
				game::ShadowModelShapeCInfo shadowInfo{ GetComponent<fnd::GOCVisualModel>(), pInfo->ShadowModel, 50.0f };
				shadowInfo.ShadowQuality = 4;

				pShadowGoc->Setup({ &shadowInfo });
				pShadowGoc->SetVisible(false);
			}

			fnd::GOComponent::EndSetup(*this);

			InitFSM();
		}

		void RemoveCallback(GameDocument& in_rDocument) override
		{
			if (CameraId.Value != static_cast<CSetObjectID*>((void*)ASLR(0x00FEF2BC))->get())
			{
				xgame::MsgCameraOff msg{ 1.0f, false, true, 1, PlayerNo };
				ObjUtil::SendMessageImmToSetObject(*this, CameraId, msg, false);
			}

			for (auto light : PointLights)
			{
				if (light.Get())
					light->Kill();
			}

			SoundHandle.Stop(1.0f);
		}

		void Update(const fnd::SUpdateInfo& in_rUpdateInfo) override
		{
			DispatchFSM(TiFsmEvent_t::CreateUpdate(in_rUpdateInfo.deltaTime));
		}

		bool ProcessMessage(fnd::Message& in_rMessage) override
		{
			if (PreProcessMessage(in_rMessage))
				return true;

			switch (in_rMessage.GetType())
			{
			case xgame::MsgHitEventCollision::MessageID:				return ProcMsgHitEventCollision(static_cast<xgame::MsgHitEventCollision&>(in_rMessage));
			case xgame::MsgGetExternalMovePosition::MessageID:			return ProcMsgGetExternalMovePosition(static_cast<xgame::MsgGetExternalMovePosition&>(in_rMessage));
			default:													return CSetObjectListener::ProcessMessage(in_rMessage);
			}
		}

		bool ProcMsgHitEventCollision(xgame::MsgHitEventCollision& in_rMessage)
		{
			xgame::MsgCatchPlayer catchMsg{};
			catchMsg.Unk3 = 20;
			if (!SendMessageImm(in_rMessage.Sender, catchMsg) || !catchMsg.Unk4)
				return true;

			GetComponent<game::GOCCollider>()->SetEnable(false);
			PlayerNo = ObjUtil::GetPlayerNo(*GetDocument(), in_rMessage.Sender);

			CSetObjectID cameraId{ GetAdapter()->GetData<SZeldaGoalParam>()->FixCamera };
			xgame::MsgCameraOn cameraMsg{ 0.0f, false, 3001, 1, PlayerNo, false };
			if (ObjUtil::SendMessageImmToSetObject(*this, cameraId, cameraMsg, false))
				CameraId = cameraId;

			xgame::MsgStopGameTimer stopTimerMsg{};
			ObjUtil::SendMessageImmToGameActor(*this, stopTimerMsg);

			GetComponent<game::GOCAnimationScript>()->SetAnimation(ms_pAnimationName);

			AnimListener.IsEventStarted = true;

			for (size_t i = 0; i < 4; i++)
			{
				xgame::MsgStopBgm stopBgmMsg{};
				stopBgmMsg.Unk1 = i == 0 ? 0.2f : 0.0f;
				stopBgmMsg.Unk2 = i;

				ObjUtil::SendMessageImmToGameActor(*this, stopBgmMsg);
			}

			ChangeState(&ObjZeldaGoal::StateWaitEndEvent);

			return true;
		}

		bool ProcMsgGetExternalMovePosition(xgame::MsgGetExternalMovePosition& in_rMessage)
		{
			*in_rMessage.pTrsMatrix = TransformMtx;
			return true;
		}

		void ChangeState(TiFsmState_t in_state)
		{
			FSM_TRAN(in_state);
		}

		TiFsmState_t StateIdle(const TiFsmEvent_t& in_rEvent)
		{
			return FSM_TOP();
		}

		TiFsmState_t StateWaitEndEvent(const TiFsmEvent_t& in_rEvent)
		{
			switch (in_rEvent.getSignal())
			{
			case TiFSM_SIGNAL_ENTER:
			{
				ElapsedTime = 0.0f;
				DoNeedToShowModel = true;
				return {};
			}
			case TiFSM_SIGNAL_UPDATE:
			{
				if (DoNeedToShowModel)
				{
					GetComponent<fnd::GOCVisualModel>()->SetVisible(true);
					GetComponent<game::GOCShadowSimple>()->SetVisible(true);
				
					DoNeedToShowModel = false;
				}
			
				if (ElapsedTime <= 0.000001f)
					SoundHandle = csl::fnd::Singleton<fnd::SoundPlayer>::GetInstance()->Play(0, ms_pBgmName, {});
				
				ElapsedTime += in_rEvent.getFloat();

				AdjustPointLight();
				AnimListener.DoUpdateLights = true;

				if (GetComponent<game::GOCAnimationScript>()->IsFinished())
					ChangeState(&ObjZeldaGoal::StateWhiteOut);

				return {};
			}
			default:
				break;
			}

			return FSM_TOP();
		}

		TiFsmState_t StateWhiteOut(const TiFsmEvent_t& in_rEvent)
		{
			switch (in_rEvent.getSignal())
			{
			case TiFSM_SIGNAL_ENTER:
			{
				CFadeInOutManager::GetInstance()->WhiteOut(1.0f, 1);

				return {};
			}
			case TiFSM_SIGNAL_UPDATE:
			{
				if (CFadeInOutManager::GetInstance()->IsFinished(3))
					ChangeState(&ObjZeldaGoal::StateFadeIn);

				return {};
			}
			default:
				break;
			}

			return FSM_TOP();
		}

		TiFsmState_t StateFadeIn(const TiFsmEvent_t& in_rEvent)
		{
			switch (in_rEvent.getSignal())
			{
			case TiFSM_SIGNAL_ENTER:
			{
				CFadeInOutManager::GetInstance()->FadeIn(1.0f, 1);

				return {};
			}
			case TiFSM_SIGNAL_UPDATE:
			{
				if (!CFadeInOutManager::GetInstance()->IsFinished(3))
					return {};

				app::xgame::MsgPlayerReachGoal msg{};
				ObjUtil::SendMessageImmToPlayer(*this, PlayerNo, msg);

				GetComponent<game::GOCAnimationScript>()->ChangeAnimation(ms_pResultAnimationName);

				ChangeState(&ObjZeldaGoal::StateIdle);

				return {};
			}
			default:
				break;
			}

			return FSM_TOP();
		}

		TiFsmState_t StateEndUp(const TiFsmEvent_t& in_rEvent)
		{
			switch (in_rEvent.getSignal())
			{
			case TiFSM_SIGNAL_ENTER:
			{
				ElapsedTime = 0.0f;

				return {};
			}
			case TiFSM_SIGNAL_UPDATE:
			{
				if (ElapsedTime > 1.5f)
				{
					ChangeState(&ObjZeldaGoal::StateIdle);
					return {};
				}

				auto* pTransformGoc = GetComponent<fnd::GOCTransform>();
				csl::math::Vector3 position{ math::Vector3Rotate(pTransformGoc->Transform.Rotation, { csl::math::Vector3::UnitY() * 3.0f * csl::math::Clamp(ElapsedTime / 1.5f, 0.0f, 1.0f) }) };
				pTransformGoc->SetLocalTranslation({ TransformMtx.GetTransVector() + position });

				ElapsedTime += in_rEvent.getFloat();

				AnimListener.DoUpdateLights = true;

				return {};
			}
			default:
				break;
			}

			return FSM_TOP();
		}

		void AnimationCallback(animation::CharactorAnimation* in_pAnimation, animation::ETriggerValueType in_triggerType, animation::CallbackParam in_param)
		{

		}
		
		void CreatePointLights()
		{
			auto* pTransformGoc = GetComponent<fnd::GOCTransform>();
			auto* pVisualGoc = GetComponent<fnd::GOCVisualModel>();

			for (size_t i = 0; i < ms_PointLightCount; i++)
			{
				if (PointLights[i].IsValid())
					continue;

				math::Transform transform{};
				if (!pVisualGoc->GetNodeTransform(1, ms_pNodeNames[i], &transform))
					continue;

				ObjectPartPointLight::CInfo createInfo{};
				createInfo.Position = transform.Position;
				createInfo.Unk1 = 25.0f;
				createInfo.LifeTime = -1.0f;
				createInfo.pParentTransform = pTransformGoc;
				createInfo.R = 0.7f;
				createInfo.G = 0.6f;
				createInfo.B = 0.4f;
				createInfo.Unk8 = true;

				PointLights[i] = ObjectPartPointLight::Create(*GetDocument(), createInfo);
			}
		}

		void AdjustPointLight()
		{
			if (ElapsedTime < 0.85f || ElapsedTime > 2.65f)
				return;

			float timeScale = csl::math::Clamp((ElapsedTime - 0.85f) / 1.8f, 0.0f, 1.0f);

			float blue = csl::math::Lerp(0.4f, 0.0f, timeScale);
			float green = csl::math::Lerp(0.6f, 0.1f, timeScale);
			float red = csl::math::Lerp(0.7f, 0.2f, timeScale);
			float radius = csl::math::Lerp(25.0f, 40.0f, timeScale);

			csl::ut::ColorF color{};
			color.A = 1.0f;
			color.B = csl::math::Max(0.0f, blue);
			color.G = csl::math::Max(0.0f, green);
			color.R = csl::math::Max(0.0f, red);

			for (auto light : PointLights)
			{
				if (!light.IsValid() || !light.Get())
					continue;

				light->ChangeRadius(radius);
				light->ChangeColor(color);
			}
		}

		void UpdatePointTransform()
		{
			auto* pVisualGoc = GetComponent<fnd::GOCVisualModel>();

			for (size_t i = 0; i < ms_PointLightCount; i++)
			{
				if (!PointLights[i].IsValid() || !PointLights[i].Get())
					continue;

				math::Transform transform{};
				if (!pVisualGoc->GetNodeTransform(1, ms_pNodeNames[i], &transform))
					continue;

				PointLights[i]->GetComponent<fnd::GOCTransform>()->SetLocalTransform(transform);
			}
		}
	};
}