#pragma once

namespace app
{
	class EnemyStalBaby : public EnemyBase
	{
	private:
		inline static const size_t ms_ShapeCount = 4;
		inline static const size_t ms_StateCount = 8;
		inline static const size_t ms_DefaultStateIndex = 0;
		inline static const float ms_ShadowRadius = 3.5f;
		inline static const csl::math::Vector3 ms_CenterPosition{ 0.0f, 8.0f, 0.0f };
		inline static const csl::math::Vector2 ms_BodyCollisionSize{ 10.0f, 3.0f };
		inline static const csl::math::Vector2 ms_HandCollisionSize{ 4.0f, 7.0f };
		inline static const csl::math::Vector3 ms_HandCollisionOffset{ -1.0f, 0.0f, 12.0f };
		inline static const csl::math::Vector3 ms_RigidBodyCollisionOffset{ 0.0f, 8.0f, 0.0f };
		inline static const char* ms_pWalkSoundName = "enm_stullbaby_walk";
		inline static const char* ms_pPunchSoundName = "enm_stullbaby_punch";
		inline static const char* ms_pPunchHitSoundName = "enm_pawn_punch_hit";
		inline static const char* ms_pDamageSoundName = "enm_cmn_damage";
		inline static const char* ms_pEffectName = "ef_en_com_wt1_hit";
		inline static const char* ms_pScoreName = "STALBABY";

	public:
		fnd::HFrame Frame{};
		game::MoveCharacterRigidBody* pMovementController{};
		csl::math::Vector3 KickPosition{};
		float Speed{};
		float MinimumTargetDistance{};
		float ElapsedTime{};
		csl::ut::Bitset<byte> Flags{};

		EnemyStalBaby() : EnemyBase()
		{
			
		}

		void AddCallback(GameDocument& in_rDocument) override
		{
			fnd::GOComponent::Create<game::GOCGravity>(*this);
			fnd::GOComponent::Create<fnd::GOCVisualModel>(*this);
			fnd::GOComponent::Create<game::GOCAnimationScript>(*this);
			fnd::GOComponent::Create<game::GOCCollider>(*this);
			fnd::GOComponent::Create<game::GOCShadowSimple>(*this);
			fnd::GOComponent::Create<game::GOCEffect>(*this);
			fnd::GOComponent::Create<game::GOCSound>(*this);
			fnd::GOComponent::Create<GOCEnemyTarget>(*this);
			fnd::GOComponent::Create<GOCEnemyHsm>(*this);
			fnd::GOComponent::Create<game::GOCMovementComplex>(*this);

			fnd::GOComponent::BeginSetup(*this);

			auto* pInfo = ObjUtil::GetObjectInfo<EnemyStalBabyInfo>(in_rDocument);
			auto* pParam = GetAdapter()->GetData<SStalBabyParam>();

			Speed = pParam->Speed;
			MinimumTargetDistance = 225.0f;

			if (auto* pTransformGoc = GetComponent<fnd::GOCTransform>())
			{
				csl::math::Vector3 position{ GetAdapter()->GetPosition() };
				csl::math::Quaternion rotation{ GetAdapter()->GetRotation() };

				CreateCenterPositionFrame(ms_CenterPosition);
				pTransformGoc->m_Frame.AddChild(&Frame);
				Frame.SetLocalTranslation(position);
				Frame.SetLocalRotation(rotation);
				Frame.ResetFlag(16);
				Frame.ResetFlag(32);
			}

			if (auto* pVisualGoc = GetComponent<fnd::GOCVisualModel>())
			{
				fnd::GOCVisualModel::Description description{};
				description.m_Model = pInfo->Model;
				description.m_Skeleton = pInfo->Skeleton;
				description.field_0C |= 0x400000;

				pVisualGoc->Setup(description);
				pVisualGoc->SetVisible(false);

				if (auto* pAnimationGoc = GetComponent<game::GOCAnimationScript>())
				{
					pAnimationGoc->Setup({ &pInfo->AnimationContainer });
					pVisualGoc->AttachAnimation(pAnimationGoc);

					pAnimationGoc->RegisterCallback(0, animation::CreateAnimCallback<EnemyStalBaby>(this, &app::EnemyStalBaby::AttachCallback, GetAllocator()));
					pAnimationGoc->RegisterCallback(1, animation::CreateAnimCallback<EnemyStalBaby>(this, &app::EnemyStalBaby::SoundCallback, GetAllocator()));
				}
			}

			if (auto* pColliderGoc = GetComponent<game::GOCCollider>())
			{
				pColliderGoc->Setup({ ms_ShapeCount });
				game::ColliCapsuleShapeCInfo bodyCollisionInfo{};
				bodyCollisionInfo.m_ShapeType = game::CollisionShapeType::ShapeType::ShapeType_Capsule;
				bodyCollisionInfo.m_MotionType = game::PhysicsMotionType::MotionType::MotionType_VALUE2;
				bodyCollisionInfo.m_Unk2 |= 1;
				bodyCollisionInfo.m_Unk3 = 0x20000;
				bodyCollisionInfo.m_ShapeID = 0;
				bodyCollisionInfo.m_Radius = ms_BodyCollisionSize.x();
				bodyCollisionInfo.m_Height = ms_BodyCollisionSize.y();
				bodyCollisionInfo.m_pParent = GetCenterPositionFrame();
				ObjUtil::SetupCollisionFilter(ObjUtil::eFilter_Unk9, bodyCollisionInfo);

				if (auto* pShape = pColliderGoc->CreateShape(bodyCollisionInfo))
					ObjUtil::SetEnableColliShape(pShape, false);

				game::ColliCapsuleShapeCInfo handCollisionInfo{};
				handCollisionInfo.m_ShapeType = game::CollisionShapeType::ShapeType::ShapeType_Capsule;
				handCollisionInfo.m_MotionType = game::PhysicsMotionType::MotionType::MotionType_VALUE2;
				handCollisionInfo.m_Unk2 |= 1;
				handCollisionInfo.m_ShapeID = 1;
				handCollisionInfo.m_Radius = ms_HandCollisionSize.x();
				handCollisionInfo.m_Height = ms_HandCollisionSize.y();
				handCollisionInfo.m_pParent = GetCenterPositionFrame();
				handCollisionInfo.SetLocalPosition(ms_HandCollisionOffset);
				ObjUtil::SetupCollisionFilter(ObjUtil::eFilter_Unk9, handCollisionInfo);

				if (auto* pShape = pColliderGoc->CreateShape(handCollisionInfo))
					ObjUtil::SetEnableColliShape(pShape, false);

				game::CharacterRigidBodyCinfo rigidBodyCollisionInfo{};
				rigidBodyCollisionInfo.m_Unk7 = 8.0f;
				rigidBodyCollisionInfo.m_Unk8 = 0.0f;
				rigidBodyCollisionInfo.m_Unk10 = 300.0f;
				rigidBodyCollisionInfo.m_Flags = 30;
				rigidBodyCollisionInfo.m_ShapeID = 2;
				rigidBodyCollisionInfo.SetLocalPosition(ms_RigidBodyCollisionOffset);
				pColliderGoc->CreateCharacterRigidBody(rigidBodyCollisionInfo);

				game::ColliCapsuleShapeCInfo searchCollisionInfo{};
				searchCollisionInfo.m_ShapeType = game::CollisionShapeType::ShapeType::ShapeType_Capsule;
				searchCollisionInfo.m_MotionType = game::PhysicsMotionType::MotionType::MotionType_VALUE2;
				searchCollisionInfo.m_Unk2 |= 3;
				searchCollisionInfo.m_ShapeID = 3;
				searchCollisionInfo.m_Radius = pParam->SearchRange;
				searchCollisionInfo.m_Height = csl::math::Max(pParam->SearchHeight, pParam->SearchRange);
				ObjUtil::SetupCollisionFilter(ObjUtil::eFilter_Unk6, searchCollisionInfo);
				pColliderGoc->CreateShape(searchCollisionInfo);
			}

			if (auto* pEnemyHsmGoc = GetComponent<GOCEnemyHsm>())
			{
				GOCEnemyHsm::Description description{ StateDescriptors, ms_StateCount, ms_DefaultStateIndex };
				pEnemyHsmGoc->Setup(description);
			}
			
			if (GetComponent<game::GOCGravity>())
				game::GOCGravity::SimpleSetup(this, 1);

			if (GetComponent<game::GOCEffect>())
				game::GOCEffect::SimpleSetup(this, 1, false);

			game::GOCSound::SimpleSetup(this, 0, 0);

			if (auto* pShadowGoc = GetComponent<game::GOCShadowSimple>())
			{
				game::ShadowHemisphereShapeCInfo shadowInfo{ ms_ShadowRadius };
				game::GOCShadowSimple::Description description{ &shadowInfo };
				pShadowGoc->Setup(description);
			}

			if (auto* pMovementGoc = GetComponent<game::GOCMovementComplex>())
			{
				if (pMovementController = pMovementGoc->SetMoveController<game::MoveCharacterRigidBody>())
				{
					game::MoveCharacterRigidBody::Description description{ 2, 1 };
					pMovementController->Setup(description);

					pMovementController->SetMoveRangeBasePosition(GetAdapter()->GetPosition());
					pMovementController->SetMoveRange(pParam->MoveRange);
				
					game::MoveStraightCallback callback{ &EnemyStalBaby::NotifyMovementRangeOutCallback };
					pMovementController->SetNotifyMoveRangeOutCallback(callback);
				}
			}

			if (auto* pEnemyTargetGoc = GetComponent<GOCEnemyTarget>())
			{
				pEnemyTargetGoc->Setup({ false });
				pEnemyTargetGoc->SetColliderEyesight(3);
				pEnemyTargetGoc->SetEyesightFrame(GetCenterPositionFrame());
			}

			SetRandomPosition();

			auto* pLevelInfo = GetService<CLevelInfo>();
			if (pLevelInfo && pLevelInfo->IsPlayingZeldaEvent())
				Flags.set(3);

			if (pParam->isEventDriven || (pLevelInfo && pLevelInfo->IsPlayingZeldaEvent()))
				Sleep();

			fnd::GOComponent::EndSetup(*this);
		}

		void Update(const fnd::SUpdateInfo& in_rUpdateInfo) override
		{
			if (!pMovementController)
				return;
		
			if (!pMovementController->IsOnGround())
			{
				ElapsedTime += in_rUpdateInfo.deltaTime;
				if (ElapsedTime < 1.0f)
					return;
			
				enemy::DeadEffectCInfo createInfo{};
				createInfo.Owner = this;
				createInfo.EffectSize = 0;
				createInfo.Flags.reset(2);
				createInfo.Flags.reset(1);
				CreateDeadEffect(createInfo);
				OnDead();
			}
			else
			{
				ElapsedTime = 0.0f;
			}
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
			case xgame::MsgNotifyObjectEvent::MessageID:			return ProcMsgNotifyObjectEvent(static_cast<xgame::MsgNotifyObjectEvent&>(in_rMessage));
			case xgame::MsgDlcZeldaNoticeStopEnemy::MessageID:		return ProcMsgDlcZeldaNoticeStopEnemy(static_cast<xgame::MsgDlcZeldaNoticeStopEnemy&>(in_rMessage));
			case xgame::MsgDlcZeldaNoticeActiveEnemy::MessageID:	return ProcMsgDlcZeldaNoticeActiveEnemy(static_cast<xgame::MsgDlcZeldaNoticeActiveEnemy&>(in_rMessage));
			case xgame::MsgHitEventCollision::MessageID:			return ProcMsgHitEventCollision(static_cast<xgame::MsgHitEventCollision&>(in_rMessage));
			default:												return EnemyBase::ProcessMessage(in_rMessage);
			}
		}

		bool ProcMsgDamage(xgame::MsgDamage& in_rMessage)
		{
			if (!EnemyUtil::IsDamage(in_rMessage.DefensePower, 0, in_rMessage.AttackType))
				return false;

			auto* pEnemyHsmGoc = GetComponent<GOCEnemyHsm>();
			auto* pTransformGoc = GetComponent<fnd::GOCTransform>();

			if (EnemyUtil::IsFatalDamage(in_rMessage) || pEnemyHsmGoc->GetCurrentStateID() == 5)
			{
				in_rMessage.SetReply(pTransformGoc->m_Frame.m_Unk3.GetTranslation(), true);
				enemy::DeadEffectCInfo createInfo{};
				createInfo.Owner = this;
				createInfo.SetMsgDamage(in_rMessage);
				createInfo.SetZeldaStalBaby();
				CreateDeadEffect(createInfo);
				
				ProcMission(in_rMessage);
				ObjUtil::AddScore(*this, ms_pScoreName, in_rMessage);

				pEnemyHsmGoc->ChangeState(7);
			}
			else if (in_rMessage.m_SenderType == 3)
			{
				in_rMessage.SetReply(pTransformGoc->m_Frame.m_Unk3.GetTranslation(), true);
				ObjUtil::AddScore(*this, ms_pScoreName, in_rMessage);
			
				enemy::DeadEffectCInfo createInfo{};
				createInfo.Owner = this;
				createInfo.SetMsgDamage(in_rMessage);
				createInfo.SetZeldaStalBaby();
				CreateDeadEffect(createInfo);

				ProcMission();
				
				pEnemyHsmGoc->ChangeState(7);
			}
			else
			{
				if (pEnemyHsmGoc->GetCurrentStateID() == 7)
					return true;
			
				auto* pSenderShape = in_rMessage.m_SenderShape.Get();
				auto* pReceiverShape = in_rMessage.m_RecieverShape.Get();

				game::PhysicsContactPoint contactPoint{};
				if (pSenderShape && pReceiverShape && pReceiverShape->GetClosestPoint(*pSenderShape, &contactPoint))
				{
					if (AttackType::And(in_rMessage.AttackType, 64))
						in_rMessage.m_ReplyStatus.set(0);

					in_rMessage.SetReply(pTransformGoc->m_Frame.m_Unk3.GetTranslation(), 0, *csl::math::Vector3::Zero);
					GetComponent<game::GOCEffect>()->CreateEffectWorld(ms_pEffectName, GetComponent<fnd::GOCTransform>()->m_Frame.m_Unk3.m_Mtx, 1.0f);
				}

				auto* pEnemyTarget = GetComponent<GOCEnemyTarget>();
				if (pEnemyTarget->IsFindTarget())
					pEnemyTarget->LockTarget();

				GetComponent<game::GOCSound>()->Play3D(ms_pDamageSoundName, 0.0f);
				pEnemyHsmGoc->ChangeState(5);
			}

			return true;
		}

		bool ProcMsgKick(xgame::MsgKick& in_rMessage)
		{
			GetComponent<GOCEnemyHsm>();
			
			in_rMessage.SetReplyForSucceed();
			ObjUtil::AddScore(*this, ms_pScoreName, in_rMessage);
			
			Flags.set(1);
			
			KickPosition = in_rMessage.m_Unk3;
			
			GetComponent<GOCEnemyHsm>()->ChangeState(7);

			return true;
		}

		bool ProcMsgPLGetHomingTargetInfo(xgame::MsgPLGetHomingTargetInfo& in_rMessage)
		{
			if (Flags.test(2))
				EnemyBase::ProcMsgPLGetHomingTargetInfo(in_rMessage);
			else
				in_rMessage.m_Flags.set(0);

			return true;
		}

		bool ProcMsgNotifyObjectEvent(xgame::MsgNotifyObjectEvent& in_rMessage)
		{
			if (in_rMessage.GetEventType() == 1)
				Resume();

			return true;
		}

		bool ProcMsgDlcZeldaNoticeStopEnemy(xgame::MsgDlcZeldaNoticeStopEnemy& in_rMessage)
		{
			auto* pEnemyHsmGoc = GetComponent<GOCEnemyHsm>();
			if (pEnemyHsmGoc->GetCurrentStateID())
			{
				GetComponent<fnd::GOCVisualModel>()->SetVisible(false);
				GetComponent<game::GOCShadowSimple>()->SetVisible(false);
				GetComponent<game::GOCAnimationScript>()->SetSpeed(0.0f);
				GetComponent<game::GOCMovementComplex>()->DisableMovementFlag(0);
				GetComponent<game::GOCCollider>()->SetEnable(false);

				pEnemyHsmGoc->Dispatch(in_rMessage);
			}

			Sleep();
			Flags.set(3);

			return true;
		}

		bool ProcMsgDlcZeldaNoticeActiveEnemy(xgame::MsgDlcZeldaNoticeActiveEnemy& in_rMessage)
		{
			auto* pEnemyHsmGoc = GetComponent<GOCEnemyHsm>();
			if (pEnemyHsmGoc->GetCurrentStateID())
			{
				GetComponent<fnd::GOCVisualModel>()->SetVisible(true);
				GetComponent<game::GOCShadowSimple>()->SetVisible(true);
				GetComponent<game::GOCAnimationScript>()->SetSpeed(1.0f);
				GetComponent<game::GOCMovementComplex>()->EnableMovementFlag(0);
				GetComponent<game::GOCCollider>()->SetEnable(true);

				pEnemyHsmGoc->Dispatch(in_rMessage);
			}

			Resume();
			Flags.reset(3);

			return true;
		}

		bool ProcMsgHitEventCollision(xgame::MsgHitEventCollision& in_rMessage)
		{
			if (Flags.test(3))
				return true;
		
			if (ObjUtil::CheckShapeUserID(in_rMessage.m_pSelf, 1))
			{
				xgame::MsgDamage msg{ 3, 8, 2, in_rMessage, *csl::math::Vector3::Zero };
				SendMessageImm(in_rMessage.m_Sender, msg);
				GetComponent<game::GOCSound>()->Play3D(ms_pPunchHitSoundName, 0.0f);
			}
			else
			{
				if (!ObjUtil::CheckShapeUserID(in_rMessage.m_pSelf, 3))
					SendTouchDamage(in_rMessage);
			}

			return true;
		}

		void NotifyMovementRangeOutCallback()
		{
			Flags.set(0);
		}

		void AttachCallback(animation::CharactorAnimation* in_pAnimation, animation::ETriggerValueType in_triggerType, animation::CallbackParam in_param)
		{
			if (in_triggerType)
				return;

			if (in_param.m_Int == 1)
				ObjUtil::SetEnableColliShape(GetComponent<game::GOCCollider>(), 1, false);
			else if (in_param.m_Int == 0)
				ObjUtil::SetEnableColliShape(GetComponent<game::GOCCollider>(), 1, true);
		}

		void SoundCallback(animation::CharactorAnimation* in_pAnimation, animation::ETriggerValueType in_triggerType, animation::CallbackParam in_param)
		{
			if (in_triggerType)
				return;

			if (in_param.m_Int == 1)
				GetComponent<game::GOCSound>()->Play3D(ms_pPunchSoundName, 0.0f);
			else if (in_param.m_Int == 0)
				GetComponent<game::GOCSound>()->Play3D(ms_pWalkSoundName, 0.0f);
		}

		float GetMoveSpeed()
		{
			return Speed;
		}

		csl::math::Vector3 GetTurnDirection(const csl::math::Vector3& in_rTargetPosition, float in_deltaTime)
		{
			auto* pTransformGoc = GetComponent<fnd::GOCTransform>();
			csl::math::Matrix34 transformMtx{ pTransformGoc->m_Transform.GetTransformMatrix() };
			csl::math::Vector3 upVector{ transformMtx.GetColumn(1) };
			csl::math::Vector3 frontVector{ transformMtx.GetColumn(2) };
			csl::math::Vector3 leftVector{ transformMtx.GetColumn(0) };

			csl::math::Vector3 distance{ in_rTargetPosition - transformMtx.GetTransVector() };
			distance = { distance - csl::math::Vector3(upVector * distance.dot(upVector)) };
			if (distance.squaredNorm() <= 0.000001f)
				return *csl::math::Vector3::Zero;
			
			distance = distance.Normalize();
			if (MATHF_PI / (4.0f / 3.0f) * in_deltaTime < acosf(csl::math::Clamp(distance.dot(frontVector), -1.0f, 1.0f)))
			{
				float angle = csl::math::Select(leftVector.dot(distance), fabs(MATHF_PI / (4.0f / 3.0f) * in_deltaTime), csl::math::Nabs(MATHF_PI / (4.0f / 3.0f) * in_deltaTime));
				csl::math::Quaternion rotation{ Eigen::AngleAxisf(angle, upVector) };
				return math::Vector3Rotate(rotation, frontVector);
			}

			return distance;
		}

		void SetEnableCollision(bool in_isEnableBodyCollision, bool in_isEnableHandCollision)
		{
			auto* pColliderGoc = GetComponent<game::GOCCollider>();
			ObjUtil::SetEnableColliShape(pColliderGoc, 0, in_isEnableBodyCollision);
			ObjUtil::SetEnableColliShape(pColliderGoc, 1, in_isEnableHandCollision);
			ObjUtil::SetEnableColliShape(pColliderGoc, 2, in_isEnableBodyCollision);

			Flags.set(2, in_isEnableBodyCollision);
		}

		void SetRandomPosition()
		{
			auto* pTransformGoc = GetComponent<fnd::GOCTransform>();

			auto* pParam = GetAdapter()->GetData<SStalBabyParam>();
			float appearOffset = SonicUSA::System::Random::GetInstance()->genrand_float32() * pParam->AppearRange;
			float offset = SonicUSA::System::Random::GetInstance()->genrand_float32() * MATHF_PI * 2.0f;
		
			csl::math::Matrix34 transformMtx{ pTransformGoc->m_Frame.m_Unk3.m_Mtx };
			csl::math::Vector3 positionOffset{ transformMtx * csl::math::Vector4({ math::Vector3RotateY(offset, { csl::math::Vector3::UnitZ() }) * appearOffset }, 1.0) };
			
			game::PhysicsRaycastOutput output{};
			if (ObjUtil::RaycastNearestCollision(&output, *GetDocument(), { positionOffset + transformMtx.GetColumn(1) * 50.0f }, { positionOffset - transformMtx.GetColumn(1) * 50.0f }, 0xC996))
				pTransformGoc->SetLocalTranslation(output.m_HitPoint);
		}

		void OnDead()
		{
			SetStatusTemporaryRetire(SonicUSA::System::Random::GetInstance()->genrand_float32() * 3.0f + 3.0f);
			Kill();
		}

		class State
		{
		private:
			inline static bool ms_IsInRangeValue1Initialized = false;
			inline static float ms_IsInRangeValue1{};
			inline static bool ms_IsInRangeValue2Initialized = false;
			inline static float ms_IsInRangeValue2{};

		public:
			class Idle : public EnemyState<EnemyStalBaby>
			{
			public:
				typedef EnemyStalBaby context_type;

			private:
				inline static const char* ms_pAnimationName = "IDLE";

			public:
				GOCEnemyTarget* pEnemyTargetGoc{};

				Idle()
				{

				}

				void OnEnter(EnemyStalBaby& in_rObj, int in_unk) override;
				void OnLeave(EnemyStalBaby& in_rObj, int in_unk) override;
				bool Step(EnemyStalBaby& in_rObj, float in_deltaTime) override;
			};

			class Find : public EnemyState<EnemyStalBaby>
			{
			public:
				typedef EnemyStalBaby context_type;

			private:
				inline static const char* ms_pAnimationName = "APPEAR";
				inline static const char* ms_pSoundName = "enm_stullbaby_appear";
				inline static const char* ms_pEffectName = "ef_dl3_stalbaby_appear";

			public:
				game::GOCAnimationScript* pAnimationGoc{};
				Effect::CEffectHandle<> EffectHandle{};
				float ElapsedTime{};

				Find()
				{

				}

				void OnEnter(EnemyStalBaby& in_rObj, int in_unk) override;
				void OnLeave(EnemyStalBaby& in_rObj, int in_unk) override;
				bool Step(EnemyStalBaby& in_rObj, float in_deltaTime) override;
				bool ProcessMessage(GameObject& in_rObj, fnd::Message& in_rMessage) override;
				bool ProcMsgDlcZeldaNoticeStopEnemy(GameObject& in_rObj, xgame::MsgDlcZeldaNoticeStopEnemy& in_rMessage);
				bool ProcMsgDlcZeldaNoticeActiveEnemy(GameObject& in_rObj, xgame::MsgDlcZeldaNoticeActiveEnemy& in_rMessage);
			};

			class Chase : public EnemyState<EnemyStalBaby>
			{
			public:
				typedef EnemyStalBaby context_type;

			private:
				inline static const char* ms_pAnimationName = "WALK";

			public:
				GOCEnemyTarget* pEnemyTargetGoc{};

				Chase()
				{

				}

				void OnEnter(EnemyStalBaby& in_rObj, int in_unk) override;
				bool Step(EnemyStalBaby& in_rObj, float in_deltaTime) override;
			};

			class Attack : public EnemyState<EnemyStalBaby>
			{
			public:
				typedef EnemyStalBaby context_type;

			private:
				inline static const char* ms_pAnimationName = "ATTACK";

			public:
				game::GOCAnimationScript* pAnimationGoc{};

				Attack()
				{

				}

				void OnEnter(EnemyStalBaby& in_rObj, int in_unk) override;
				bool Step(EnemyStalBaby& in_rObj, float in_deltaTime) override;
			};

			class Gap : public EnemyState<EnemyStalBaby>
			{
			public:
				typedef EnemyStalBaby context_type;

			private:
				inline static const char* ms_pAnimationName = "IDLE";

			public:
				GOCEnemyTarget* pEnemyTargetGoc{};
				float LifeSpan{};

				Gap()
				{

				}
				
				void OnEnter(EnemyStalBaby& in_rObj, int in_unk) override;
				bool Step(EnemyStalBaby& in_rObj, float in_deltaTime) override;
			};

			class Stagger : public EnemyState<EnemyStalBaby>
			{
			public:
				typedef EnemyStalBaby context_type;

			private:
				inline static const char* ms_pAnimationName = "HITBACK";

			public:
				game::GOCAnimationScript* pAnimationGoc{};
				float LifeSpan{};
				bool AnimationLoopFinished{};

				Stagger()
				{

				}

				void OnEnter(EnemyStalBaby& in_rObj, int in_unk) override;
				bool Step(EnemyStalBaby& in_rObj, float in_deltaTime) override;
			};

			class Hide : public EnemyState<EnemyStalBaby>
			{
			public:
				typedef EnemyStalBaby context_type;

			private:
				inline static const char* ms_pAnimationName = "IDLE";
				inline static const char* ms_pEffectName = "ef_dl3_stalbaby_appear";

			public:
				Effect::CEffectHandle<> EffectHandle{};
				float ElapsedTime{};
				
				Hide()
				{

				}

				void OnEnter(EnemyStalBaby& in_rObj, int in_unk) override;
				bool Step(EnemyStalBaby& in_rObj, float in_deltaTime) override;
				bool ProcessMessage(GameObject& in_rObj, fnd::Message& in_rMessage) override;
				bool ProcMsgDlcZeldaNoticeStopEnemy(GameObject& in_rObj, xgame::MsgDlcZeldaNoticeStopEnemy& in_rMessage);
				bool ProcMsgDlcZeldaNoticeActiveEnemy(GameObject& in_rObj, xgame::MsgDlcZeldaNoticeActiveEnemy& in_rMessage);
			};

			class Dead : public EnemyState<EnemyStalBaby>
			{
			public:
				typedef EnemyStalBaby context_type;

			private:
				inline static const char* ms_pDeadAnimationName = "DEAD";
				inline static const char* ms_pDeadNoHeadAnimationName = "DEAD_NO_HEAD";
				inline static const char* ms_pEffectName = "ef_dl3_stalbaby_dead";
				inline static const char* ms_pHeadNodeName = "head";

			public:
				game::GOCAnimationScript* pAnimationGoc{};
				float ElapsedTime{};
				bool IsDeadNoHead{};

				Dead()
				{

				}

				void OnEnter(EnemyStalBaby& in_rObj, int in_unk) override;
				bool Step(EnemyStalBaby& in_rObj, float in_deltaTime) override;
			};

			static bool IsInRangeAttack(EnemyStalBaby& in_rObj, const csl::math::Vector3&);
			static void MoveStop(EnemyStalBaby& in_rObj);
		};

		inline static ut::internal::StateDescImpl States[] =
		{
			{ "Idle", (ut::internal::StateCreate_t)&ut::StateCreatorFuncTemplate<EnemyStalBaby::State::Idle>::Create, -1 },
			{ "Find", (ut::internal::StateCreate_t)&ut::StateCreatorFuncTemplate<EnemyStalBaby::State::Find>::Create, -1 },
			{ "Chase", (ut::internal::StateCreate_t)&ut::StateCreatorFuncTemplate<EnemyStalBaby::State::Chase>::Create, -1 },
			{ "Attack", (ut::internal::StateCreate_t)&ut::StateCreatorFuncTemplate<EnemyStalBaby::State::Attack>::Create, -1 },
			{ "Gap", (ut::internal::StateCreate_t)&ut::StateCreatorFuncTemplate<EnemyStalBaby::State::Gap>::Create, -1 },
			{ "Stagger", (ut::internal::StateCreate_t)&ut::StateCreatorFuncTemplate<EnemyStalBaby::State::Stagger>::Create, -1 },
			{ "Hide", (ut::internal::StateCreate_t)&ut::StateCreatorFuncTemplate<EnemyStalBaby::State::Hide>::Create, -1 },
			{ "Dead", (ut::internal::StateCreate_t)&ut::StateCreatorFuncTemplate<EnemyStalBaby::State::Dead>::Create, -1 },
		};

		inline static GOCEnemyHsm::StateDesc StateDescriptors[] =
		{
			{ 0, &States[0] },
			{ 1, &States[1] },
			{ 2, &States[2] },
			{ 3, &States[3] },
			{ 4, &States[4] },
			{ 5, &States[5] },
			{ 6, &States[6] },
			{ 7, &States[7] },
		};
	};
}