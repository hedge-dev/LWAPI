#pragma once

namespace app
{
	class EnemyPiranhaPlant : public EnemyBase
	{
	private:
		inline static csl::math::Vector3 ms_CenterOffset = { 0.0f, 2.5f, 0.0f };
		inline static csl::math::Vector3 ms_CollisionOffset = { 7.0f, 0.0f, 0.0f };
		inline static csl::math::Vector3 ms_EyesightOffset = { 0.0f, 5.0f, 0.0f };
		inline static const char* ms_pSoundName = "enm_pakkunflower_bite";
		inline static const size_t ms_ShapeCount = 3;
		inline static const float ms_ShadowRadius = 4.0f;
		inline static size_t ms_StateCount = 5;
		inline static int ms_DefaultState = 0;

	public:
		class AnimListener : public animation::AnimationListener
		{
		public:
			EnemyPiranhaPlant* pOwner{};

			void OnEvent(animation::NotifyTiming timing) override
			{
				if (!pOwner)
					return;
			
				pOwner->AfterUpdatePoseCallback();
			}
		};

		AnimListener Listener{};
		fnd::HFrame Frame{};
		float HeadRotation{ -(MATHF_PI / 2.0f) };
		float Scale{ 1.0f };
		uint PlayerNo{ static_cast<uint>(-1) };
		csl::ut::Bitset<byte> Flags{};

		EnemyPiranhaPlant() : EnemyBase()
		{
			Listener.Timing = 2;
		}

		void AddCallback(GameDocument* in_pDocument) override
		{
			fnd::GOComponent::Create<fnd::GOCVisualModel>(*this);
			fnd::GOComponent::Create<game::GOCAnimationScript>(*this);
			fnd::GOComponent::Create<game::GOCShadowSimple>(*this);
			fnd::GOComponent::Create<game::GOCEffect>(*this);
			fnd::GOComponent::Create<game::GOCSound>(*this);
			fnd::GOComponent::Create<game::GOCCollider>(*this);
			fnd::GOComponent::Create<GOCEnemyTarget>(*this);
			fnd::GOComponent::Create<GOCEnemyHsm>(*this);

			fnd::GOComponent::BeginSetup(*this);

			auto* pInfo = ObjUtil::GetObjectInfo<EnemyPiranhaPlantInfo>(*in_pDocument);
			auto* pParam = GetAdapter()->GetData<SPiranhaPlantParam>();

			Flags.set(0, !pParam->Direction);
	
			auto* pTransform = GetComponent<fnd::GOCTransform>();
			if (pTransform->IsExistParent())
			{
				pTransform->SetInheriteFlags(1);
				CreateCenterPositionFrame(ms_CenterOffset);
				GetCenterPositionFrame()->AddChild(&Frame);
				Flags.set(4);
			}
			else
			{
				CreateCenterPositionFrame({ 0.0f, 0.0f, 0.0f });
				GetCenterPositionFrame()->AddChild(&Frame);
			}

			if (auto* pVisualModel = GetComponent<fnd::GOCVisualModel>())
			{
				fnd::GOCVisualModel::Description description{};
				description.Model = pInfo->Model;
				description.Skeleton = pInfo->Skeleton;
				description.field_0C |= 0x400000u;
				description.pParent = GetCenterPositionFrame();

				pVisualModel->Setup(description);
				auto* pTexSrtControl = pVisualModel->SetTexSrtAnimation({pInfo->TextureAnimation, 1});
				pTexSrtControl->SetSpeed(0.0f);

				if (auto* pAnimationScript = GetComponent<game::GOCAnimationScript>())
				{
					pAnimationScript->Setup({ &pInfo->AnimationContainer });
					pVisualModel->AttachAnimation(pAnimationScript);

					if (Flags.test(0))
						pAnimationScript->SetAnimation("IDLE_L");
					else
						pAnimationScript->SetAnimation("IDLE_R");

					Listener.pOwner = this;
					pAnimationScript->AddListener(&Listener);

					pAnimationScript->RegisterCallback(1, animation::CreateAnimCallback<EnemyPiranhaPlant>(this, &app::EnemyPiranhaPlant::SoundCallback, GetAllocator()));
				}
			}

			if (auto* pShadowSimple = GetComponent<game::GOCShadowSimple>())
			{
				game::ShadowSphereShapeCInfo shadowInfo{ ms_ShadowRadius };
				game::GOCShadowSimple::Description description{ &shadowInfo };
				pShadowSimple->Setup(description);

				if (Flags.test(4))
					pShadowSimple->SetVisible(false);
			}

			if (GetComponent<game::GOCEffect>())
				game::GOCEffect::SimpleSetup(this);

			game::GOCSound::SimpleSetup(this, 1, 0);

			if (auto* pCollider = GetComponent<game::GOCCollider>())
			{
				pCollider->Setup({ ms_ShapeCount });
				game::ColliSphereShapeCInfo collisionInfo{};
				collisionInfo.ShapeType = game::CollisionShapeType::ShapeType::eShapeType_Sphere;
				collisionInfo.MotionType = game::PhysicsMotionType::MotionType::eMotionType_Value2;
				collisionInfo.Unk2 |= 3;
				collisionInfo.ShapeID = 0;
				collisionInfo.Radius = pParam->searchRadius;
				ObjUtil::SetupCollisionFilter(ObjUtil::eFilter_Unk6, collisionInfo);
				pCollider->CreateShape(collisionInfo);

				collisionInfo = {};
				collisionInfo.ShapeType = game::CollisionShapeType::ShapeType::eShapeType_Sphere;
				collisionInfo.MotionType = game::PhysicsMotionType::MotionType::eMotionType_Value2;
				collisionInfo.Unk2 |= 1;
				collisionInfo.ShapeID = 1;
				collisionInfo.Radius = 6.0f;
				ObjUtil::SetupCollisionFilter(ObjUtil::eFilter_Unk9, collisionInfo);
				pCollider->CreateShape(collisionInfo);

				collisionInfo = {};
				collisionInfo.ShapeType = game::CollisionShapeType::ShapeType::eShapeType_Sphere;
				collisionInfo.MotionType = game::PhysicsMotionType::MotionType::eMotionType_Value2;
				collisionInfo.Unk2 |= 1;
				collisionInfo.ShapeID = 2;
				collisionInfo.Radius = 3.0f;
				collisionInfo.pParent = &Frame;
				collisionInfo.SetLocalPosition(ms_CollisionOffset);
				ObjUtil::SetupCollisionFilter(ObjUtil::eFilter_Unk9, collisionInfo);
				pCollider->CreateShape(collisionInfo);
			}

			if (auto* pEnemyTarget = GetComponent<GOCEnemyTarget>())
			{
				pEnemyTarget->Setup({ false });
				pEnemyTarget->SetColliderEyesight(0);
				pEnemyTarget->SetEyesightOffset(ms_EyesightOffset);
			}

			if (auto* pEnemyHsm = GetComponent<GOCEnemyHsm>())
			{
				GOCEnemyHsm::Description description{ StateDescriptors, ms_StateCount, ms_DefaultState };
				pEnemyHsm->Setup(description);
			}

			fnd::GOComponent::EndSetup(*this);
		}

		bool ProcessMessage(fnd::Message& in_rMessage) override
		{
			if (PreProcessMessage(in_rMessage))
				return true;

			switch (in_rMessage.GetType())
			{
			case xgame::MsgDamage::MessageID:					return ProcMsgDamage(static_cast<xgame::MsgDamage&>(in_rMessage));
			case xgame::MsgHitEventCollision::MessageID:		return ProcMsgHitEventCollision(static_cast<xgame::MsgHitEventCollision&>(in_rMessage));
			default:											return EnemyBase::ProcessMessage(in_rMessage);
			}
		}

		bool ProcMsgDamage(xgame::MsgDamage& in_rMessage)
		{
			if (in_rMessage.SenderType == 3)
			{
				GetComponent<GOCEnemyHsm>()->Dispatch(in_rMessage);
			}
			else if (in_rMessage.Bonus.Unk1 == 3)
			{
				auto* pPlayerInfo = ObjUtil::GetPlayerInformation(*GetDocument(), 0);
				if (!pPlayerInfo || pPlayerInfo->PixieNo == Game::EPhantomType::ePhantom_Bomb)
					return false;

				GetComponent<GOCEnemyHsm>()->Dispatch(in_rMessage);
			}

			return true;
		}

		bool ProcMsgHitEventCollision(xgame::MsgHitEventCollision& in_rMessage)
		{
			if (!Flags.test(3))
				return false;

			if (ObjUtil::CheckShapeUserID(in_rMessage.pSelf, 0))
				return true;

			xgame::MsgDamage msg{ 3, 8, 3, in_rMessage, { 0.0f, 0.0f, 0.0f } };
			SendMessageImm(in_rMessage.Sender, msg);

			return true;
		}

		void SoundCallback(animation::CharactorAnimation* in_pAnimation, animation::ETriggerValueType in_triggerType, animation::CallbackParam in_param)
		{
			if (in_triggerType || in_param.Int)
				return;

			if (auto* pSound = GetComponent<game::GOCSound>())
				pSound->Play3D(ms_pSoundName, 0.0f);
		}

		void AfterUpdatePoseCallback()
		{
			auto* pVisualModel = GetComponent<fnd::GOCVisualModel>();

			float angle = HeadRotation / 4.0f;
			if (!Flags.test(2))
				angle = fabs(angle);

			for (size_t i = 2; i <= 5; i++)
			{
				char buff[8]{};
				csl::fnd::Snprintf(buff, sizeof(buff), "Body%d", i);

				math::Transform transform{};
				if (!pVisualModel->GetNodeTransform(2, buff, &transform))
					continue;

				transform.Rotation = { Eigen::AngleAxisf(angle, csl::math::Vector3::UnitY()) };
				transform.SetFlag(1);

				pVisualModel->SetNodeTransform(2, buff, transform);
			}

			math::Transform transform{};
			if (pVisualModel->GetNodeTransform(1, "Head", &transform))
				Frame.SetLocalTransform(transform.GetTransformMatrix());
		}

		void SetEnableCollision(bool in_enable)
		{
			ObjUtil::SetEnableColliShape(GetComponent<game::GOCCollider>(), 2, in_enable);
			ObjUtil::SetEnableColliShape(GetComponent<game::GOCCollider>(), 1, in_enable);
		}

		void SetEnableDamageCollision(bool in_enable)
		{
			Flags.set(3, in_enable);
			ObjUtil::SetEnableColliShape(GetComponent<game::GOCCollider>(), 2, in_enable);
		}

		void SetScale(float in_scale)
		{
			GetComponent<fnd::GOCVisualModel>()->SetLocalScale({ in_scale, in_scale, in_scale });
			GetComponent<game::GOCShadowSimple>()->SetScale({ in_scale, in_scale, in_scale });

			Scale = in_scale;
		}

		class State
		{
		private:
			inline static const char* ms_pSoundName = "enm_pakkunflower_down";

		public:
			class Idle : public EnemyState<EnemyPiranhaPlant>
			{
			public:
				typedef EnemyPiranhaPlant context_type;

				GOCEnemyTarget* pEnemyTargetGoc{};

				Idle()
				{

				}

				void OnEnter(EnemyPiranhaPlant& in_rObj, int in_unk) override;
				bool Step(EnemyPiranhaPlant& in_rObj, float in_deltaTime) override;
				bool ProcessMessage(GameObject& in_rObj, fnd::Message& in_rMessage) override;
				bool ProcMsgDamage(EnemyPiranhaPlant& in_rObj, xgame::MsgDamage& in_rMessage);
			};

			class ShiftAttack : public EnemyState<EnemyPiranhaPlant>
			{
			public:
				typedef EnemyPiranhaPlant context_type;

				float ElapsedTime{};

				ShiftAttack()
				{

				}

				void OnEnter(EnemyPiranhaPlant& in_rObj, int in_unk) override;
				bool Step(EnemyPiranhaPlant& in_rObj, float in_deltaTime) override;
				bool ProcessMessage(GameObject& in_rObj, fnd::Message& in_rMessage) override;
				bool ProcMsgDamage(EnemyPiranhaPlant& in_rObj, xgame::MsgDamage& in_rMessage);
			};

			class Attack : public EnemyState<EnemyPiranhaPlant>
			{
			public:
				typedef EnemyPiranhaPlant context_type;

				GOCEnemyTarget* pEnemyTargetGoc{};

				Attack()
				{

				}

				void OnEnter(EnemyPiranhaPlant& in_rObj, int in_unk) override;
				bool Step(EnemyPiranhaPlant& in_rObj, float in_deltaTime) override;
				bool ProcessMessage(GameObject& in_rObj, fnd::Message& in_rMessage) override;
				bool ProcMsgDamage(EnemyPiranhaPlant& in_rObj, xgame::MsgDamage& in_rMessage);
			};

			class ShiftIdle : public EnemyState<EnemyPiranhaPlant>
			{
			public:
				typedef EnemyPiranhaPlant context_type;

				float ElapsedTime{};

				ShiftIdle()
				{

				}

				void OnEnter(EnemyPiranhaPlant& in_rObj, int in_unk) override;
				bool Step(EnemyPiranhaPlant& in_rObj, float in_deltaTime) override;
				bool ProcessMessage(GameObject& in_rObj, fnd::Message& in_rMessage) override;
				bool ProcMsgDamage(EnemyPiranhaPlant& in_rObj, xgame::MsgDamage& in_rMessage);
			};

			class Dead : public EnemyState<EnemyPiranhaPlant>
			{
			public:
				typedef EnemyPiranhaPlant context_type;

				enum SubState
				{
					eSubState_Freeze,
					eSubState_Hit,
					eSubState_Shrink,
					eSubState_Dead,
				};

				csl::ut::Enum<SubState, byte> State{};
				float ElapsedTime{};
				float HeadRotation{};
				float Scale{};

				Dead()
				{

				}

				void ChangeSubState(SubState in_subState);
				void OnEnter(EnemyPiranhaPlant& in_rObj, int in_unk) override;
				bool Step(EnemyPiranhaPlant& in_rObj, float in_deltaTime) override;
			};

			static void UpdateHeadPosture(EnemyPiranhaPlant& in_rObj, bool in_changeAnimation);
		};

		inline static ut::internal::StateDescImpl States[] =
		{
			{ "Idle", (ut::internal::StateCreate_t)&ut::StateCreatorFuncTemplate<EnemyPiranhaPlant::State::Idle>::Create, -1 },
			{ "ShiftAttack", (ut::internal::StateCreate_t)&ut::StateCreatorFuncTemplate<EnemyPiranhaPlant::State::ShiftAttack>::Create, -1 },
			{ "Attack", (ut::internal::StateCreate_t)&ut::StateCreatorFuncTemplate<EnemyPiranhaPlant::State::Attack>::Create, -1 },
			{ "ShiftIdle", (ut::internal::StateCreate_t)&ut::StateCreatorFuncTemplate<EnemyPiranhaPlant::State::ShiftIdle>::Create, -1 },
			{ "Dead", (ut::internal::StateCreate_t)&ut::StateCreatorFuncTemplate<EnemyPiranhaPlant::State::Dead>::Create, -1 },
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