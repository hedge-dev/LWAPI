#pragma once

namespace app
{
	class EnemyDekunuts : public EnemyBase
	{
	protected:
		inline static constexpr int FLAG_IS_DEACTIVATED = 0;
		inline static constexpr int FLAG_IS_BODY_COLLISION_ENABLED = 1;
		inline static constexpr int FLAG_IS_READY_TO_ATTACK = 2;
		inline static constexpr int FLAG_IS_DAMAGE_RECEIVED = 3;
		inline static constexpr int FLAG_IS_OBJECT_STOPPED = 4;

	private:
		inline static const char* ms_pAnimationNames[] = { "IDLE_LOOP", "UNDERGROUND_LOOP", "APPEARE", "ESCAPE", "DAMAGE", "ATTACK" };
		inline static const char* ms_pScoreName = "DEKUNUTS";
		inline static const char* ms_pDeathSoundName = "enm_dekunuts_cry";
		inline static const char* ms_pShotSoundName = "enm_dekunuts_bullet";
		inline static const size_t ms_ShapeCount = 3;
		inline static const size_t ms_ModelCount = 2;
		inline static const size_t ms_AnimationCount = 2;
		inline static const size_t ms_MaxShotCount = 64;
		inline static const float ms_HideCollisionRadius = 50.0f;
		inline static const float ms_CollisionRadius = 13.0f * 0.5f;
		inline static size_t ms_StateCount = 5;
		inline static int ms_DefaultState = 0;

	public:
		class Listener : public animation::AnimationListener
		{
		public:
			EnemyDekunuts* pOwner{};
			bool IsShotRequested{};

			void OnEvent(animation::NotifyTiming timing) override
			{
				if (!pOwner)
					return;
			
				if (IsShotRequested)
				{
					pOwner->Shot();
					IsShotRequested = false;
				}
			}
		};

		float RotationAngle{};
		csl::ut::Bitset<uint8> Flags{};
		Listener AnimListener{};
		fnd::HFrame Frame{};
		csl::math::Matrix34 LookAtMatrix{};
		GameObjectHandle<EnemyDekunutsShot> ShotHandles[ms_MaxShotCount]{};

		EnemyDekunuts() : EnemyBase()
		{
			AnimListener.Timing = 2;
		}

		void AddCallback(GameDocument* in_pDocument) override
		{
			fnd::GOComponent::Create<fnd::GOCVisualContainer>(*this);
			fnd::GOComponent::Create<game::GOCAnimationContainer>(*this);
			fnd::GOComponent::Create<game::GOCCollider>(*this);
			fnd::GOComponent::Create<GOCEnemyHsm>(*this);
			fnd::GOComponent::Create<GOCEnemyTarget>(*this);
			fnd::GOComponent::Create<game::GOCSound>(*this);

			fnd::GOComponent::BeginSetup(*this);

			auto* pInfo = ObjUtil::GetObjectInfo<EnemyDekunutsInfo>(*in_pDocument);
			auto* pParam = GetAdapter()->GetData<SDekunutsParam>();

			Flags.set(FLAG_IS_DEACTIVATED, pParam->MessageBoot);

			auto* pTransform = GetComponent<fnd::GOCTransform>();
			pTransform->Frame.AddChild(&Frame);
			csl::math::Matrix34Inverse(pTransform->Frame.Unk3.Mtx, &LookAtMatrix);

			if (auto* pVisualContainerGoc = GetComponent<fnd::GOCVisualContainer>())
			{
				pVisualContainerGoc->Setup({ ms_ModelCount });

				if (auto* pVisualGoc = pVisualContainerGoc->CreateSingle<fnd::GOCVisualModel>(*this))
				{
					fnd::GOCVisualModel::Description description{};

					description.Model = pInfo->ModelContainer.Models[0];
					description.Skeleton = pInfo->SkeletonContainer.Skeletons[0];

					pVisualGoc->Setup(description);
					pVisualGoc->SetLocalScale({ 1.0f, 1.0f, 1.0f });
					pVisualContainerGoc->Add(pVisualGoc);

					if (auto* pAnimationContainerGoc = GetComponent<game::GOCAnimationContainer>())
					{
						auto* pAnimationScriptGoc = pAnimationContainerGoc->CreateSingle<game::GOCAnimationScript>(*this);
						pAnimationScriptGoc->Setup({ &pInfo->BaseAnimationContainer });

						pVisualGoc->AttachAnimation(pAnimationScriptGoc);
						pAnimationScriptGoc->SetAnimation(ms_pAnimationNames[0]);
						pAnimationContainerGoc->Add(pAnimationScriptGoc);
					}
				}

				if (auto* pVisualGoc = pVisualContainerGoc->CreateSingle<fnd::GOCVisualModel>(*this))
				{
					fnd::GOCVisualModel::Description description{};

					description.Model = pInfo->ModelContainer.Models[1];
					description.Skeleton = pInfo->SkeletonContainer.Skeletons[1];
					description.pParent = &Frame;

					pVisualGoc->Setup(description);
					pVisualGoc->SetLocalScale({ 1.0f, 1.0f, 1.0f });
					pVisualContainerGoc->Add(pVisualGoc);

					if (auto* pAnimationContainerGoc = GetComponent<game::GOCAnimationContainer>())
					{
						auto* pAnimationScriptGoc = pAnimationContainerGoc->CreateSingle<game::GOCAnimationScript>(*this);
						pAnimationScriptGoc->Setup({ &pInfo->AnimationContainer });

						pVisualGoc->AttachAnimation(pAnimationScriptGoc);
						pAnimationScriptGoc->SetAnimation(ms_pAnimationNames[0]);

						pAnimationScriptGoc->RegisterCallback(0, animation::CreateAnimCallback<EnemyDekunuts>(this, &app::EnemyDekunuts::AnimationCallback, GetAllocator()));

						AnimListener.pOwner = this;
						pAnimationScriptGoc->AddListener(&AnimListener);
						pAnimationContainerGoc->Add(pAnimationScriptGoc);
					}
				}
			}

			if (auto* pCollider = GetComponent<game::GOCCollider>())
			{
				pCollider->Setup({ ms_ShapeCount });
				game::ColliSphereShapeCInfo appearCollisionInfo{};
				appearCollisionInfo.ShapeType = game::CollisionShapeType::ShapeType::eShapeType_Sphere;
				appearCollisionInfo.MotionType = game::PhysicsMotionType::MotionType::eMotionType_Value2;
				appearCollisionInfo.Unk2 = 6;
				appearCollisionInfo.ShapeID = 0;
				appearCollisionInfo.Radius = pParam->AppearRange;
				ObjUtil::SetupCollisionFilter(ObjUtil::eFilter_Unk6, appearCollisionInfo);
				appearCollisionInfo.SetLocalPosition({ pParam->RangeAddX, pParam->RangeAddY, pParam->RangeAddZ });
				pCollider->CreateShape(appearCollisionInfo);

				game::ColliSphereShapeCInfo hideCollisionInfo{};
				hideCollisionInfo.ShapeType = game::CollisionShapeType::ShapeType::eShapeType_Sphere;
				hideCollisionInfo.MotionType = game::PhysicsMotionType::MotionType::eMotionType_Value2;
				hideCollisionInfo.Unk2 = 6;
				hideCollisionInfo.ShapeID = 1;
				hideCollisionInfo.Radius = ms_HideCollisionRadius;
				ObjUtil::SetupCollisionFilter(ObjUtil::eFilter_Unk6, hideCollisionInfo);
				pCollider->CreateShape(hideCollisionInfo);

				game::ColliSphereShapeCInfo collisionInfo{};
				collisionInfo.ShapeType = game::CollisionShapeType::ShapeType::eShapeType_Sphere;
				collisionInfo.MotionType = game::PhysicsMotionType::MotionType::eMotionType_Value2;
				collisionInfo.Unk2 = 1;
				collisionInfo.ShapeID = 2;
				collisionInfo.Radius = ms_CollisionRadius;
				ObjUtil::SetupCollisionFilter(ObjUtil::eFilter_Unk9, collisionInfo);
				collisionInfo.SetLocalPosition({ csl::math::Vector3(0.0f, 1.0f, 0.0f) * ms_CollisionRadius });
				pCollider->CreateShape(collisionInfo);
			}

			if (auto* pEnemyTarget = GetComponent<GOCEnemyTarget>())
			{
				pEnemyTarget->Setup({ false });
				pEnemyTarget->SetSphereEyesight(pParam->SearchRange);
				pEnemyTarget->SetEyesightOffset({ pParam->RangeAddX, pParam->RangeAddY, pParam->RangeAddZ });
			}

			if (auto* pEnemyHsm = GetComponent<GOCEnemyHsm>())
			{
				GOCEnemyHsm::Description description{ StateDescriptors, ms_StateCount, ms_DefaultState };
				pEnemyHsm->Setup(description);
			}

			game::GOCSound::SimpleSetup(this, 1, 0);

			if (Flags.test(FLAG_IS_DEACTIVATED))
				GetComponent<game::GOCCollider>()->SetEnable(false);

			fnd::GOComponent::EndSetup(*this);
		}

		bool ProcessMessage(fnd::Message& in_rMessage) override
		{
			if (PreProcessMessage(in_rMessage))
				return true;

			switch (in_rMessage.GetType())
			{
			case xgame::MsgDamage::MessageID:						return ProcMsgDamage(static_cast<xgame::MsgDamage&>(in_rMessage));
			case xgame::MsgNotifyObjectEvent::MessageID:			return ProcMsgNotifyObjectEvent(static_cast<xgame::MsgNotifyObjectEvent&>(in_rMessage));
			case xgame::MsgDlcZeldaNoticeStopEnemy::MessageID:		return ProcMsgDlcZeldaNoticeStopEnemy(static_cast<xgame::MsgDlcZeldaNoticeStopEnemy&>(in_rMessage));
			case xgame::MsgDlcZeldaNoticeActiveEnemy::MessageID:	return ProcMsgDlcZeldaNoticeActiveEnemy(static_cast<xgame::MsgDlcZeldaNoticeActiveEnemy&>(in_rMessage));
			case xgame::MsgHitEventCollision::MessageID:			return ProcMsgHitEventCollision(static_cast<xgame::MsgHitEventCollision&>(in_rMessage));
			case xgame::MsgLeaveEventCollision::MessageID:			return ProcMsgLeaveEventCollision(static_cast<xgame::MsgLeaveEventCollision&>(in_rMessage));
			case xgame::MsgStayTrigger::MessageID:					return ProcMsgStayTrigger(static_cast<xgame::MsgStayTrigger&>(in_rMessage));
			default:												return EnemyBase::ProcessMessage(in_rMessage);
			}
		}

		bool ProcMsgDamage(xgame::MsgDamage& in_rMessage)
		{
			if (Flags.test(FLAG_IS_DEACTIVATED))
				return true;

			if (!ObjUtil::CheckShapeUserID(in_rMessage.SenderShape, 2))
				return false;

			if (!EnemyUtil::IsDamage(in_rMessage.DefensePower, 0, in_rMessage.AttackType))
				return false;

			if (!Flags.test(FLAG_IS_BODY_COLLISION_ENABLED))
				return false;

			if (in_rMessage.SenderType != 2)
				return false;

			csl::math::Vector3 position{ Frame.Unk3.GetTranslation() };
			in_rMessage.SetReply(position, true);
			ObjUtil::AddScore(*this, ms_pScoreName, 0, position);
			
			GetComponent<game::GOCSound>()->Play3D(ms_pDeathSoundName, 0.0f);
			GetComponent<game::GOCCollider>()->SetEnable(false);
			GetComponent<GOCEnemyTarget>()->SetEnableEyesight(false);

			Flags.set(FLAG_IS_DAMAGE_RECEIVED);

			return true;
		}

		bool ProcMsgNotifyObjectEvent(xgame::MsgNotifyObjectEvent& in_rMessage)
		{
			if (in_rMessage.GetEventType() == 0)
				in_rMessage.eventType = 0;

			return Activate(in_rMessage.GetEventType());
		}

		bool ProcMsgDlcZeldaNoticeStopEnemy(xgame::MsgDlcZeldaNoticeStopEnemy& in_rMessage)
		{
			if (Flags.test(FLAG_IS_DAMAGE_RECEIVED))
				return true;

			if (!Activate(false))
				return true;

			KillShots(false);
			Flags.set(FLAG_IS_OBJECT_STOPPED);

			return true;
		}

		bool ProcMsgDlcZeldaNoticeActiveEnemy(xgame::MsgDlcZeldaNoticeActiveEnemy& in_rMessage)
		{
			if (!Flags.test(FLAG_IS_OBJECT_STOPPED))
				return false;

			Flags.reset(FLAG_IS_OBJECT_STOPPED);
			Activate(true);

			return true;
		}

		bool ProcMsgHitEventCollision(xgame::MsgHitEventCollision& in_rMessage)
		{
			if (Flags.test(FLAG_IS_DEACTIVATED))
				return true;

			if (!Flags.test(FLAG_IS_BODY_COLLISION_ENABLED))
				return false;

			if (!ObjUtil::CheckShapeUserID(in_rMessage.pSelf, 2))
				return false;

			xgame::MsgDamage msg{ 3, 8, 1, in_rMessage, { 0.0f, 0.0f, 0.0f } };
			SendMessageImm(in_rMessage.Sender, msg);

			return true;
		}

		bool ProcMsgLeaveEventCollision(xgame::MsgLeaveEventCollision& in_rMessage)
		{
			if (Flags.test(FLAG_IS_DEACTIVATED))
				return true;

			if (ObjUtil::CheckShapeUserID(in_rMessage.Self, 1))
				Flags.set(FLAG_IS_READY_TO_ATTACK);

			if (ObjUtil::CheckShapeUserID(in_rMessage.Self, 0))
				Flags.reset(FLAG_IS_READY_TO_ATTACK);

			return true;
		}

		bool ProcMsgStayTrigger(xgame::MsgStayTrigger& in_rMessage)
		{
			if (Flags.test(FLAG_IS_DEACTIVATED))
				return true;

			if (ObjUtil::CheckShapeUserID(in_rMessage.Unk1, 0))
				Flags.set(FLAG_IS_READY_TO_ATTACK);

			if (ObjUtil::CheckShapeUserID(in_rMessage.Unk1, 1))
				Flags.reset(FLAG_IS_READY_TO_ATTACK);

			return true;
		}

		void AnimationCallback(animation::CharactorAnimation* in_pAnimation, animation::ETriggerValueType in_triggerType, animation::CallbackParam in_param)
		{
			if (in_triggerType == 1)
				RequestShot();
		}

		bool Activate(bool in_activate)
		{
			if (in_activate && Flags.test(FLAG_IS_DEACTIVATED))
			{
				GetComponent<game::GOCCollider>()->SetEnable(true);
				Flags.reset(FLAG_IS_DEACTIVATED);

				return true;
			}
			else if (!Flags.test(FLAG_IS_DEACTIVATED))
			{
				GetComponent<game::GOCCollider>()->SetEnable(false);
				Flags.set(FLAG_IS_DEACTIVATED);
				Flags.reset(FLAG_IS_READY_TO_ATTACK);

				return true;
			}

			return false;
		}

		void SetBodyCollisionEnable(bool in_enable)
		{
			Flags.set(FLAG_IS_BODY_COLLISION_ENABLED, in_enable);
		}

		void RotateTarget(float in_unk1, float in_unk2)
		{
			auto* pPlayerInfo = ObjUtil::GetPlayerInformation(*GetDocument(), 0);
			if (!pPlayerInfo)
				return;

			csl::math::Vector3 playerDirection { LookAtMatrix * csl::math::Vector4(pPlayerInfo->Unk15, 1.0f) };
			playerDirection = { playerDirection - csl::math::Vector3(csl::math::Vector3::UnitY() * playerDirection.dot(csl::math::Vector3::UnitY())) };
			if (!math::Vector3NormalizeIfNotZero(playerDirection, &playerDirection))
				return;

			csl::math::Vector3 forwardVec{ math::Vector3RotateY(RotationAngle, { csl::math::Vector3::UnitZ() }) };
			float distance = acosf(csl::math::Clamp(forwardVec.dot(playerDirection), -1.0f, 1.0f));
			if (in_unk1 > 0.0f)
				distance = csl::math::Min(distance, in_unk1);

			if (in_unk2 > 1.0f)
				distance *= in_unk2;

			RotationAngle += csl::math::Select(csl::math::Vector3::UnitY().cross(forwardVec).dot(playerDirection), fabs(distance), csl::math::Nabs(fabs(distance)));
			Frame.SetLocalRotation({ Eigen::AngleAxisf(RotationAngle, Eigen::Vector3f::UnitY()) });
		}

		void RequestShot()
		{
			AnimListener.IsShotRequested = true;
		}

		void Shot()
		{
			game::ColliSphereShapeCInfo collisionInfo{};
			collisionInfo.ShapeType = game::CollisionShapeType::ShapeType::eShapeType_Sphere;
			collisionInfo.MotionType = game::PhysicsMotionType::MotionType::eMotionType_Value2;
			collisionInfo.Unk2 |= 1;
			collisionInfo.ShapeID = 0;
			collisionInfo.Radius = 3.0f;
			ObjUtil::SetupCollisionFilter(ObjUtil::eFilter_Unk6, collisionInfo);

			auto* pInfo = ObjUtil::GetObjectInfo<EnemyDekunutsInfo>(*GetDocument());

			auto* pVisualModel = static_cast<fnd::GOCVisualModel*>(GetComponent<fnd::GOCVisualContainer>()->Visuals[1]);
			if (!pVisualModel)
				return;

			app::math::Transform muzzleTransform{};
			if (!pVisualModel->GetNodeTransform(0, "Muzzle", &muzzleTransform))
				return;
			
			dekunuts_shot::CreateInfo createInfo{};
			createInfo.TrasnformMtx = math::Matrix34AffineTransformation(muzzleTransform.Position, Frame.Unk3.GetRotationQuaternion());
			createInfo.ShotModel = pInfo->ShotModel;
			createInfo.Speed = 80.0f;
			createInfo.LifeSpan = 3.5f;
			auto* pShotObject = dekunuts_shot::Create(createInfo, GetDocument(), GetAllocator());
			if (!pShotObject)
				return;
		
			for (size_t i = 0; i < ms_MaxShotCount; i++)
			{
				if (!ShotHandles[i].IsValid())
				{
					ShotHandles[i] = pShotObject;
					GetComponent<game::GOCSound>()->Play3D(ms_pShotSoundName, 0.0f);

					break;
				}
			}
		}

		void KillShots(bool in_isExploded)
		{
			for (auto& handle : ShotHandles)
			{
				if (auto* pShot = handle.Get())
				{
					if (in_isExploded)
						pShot->Explosion();
					else
						pShot->Kill();
				}
			}
		}

		void SetAnimation(uint in_animationNo)
		{
			for (size_t i = 0; i < ms_AnimationCount; i++)
				static_cast<game::GOCAnimationScript*>(GetComponent<game::GOCAnimationContainer>()->Get(i))->ChangeAnimation(ms_pAnimationNames[in_animationNo]);
		}

		bool IsCurrentAnimation(uint in_animationNo) const
		{
			for (size_t i = 0; i < ms_AnimationCount; i++)
			{
				if (!static_cast<game::GOCAnimationScript*>(GetComponent<game::GOCAnimationContainer>()->Get(i))->IsCurrentAnimation(ms_pAnimationNames[in_animationNo]))
					return false;
			}

			return true;
		}

		bool IsEndAnimation(size_t in_animationNo) const
		{
			if (!IsCurrentAnimation(in_animationNo))
				return false;
		
			for (size_t i = 0; i < ms_AnimationCount; i++)
			{
				if (!static_cast<game::GOCAnimationScript*>(GetComponent<game::GOCAnimationContainer>()->Get(i))->IsFinished())
					return false;
			}

			return true;
		}

		class State
		{
		public:
			class Hide : public EnemyState<EnemyDekunuts>
			{
			public:
				typedef EnemyDekunuts context_type;

				Hide()
				{

				}

				void OnEnter(EnemyDekunuts& in_rObj, int in_unk) override;
				bool Step(EnemyDekunuts& in_rObj, float in_deltaTime) override;
			};

			class Appear : public EnemyState<EnemyDekunuts>
			{
			private:
				inline static const char* ms_pAppearSoundName = "enm_dekunuts_appear";

			public:
				typedef EnemyDekunuts context_type;

				float ElapsedTime{};

				Appear()
				{

				}

				void OnEnter(EnemyDekunuts& in_rObj, int in_unk) override;
				bool Step(EnemyDekunuts& in_rObj, float in_deltaTime) override;
			};

			class Retreat : public EnemyState<EnemyDekunuts>
			{
			private:
				inline static const char* ms_pRetreatSoundName = "enm_dekunuts_appear";

			public:
				typedef EnemyDekunuts context_type;

				float ElapsedTime{};

				Retreat()
				{

				}

				void OnEnter(EnemyDekunuts& in_rObj, int in_unk) override;
				bool Step(EnemyDekunuts& in_rObj, float in_deltaTime) override;
			};

			class Attack : public EnemyState<EnemyDekunuts>
			{
			public:
				typedef EnemyDekunuts context_type;

				float RemainingTime{};

				Attack()
				{

				}

				void OnEnter(EnemyDekunuts& in_rObj, int in_unk) override;
				bool Step(EnemyDekunuts& in_rObj, float in_deltaTime) override;
			};

			class Disappear : public EnemyState<EnemyDekunuts>
			{
			private:
				inline static const char* ms_pDisappearSoundName = "enm_dekunuts_appear";

			public:
				typedef EnemyDekunuts context_type;

				Disappear()
				{

				}
				
				void OnEnter(EnemyDekunuts& in_rObj, int in_unk) override;
				bool Step(EnemyDekunuts& in_rObj, float in_deltaTime) override;
			};
		};

		inline static ut::internal::StateDescImpl States[] =
		{
			{ "Hide", (ut::internal::StateCreate_t)&ut::StateCreatorFuncTemplate<EnemyDekunuts::State::Hide>::Create, -1 },
			{ "Appear", (ut::internal::StateCreate_t)&ut::StateCreatorFuncTemplate<EnemyDekunuts::State::Appear>::Create, -1 },
			{ "Retreat", (ut::internal::StateCreate_t)&ut::StateCreatorFuncTemplate<EnemyDekunuts::State::Retreat>::Create, -1 },
			{ "Attack", (ut::internal::StateCreate_t)&ut::StateCreatorFuncTemplate<EnemyDekunuts::State::Attack>::Create, -1 },
			{ "Disappear", (ut::internal::StateCreate_t)&ut::StateCreatorFuncTemplate<EnemyDekunuts::State::Disappear>::Create, -1 },
		};

		inline static GOCEnemyHsm::StateDesc StateDescriptors[] =
		{
			{ 0, &States[0] },
			{ 1, &States[1] },
			{ 2, &States[2] },
			{ 3, &States[3] },
			{ 4, &States[4] },
		};
	};
}