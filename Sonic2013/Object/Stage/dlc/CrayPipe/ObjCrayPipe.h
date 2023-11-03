#pragma once

namespace app
{
	class ObjCrayPipe : public CSetObjectListener, public TTinyFsm<ObjCrayPipe>
	{
	protected:
		inline static const char* ms_pSoundName = "obj_yossypipe_in_out";
		inline static const size_t ms_ShapeCount = 1;

	public:
		int PlayerNo{};
		csl::math::Matrix34 PlayerMatrix{};
		float ElapsedTime{};
		float DeltaTime{ 1 / 60.0f };
		bool IsDirectionDown{ true };
		bool IsPlayerMovedSideWays{ true };
		int Unk3{};

		ObjCrayPipe() : CSetObjectListener(), TTinyFsm<ObjCrayPipe>(&ObjCrayPipe::StateIdle)
		{
			
		}

		void AddCallback(GameDocument* in_pDocument) override
		{
			fnd::GOComponent::Create<game::GOCSound>(*this);
			fnd::GOComponent::Create<game::GOCCollider>(*this);
			
			fnd::GOComponent::BeginSetup(*this);

			auto* pParam = GetAdapter()->GetData<SCrayPipeParam>();
			IsDirectionDown = pParam->Direction == SCrayPipeParam::Direction::DOWN;
			
			game::GOCSound::SimpleSetup(this, 0, 0);

			if (auto* pCollider = GetComponent<game::GOCCollider>())
			{
				pCollider->Setup({ ms_ShapeCount });
				game::ColliSphereShapeCInfo collisionInfo{};
				collisionInfo.ShapeType = game::CollisionShapeType::ShapeType::eShapeType_Sphere;
				collisionInfo.MotionType = game::PhysicsMotionType::MotionType::eMotionType_Value2;
				collisionInfo.Unk2 |= 4;
				collisionInfo.Radius = pParam->CollisionRadius;
				ObjUtil::SetupCollisionFilter(ObjUtil::eFilter_Unk7, collisionInfo);

				pCollider->CreateShape(collisionInfo);
			}

			fnd::GOComponent::EndSetup(*this);
		}

		bool ProcessMessage(fnd::Message& in_rMessage) override
		{
			if (PreProcessMessage(in_rMessage))
				return true;

			switch (in_rMessage.GetType())
			{
			case xgame::MsgGetExternalMovePosition::MessageID:			return ProcMsgGetExternalMovePosition(static_cast<xgame::MsgGetExternalMovePosition&>(in_rMessage));
			case xgame::MsgStayTrigger::MessageID:						return ProcMsgStayTrigger(static_cast<xgame::MsgStayTrigger&>(in_rMessage));
			default:													return CSetObjectListener::ProcessMessage(in_rMessage);
			}
		}

		void Update(const fnd::SUpdateInfo& in_rUpdateInfo) override
		{
			DispatchFSM(TiFsmBasicEvent<ObjCrayPipe>::CreateUpdate(in_rUpdateInfo.deltaTime));
		}

		bool ProcMsgGetExternalMovePosition(xgame::MsgGetExternalMovePosition& in_rMessage)
		{
			DispatchFSM(TiFsmBasicEvent<ObjCrayPipe>::CreateMessage(in_rMessage));
			return true;
		}

		bool ProcMsgStayTrigger(xgame::MsgStayTrigger& in_rMessage)
		{
			DispatchFSM(TiFsmBasicEvent<ObjCrayPipe>::CreateMessage(in_rMessage));
			return true;
		}

		void ChangeState(TiFsmState_t in_state)
		{
			FSM_TRAN(in_state);
		}

		TiFsmState_t StateIdle(const TiFsmBasicEvent<ObjCrayPipe>& in_rEvent)
		{
			switch (in_rEvent.getSignal())
			{
			case TiFSM_SIGNAL_MESSAGE:
			{
				if (in_rEvent.getMessage().GetType() != xgame::MsgStayTrigger::MessageID)
					return FSM_TOP();
			
				PlayerNo = ObjUtil::GetPlayerNo(*GetDocument(), static_cast<xgame::MsgStayTrigger&>(in_rEvent.getMessage()).Sender);
				auto pPlayerInfo = ObjUtil::GetPlayerInformation(*GetDocument(), PlayerNo);
				if (!pPlayerInfo)
				{
					in_rEvent.getMessage().Handled = true;
					return {};
				}
			
				if (!IsDirectionDown || pPlayerInfo->IsOnGround)
				{
					xgame::MsgPLGetInputButton::Input key { IsDirectionDown ? xgame::MsgPLGetInputButton::Input::DOWN : xgame::MsgPLGetInputButton::Input::UP };
					xgame::MsgPLGetInputButton msgInput{ key, xgame::MsgPLGetInputButton::Status::PRESSED };

					if (ObjUtil::SendMessageImmToPlayer(*this, PlayerNo, msgInput) && msgInput.IsPressed)
					{
						PlayerMatrix = math::Matrix34AffineTransformation(pPlayerInfo->Position, pPlayerInfo->Rotation);
						xgame::MsgCatchPlayer msgCatch{};
						msgCatch.Unk2 = PlayerMatrix;
						msgCatch.Unk3 = 18;
						if (ObjUtil::SendMessageImmToPlayer(*this, PlayerNo, msgCatch) && msgCatch.Unk4)
						{
							IsPlayerMovedSideWays = true;
							ChangeState(&ObjCrayPipe::StatePipeIn);
						}
					}
				}

				return {};
			}
			default:
				return FSM_TOP();
			}
		}

		TiFsmState_t StatePipeIn(const TiFsmBasicEvent<ObjCrayPipe>& in_rEvent)
		{
			switch (in_rEvent.getSignal())
			{
			case TiFSM_SIGNAL_UPDATE:
			{
				DeltaTime = in_rEvent.getFloat();
				
				if (!IsPlayerMovedSideWays)
				{
					ElapsedTime += DeltaTime;
					
					if (20.0f <= ElapsedTime * 15.0f)
						ChangeState(&ObjCrayPipe::StateWarp);
				}

				return {};
			}
			case TiFSM_SIGNAL_ENTER:
			{
				ElapsedTime = 0.0f;
				
				xgame::MsgStopGameTimer msg{};
				ObjUtil::SendMessageImmToGameActor(*this, msg);
				
				auto pEggManager = GetDocument()->GetService<EggManager>();
				if (pEggManager)
					pEggManager->SetForceSpaceShrink(true);
			
				return {};
			}
			case TiFSM_SIGNAL_MESSAGE:
			{
				if (in_rEvent.getMessage().GetType() != xgame::MsgGetExternalMovePosition::MessageID)
					return FSM_TOP();

				auto pPlayerInfo = ObjUtil::GetPlayerInformation(*GetDocument(), PlayerNo);
				if (!pPlayerInfo)
				{
					in_rEvent.getMessage().Handled = true;
					return {};
				}

				if (IsPlayerMovedSideWays)
				{
					csl::math::Vector3 objectPosition{};
					csl::math::Matrix34 objectMatrix = GetComponent<fnd::GOCTransform>()->Frame.Unk3.Mtx;
					csl::math::Vector3 objectYAxis = { objectMatrix.GetColumn(1) };
					
					if (IsDirectionDown)
					{
						objectPosition = objectMatrix.GetTransVector();
					}
					else
					{
						objectPosition = { objectMatrix * csl::math::Vector4(0.0f, -9.0f, 0.0f, 1.0f) };
					}
					
					csl::math::Vector3 posOffset{ pPlayerInfo->Position - objectPosition };
					csl::math::Vector3 posOffsetNorm{};
					math::Vector3NormalizeZero(posOffset, &posOffsetNorm);
					
					float similarity = posOffset.dot(objectYAxis);
					float minLength = csl::math::Vector3Length({ posOffset - objectYAxis * similarity });
					float yLength = csl::math::Min(30.0f * DeltaTime, minLength);

					PlayerMatrix.SetTransVector({ objectPosition + posOffsetNorm * (minLength - yLength) });

					if (fabs(minLength - yLength) <= 0.000001f)
					{
						if (auto* pSound = GetComponent<game::GOCSound>()) pSound->Play3D(ms_pSoundName, *csl::math::Vector3::Zero, 0.0f);

						xgame::MsgPLVisibleItemEffect msg{};
						msg.IsVisible = false;
						ObjUtil::SendMessageImmToPlayer(*this, PlayerNo, msg);

						IsPlayerMovedSideWays = false;
					}
				}

				float scalar = IsDirectionDown ? -1.0f : 1.0f;
				
				csl::math::Vector3 yPositionOffset{ 0.0f, csl::math::Min(ElapsedTime * 15.0f, 20.0f) * scalar, 0.0f };
				Eigen::Matrix4f playerMatrixOffset = PlayerMatrix + app::math::Matrix34AffineTransformation(yPositionOffset, csl::math::Quaternion::Identity);

				static_cast<xgame::MsgGetExternalMovePosition&>(in_rEvent.getMessage()).pTrsMatrix->SetTransVector(
					static_cast<csl::math::Matrix34*>(&playerMatrixOffset)->GetTransVector());

				in_rEvent.getMessage().Handled = true;
				return {};
			}
			default:
				return FSM_TOP();
			}
		}
		
		TiFsmState_t StateWarp(const TiFsmBasicEvent<ObjCrayPipe>& in_rEvent)
		{
			switch (in_rEvent.getSignal())
			{
			case TiFSM_SIGNAL_ENTER:
			{
				xgame::MsgWarpNewArea msgWarp{};

				auto* pParam = GetAdapter()->GetData<SCrayPipeParam>();
				if (ObjUtil::GetSetObjectTransform(*GetDocument(), { pParam->TargetLocater }, &msgWarp.TargetPosition, &msgWarp.TargetRotation))
				{
					xgame::MsgNotifyObjectEvent msgEvent{ 1 };
					ObjUtil::SendMessageImmToSetObject(*this, { pParam->TargetLocater }, msgEvent, false);
					
					msgWarp.PlayerNo = PlayerNo;
					msgWarp.ToSideView = true;
					msgWarp.Unk1 = 5;
					msgWarp.Unk3 = 1;

					ObjUtil::SendMessageImmToGameActor(*this, msgWarp);
				}

				return {};
			}
			case TiFSM_SIGNAL_UPDATE:
			case TiFSM_SIGNAL_LEAVE:
				return {};
			}

			return FSM_TOP();
		}
	};
	
	class ObjCrayPipeExit : public CSetObjectListener, public TTinyFsm<ObjCrayPipeExit>
	{
	protected:
		inline static const char* ms_pSoundName = "obj_yossypipe_in_out";
		inline static const size_t ms_ShapeCount = 1;
		inline static const float ms_CollisionRadius = 3.0f;

	public:
		int PlayerNo{};
		float ElapsedTime{};
		bool IsDirectionUp{};
		bool IsPlayerFound{};
		bool IsPlayerMoveFinished{};

		ObjCrayPipeExit() : CSetObjectListener(), TTinyFsm<ObjCrayPipeExit>(&ObjCrayPipeExit::StateIdle)
		{

		}

	protected:
		void AddCallback(GameDocument* in_pDocument) override
		{
			fnd::GOComponent::Create<game::GOCSound>(*this);
			fnd::GOComponent::Create<game::GOCCollider>(*this);
			
			fnd::GOComponent::BeginSetup(*this);

			auto* pParam = GetAdapter()->GetData<SCrayPipeExitParam>();
			IsDirectionUp = pParam->Direction == SCrayPipeExitParam::Direction::UP;
			
			game::GOCSound::SimpleSetup(this, 0, 0);

			if (auto* pCollider = GetComponent<game::GOCCollider>())
			{
				pCollider->Setup({ ms_ShapeCount });
				game::ColliSphereShapeCInfo collisionInfo{};
				collisionInfo.ShapeType = game::CollisionShapeType::ShapeType::eShapeType_Sphere;
				collisionInfo.MotionType = game::PhysicsMotionType::MotionType::eMotionType_Value2;
				collisionInfo.Unk2 |= 1;
				collisionInfo.Radius = ms_CollisionRadius;
				ObjUtil::SetupCollisionFilter(ObjUtil::eFilter_Unk7, collisionInfo);

				pCollider->CreateShape(collisionInfo);
			
				if (!GetExtUserData(eExtUserDataType_High))
					pCollider->SetEnable(false);
			}

			fnd::GOComponent::EndSetup(*this);
		}

		bool ProcessMessage(fnd::Message& in_rMessage) override
		{
			if (PreProcessMessage(in_rMessage))
				return true;

			switch (in_rMessage.GetType())
			{
			case xgame::MsgGetExternalMovePosition::MessageID:			return ProcMsgGetExternalMovePosition(static_cast<xgame::MsgGetExternalMovePosition&>(in_rMessage));
			case xgame::MsgNotifyObjectEvent::MessageID:				return ProcMsgNotifyObjectEvent(static_cast<xgame::MsgNotifyObjectEvent&>(in_rMessage));
			case xgame::MsgHitEventCollision::MessageID:				return ProcMsgHitEventCollision(static_cast<xgame::MsgHitEventCollision&>(in_rMessage));
			default:													return CSetObjectListener::ProcessMessage(in_rMessage);
			}
		}

		void Update(const fnd::SUpdateInfo& in_rUpdateInfo) override
		{
			DispatchFSM(TiFsmBasicEvent<ObjCrayPipeExit>::CreateUpdate(in_rUpdateInfo.deltaTime));
		}

		bool ProcMsgGetExternalMovePosition(xgame::MsgGetExternalMovePosition& in_rMessage)
		{
			DispatchFSM(TiFsmBasicEvent<ObjCrayPipeExit>::CreateMessage(in_rMessage));
			return true;
		}

		bool ProcMsgNotifyObjectEvent(xgame::MsgNotifyObjectEvent& in_rMessage)
		{
			if (in_rMessage.GetEventType() == 1)
				SetExtUserData(eExtUserDataType_High, 1);
			else if (in_rMessage.GetEventType() == 2)
				SetExtUserData(eExtUserDataType_High, 0);

			return true;
		}

		bool ProcMsgHitEventCollision(xgame::MsgHitEventCollision& in_rMessage)
		{
			DispatchFSM(TiFsmBasicEvent<ObjCrayPipeExit>::CreateMessage(in_rMessage));
			return true;
		}

		void ChangeState(TiFsmState_t in_state)
		{
			FSM_TRAN(in_state);
		}

		TiFsmState_t StateIdle(const TiFsmBasicEvent<ObjCrayPipeExit>& in_rEvent)
		{
			switch (in_rEvent.getSignal())
			{
			case TiFSM_SIGNAL_UPDATE:
			{
				if (!IsPlayerFound)
					return {};
			
				if (auto* pTransform = GetComponent<fnd::GOCTransform>())
				{
					csl::math::Matrix34 objectMatrix = pTransform->Frame.Unk3.Mtx;
					float scalar = IsDirectionUp ? -1.0f : 1.0f;
					
					objectMatrix.SetTransVector({ objectMatrix.GetTransVector() + csl::math::Vector3(0.0f, 20.f * scalar, 0.0f) });

					xgame::MsgCatchPlayer msgCatch{};
					msgCatch.Unk2 = objectMatrix;
					msgCatch.Unk3 = 18;
					if (ObjUtil::SendMessageImmToPlayer(*this, PlayerNo, msgCatch) && msgCatch.Unk4)
					{
						IsPlayerFound = false;
						ChangeState(&ObjCrayPipeExit::StatePipeOut);
					}
				}
				
				return {};
			}
			case TiFSM_SIGNAL_MESSAGE:
			{
				if (in_rEvent.getMessage().GetType() != xgame::MsgHitEventCollision::MessageID)
					return FSM_TOP();

				if (GetExtUserData(eExtUserDataType_High) == 1)
				{
					PlayerNo = ObjUtil::GetPlayerNo(*GetDocument(), static_cast<xgame::MsgHitEventCollision&>(in_rEvent.getMessage()).Sender);
					if (PlayerNo >= 0)
						IsPlayerFound = true;
				}
				
				in_rEvent.getMessage().Handled = true;

				return {};
			}
			default:
				return FSM_TOP();
			}
		}

		TiFsmState_t StatePipeOut(const TiFsmBasicEvent<ObjCrayPipeExit>& in_rEvent)
		{
			switch (in_rEvent.getSignal())
			{
			case TiFSM_SIGNAL_ENTER:
			{
				SetExtUserData(eExtUserDataType_High, 0);

				if (auto* pCollider = GetComponent<game::GOCCollider>())
					pCollider->SetEnable(false);
			
				ElapsedTime = 0.0f;
				
				return {};
			}
			case TiFSM_SIGNAL_LEAVE:
			{
				xgame::MsgResumeGameTimer msg{};
				ObjUtil::SendMessageImmToGameActor(*this, msg);

				auto pEggManager = GetDocument()->GetService<EggManager>();
				if (pEggManager)
					pEggManager->SetForceSpaceShrink(false);

				return {};
			}
			case TiFSM_SIGNAL_UPDATE:
			{
				if (ElapsedTime < 0.5f && 0.5f <= ElapsedTime + in_rEvent.getFloat())
				{
					if (auto* pSound = GetComponent<game::GOCSound>())
						pSound->Play3D(ms_pSoundName, 0.0f);
				}

				ElapsedTime += in_rEvent.getFloat();

				if (IsPlayerMoveFinished)
				{
					IsPlayerMoveFinished = false;

					xgame::MsgCatchEndPlayer msgCatchEnd{};
					ObjUtil::SendMessageImmToPlayer(*this, PlayerNo, msgCatchEnd);

					xgame::MsgPLVisibleItemEffect msgItemEffect{};
					msgItemEffect.IsVisible = true;
					ObjUtil::SendMessageImmToPlayer(*this, PlayerNo, msgItemEffect);

					ChangeState(&ObjCrayPipeExit::StateIdle);
				}

				return {};
			}
			case TiFSM_SIGNAL_MESSAGE:
			{
				if (in_rEvent.getMessage().GetType() != xgame::MsgGetExternalMovePosition::MessageID)
					return FSM_TOP();

				if (auto* pTransform = GetComponent<fnd::GOCTransform>())
				{
					csl::math::Matrix34 objectMatrix = pTransform->Frame.Unk3.Mtx;

					float scalar = IsDirectionUp ? -1.0f : 1.0f;
					float offset = IsDirectionUp ? 0.0f : -9.0f;

					csl::math::Vector3 yPositionOffset{ 0.0f, (20.0f - csl::math::Min(csl::math::Max(ElapsedTime - 0.5f, 0.0f) * 15.0f, 20.0f)) * scalar + offset, 0.0f };
					Eigen::Matrix4f playerMatrixOffset = objectMatrix + app::math::Matrix34AffineTransformation(yPositionOffset, csl::math::Quaternion::Identity);

					static_cast<xgame::MsgGetExternalMovePosition&>(in_rEvent.getMessage()).pTrsMatrix->SetTransVector(
						static_cast<csl::math::Matrix34*>(&playerMatrixOffset)->GetTransVector());

					if (fabs((20.0f - csl::math::Min(csl::math::Max(ElapsedTime - 0.5f, 0.0f) * 15.0f, 20.0f)) * scalar) <= 0.000001f)
						IsPlayerMoveFinished = true;
				}

				return {};
			}
			default:
				return FSM_TOP();
			}
		}
	};
}