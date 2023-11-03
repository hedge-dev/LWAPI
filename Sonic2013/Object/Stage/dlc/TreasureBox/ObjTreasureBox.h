#pragma once

namespace app
{
	class ObjTreasureBox : public CSetObjectListener, public TTinyFsm<ObjTreasureBox>
	{
	protected:
		inline static const size_t ms_ModelCount = 2;
		inline static const size_t ms_AnimationCount = 1;
		inline static const size_t ms_ShapeCount = 2;
		inline static const float ms_ItemGetTwinkleEffectScale = 0.7f / 0.9f;
		inline static const csl::math::Vector3 ms_ChestScale = { 0.9f, 0.9f, 0.9f };
		inline static const csl::math::Vector3 ms_ItemScale = { 0.7f, 0.7f, 0.7f };
		inline static const csl::math::Vector3 ms_PositionOffset = { 0.0f, 11.2f, 13.0f };
		inline static const csl::math::Vector3 ms_InteractCollisionSize = { 12.0f, 10.0f, 10.0f };
		inline static const csl::math::Vector3 ms_CollisionSize = { 9.5f, 8.6f, 7.75f };
		inline static const csl::math::Vector3 ms_TwinklePositionOffset = { 0.0f, 11.2f, 13.0f };
		inline static const char* ms_pAnimationName = "Open";
		inline static const char* ms_pHudName = "HudWipeTreasureBox";
		inline static const char* ms_pHudPackfileName = "ui_zdlc03_gamemodestage.pac";
		inline static const char* ms_pHudProjectName = "ui_wipe_zdlc03";
		inline static const char* ms_pHudSceneName = "ui_wipe_zdlc03";
		inline static const char* ms_pHudMaskLayerName = "wipe_mask";
		inline static const char* ms_pCameraNodeName = "Const_Camera";
		inline static const char* ms_pCameraLookAtNodeName = "Const_Target";
		inline static const char* ms_pHudIntroAnimationName = "Intro_Anim";
		inline static const char* ms_pHudIdleAnimationName = "Usual_Anim";
		inline static const char* ms_pHudOutroAnimationName = "Outro_Anim";
		inline static const char* ms_pChestOpeningEffectName = "ef_dl3_treasurebox_open";
		inline static const char* ms_pItemGetTwinkleEffectName = "ef_dl3_treasurebox_twinkle";
		inline static const char* ms_pVanishEffectName = "ef_dl3_treasurebox_vanish";
		inline static const char* ms_pChestOpeningSoundName = "obj_zeldatreasure_open";
		inline static const char* ms_pItemGetSoundName = "obj_zeldaitem_get";

	public:
		enum EItemType : int
		{
			eItemType_HeartContainer,
			eItemType_RupeePurple,
			eItemType_RupeeGold,
			eItemType_MAX
		};

		class Listener : public animation::AnimationListener
		{
		public:
			ObjTreasureBox* pOwner{};

			void OnEvent(animation::NotifyTiming timing) override
			{
				if (!pOwner)
					return;

				pOwner->UpdateCameraParameter();
			}
		};

		Listener AnimListener{};
		ut::RefPtr<Camera::TreasureBoxCamera> rpCamera{}; // boost::intrusive_ptr<Camera::TreasureBoxCamera>
		csl::math::Vector3 CameraPosition{};
		csl::math::Vector3 CameraLookAt{};
		csl::math::Matrix34 TransformMtx{};
		uint PlayerNo{ static_cast<uint>(-1) };
		EItemType ItemType{};
		float ElapsedTime{};
		game::HudLayerController* pLayerController{};

	public:
		ObjTreasureBox() : CSetObjectListener(), TTinyFsm<ObjTreasureBox>(&ObjTreasureBox::StateInitialize)
		{
			AnimListener.Timing = 2;
		}

		void AddCallback(GameDocument* in_pDocument) override
		{
			ItemType = (EItemType)GetAdapter()->GetData<STreasureBoxParam>()->ItemType;
			
			fnd::GOComponent::Create<fnd::GOCVisualContainer>(*this);
			fnd::GOComponent::Create<game::GOCAnimationSimple>(*this);
			fnd::GOComponent::Create<game::GOCCollider>(*this);
			fnd::GOComponent::Create<game::GOCSound>(*this);
			fnd::GOComponent::Create<game::GOCEffect>(*this);
			fnd::GOComponent::Create<game::GOCHud>(*this);

			fnd::GOComponent::BeginSetup(*this);

			auto* pTransform = GetComponent<fnd::GOCTransform>();
			TransformMtx = pTransform->Frame.Unk3.Mtx;
			pTransform->Frame.Unk3.GetRotationQuaternion();

			auto* pTreasureBoxInfo = ObjUtil::GetObjectInfo<ObjTreasureBoxInfo>(*in_pDocument);
			auto* pPopupItemInfo = ObjUtil::GetObjectInfo<ObjZeldaPopupItemInfo>(*in_pDocument);

			if (auto* pVisualContainerGoc = GetComponent<fnd::GOCVisualContainer>())
			{
				pVisualContainerGoc->Setup({ ms_ModelCount });

				if (auto* pVisualGoc = pVisualContainerGoc->CreateSingle<fnd::GOCVisualModel>(*this))
				{
					fnd::GOCVisualModel::Description description{};
					description.Model = pTreasureBoxInfo->Model;
					description.Skeleton = pTreasureBoxInfo->Skeleton;
				
					pVisualGoc->Setup(description);
					pVisualGoc->SetLocalScale(ms_ChestScale);
					
					pVisualContainerGoc->Add(pVisualGoc);

					if (auto* pAnimationGoc = GetComponent<game::GOCAnimationSimple>())
					{
						pAnimationGoc->Setup({ ms_AnimationCount });
						pVisualGoc->AttachAnimation(pAnimationGoc);

						pAnimationGoc->Add(ms_pAnimationName, pTreasureBoxInfo->Animation, game::PlayPolicy::Once);
						
						AnimListener.pOwner = this;
						pAnimationGoc->AddListener(&AnimListener);
					}
				}

				if (auto* pVisualGoc = pVisualContainerGoc->CreateSingle<fnd::GOCVisualModel>(*this))
				{
					fnd::GOCVisualModel::Description description{};
					switch (ItemType)
					{
					case app::ObjTreasureBox::eItemType_HeartContainer:
						description.Model = pTreasureBoxInfo->HeartContainerModel;
						break;
					case app::ObjTreasureBox::eItemType_RupeePurple:
						description.Model = pPopupItemInfo->Models[3];
						break;
					case app::ObjTreasureBox::eItemType_RupeeGold:
						description.Model = pPopupItemInfo->Models[4];
						break;
					default:
						description.Model = pPopupItemInfo->Models[0];
						break;
					}

					pVisualGoc->Setup(description);
					pVisualGoc->SetLocalScale(ms_ItemScale);

					pVisualContainerGoc->Add(pVisualGoc);
					
					pVisualGoc->SetLocalTranslation(ms_PositionOffset);
					pVisualGoc->SetVisible(false);
				}
			}

			if (auto* pColliderGoc = GetComponent<game::GOCCollider>())
			{
				pColliderGoc->Setup({ ms_ShapeCount });

				game::ColliBoxShapeCInfo interactCollisionInfo{};
				interactCollisionInfo.ShapeType = game::CollisionShapeType::ShapeType::eShapeType_Box;
				interactCollisionInfo.MotionType = game::PhysicsMotionType::MotionType::eMotionType_Value2;
				interactCollisionInfo.ShapeID = 0;
				interactCollisionInfo.Unk2 |= 1;
				interactCollisionInfo.Size = { ms_InteractCollisionSize * ms_ChestScale.y() };
				interactCollisionInfo.SetLocalPosition({ 0.0f, 10.0f * ms_ChestScale.y(), 0.0f });
				ObjUtil::SetupCollisionFilter(ObjUtil::EFilter::eFilter_Default, interactCollisionInfo);
				pColliderGoc->CreateShape(interactCollisionInfo);
			
				game::ColliBoxShapeCInfo collisionInfo{};
				collisionInfo.ShapeType = game::CollisionShapeType::ShapeType::eShapeType_Box;
				collisionInfo.MotionType = game::PhysicsMotionType::MotionType::eMotionType_Value2;
				collisionInfo.ShapeID = 1;
				collisionInfo.Unk2 |= 0x100;
				collisionInfo.Size = { ms_CollisionSize * ms_ChestScale.y() };
				collisionInfo.SetLocalPosition({ 0.0f, 8.6f * ms_ChestScale.y(), 0.0f });
				collisionInfo.Flags = 2;
				collisionInfo.Unk3 = 3;
				pColliderGoc->CreateShape(collisionInfo);
			}

			if (GetComponent<game::GOCEffect>())
				game::GOCEffect::SimpleSetup(this, 1, 0);

			game::GOCSound::SimpleSetup(this, 0, 0);

			if (auto* pHudGoc = GetComponent<game::GOCHud>())
			{
				pHudGoc->Setup({ ms_pHudName, 8, 8, (char)128, 1, 2048, 0 });
				auto rawData = csl::fnd::Singleton<fnd::ResourceManager>::GetInstance()->Get<fnd::ResRawData>(ms_pHudPackfileName);
				if (rawData.IsValid())
				{
					hh::ut::PackFile packFile{ rawData->GetAddress() };

					SurfRide::ReferenceCount<SurfRide::Project> rcProject{};
					pHudGoc->SetupProject(&rcProject, ms_pHudProjectName, packFile);
					if (rcProject)
					{
						if (auto rcScene = rcProject->GetScene(ms_pHudSceneName))
						{
							HUD::SRUtility::AllLayerHide(rcScene);
							if (auto rcLayer = rcScene->GetLayer(ms_pHudMaskLayerName))
							{
								pLayerController = pHudGoc->CreateLayerController({ rcLayer }, 0);
							}
						}
					}
				}
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
			case xgame::MsgGetExternalMovePosition::MessageID:			return ProcMsgGetExternalMovePosition(static_cast<xgame::MsgGetExternalMovePosition&>(in_rMessage));
			default:													return CSetObjectListener::ProcessMessage(in_rMessage);
			}
		}

		bool ProcMsgHitEventCollision(xgame::MsgHitEventCollision& in_rMessage)
		{
			DispatchFSM(TiFsmEvent_t::CreateMessage(in_rMessage));
			return true;
		}

		bool ProcMsgGetExternalMovePosition(xgame::MsgGetExternalMovePosition& in_rMessage)
		{
			*in_rMessage.pTrsMatrix = TransformMtx;

			DispatchFSM(TiFsmEvent_t::CreateMessage(in_rMessage));
			return true;
		}

		void Update(const fnd::SUpdateInfo& in_rUpdateInfo) override
		{
			DispatchFSM(TiFsmEvent_t::CreateUpdate(in_rUpdateInfo.deltaTime));
		}

		bool GetNodeTransform(const char* in_pNodeName, math::Transform* out_pTransform)
		{
			return static_cast<fnd::GOCVisualModel*>(GetComponent<fnd::GOCVisualContainer>()->Visuals[0])->GetNodeTransform(0, in_pNodeName, out_pTransform);
		}

		bool IsPlayerPhantom()
		{
			auto* pPlayerInfo = ObjUtil::GetPlayerInformation(*GetDocument(), 0);
			return pPlayerInfo && pPlayerInfo->PixieNo != static_cast<Game::EPhantomType>(-1);
		}

		void PushCamera()
		{
			if (rpCamera)
				return;

			if (rpCamera = new Camera::TreasureBoxCamera())
			{
				rpCamera->SetCameraParameter(CameraPosition, GetComponent<fnd::GOCTransform>()->Frame.Unk3.Mtx.GetColumn(1), CameraLookAt);
				rpCamera->SetFovy(35.0f);
			}

			xgame::MsgPushCameraController msg{ rpCamera, 0.0f, false, 4000, 1, true };
			ObjUtil::SendMessageImmToCamera(*this, msg);
		}

		void PopCamera()
		{
			if (!rpCamera)
				return;
		
			xgame::MsgPopCameraController msg{ rpCamera, 0.0f, false, 1, true };
			ObjUtil::SendMessageImmToCamera(*this, msg);
		}

		void UpdateCameraParameter()
		{
			csl::math::Vector3 cameraPosition{};
			csl::math::Vector3 lookAtPosition{};
			
			math::Transform cameraTransform{};
			if (GetNodeTransform(ms_pCameraNodeName, &cameraTransform))
				cameraPosition = cameraTransform.Position;

			math::Transform lookAtTransform{};
			if (GetNodeTransform(ms_pCameraLookAtNodeName, &lookAtTransform))
				lookAtPosition = lookAtTransform.Position;

			if (rpCamera)
				rpCamera->SetCameraParameter(cameraPosition, GetComponent<fnd::GOCTransform>()->Frame.Unk3.Mtx.GetColumn(1), lookAtPosition);
		}

		void ChangeState(TiFsmState_t in_state)
		{
			FSM_TRAN(in_state);
		}

		TiFsmState_t StateInitialize(const TiFsmEvent_t& in_rEvent)
		{
			switch (in_rEvent.getSignal())
			{
			case TiFSM_SIGNAL_ENTER:
			{
				math::Transform transform{};

				if (GetNodeTransform(ms_pCameraNodeName, &transform))
					CameraPosition = transform.Position;

				if (GetNodeTransform(ms_pCameraLookAtNodeName, &transform))
					CameraLookAt = transform.Position;

				break;
			}
			case TiFSM_SIGNAL_UPDATE:
			{
				ChangeState(&ObjTreasureBox::StateWait);
				break;
			}
			default:
				break;
			}

			return FSM_TOP();
		}

		TiFsmState_t StateWait(const TiFsmEvent_t& in_rEvent)
		{
			switch (in_rEvent.getSignal())
			{
			case TiFSM_SIGNAL_UPDATE:
			{
				if (IsPlayerPhantom())
					ChangeState(&ObjTreasureBox::StateHitOff);

				break;
			}
			case TiFSM_SIGNAL_MESSAGE:
			{
				if (in_rEvent.getMessage().GetType() != xgame::MsgHitEventCollision::MessageID)
					break;
			
				auto& message = static_cast<xgame::MsgHitEventCollision&>(in_rEvent.getMessage());

				xgame::MsgCatchPlayer catchMsg{};
				catchMsg.Unk2 = TransformMtx;
				catchMsg.Unk3 = 19;
				catchMsg.Unk4 = false;

				auto playerNo = ObjUtil::GetPlayerNo(*GetDocument(), message.Sender);
				if (playerNo < 0)
				{
					message.Handled = true;
					break;
				}

				catchMsg.Unk1.set(5);
				if (!ObjUtil::SendMessageImmToPlayer(*this, playerNo, catchMsg) && !catchMsg.Unk4)
				{
					message.Handled = true;
					break;
				}

				PlayerNo = playerNo;
				
				PushCamera();

				xgame::MsgStopGameTimer stopTimerMsg{};
				ObjUtil::SendMessageImmToGameActor(*this, stopTimerMsg);

				xgame::MsgDlcZeldaNoticeStopEnemy stopEnemyMsg{};
				ObjUtil::SendMessageImmToGameActor(*this, stopEnemyMsg);

				GetComponent<game::GOCCollider>()->SetEnable(false);
				GetComponent<game::GOCAnimationSimple>()->SetAnimation(ms_pAnimationName);
				
				if (pLayerController)
				{
					pLayerController->ReserveAnimation(ms_pHudIntroAnimationName, game::HudPlayPolicy::eHudPlayPolicy_Once, false);
					pLayerController->ReserveAnimation(ms_pHudIdleAnimationName, game::HudPlayPolicy::eHudPlayPolicy_Loop, false);
					pLayerController->PlayReservedAnimation();
				}

				GetComponent<game::GOCEffect>()->CreateEffect(ms_pChestOpeningEffectName);
				GetComponent<game::GOCSound>()->Play(ms_pChestOpeningSoundName, 0.0f);

				xgame::MsgChangeBGMVolume changeBgmVolumeMsg{};
				changeBgmVolumeMsg.Unk2 = 0.2f;
				ObjUtil::SendMessageImmToGameActor(*this, changeBgmVolumeMsg);

				ChangeState(&ObjTreasureBox::StateOpen_ControlCamera);
				
				message.Handled = true;
				
				return {};
			}
			default:
				break;
			}

			return FSM_TOP();
		}

		TiFsmState_t StateHitOff(const TiFsmEvent_t& in_rEvent)
		{
			switch (in_rEvent.getSignal())
			{
			case TiFSM_SIGNAL_ENTER:
			{
				ObjUtil::SetEnableColliShape(GetComponent<game::GOCCollider>(), 0, false);
				ElapsedTime = 0.0f;

				break;
			}
			case TiFSM_SIGNAL_UPDATE:
			{
				if (!IsPlayerPhantom())
				{
					ElapsedTime += in_rEvent.getFloat();
					if (ElapsedTime > 0.25f)
					{
						ObjUtil::SetEnableColliShape(GetComponent<game::GOCCollider>(), 0, true);
						ChangeState(&ObjTreasureBox::StateWait);
					}
				}
				else
				{
					ElapsedTime = 0.0f;
				}

				break;
			}
			default:
				break;
			}

			return FSM_TOP();
		}

		TiFsmState_t StateOpen_ControlCamera(const TiFsmEvent_t& in_rEvent)
		{
			switch (in_rEvent.getSignal())
			{
			case TiFSM_SIGNAL_UPDATE:
			{
				auto* pAnimationGoc = GetComponent<game::GOCAnimationSimple>();
				float frame = pAnimationGoc->GetFrame();
				if (frame >= 460.0f)
				{
					GetComponent<fnd::GOCVisualContainer>()->Visuals[1]->SetVisible(true);
					GetComponent<game::GOCSound>()->Play(ms_pItemGetSoundName, 0.0f);

					game::EffectCreateInfo effectInfo{};
					effectInfo.pName = ms_pItemGetTwinkleEffectName;
					effectInfo.Unk1 = ms_ItemGetTwinkleEffectScale;
					effectInfo.Position = ms_TwinklePositionOffset;
					effectInfo.Unk3 = true;

					GetComponent<game::GOCEffect>()->CreateEffectEx(effectInfo);

					ChangeState(&ObjTreasureBox::StateOpen_WaitAnim);
					break;
				}

				if (frame <= 430.0f || !rpCamera)
					break;

				rpCamera->SetFovy(csl::math::Lerp(35.0f, 25.0f, csl::math::Clamp((frame - 430.0f) / 30.0f, 0.0f, 1.0f)));
				break;
			}
			default:
				break;
			}

			return FSM_TOP();
		}

		TiFsmState_t StateOpen_WaitAnim(const TiFsmEvent_t& in_rEvent)
		{
			switch (in_rEvent.getSignal())
			{
			case TiFSM_SIGNAL_ENTER:
			{
				ElapsedTime = 0.0f;
				break;
			}
			case TiFSM_SIGNAL_UPDATE:
			{
				ElapsedTime += in_rEvent.getFloat();

				auto* pItemVisualGoc = static_cast<fnd::GOCVisualTransformed*>(GetComponent<fnd::GOCVisualContainer>()->Visuals[1]);
				pItemVisualGoc->SetLocalRotation({ Eigen::AngleAxisf(2.2689281f * ElapsedTime, csl::math::Vector3::UnitY()) });

				if (!GetComponent<game::GOCAnimationSimple>()->IsFinished())
					break;
				
				auto* pTransform = GetComponent<fnd::GOCTransform>();

				auto rotation = csl::math::QuaternionMultiply(pTransform->Frame.Unk3.GetRotationQuaternion(), csl::math::Quaternion(Eigen::AngleAxisf(MATHF_PI, csl::math::Vector3::UnitY())));
				TransformMtx = math::Matrix34AffineTransformation({ pTransform->Frame.Unk3.Mtx * csl::math::Vector4(0.0f, 0.0f, 10.0f, 1.0f) }, csl::math::QuaternionNormalize(rotation));

				ChangeState(&ObjTreasureBox::StateOpen_End);

				break;
			}
			default:
				break;
			}

			return FSM_TOP();
		}

		TiFsmState_t StateOpen_End(const TiFsmEvent_t& in_rEvent)
		{
			switch (in_rEvent.getSignal())
			{
			case TiFSM_SIGNAL_ENTER:
			{
				ElapsedTime = 0.0f;
				break;
			}
			case TiFSM_SIGNAL_UPDATE:
			{
				if (ElapsedTime <= 0.0f)
					break;

				switch (ItemType)
				{
				case app::ObjTreasureBox::eItemType_HeartContainer:
				{
					xgame::MsgDlcZeldaTakeHeartContainer msg{};
					ObjUtil::SendMessageImmToGameActor(*this, msg);

					if (auto* pPlayerInfo = ObjUtil::GetPlayerInformation(*GetDocument(), PlayerNo))
					{
						ObjZeldaOneUp::CInfo createInfo{};
						createInfo.PlayerNo = PlayerNo;
						createInfo.Position = pPlayerInfo->Position;
						createInfo.Rotation = pPlayerInfo->Rotation;
						ObjZeldaOneUp::Create(*GetDocument(), createInfo);
					}
					
					break;
				}
				case app::ObjTreasureBox::eItemType_RupeePurple:
				case app::ObjTreasureBox::eItemType_RupeeGold:
				{
					xgame::MsgGetAnimal msg{ 50 };
					ObjUtil::SendMessageImmToGameActor(*this, msg);

					break;
				}
				}

				auto* pVisualContainerGoc = GetComponent<fnd::GOCVisualContainer>();
				pVisualContainerGoc->Visuals[1]->SetVisible(false);
				pVisualContainerGoc->Visuals[0]->SetVisible(false);

				GetComponent<game::GOCEffect>()->CreateEffect(ms_pVanishEffectName);

				if (pLayerController)
				{
					pLayerController->ClearReservedAnimation();
					pLayerController->PlayAnimation(ms_pHudOutroAnimationName, game::HudPlayPolicy::eHudPlayPolicy_Once, false);
				}

				xgame::MsgDlcZeldaNoticeActiveEnemy activeEnemyMsg{};
				ObjUtil::SendMessageImmToGameActor(*this, activeEnemyMsg);

				xgame::MsgResumeGameTimer resumeTimerMsg{};
				ObjUtil::SendMessageImmToGameActor(*this, resumeTimerMsg);

				PopCamera();
				
				xgame::MsgCatchEndPlayer catchEndMsg{};
				catchEndMsg.Unk1 = false;
				ObjUtil::SendMessageImmToPlayer(*this, catchEndMsg);

				PlayerNo = static_cast<uint>(-1);

				ChangeState(&ObjTreasureBox::StateOpened);

				break;
			}
			case TiFSM_SIGNAL_MESSAGE:
			{
				if (in_rEvent.getMessage().GetType() != xgame::MsgGetExternalMovePosition::MessageID)
					break;

				auto& message = static_cast<xgame::MsgGetExternalMovePosition&>(in_rEvent.getMessage());
				message.Handled = true;
				ElapsedTime = 1.0f;
				return {};
			}
			default:
				break;
			}

			return FSM_TOP();
		}

		TiFsmState_t StateOpened(const TiFsmEvent_t& in_rEvent)
		{
			switch (in_rEvent.getSignal())
			{
			case TiFSM_SIGNAL_ENTER:
			{
				ElapsedTime = 1.0f;
				break;
			}
			case TiFSM_SIGNAL_UPDATE:
			{
				if (ElapsedTime > 0.0f)
				{
					ElapsedTime -= in_rEvent.getFloat();
					if (ElapsedTime >= 0.0f)
						break;
				
					xgame::MsgChangeBGMVolume msg{};
					msg.Unk1 = 1.0f;
					msg.Unk2 = 2.0f;
					ObjUtil::SendMessageImmToGameActor(*this, msg);
				}
				else
				{
					if (!pLayerController->IsEndAnimation())
						break;
				
					SetStatusRetire();
					Kill();
				}

				break;
			}
			default:
				break;
			}

			return FSM_TOP();
		}
	};
}