#pragma once

namespace app
{
	class ObjYoshiGoal : public CSetObjectListener, public TTinyFsm<ObjYoshiGoal>
	{
	protected:
		inline static const char* ms_pEffectName = "ef_dl2_goal_vanish";
		inline static const char* ms_pResultMusic = "bgm_result_zdlc02";
		inline static const char* ms_pClearJingle = "jingle_stg_clear_zdlc02";
		inline static const char* ms_pRouletteSound = "obj_yossygoal_roulette";
		inline static const char* ms_pRouletteSuccessSound = "obj_yossygoal_roulette_success";
		inline static const char* ms_pRouletteMissSound = "obj_yossygoal_roulette_miss";
		inline static const char* ms_pRouletteDisappearSound = "obj_yossygoal_roulette_disappear";
		inline static const size_t ms_ModelCount = 20;
		inline static const size_t ms_ShapeCount = 1;
		inline static const csl::math::Vector3 ms_CollisionSize = { 20.0f, 20.f, 1.0f };

	public:
		typedef uint8 Type;

		int ModelId{};
		int RouletteCount{};
		float ElapsedTime{};
		float ModelUpdateTime{};
		int PlayerActorID{};
		CSetObjectID Camera{};
		int ModelToDisappearId{};
		float RoueletteElapsedTime{};
		csl::ut::Bitset<uint8> Flags{};
		fnd::SoundHandle SoundHandle{};

		ObjYoshiGoal() : CSetObjectListener(), TTinyFsm<ObjYoshiGoal>(&ObjYoshiGoal::StateWait)
		{

		}

		void AddCallback(GameDocument& in_rDocument) override
		{
			fnd::GOComponent::Create<fnd::GOCVisualContainer>(*this);
			fnd::GOComponent::Create<game::GOCCollider>(*this);
			fnd::GOComponent::Create<game::GOCEffect>(*this);
			fnd::GOComponent::Create<game::GOCSound>(*this);
			
			fnd::GOComponent::BeginSetup(*this);

			if (auto* pVisualContainer = GetComponent<fnd::GOCVisualContainer>())
			{
				pVisualContainer->Setup({ ms_ModelCount });

				auto* pInfo = ObjUtil::GetObjectInfo<ObjYoshiGoalInfo>(in_rDocument);
				csl::math::Vector3 startPosition{ app::math::Vector3Rotate({ Eigen::AngleAxisf(MATHF_PI / 4.5f, csl::math::Vector3::UnitY()) }, { csl::math::Vector3::UnitZ() }) };
			
				for (size_t i = 0; i < ms_ModelCount; i++)
				{
					auto* pVisual = pVisualContainer->CreateSingle<fnd::GOCVisualModel>(*this);
					fnd::GOCVisualModel::Description description{};
					
					Type modelType = GetModelType(i);
					description.m_Model = pInfo->OnModelContainer.Models[modelType];
					
					if (i >= ms_ModelCount / 2)
					{
						modelType = GetModelType(i - ms_ModelCount / 2);
						description.m_Model = pInfo->OffModelContainer.Models[modelType];
					}

					pVisual->Setup(description);

					csl::math::Vector3 position = app::math::Vector3Rotate({ Eigen::AngleAxisf(MATHF_PI * 2 / 10.0f * i, startPosition) }, { csl::math::Vector3::UnitY() * 20.0f });
					pVisual->SetLocalTranslation(position);
					pVisualContainer->Add(pVisual);

					if (i < ms_ModelCount / 2)
						pVisual->SetVisible(false);
				}
			}

			if (auto* pCollider = GetComponent<game::GOCCollider>())
			{
				pCollider->Setup({ ms_ShapeCount });
				game::ColliBoxShapeCInfo collisionInfo{};
				collisionInfo.m_ShapeType = game::CollisionShapeType::ShapeType::ShapeType_Box;
				collisionInfo.m_MotionType = game::PhysicsMotionType::MotionType::MotionType_VALUE2;
				collisionInfo.m_Unk2 |= 1;
				collisionInfo.m_Size = ms_CollisionSize;
				ObjUtil::SetupCollisionFilter(ObjUtil::eFilter_Unk7, collisionInfo);

				pCollider->CreateShape(collisionInfo);
			}

			if (GetComponent<game::GOCEffect>()) game::GOCEffect::SimpleSetup(this, 0, false);
			game::GOCSound::SimpleSetup(this, 0, 0);

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
			default:													return CSetObjectListener::ProcessMessage(in_rMessage);
			}
		}

		void Update(const fnd::SUpdateInfo& in_rUpdateInfo) override
		{
			DebugDrawFlowerPos();
			DispatchFSM(TiFsmBasicEvent<ObjYoshiGoal>::CreateUpdate(in_rUpdateInfo.deltaTime));
		}

		bool ProcMsgHitEventCollision(xgame::MsgHitEventCollision& in_rMessage)
		{
			DispatchFSM(TiFsmBasicEvent<ObjYoshiGoal>::CreateMessage(in_rMessage));
			return true;
		}

		void ChangeState(TiFsmState_t in_state)
		{
			FSM_TRAN(in_state);
		}

		TiFsmState_t StateWait(const TiFsmBasicEvent<ObjYoshiGoal>& in_rEvent)
		{
			switch (in_rEvent.getSignal())
			{
			case TiFSM_SIGNAL_ENTER:
			{
				ElapsedTime = 0.05f;

				return {};
			}
			case TiFSM_SIGNAL_UPDATE:
			{
				UpdateSelectModel(in_rEvent.getFloat());

				return {};
			}
			case TiFSM_SIGNAL_MESSAGE:
			{
				if (in_rEvent.getMessage().GetType() != xgame::MsgHitEventCollision::MessageID)
					return FSM_TOP();

				uint playerNo = ObjUtil::GetPlayerNo(*GetDocument(), static_cast<xgame::MsgHitEventCollision&>(in_rEvent.getMessage()).m_Sender);
				if (playerNo < 0)
				{
					in_rEvent.getMessage().m_Handled = true;
					return{};
				}
				
				auto* pParam = GetAdapter()->GetData<SYoshiGoalParam>();

				PlayerActorID = static_cast<xgame::MsgHitEventCollision&>(in_rEvent.getMessage()).m_Sender;
				xgame::MsgPLHoldOn msgHold{};
				msgHold.Unk1 = 1;
				SendMessageImm(PlayerActorID, msgHold);

				csl::math::Vector3 locatorPos{};
				csl::math::Quaternion locatorRot{};
				if (ObjUtil::GetSetObjectTransform(*GetDocument(), { pParam->Locator }, &locatorPos, &locatorRot))
				{
					xgame::MsgPLJumpToTargetPosition msgJump{};
					msgJump.TargetPosition = locatorPos;
					msgJump.TargetRotation = locatorRot;
					msgJump.Unk1 = 100.0f;
					msgJump.Unk2 = 200.0f;
					msgJump.Unk3 = true;
					SendMessageImm(PlayerActorID, msgJump);
				}

				xgame::MsgCameraOn msgCamera{0.5f, false, 3001, 1, playerNo, false};
				if (ObjUtil::SendMessageImmToSetObject(*this, { pParam->FixCamera }, msgCamera, false))
					Camera.Value = pParam->FixCamera;

				if (auto* pEggManager = GetDocument()->GetService<EggManager>())
					pEggManager->StartExtrication();
			
				xgame::MsgStopGameTimer msgStopTimer{};
				ObjUtil::SendMessageImmToGameActor(*this, msgStopTimer);

				xgame::MsgDisableItemBag msgDisableItemBag{};
				ObjUtil::SendMessageImmToGameActor(*this, msgDisableItemBag);

				for (size_t i = 0; i < 3; i++)
				{
					xgame::MsgStopBgm msgStopBgm{};
					msgStopBgm.Unk2 = i;

					ObjUtil::SendMessageImmToGameActor(*this, msgStopBgm);
				}

				ChangeState(&ObjYoshiGoal::StateWaitStartRoulette);

				return {};
			}
			default:
				return FSM_TOP();
			}

			return {};
		}

		TiFsmState_t StateWaitStartRoulette(const TiFsmBasicEvent<ObjYoshiGoal>& in_rEvent)
		{
			switch (in_rEvent.getSignal())
			{
			case TiFSM_SIGNAL_ENTER:
			{
				RoueletteElapsedTime = 0.0f;

				return {};
			}
			case TiFSM_SIGNAL_UPDATE:
			{
				if (RoueletteElapsedTime < 0.000001f)
					SoundHandle = csl::fnd::Singleton<fnd::SoundPlayer>::GetInstance()->Play(0, ms_pClearJingle, {});

				if (UpdateSelectModel(in_rEvent.getFloat()))
				{
					if (auto* pSound = GetComponent<game::GOCSound>())
						pSound->Play(ms_pRouletteSound, 0.0f);
				}

				RoueletteElapsedTime += in_rEvent.getFloat();
				
				if (RoueletteElapsedTime > 1.5f)
					ChangeState(&ObjYoshiGoal::StateRoulette);

				return {};
			}
			default:
				return FSM_TOP();
			}
		}

		TiFsmState_t StateRoulette(const TiFsmBasicEvent<ObjYoshiGoal>& in_rEvent)
		{
			switch (in_rEvent.getSignal())
			{
			case TiFSM_SIGNAL_ENTER:
			{
				return {};
			}
			case TiFSM_SIGNAL_UPDATE:
			{
				if (!UpdateSelectModel(in_rEvent.getFloat()))
					return {};

				if (auto* pSound = GetComponent<game::GOCSound>())
					pSound->Play(ms_pRouletteSound, 0.0f);

				RouletteCount++;
				ElapsedTime += 0.05f;

				if (RouletteCount >= 12)
					ChangeState(&ObjYoshiGoal::StateCheckHitFlower);
				
				return {};
			}
			default:
				return FSM_TOP();
			}
		}

		TiFsmState_t StateCheckHitFlower(const TiFsmBasicEvent<ObjYoshiGoal>& in_rEvent)
		{
			switch (in_rEvent.getSignal())
			{
			case TiFSM_SIGNAL_ENTER:
			{
				RoueletteElapsedTime = 0.0f;

				return {};
			}
			case TiFSM_SIGNAL_UPDATE:
			{
				RoueletteElapsedTime += in_rEvent.getFloat();

				if (RoueletteElapsedTime <= 1.5f)
					return {};

				Flags.set(0, GetModelType(ModelId) == 0);
				if (Flags.test(0))
				{
					for (size_t i = 0; i < ms_ModelCount / 2; i++)
					{
						xgame::MsgTakeObject msg{ xgame::MsgTakeObject::EType::eType_OneUp };
						SendMessageImm(PlayerActorID, msg);
					}

					Flags.set(1);

					if (auto* pSound = GetComponent<game::GOCSound>())
						pSound->Play(ms_pRouletteSuccessSound, 0.0f);
				}
				else
				{
					if (auto* pSound = GetComponent<game::GOCSound>())
						pSound->Play(ms_pRouletteMissSound, 0.0f);
				}

				ChangeState(&ObjYoshiGoal::StateDisappearModel);
				return {};
			}
			default:
				return FSM_TOP();
			}
		}

		TiFsmState_t StateDisappearModel(const TiFsmBasicEvent<ObjYoshiGoal>& in_rEvent)
		{
			switch (in_rEvent.getSignal())
			{
			case TiFSM_SIGNAL_ENTER:
			{
				RoueletteElapsedTime = 0.0f;
				ModelToDisappearId = ModelId;

				return {};
			}
			case TiFSM_SIGNAL_UPDATE:
			{
				RoueletteElapsedTime -= in_rEvent.getFloat();

				if (RoueletteElapsedTime > 0.0f)
					return {};

				ModelToDisappearId++;
				RoueletteElapsedTime = 0.1f;
				if (ModelToDisappearId >= ms_ModelCount / 2)
					ModelToDisappearId = 0;

				if (auto* pVisualContainer = GetComponent<fnd::GOCVisualContainer>())
				{
					pVisualContainer->m_Visuals[ModelToDisappearId]->SetVisible(false);
					pVisualContainer->m_Visuals[ModelToDisappearId + ms_ModelCount / 2]->SetVisible(false);

					if (auto* pEffect = GetComponent<game::GOCEffect>())
					{
						game::EffectCreateInfo effectInfo{};
						effectInfo.m_pName = ms_pEffectName;
						effectInfo.m_Unk1 = 1.0f;
						effectInfo.m_Unk2 = 3;
						effectInfo.m_pVisual = pVisualContainer->m_Visuals[ModelToDisappearId];

						if (Flags.test(0) && ModelToDisappearId == ModelId)
							effectInfo.m_Unk1 = 2.0f;

						pEffect->CreateEffectEx(effectInfo);
					}
				}

				if (Flags.test(0))
				{
					DoCheckPlayResultBGM();
				}
				else
				{
					if (auto* pSound = GetComponent<game::GOCSound>())
						SoundHandle = pSound->Play(ms_pRouletteDisappearSound, 0.0f);
				}

				if (ModelToDisappearId == ModelId)
				{
					Flags.set(1);
					ChangeState(&ObjYoshiGoal::StateWaitYoshiExtrication);
				}

				return {};
			}
			default:
				return FSM_TOP();
			}
		}

		TiFsmState_t StateWaitYoshiExtrication(const TiFsmBasicEvent<ObjYoshiGoal>& in_rEvent)
		{
			switch (in_rEvent.getSignal())
			{
			case TiFSM_SIGNAL_UPDATE:
			{
				auto* pEggManager = GetDocument()->GetService<EggManager>();
				if (!pEggManager)
					return FSM_TOP();
			
				if (!pEggManager->IsEndExtrication())
					return FSM_TOP();

				xgame::MsgPlayerReachGoal msg{};
				SendMessageImm(PlayerActorID, msg);

				DoCheckPlayResultBGM();

				ChangeState(&ObjYoshiGoal::StateResult);

				return FSM_TOP();
			}
			default:
				return FSM_TOP();
			}
		}

		TiFsmState_t StateResult(const TiFsmBasicEvent<ObjYoshiGoal>& in_rEvent)
		{
			if (in_rEvent.getSignal())
				return FSM_TOP();
			
			DoCheckPlayResultBGM();
			return {};
		}
		
		Type GetModelType(size_t index) const
		{
			if (auto* pEggManager = GetDocument()->GetService<EggManager>())
			{
				if ((index & 1) == 0)
					return pEggManager->IsYoshiSpecialFlowerTaked(index >> 1) == 0;
			}
		
			return index & 1;
		}

		void DoCheckPlayResultBGM()
		{
			if (!Flags.test(1))
				return;
		
			if (SoundHandle.IsValid())
				return;

			SoundHandle = csl::fnd::Singleton<fnd::SoundPlayer>::GetInstance()->Play(0, ms_pResultMusic, {});

			Flags.reset(1);
		}

		bool UpdateSelectModel(float in_delta)
		{
			ModelUpdateTime -= in_delta;
			if (ModelUpdateTime <= 0.0f)
			{
				if (auto* pVisualContainer = GetComponent<fnd::GOCVisualContainer>())
				{
					pVisualContainer->m_Visuals[ModelId]->SetVisible(false);
					pVisualContainer->m_Visuals[ModelId + ms_ModelCount / 2]->SetVisible(true);
				
					ModelId += 1;
					if (ModelId >= 10)
						ModelId = 0;

					pVisualContainer->m_Visuals[ModelId]->SetVisible(true);
				}

				ModelUpdateTime = ElapsedTime;
				return true;
			}

			return false;
		}

		void DebugDrawFlowerPos()
		{

		}
	};
}