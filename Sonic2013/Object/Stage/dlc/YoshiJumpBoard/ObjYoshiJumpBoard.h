#pragma once

namespace app
{
	void SetShotInfo(float in_firstSpeed, float in_keepVelocityDistance, float in_outOfControl, csl::math::Matrix34& in_rObjectMtx, uint in_type, game::GOCLauncher::ShotInfo* out_pShotInfo);

	namespace yoshi_jump_board
	{
		enum class JumpBoardType : uint
		{
			Big,
			Small
		};
	}

	class ObjYoshiJumpBoard : public CSetObjectListener, public TTinyFsm<ObjYoshiJumpBoard>
	{
	public:
		inline static constexpr int FLAG_YOSHI_JUMP_BOARD_IS_PATH_CHANGE = 0;
		inline static constexpr int FLAG_YOSHI_JUMP_BOARD_IS_CHANGE_CAMERA_WHEN_PATH_CHANGE = 1;
		inline static constexpr int FLAG_YOSHI_JUMP_BOARD_IS_UPDATE_YAW = 2;
		inline static constexpr int FLAG_YOSHI_JUMP_BOARD_IS_PUSH_JUMP = 4;

	private:
		inline static const char* ms_pSoundName = "obj_yossyjumpboard";
		inline static const char* ms_pAnimationNames[] = { "JUMP_SMALL", "JUMP_BIG" };
		inline static const char* ms_pShotInfoNames[] = { "NORMAL", "PUSH_JUMP" };
		inline static const size_t ms_ShapeCount = 1;
		inline static const float ms_CollisionRadiuses[] = { 5.0f, 2.5f };
		inline static const float ms_CollisionHeights[] = { 4.75f, 3.7f };
		inline static const float ms_CollisionOffset[] = { 4.75 * 0.5f + 5.0f, 3.7f * 0.5f + 2.5f };
		inline static const float ms_ShadowRadiuses[] = { 6.25f, 3.75f };
		inline static const float ms_Scales[] = { 1.25f, 0.75f };
		inline static const float ms_NormalShotFirstSpeeds[] = { 100.0f, 75.0f };
		inline static const float ms_NormalShotKeepVelocityDistances[] = { 10.0f, 7.5f };
		inline static const float ms_NormalShotOutOfControls[] = { 0.125f, 0.1f };

		inline static const float ms_PositionOffsets[] = { 1.5f, 0.5f };
		inline static const float ms_FrameAdjustors[] = { 11.2f, 8.0f };

	public:
		yoshi_jump_board::JumpBoardType Type{};
		csl::ut::Bitset<uint8> Flags{};
		int PlayerActorID{};
		csl::math::Vector3 Position{};
		csl::math::Quaternion Rotation{};
		float OutOfParkour{};
		
		ObjYoshiJumpBoard(yoshi_jump_board::JumpBoardType in_type) : CSetObjectListener(), TTinyFsm<ObjYoshiJumpBoard>(&ObjYoshiJumpBoard::StateWait)
		{
			Type = in_type;
		}

	protected:
		void AddCallback(GameDocument* in_pDocument) override
		{
			fnd::GOComponent::Create<fnd::GOCVisualModel>(*this);
			fnd::GOComponent::Create<game::GOCAnimationScript>(*this);
			fnd::GOComponent::Create<game::GOCCollider>(*this);
			fnd::GOComponent::Create<game::GOCShadowSimple>(*this);
			fnd::GOComponent::Create<game::GOCLauncher>(*this);
			fnd::GOComponent::Create<game::GOCSound>(*this);

			auto* pParam = GetAdapter()->GetData<SYoshiJumpBoardParam>();
			Flags.set(FLAG_YOSHI_JUMP_BOARD_IS_PATH_CHANGE, pParam->IsPathChange);
			Flags.set(FLAG_YOSHI_JUMP_BOARD_IS_CHANGE_CAMERA_WHEN_PATH_CHANGE, pParam->IsChangeCameraWhenChange);
			Flags.set(FLAG_YOSHI_JUMP_BOARD_IS_UPDATE_YAW, pParam->IsUpdateYaw);
			
			fnd::GOComponent::BeginSetup(*this);
			
			auto* pInfo = ObjUtil::GetObjectInfo<ObjYoshiJumpBoardInfo>(*in_pDocument);

			if (auto* pVisualModel = GetComponent<fnd::GOCVisualModel>())
			{
				fnd::GOCVisualModel::Description description{};
				description.Model = pInfo->Model;
				description.Skeleton = pInfo->Skeleton;
				description.Unk2 |= 0x400000u;

				pVisualModel->Setup(description);
				pVisualModel->SetLocalScale({ ms_Scales[(int)Type], ms_Scales[(int)Type], ms_Scales[(int)Type] });

				if (auto* pAnimationScript = GetComponent<game::GOCAnimationScript>())
				{
					pAnimationScript->Setup({ &pInfo->AnimationContainer });
					pVisualModel->AttachAnimation(pAnimationScript);
				}
			}

			if (auto* pCollider = GetComponent<game::GOCCollider>())
			{
				pCollider->Setup({ ms_ShapeCount });
				game::ColliCapsuleShapeCInfo collisionInfo{};
				collisionInfo.ShapeType = game::CollisionShapeType::ShapeType::eShapeType_Capsule;
				collisionInfo.MotionType = game::PhysicsMotionType::MotionType::eMotionType_Value2;
				collisionInfo.Unk2 |= 1;
				collisionInfo.Radius = ms_CollisionRadiuses[(int)Type];
				collisionInfo.Height = ms_CollisionHeights[(int)Type];
				collisionInfo.SetLocalPosition({ 0.0f, ms_CollisionOffset[(int)Type], 0.0f});
				ObjUtil::SetupCollisionFilter(ObjUtil::eFilter_Default, collisionInfo);

				pCollider->CreateShape(collisionInfo);
			}
			
			if (auto* pShadowSimple = GetComponent<game::GOCShadowSimple>())
			{
				game::ShadowHemisphereShapeCInfo shadowInfo{ ms_ShadowRadiuses[(int)Type] };
				shadowInfo.Unk2 = 6;
				shadowInfo.ShadowQuality = 0;

				game::GOCShadowSimple::Description description{ &shadowInfo };
				pShadowSimple->Setup(description);
			}

			OutOfParkour = pParam->OutOfParkour;

			if (auto* pLauncher = GetComponent<game::GOCLauncher>())
			{
				if (auto* pTransform = GetComponent<fnd::GOCTransform>())
				{
					game::GOCLauncher::ShotInfo shotInfo{};

					csl::math::Matrix34 objectMtx = pTransform->Frame.Unk3.Mtx;

					SetShotInfo(pParam->FirstSpeed, pParam->KeepVelocityDistance, pParam->OutOfControl,
						objectMtx, (uint)Type, &shotInfo);

					pLauncher->Add(shotInfo, 1.0f, ms_pShotInfoNames[1]);

					SetShotInfo(ms_NormalShotFirstSpeeds[(int)Type], ms_NormalShotKeepVelocityDistances[(int)Type], ms_NormalShotOutOfControls[(int)Type],
						objectMtx, (uint)Type, &shotInfo);

					pLauncher->Add(shotInfo, 1.0f, ms_pShotInfoNames[0]);
				}
			}

			game::GOCSound::SimpleSetup(this, 0, 0);

			fnd::GOComponent::EndSetup(*this);

			InitFSM();
		}

		bool ProcessMessage(fnd::Message& in_rMessage) override
		{
			switch (in_rMessage.GetType())
			{
			case xgame::MsgGetExternalMovePosition::MessageID:			return ProcMsgGetExternalMovePosition(static_cast<xgame::MsgGetExternalMovePosition&>(in_rMessage));
			case xgame::MsgHitEventCollision::MessageID:				return ProcMsgHitEventCollision(static_cast<xgame::MsgHitEventCollision&>(in_rMessage));
			default:													return CSetObjectListener::ProcessMessage(in_rMessage);
			}
		}

		void Update(const fnd::SUpdateInfo& in_rUpdateInfo)
		{
			DispatchFSM(TiFsmBasicEvent<ObjYoshiJumpBoard>::CreateUpdate(in_rUpdateInfo.deltaTime));
		}

		bool ProcMsgGetExternalMovePosition(xgame::MsgGetExternalMovePosition& in_rMessage)
		{
			DispatchFSM(TiFsmBasicEvent<ObjYoshiJumpBoard>::CreateMessage(in_rMessage));
			return true;
		}

		bool ProcMsgHitEventCollision(xgame::MsgHitEventCollision& in_rMessage)
		{
			DispatchFSM(TiFsmBasicEvent<ObjYoshiJumpBoard>::CreateMessage(in_rMessage));
			return true;
		}

		csl::math::Vector3 CalcYawDirection() const
		{
			return math::Vector3Rotate(GetComponent<fnd::GOCTransform>()->Frame.Unk3.GetRotationQuaternion(), { csl::math::Vector3::UnitZ() });
		}

		csl::math::Vector3 CatchPlayerLocalPosAdjustAnim()
		{
			if (auto* pAnimationScript = GetComponent<game::GOCAnimationScript>())
			{
				float frame = pAnimationScript->GetFrame();
				
				float scalar = 10.0f * ms_Scales[(int)Type];
				if (frame >= 8.0f)
				{
					float power = csl::math::Clamp((frame - 8.0f) / ms_FrameAdjustors[Flags.test(FLAG_YOSHI_JUMP_BOARD_IS_PUSH_JUMP)], 0.0f, 1.0f);
					float scaledScalar = scalar * ms_PositionOffsets[Flags.test(FLAG_YOSHI_JUMP_BOARD_IS_PUSH_JUMP)] + scalar * 0.65f;
					scalar = scaledScalar * power - scalar * 0.65f;
				}
				else
				{					
					float power = csl::math::Clamp(frame * 0.125f, 0.0f, 1.0f);			
					scalar = -(scalar * 0.65f * power);
				}

				csl::math::Vector3 localPos{ Position + (csl::math::Vector3::UnitY() * scalar) };

				if (localPos.y() < 0.0f)
					localPos.y() = 0.0f;
			
				return localPos;
			}
		}
		void ChangeState(TiFsmState_t in_state)
		{
			FSM_TRAN(in_state);
		}

		TTinyFsmState<ObjYoshiJumpBoard, TiFsmBasicEvent<ObjYoshiJumpBoard>> StateWait(const TiFsmBasicEvent<ObjYoshiJumpBoard>& in_rEvent)
		{
			switch (in_rEvent.getSignal())
			{
			case TiFSM_SIGNAL_ENTER:
			{
				PlayerActorID = 0;
				Flags.reset(3);
				Flags.reset(4);

				return {};
			}
			case TiFSM_SIGNAL_MESSAGE:
			{
				if (in_rEvent.getMessage().GetType() != xgame::MsgHitEventCollision::MessageID)
					return FSM_TOP();

				int playerNo = ObjUtil::GetPlayerNo(*GetDocument(), static_cast<xgame::MsgHitEventCollision&>(in_rEvent.getMessage()).Sender);
				if (playerNo < 0)
				{
					in_rEvent.getMessage().Handled = true;
					return {};
				}

				auto pPlayerInfo = ObjUtil::GetPlayerInformation(*GetDocument(), playerNo);
				if (!pPlayerInfo || pPlayerInfo->PixieNo != -1)
				{
					in_rEvent.getMessage().Handled = true;
					return {};
				}

				if (auto* pTransform = GetComponent<fnd::GOCTransform>())
				{
					csl::math::Matrix34 objectMtx = pTransform->Frame.Unk3.Mtx;
					csl::math::Matrix34 playerMtx = math::Matrix34AffineTransformation(pPlayerInfo->Position, pPlayerInfo->Rotation);

					xgame::MsgCatchPlayer msgCatch{};
					msgCatch.Unk2 = playerMtx;
					msgCatch.Unk3 = 18;

					if (SendMessageImm(static_cast<xgame::MsgHitEventCollision&>(in_rEvent.getMessage()).Sender, msgCatch))
					{
						csl::math::Matrix34Inverse(objectMtx, &objectMtx);
						Position = { objectMtx * csl::math::Vector4(pPlayerInfo->Position, 1.0f)};
						Rotation = pPlayerInfo->Rotation;
						Flags.set(3, !pPlayerInfo->IsOnGround);
						PlayerActorID = static_cast<xgame::MsgHitEventCollision&>(in_rEvent.getMessage()).Sender;

						ChangeState(&ObjYoshiJumpBoard::StateExpansion);
					}
				}

				in_rEvent.getMessage().Handled = true;
				return {};
			}
			default:
				return FSM_TOP();
			}
		}

		TiFsmState_t StateExpansion(const TiFsmBasicEvent<ObjYoshiJumpBoard>& in_rEvent)
		{
			switch (in_rEvent.getSignal())
			{
			case TiFSM_SIGNAL_ENTER:
			{
				if (auto* pAnimationScript = GetComponent<game::GOCAnimationScript>())
					pAnimationScript->SetAnimation(ms_pAnimationNames[0]);

				return {};
			}
			case TiFSM_SIGNAL_UPDATE:
			{
				if (Flags.test(3))
				{
					xgame::MsgPLGetInputButton msgInput{ xgame::MsgPLGetInputButton::Input::Input0, xgame::MsgPLGetInputButton::Status::Status0 };
					if (SendMessageImm(PlayerActorID, msgInput) && msgInput.IsPressed)
						Flags.set(FLAG_YOSHI_JUMP_BOARD_IS_PUSH_JUMP);
				}

				if (auto* pAnimationScript = GetComponent<game::GOCAnimationScript>())
				{
					if (pAnimationScript->GetFrame() < 10.0f)
						return {};

					if (auto* pLauncher = GetComponent<game::GOCLauncher>())
					{
						const char* pInfoName = Flags.test(FLAG_YOSHI_JUMP_BOARD_IS_PUSH_JUMP) ? ms_pShotInfoNames[1] : ms_pShotInfoNames[0];
						game::GOCLauncher::ShotInfo shotInfo = pLauncher->GetShotInfo(pInfoName);

						if (auto* pTransform = GetComponent<fnd::GOCTransform>())
						{
							csl::math::Matrix34 objectMtx = pTransform->Frame.Unk3.Mtx;

							auto pos = CatchPlayerLocalPosAdjustAnim();
							xgame::MsgSpringImpulse msgImpulse{ { objectMtx * csl::math::Vector4(pos, 1.0f) }, shotInfo.Direction, shotInfo.OutOfControl, shotInfo.TravelTime };
							msgImpulse.Flags.set(0, Flags.test(FLAG_YOSHI_JUMP_BOARD_IS_PATH_CHANGE));
							msgImpulse.Flags.set(3, Flags.test(FLAG_YOSHI_JUMP_BOARD_IS_CHANGE_CAMERA_WHEN_PATH_CHANGE));
							msgImpulse.Flags.set(5, true);
							msgImpulse.Flags.set(8, Flags.test(FLAG_YOSHI_JUMP_BOARD_IS_UPDATE_YAW));
							msgImpulse.YawDirection = CalcYawDirection();

							if (Flags.test(FLAG_YOSHI_JUMP_BOARD_IS_PUSH_JUMP))
								msgImpulse.OutOfParkour = OutOfParkour;
							else
								msgImpulse.OutOfParkour = 1.0f;

							if (SendMessageImm(PlayerActorID, msgImpulse) && msgImpulse.IsHandled)
							{
								if (Flags.test(FLAG_YOSHI_JUMP_BOARD_IS_PUSH_JUMP))
									pAnimationScript->ChangeAnimation(ms_pAnimationNames[1]);

								if (auto* pSound = GetComponent<game::GOCSound>())
									pSound->Play(ms_pSoundName, 0.0f);
							}
						}
					}
				}

				ChangeState(&ObjYoshiJumpBoard::StateWait);
				return {};
			}
			case TiFSM_SIGNAL_MESSAGE:
			{
				if (in_rEvent.getMessage().GetType() != xgame::MsgGetExternalMovePosition::MessageID)
					return FSM_TOP();

				if (auto* pTransform = GetComponent<fnd::GOCTransform>())
				{
					csl::math::Matrix34 objectMtx = pTransform->Frame.Unk3.Mtx;

					auto pos = CatchPlayerLocalPosAdjustAnim();
					*static_cast<xgame::MsgGetExternalMovePosition&>(in_rEvent.getMessage()).pTrsMatrix =
						app::math::Matrix34AffineTransformation({ objectMtx * csl::math::Vector4(pos, 1.0f) }, Rotation);

					in_rEvent.getMessage().Handled = true;
				}

				return {};
			}
			default:
				return FSM_TOP();
			}
		}
			
	public:
		static CSetObjectListener* Create_Big()
		{
			return new ObjYoshiJumpBoard(yoshi_jump_board::JumpBoardType::Big);
		}
		
		static CSetObjectListener* Create_Small()
		{
			return new ObjYoshiJumpBoard(yoshi_jump_board::JumpBoardType::Small);
		}
	};

	inline void SetShotInfo(float in_firstSpeed, float in_keepVelocityDistance, float in_outOfControl, csl::math::Matrix34& in_rObjectMtx, uint in_type, game::GOCLauncher::ShotInfo* out_pShotInfo)
	{
		if (!out_pShotInfo)
			return;

		csl::math::Vector3 yAxis = in_rObjectMtx.GetColumn(1);
		csl::math::Vector3 position = in_rObjectMtx.GetTransVector();
		float scalar = 2.0f * (5.0f * !in_type ? 1.25f : 0.75);
		
		csl::math::Vector3 scaledYAxis = { yAxis * scalar };

		out_pShotInfo->Position = { position + scaledYAxis };

		scaledYAxis = { yAxis * in_firstSpeed };

		out_pShotInfo->Direction = scaledYAxis;
		out_pShotInfo->TravelTime = in_keepVelocityDistance / in_firstSpeed;
		out_pShotInfo->OutOfControl = in_outOfControl;
	}
}