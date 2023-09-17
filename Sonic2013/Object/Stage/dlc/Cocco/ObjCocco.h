#pragma once
#pragma push_macro("SendMessage")
#undef SendMessage

namespace app
{
	class ObjCocco : public CSetObjectListener, public TTinyFsm<ObjCocco>
	{
	protected:
		inline static bool IS_GLOBAL_1_ENABLED{};
		inline static float GLOBAL_1_VALUE{};
		inline static bool IS_GLOBAL_2_ENABLED{};
		inline static float GLOBAL_2_VALUE{};

		inline static const size_t ms_ShapeCount = 1;
		inline static const float ms_CollisionRadius = 2.0f;
		inline static const float ms_ShadowRadius = 2.5f;
		inline static const csl::math::Vector3 ms_CollisionOffset = { 0.0f, 3.0f, 0.0f };
		inline static const csl::math::Vector3 ms_ShadowOffset = { 0.0f, 3.0f, 0.0f };
		inline static const csl::math::Vector3 ms_CursorOffset = { 0.0f, 3.0f, 0.0f };
		inline static const char* ms_pIdleAnimationName = "IDLE";
		inline static const char* ms_pMoveAnimationName = "MOVE";
		inline static const char* ms_pAttackAnimationName = "ATTACK";
		inline static const char* ms_pAttack2AnimationName = "ATTACK2";
		inline static const char* ms_pDamageAnimationName = "DAMAGE";
		inline static const char* ms_pFlyAnimationName = "FLY";
		inline static const char* ms_pFlapSoundName = "obj_cock_flap";
		inline static const char* ms_pCrySoundName = "obj_cock_cry";
		inline static const char* ms_pAttackSoundName = "obj_cock_attack";
		inline static const char* ms_pDamageSoundName = "obj_cock_damage";
		inline static const char* ms_pEffectNodeName = "waist";
		inline static const char* ms_pEffectName = "ef_dl3_cocco_dmg";

	public:
		class CInfo
		{
		public:
			csl::math::Vector3 Position{};
			csl::math::Quaternion Rotation{};
			SCoccoParam* pSpawner{};
			int Unk1{};
		};

		enum ActionType : byte
		{
			eActionType_Idle,
			eActionType_Attack
		};
		
		const CInfo CreateInfo{};
		csl::ut::Enum<ActionType, byte> Type{};
		MoveObjCocco* pMovementController{};
		csl::ut::ObjectMoveArray<GameObjectHandle<ObjCocco>> SubCoccos{ GetAllocator() };
		float RotationAngle{};
		float MoveRange{};
		float RunAwayTime{};
		float ElapsedTime{};
		float CryTime{};
		int HealthPoint{ 3 };
		csl::ut::Bitset<byte> Flags{};

		ObjCocco() : CSetObjectListener(), TTinyFsm<ObjCocco>(&ObjCocco::StateIdle)
		{
			ObjUtil::SetPropertyLockonTarget(this);
		}

		ObjCocco(const CInfo& in_rCreateInfo) : CSetObjectListener(), TTinyFsm<ObjCocco>(&ObjCocco::StateAttackIn)
			, CreateInfo(in_rCreateInfo)
			, Type(ActionType::eActionType_Attack)
		{

		}

		void AddCallback(GameDocument& in_rDocument) override
		{
			fnd::GOComponent::Create<fnd::GOCVisualModel>(*this);
			fnd::GOComponent::Create<game::GOCAnimationScript>(*this);
			fnd::GOComponent::Create<game::GOCCollider>(*this);
			fnd::GOComponent::Create<game::GOCEffect>(*this);
			fnd::GOComponent::Create<game::GOCSound>(*this);
			fnd::GOComponent::Create<game::GOCShadowSimple>(*this);
			fnd::GOComponent::Create<game::GOCMovementComplex>(*this);
			
			fnd::GOComponent::BeginSetup(*this);

			GetParentObject();

			MoveRange = GetSpawner()->MoveRange;
			
			auto* pInfo = ObjUtil::GetObjectInfo<ObjCoccoInfo>(in_rDocument);

			if (Type == ActionType::eActionType_Attack)
				GetComponent<fnd::GOCTransform>()->SetLocalTranslationAndRotation(CreateInfo.Position, CreateInfo.Rotation);

			if (auto* pVisualGoc = GetComponent<fnd::GOCVisualModel>())
			{
				fnd::GOCVisualModel::Description description{};
				description.m_Model = pInfo->Model;
				description.m_Skeleton = pInfo->Skeleton;
				description.field_0C |= 0x400000;

				pVisualGoc->Setup(description);

				if (auto* pAnimationGoc = GetComponent<game::GOCAnimationScript>())
				{
					pAnimationGoc->Setup({ &pInfo->AnimationContainer });
					pVisualGoc->AttachAnimation(pAnimationGoc);
					pAnimationGoc->SetAnimation(ms_pIdleAnimationName);

					pAnimationGoc->RegisterCallback(0, animation::CreateAnimCallback<ObjCocco>(this, &app::ObjCocco::SoundCallback, GetAllocator()));
				}
			}

			if (auto* pColliderGoc = GetComponent<game::GOCCollider>())
			{
				pColliderGoc->Setup({ ms_ShapeCount });
				game::ColliSphereShapeCInfo collisionInfo{};
				collisionInfo.m_ShapeType = game::CollisionShapeType::ShapeType::ShapeType_Sphere;
				collisionInfo.m_MotionType = game::PhysicsMotionType::MotionType::MotionType_VALUE2;
				collisionInfo.m_Unk2 = 1;
				collisionInfo.m_Radius = ms_CollisionRadius;
				ObjUtil::SetupCollisionFilter(ObjUtil::eFilter_Default, collisionInfo);
				if (Type == ActionType::eActionType_Idle)
					collisionInfo.m_Unk3 = 0x20000;

				collisionInfo.SetLocalPosition(ms_CollisionOffset);
				pColliderGoc->CreateShape(collisionInfo);
			}

			game::GOCSound::SimpleSetup(this, 0, 0);
			if (GetComponent<game::GOCEffect>())
				game::GOCEffect::SimpleSetup(this, 1, true);

			if (auto* pShadowGoc = GetComponent<game::GOCShadowSimple>())
			{
				game::ShadowSphereShapeCInfo shadowInfo{ ms_ShadowRadius };
				shadowInfo.Unk2 = 1;
				shadowInfo.ShadowQuality = 2;

				game::GOCShadowSimple::Description description{ &shadowInfo };
				pShadowGoc->Setup(description);
				pShadowGoc->SetLocalOffsetPosition(ms_ShadowOffset);
			}

			if (auto* pMovementGoc = GetComponent<game::GOCMovementComplex>())
			{
				if (pMovementController = pMovementGoc->SetMoveController<MoveObjCocco>())
				{
					pMovementController->SetNotifyStopCallback(&ObjCocco::NotifyStopCallback, this);
				}
			}

			if (GetExtUserData(CSetObjectListener::EExtUserDataType::eExtUserDataType_High) == 1)
			{
				GetComponent<fnd::GOCVisualModel>()->SetVisible(false);
				GetComponent<game::GOCShadowSimple>()->SetVisible(false);
				GetComponent<game::GOCCollider>()->SetEnable(false);
				Sleep();
			}
			
			SetEnableAttack(true);

			fnd::GOComponent::EndSetup(*this);
		
			InitFSM();
		}

		void RemoveCallback(GameDocument& in_rDocument) override
		{
			ShutdownFSM();
		}

		bool ProcessMessage(fnd::Message& in_rMessage) override
		{
			if (PreProcessMessage(in_rMessage))
				return true;

			switch (in_rMessage.GetType())
			{
			case xgame::MsgDamage::MessageID:						return ProcMsgDamage(static_cast<xgame::MsgDamage&>(in_rMessage));
			case xgame::MsgKick::MessageID:							return ProcMsgKick(static_cast<xgame::MsgKick&>(in_rMessage));
			case xgame::MsgPLGetHomingTargetInfo::MessageID:		return ProcMsgPLGetHomingTargetInfo(static_cast<xgame::MsgPLGetHomingTargetInfo&>(in_rMessage));
			case xgame::MsgPLKickTargetting::MessageID:				return ProcMsgPLKickTargetting(static_cast<xgame::MsgPLKickTargetting&>(in_rMessage));
			case xgame::MsgDlcZeldaNoticeStopEnemy::MessageID:		return ProcMsgDlcZeldaNoticeStopEnemy(static_cast<xgame::MsgDlcZeldaNoticeStopEnemy&>(in_rMessage));
			case xgame::MsgDlcZeldaNoticeActiveEnemy::MessageID:	return ProcMsgDlcZeldaNoticeActiveEnemy(static_cast<xgame::MsgDlcZeldaNoticeActiveEnemy&>(in_rMessage));
			case xgame::MsgHitEventCollision::MessageID:			return ProcMsgHitEventCollision(static_cast<xgame::MsgHitEventCollision&>(in_rMessage));
			default:												return CSetObjectListener::ProcessMessage(in_rMessage);
			}
		}

		bool ProcMsgDamage(xgame::MsgDamage& in_rMessage)
		{
			DispatchFSM(TiFsmEvent_t::CreateMessage(in_rMessage));
			in_rMessage.SetReply(in_rMessage.m_Unk2, --HealthPoint);
			Flags.set(5);

			return true;
		}

		bool ProcMsgKick(xgame::MsgKick& in_rMessage)
		{
			DispatchFSM(TiFsmEvent_t::CreateMessage(in_rMessage));
			in_rMessage.SetReplyForSucceed();
			return true;
		}

		bool ProcMsgPLGetHomingTargetInfo(xgame::MsgPLGetHomingTargetInfo& in_rMessage)
		{
			if (HealthPoint <= 0)
			{
				in_rMessage.m_Flags.set(0);
				return true;
			}

			in_rMessage.m_LockonCount = HealthPoint;
			in_rMessage.m_CursorPosition = { GetComponent<fnd::GOCTransform>()->m_Frame.m_Unk3.m_Mtx * csl::math::Vector4(ms_CursorOffset, 1.0f) };

			return true;
		}

		bool ProcMsgPLKickTargetting(xgame::MsgPLKickTargetting& in_rMessage)
		{
			in_rMessage.Success = true;
			return true;
		}

		bool ProcMsgDlcZeldaNoticeStopEnemy(xgame::MsgDlcZeldaNoticeStopEnemy& in_rMessage)
		{
			SetExtUserData(CSetObjectListener::EExtUserDataType::eExtUserDataType_High, 1);

			if (FSM_STATE() == &ObjCocco::StateIdle)
			{
				GetComponent<fnd::GOCVisualModel>()->SetVisible(false);
				GetComponent<game::GOCShadow>()->SetVisible(false);
				GetComponent<game::GOCCollider>()->SetEnable(false);
				Sleep();
			}
			else
			{
				xgame::MsgKill msg{};
				for (auto cocco : SubCoccos)
					if (cocco.Get())
						cocco->SendMessage(msg);

				Kill();
			}

			return true;
		}

		bool ProcMsgDlcZeldaNoticeActiveEnemy(xgame::MsgDlcZeldaNoticeActiveEnemy& in_rMessage)
		{
			SetExtUserData(CSetObjectListener::EExtUserDataType::eExtUserDataType_High, 0);
			GetComponent<fnd::GOCVisualModel>()->SetVisible(true);
			GetComponent<game::GOCShadow>()->SetVisible(true);
			GetComponent<game::GOCCollider>()->SetEnable(true);
			Resume();

			return true;
		}

		bool ProcMsgHitEventCollision(xgame::MsgHitEventCollision& in_rMessage)
		{
			DispatchFSM(TiFsmEvent_t::CreateMessage(in_rMessage));
			return true;
		}

		void Update(const fnd::SUpdateInfo& in_rUpdateInfo) override
		{
			DispatchFSM(TiFsmEvent_t::CreateUpdate(in_rUpdateInfo.deltaTime));

			if (!Flags.test(1) || Type != ActionType::eActionType_Idle)
				return;
		
			float time = ElapsedTime;
			ElapsedTime += in_rUpdateInfo.deltaTime;
			if (ElapsedTime > 7.0f)
			{
				SetStatusRetire();
				Kill();
			}

			for (auto& cocco : SubCoccos)
				if (cocco.IsValid())
					SubCoccos.erase(&cocco);

			if ((int)(time / 0.7f) < (int)(ElapsedTime / 0.7f))
				CreateAttackers();
		}

		void SoundCallback(animation::CharactorAnimation* in_pAnimation, animation::ETriggerValueType in_triggerType, animation::CallbackParam in_param)
		{
			if (in_triggerType)
				return;

			if (auto* pSoundGoc = GetComponent<game::GOCSound>())
				pSoundGoc->Play3D(ms_pFlapSoundName, 0.0f);
		}

		void NotifyStopCallback()
		{
			Flags.set(0);
		}

		void ChangeState(TiFsmState_t in_state)
		{
			FSM_TRAN(in_state);
		}

		TiFsmState_t StateIdle(const TiFsmEvent_t& in_rEvent)
		{
			switch (in_rEvent.getSignal())
			{
			case TiFSM_SIGNAL_ENTER:
			{
				SetTargetOnCircle();
				GetComponent<game::GOCAnimationScript>()->ChangeAnimation(ms_pMoveAnimationName);

				return {};
			}
			case TiFSM_SIGNAL_LEAVE:
			{
				return {};
			}
			case TiFSM_SIGNAL_UPDATE:
			{
				auto* pAnimationGoc = GetComponent<game::GOCAnimationScript>();

				if (CryTime > 0.0f)
				{
					CryTime -= in_rEvent.getFloat();
				}
				else
				{
					GetComponent<game::GOCSound>()->Play3D(ms_pCrySoundName, 0.0f);
					CryTime += 2.0f;
				}

				if (!Flags.test(0))
					return {};

				Flags.reset(0);

				if (HealthPoint <= 0)
				{
					pAnimationGoc->ChangeAnimation(ms_pAttackAnimationName);
					ChangeState(&ObjCocco::StateAttackOut);

					return {};
				}

				SetTargetOnCircle();
				pAnimationGoc->ChangeAnimation(ms_pMoveAnimationName);

				return {};
			}
			case TiFSM_SIGNAL_MESSAGE:
			{
				switch (in_rEvent.getMessage().GetType())
				{
				case xgame::MsgDamage::MessageID:
				{
					xgame::MsgDamage& message = static_cast<xgame::MsgDamage&>(in_rEvent.getMessage());

					DamageJump(message.m_Unk3);
					HealthPoint -= message.m_Damage;

					message.m_Handled = true;

					break;
				}
				case xgame::MsgKick::MessageID:
				{
					xgame::MsgKick& message = static_cast<xgame::MsgKick&>(in_rEvent.getMessage());

					DamageJump(message.m_Unk3);
					HealthPoint--;

					message.m_Handled = true;

					break;
				}
				default:
					break;
				}

				return {};
			}
			default:
				break;
			}

			return FSM_TOP();
		}

		TiFsmState_t StateAttackIn(const TiFsmEvent_t& in_rEvent)
		{
			switch (in_rEvent.getSignal())
			{
			case TiFSM_SIGNAL_ENTER:
			{
				SetTargetPlayer();
				Flags.set(1);
				GetComponent<game::GOCAnimationScript>()->ChangeAnimation(ms_pFlyAnimationName);

				return {};
			}
			case TiFSM_SIGNAL_LEAVE:
			{
				return {};
			}
			case TiFSM_SIGNAL_UPDATE:
			{
				auto* pAnimationGoc = GetComponent<game::GOCAnimationScript>();

				if (CryTime > 0.0f)
				{
					CryTime -= in_rEvent.getFloat();
				}
				else
				{
					GetComponent<game::GOCSound>()->Play3D(ms_pAttackSoundName, 0.0f);
					CryTime += 2.0f;
				}

				if (Type == ActionType::eActionType_Idle)
				{
					auto* pPlayerInfo = ObjUtil::GetPlayerInformation(*GetDocument(), 0);
					if (pPlayerInfo)
					{
						if (fabs(pPlayerInfo->Position.z() - GetComponent<fnd::GOCTransform>()->m_Frame.m_Unk3.GetTranslation().z() > 100.0f))
							Kill();
					}
				}

				if (Flags.test(0))
				{
					csl::math::Matrix34 transformMtx{ GetComponent<fnd::GOCTransform>()->m_Frame.m_Unk3.m_Mtx };

					Flags.reset(0);

					csl::math::Vector3 upVector{ transformMtx.GetColumn(1) };
					csl::math::Vector3 from{ transformMtx.GetTransVector() + upVector * 5.0f };
					csl::math::Vector3 to{ from + csl::math::Vector3(-from * 50.0f) };

					game::PhysicsRaycastOutput output{};
					if (ObjUtil::RaycastNearestCollision(&output, *GetDocument(), from, to, 0xC996))
					{
						pAnimationGoc->ChangeAnimation(ms_pAttack2AnimationName);
						ChangeState(&ObjCocco::StateAttackOut);

						return {};
					}

					pMovementController->SetTargetDirection(transformMtx.GetColumn(2), 70.0f);
				}

				return {};
			}
			case TiFSM_SIGNAL_MESSAGE:
			{
				switch (in_rEvent.getMessage().GetType())
				{
				case xgame::MsgHitEventCollision::MessageID:
				{
					xgame::MsgHitEventCollision& message = static_cast<xgame::MsgHitEventCollision&>(in_rEvent.getMessage());
					
					xgame::MsgDamage damageMsg{ 3, 8, 3, message, *csl::math::Vector3::Zero };
					SendMessageImm(message.m_Sender, damageMsg);

					message.m_Handled = true;

					break;
				}
				default:
					break;
				}

				return {};
			}
			default:
				break;
			}

			return FSM_TOP();
		}

		TiFsmState_t StateAttackOut(const TiFsmEvent_t& in_rEvent)
		{
			switch (in_rEvent.getSignal())
			{
			case TiFSM_SIGNAL_ENTER:
			{
				if (auto* pPlayerInfo = ObjUtil::GetPlayerInformation(*GetDocument(), 0))
				{
					if (pow(150.0f, 2.0f) >= pPlayerInfo->Velocity.squaredNorm())
						pMovementController->SetTargetPlayer(70.0f, 20.0f);
					else
						pMovementController->SetTargetPlayer(220.0f, 20.0f);
				}

				if (Flags.test(2))
				{
					Flags.set(1);

					if (Type == ActionType::eActionType_Idle)
					{
						auto* pParam = GetSpawner();
						for (auto coccoId : pParam->CoccoList)
						{
							if (auto* pCocco = static_cast<ObjCocco*>(ObjUtil::GetGameObjectHandle(*GetDocument(), { coccoId }).Get()))
								pCocco->SetEnableAttack(false);
						}
					}
				}

				RunAwayTime = 0.0f;

				return {};
			}
			case TiFSM_SIGNAL_LEAVE:
			{
				if (Flags.test(1) && Type == ActionType::eActionType_Idle)
				{
					auto* pParam = GetSpawner();
					for (auto coccoId : pParam->CoccoList)
					{
						if (auto* pCocco = static_cast<ObjCocco*>(ObjUtil::GetGameObjectHandle(*GetDocument(), { coccoId }).Get()))
							pCocco->SetEnableAttack(true);
					}
				}

				return {};
			}
			case TiFSM_SIGNAL_UPDATE:
			{
				auto* pAnimationGoc = GetComponent<game::GOCAnimationScript>();

				RunAwayTime += in_rEvent.getFloat();

				if (CryTime > 0.0f)
				{
					CryTime -= in_rEvent.getFloat();
				}
				else
				{
					GetComponent<game::GOCSound>()->Play3D(ms_pAttackSoundName, 0.0f);
					CryTime += 2.0f;
				}

				if (!Flags.test(0))
				{
					if (RunAwayTime <= 0.5f || IsInCamera())
						return {};
				}

				Flags.reset(0);

				if (Type != ActionType::eActionType_Idle)
					Kill();
				else
					ChangeState(&ObjCocco::StateEnd);

				return {};
			}
			case TiFSM_SIGNAL_MESSAGE:
			{
				switch (in_rEvent.getMessage().GetType())
				{
				case xgame::MsgHitEventCollision::MessageID:
				{
					xgame::MsgHitEventCollision& message = static_cast<xgame::MsgHitEventCollision&>(in_rEvent.getMessage());

					xgame::MsgDamage damageMsg{ 3, 8, 3, message, *csl::math::Vector3::Zero };
					SendMessageImm(message.m_Sender, damageMsg);

					message.m_Handled = true;

					break;
				}
				default:
					break;
				}

				return {};
			}
			default:
				break;
			}

			return FSM_TOP();
		}

		TiFsmState_t StateEnd(const TiFsmEvent_t& in_rEvent)
		{
			switch (in_rEvent.getSignal())
			{
			case TiFSM_SIGNAL_ENTER:
			{
				GetComponent<fnd::GOCVisualModel>()->SetVisible(false);
				GetComponent<game::GOCShadowSimple>()->SetVisible(false);
				GetComponent<game::GOCMovementComplex>()->DisableMovementFlag(0);

				return {};
			}
			case TiFSM_SIGNAL_LEAVE:
			case TiFSM_SIGNAL_UPDATE:
			{
				return {};
			}
			default:
				break;
			}

			return FSM_TOP();
		}

		SCoccoParam* GetSpawner() const
		{
			if (Type != ActionType::eActionType_Idle)
				return CreateInfo.pSpawner;
			else
				return GetAdapter()->GetData<SCoccoParam>();
		}

		void SetEnableAttack(bool in_isEnable)
		{
			Flags.set(2, in_isEnable);
		}

		void SetTargetOnCircle()
		{
			csl::math::Matrix34 transformMtx{ GetComponent<fnd::GOCTransform>()->m_Frame.m_Unk3.m_Mtx };

			float random = SonicUSA::System::Random::GetInstance()->genrand_float32();
			float rotationAngle = SonicUSA::System::RadianMaskS(random * MATHF_PI + (RotationAngle + MATHF_PI / 2.0f));
			csl::math::Quaternion rotation{ Eigen::AngleAxisf(rotationAngle, transformMtx.GetColumn(1)) };

			csl::math::Quaternion setRotation{ GetAdapter()->GetRotation() };
			csl::math::Vector3 offset{ math::Vector3Rotate(rotation, math::Vector3Rotate(setRotation, { csl::math::Vector3::UnitZ() })) * MoveRange };

			pMovementController->SetTargetPoint({ GetAdapter()->GetPosition() + offset }, 10.0f);
			RotationAngle = rotationAngle;
		}
	
		void SetTargetPlayer()
		{
			csl::math::Matrix34 transformMtx{ GetComponent<fnd::GOCTransform>()->m_Frame.m_Unk3.m_Mtx };
			csl::math::Vector3 upVector{ transformMtx.GetColumn(1) };
			csl::math::Vector3 frontVector{ transformMtx.GetColumn(2) };

			float angle = SonicUSA::System::Random::GetInstance()->genrand_float32() * MATHF_PI / 4.5f + (MATHF_PI / 6.0f);
			csl::math::Quaternion direction{};
			if (CreateInfo.Unk1)
			{
				if ((CreateInfo.Unk1 & 1) == 0)
					direction = { Eigen::AngleAxisf(angle, upVector) };
			}
			else
			{
				float random = powf(SonicUSA::System::Random::GetInstance()->genrand_float32(), 2.0f);
				if (random >= 0.0f)
				{
					direction = { Eigen::AngleAxisf(angle, upVector) };
				}
				else
				{
					if (!(int)random)
						direction = { Eigen::AngleAxisf(angle, upVector) };
				}
			}
			
			direction = { Eigen::AngleAxisf(-angle, upVector) };

			csl::math::Vector3 targetDirection{ math::Vector3Rotate(direction, csl::math::Vector3(frontVector * (SonicUSA::System::Random::GetInstance()->genrand_float32() * 30.0f + 20.0f))) };

			auto* pPlayerInfo = ObjUtil::GetPlayerInformation(*GetDocument(), 0);
			if (!pPlayerInfo)
				return;
		
			if (powf(150.0f, 2.0f) >= pPlayerInfo->Velocity.squaredNorm())
			{
				if (powf(50.0f, 2.0f) >= pPlayerInfo->Velocity.squaredNorm())
					pMovementController->SetRelativeTargetPoint(targetDirection, SonicUSA::System::Random::GetInstance()->genrand_float32() * 10.0f + 50.0f);
				else
					pMovementController->SetRelativeTargetPoint(targetDirection, SonicUSA::System::Random::GetInstance()->genrand_float32() * 10.0f + 175.0f);
			}
			else
			{
				pMovementController->SetRelativeTargetPoint(targetDirection, SonicUSA::System::Random::GetInstance()->genrand_float32() * 10.0f + 295.0f);
			}
		}

		bool IsInCamera() const
		{
			auto* pCamera = GetDocument()->m_pWorld->GetCamera(0);

			csl::math::Vector3 ndc{};
			return pCamera->TransformNDC(ndc, GetComponent<fnd::GOCTransform>()->m_Frame.m_Unk3.GetTranslation()) && fabs(ndc.x()) < 1.1f && fabs(ndc.y()) < 1.1f;
		}

		void DamageJump(const csl::math::Vector3& in_rDamagePosition)
		{
			csl::math::Matrix34 transformMtx{ GetComponent<fnd::GOCTransform>()->m_Frame.m_Unk3.m_Mtx };
			csl::math::Vector3 upVector{ transformMtx.GetColumn(1) };

			csl::math::Vector3 jumpDistance{ in_rDamagePosition - upVector * in_rDamagePosition.dot(upVector) };
			if (!math::Vector3NormalizeIfNotZero(jumpDistance, &jumpDistance))
				jumpDistance = transformMtx.GetColumn(2);
		
			pMovementController->SetTargetDirectionJump(jumpDistance, 10.0f, 30.0f);
			
			GetComponent<game::GOCAnimationScript>()->ChangeAnimation(ms_pDamageAnimationName);

			game::EffectCreateInfo effectCreateInfo{};
			effectCreateInfo.m_Unk1 = 1.0f;
			effectCreateInfo.m_Unk2 = 1;
			effectCreateInfo.m_pName = ms_pEffectName;
			effectCreateInfo.m_pVisual = GetComponent<fnd::GOCVisualModel>();
			effectCreateInfo.m_pBoneName = ms_pEffectNodeName;
			effectCreateInfo.m_Unk9 = -1;

			GetComponent<game::GOCEffect>()->CreateEffectEx(effectCreateInfo);

			GetComponent<game::GOCSound>()->Play3D(ms_pDamageSoundName, 0.0f);
		}

		void CreateAttackers()
		{
			auto* pPlayerInfo = ObjUtil::GetPlayerInformation(*GetDocument(), 0);
			if (!pPlayerInfo)
				return;
		
			csl::math::Matrix34 cameraInvMtx{ GetDocument()->m_pWorld->GetCamera(0)->GetInvViewMatrix() };
			
			csl::math::Vector3 rightVector{ -cameraInvMtx.GetColumn(0) };
			csl::math::Vector3 downVector{ -cameraInvMtx.GetColumn(1) };
			csl::math::Vector3 frontVector{ cameraInvMtx.GetColumn(2) };
			csl::math::Vector3 position{ cameraInvMtx.GetTransVector() };

			csl::math::Vector3 rayBase{ csl::math::Vector3(position.x(), pPlayerInfo->Position.y(), position.z()) + frontVector * 10.0f };
			
			csl::math::Vector3 offset{ pPlayerInfo->Position - position };
			offset -= csl::math::Vector3(csl::math::Vector3::UnitY() * offset.dot(csl::math::Vector3::UnitY()));

			csl::math::Quaternion rotation{};
			if (math::Vector3NormalizeIfNotZero(offset, &offset))
			{
				csl::math::Matrix34 rotationMtx{};
				rotationMtx.SetColumn(0, { csl::math::Vector3::UnitY().cross(offset) });
				rotationMtx.SetColumn(1, { csl::math::Vector3::UnitY() });
				rotationMtx.SetColumn(2, offset);

				rotation = { rotationMtx };
			}
			else
			{
				rotation = { 0.0f, 0.0f, 0.0f, 1.0f };
			}

			if (!IS_GLOBAL_1_ENABLED)
			{
				IS_GLOBAL_1_ENABLED = true;
				GLOBAL_1_VALUE = 20.0f;
			}

			if (!IS_GLOBAL_2_ENABLED)
			{
				IS_GLOBAL_2_ENABLED = true;
				GLOBAL_2_VALUE = 40.0f;
			}

			for (int i = 0; i < 2; i++)
			{
				float scalar = SonicUSA::System::Random::GetInstance()->genrand_float32() * 20.0f + 10.0f;
				if (i == 0)
					scalar *= ((i + 1) / 2);
				else
					scalar *= ((i + 1) / -2);
				
				csl::math::Vector3 randomBase{ rayBase + rightVector * scalar };
				csl::math::Vector3 from{ randomBase - downVector * GLOBAL_1_VALUE };
				csl::math::Vector3 to{ from + downVector * GLOBAL_2_VALUE };

				game::PhysicsRaycastOutput output{};
				if (!ObjUtil::RaycastNearestCollision(&output, *GetDocument(), from, to, 0xC996))
					continue;

				CInfo createInfo{};
				createInfo.Position = { output.m_HitPoint - downVector * 10.0f };
				createInfo.Rotation = rotation;
				createInfo.pSpawner = GetSpawner();
				createInfo.Unk1 = i;

				auto* pCocco = CreateAttacker(createInfo);
				GetDocument()->AddGameObject(pCocco);
				SubCoccos.push_back({ pCocco });
			}
		}

		static ObjCocco* CreateAttacker(const CInfo& in_rCreateInfo)
		{
			return new ObjCocco(in_rCreateInfo);
		}
	};
}

#pragma pop_macro("SendMessage")