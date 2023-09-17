#pragma once

namespace app
{
	class EnemyShyGuy : public EnemyBase
	{
	private:
		inline static const char* ms_pScoreName = "SHYGUY";
		inline static const char* ms_pStepSoundNames[] = { "enm_heyho_voice_ho", "enm_heyho_voice_hey" };
		inline static const char* ms_pFootStepSoundName = "enm_heyho_foot";
		inline static csl::math::Vector3 ms_LockonOffset = { 0.0f, 5.0f, 0.0f };
		inline static csl::math::Vector3 ms_Scale = { 1.0f, 1.0f, 1.0f };
		inline static size_t ms_ShapeCount = 1;
		inline static float ms_CollisionRadius = 4.0f;
		inline static float ms_ShadowRadius = 4.0f;
		inline static size_t ms_StateCount = 3;
		inline static int ms_DefaultState = -1;

	public:
		csl::ut::Bitset<uint8> Flags{};

	public:
		EnemyShyGuy() : EnemyBase()
		{
			ObjUtil::SetPropertyLockonTarget(this);
		}

		void AddCallback(GameDocument& in_rDocument) override
		{
			fnd::GOComponent::Create<game::GOCGravity>(*this);
			fnd::GOComponent::Create<fnd::GOCVisualModel>(*this);
			fnd::GOComponent::Create<game::GOCAnimationScript>(*this);
			fnd::GOComponent::Create<game::GOCShadowSimple>(*this);
			fnd::GOComponent::Create<game::GOCEffect>(*this);
			fnd::GOComponent::Create<game::GOCSound>(*this);
			fnd::GOComponent::Create<game::GOCCollider>(*this);
			fnd::GOComponent::Create<GOCEnemyHsm>(*this);
			fnd::GOComponent::Create<game::GOCMovementComplex>(*this);

			fnd::GOComponent::BeginSetup(*this);

			auto* pParam = GetAdapter()->GetData<SShyGuyParam>();
			auto* pInfo = ObjUtil::GetObjectInfo<EnemyShyGuyInfo>(in_rDocument);

			Flags.set(0, pParam->IsEventDriven);
			Flags.set(2, pParam->Direction == SShyGuyParam::Direction::LEFT);

			CreateCenterPositionFrame(ms_LockonOffset);

			if (auto* pVisualModel = GetComponent<fnd::GOCVisualModel>())
			{
				fnd::GOCVisualModel::Description description{};
				description.m_Model = pInfo->Model;
				description.m_Skeleton = pInfo->Skeleton;
				description.field_0C |= 0x400000u;
				description.zOffset = pParam->DepthOffset;

				pVisualModel->Setup(description);
				pVisualModel->SetLocalScale(ms_Scale);

				if (auto* pAnimationScript = GetComponent<game::GOCAnimationScript>())
				{
					pAnimationScript->Setup({ &pInfo->AnimationContainer });
					pVisualModel->AttachAnimation(pAnimationScript);

					pAnimationScript->RegisterCallback(1, animation::CreateAnimCallback<EnemyShyGuy>(this, &app::EnemyShyGuy::SoundCallback, GetAllocator()));
				}
			}

			if (auto* pShadowSimple = GetComponent<game::GOCShadowSimple>())
			{
				game::ShadowHemisphereShapeCInfo shadowInfo{ ms_ShadowRadius };
				game::GOCShadowSimple::Description description{ &shadowInfo };
				pShadowSimple->Setup(description);
			}
			
			if (GetComponent<game::GOCEffect>()) game::GOCEffect::SimpleSetup(this, 0, false);
			if (GetComponent<game::GOCSound>()) game::GOCSound::SimpleSetup(this, 0, 0);

			if (auto* pCollider = GetComponent<game::GOCCollider>())
			{
				pCollider->Setup({ ms_ShapeCount });
				game::ColliSphereShapeCInfo collisionInfo{};
				collisionInfo.m_ShapeType = game::CollisionShapeType::ShapeType::ShapeType_Sphere;
				collisionInfo.m_MotionType = game::PhysicsMotionType::MotionType::MotionType_VALUE2;
				collisionInfo.m_Unk2 |= 1;
				collisionInfo.m_Unk3 = 0x20000;
				collisionInfo.m_Radius = ms_CollisionRadius;
				collisionInfo.m_pParent = GetCenterPositionFrame();
				ObjUtil::SetupCollisionFilter(ObjUtil::eFilter_Unk9, collisionInfo);

				pCollider->CreateShape(collisionInfo);
			}

			if (GetComponent<game::GOCGravity>()) game::GOCGravity::SimpleSetup(this, 1);

			if (auto* pMovement = GetComponent<game::GOCMovementComplex>())
			{
				auto rotation = GetAdapter()->GetRotation();

				csl::math::Vector3 velocity{ math::Vector3Rotate(rotation, { csl::math::Vector3::UnitZ() }) };

				if (auto* pMoveStraight = pMovement->SetMoveController<game::MoveStraight>())
				{
					game::MoveStraight::SetupParam param{};
					param.Position = GetAdapter()->GetPosition();
					param.Rotation = GetAdapter()->GetRotation();
					param.CheckPositionOffset = { 0.0f, 5.0f, 6.0f };
					param.Unk8 = { 0.0f, 0.0f, 10.0f };
					param.Unk9 = { 0.0f, 0.0f, 3.0f };

					pMoveStraight->SetupParameter(param);
					pMoveStraight->SetMaxMoveDistance(pParam->MaxMoveDistance, 0.0f);

					game::MoveStraightCallback callback{ &EnemyShyGuy::NotifyMovementStopCallback };
					pMoveStraight->SetNotifyStopCallback(callback);
				}

				pMovement->GetContextParam()->Velocity = { velocity * pParam->Speed };
			}

			if (auto* pEnemyHsm = GetComponent<GOCEnemyHsm>())
			{
				GOCEnemyHsm::Description description{ StateDescriptors, ms_StateCount, ms_DefaultState };
				
				if (Flags.test(0))
					description.DefaultStateID = 2;
				else
					description.DefaultStateID = 0;

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
			case xgame::MsgKick::MessageID:						return ProcMsgKick(static_cast<xgame::MsgKick&>(in_rMessage));
			case xgame::MsgNotifyObjectEvent::MessageID:		return ProcMsgNotifyObjectEvent(static_cast<xgame::MsgNotifyObjectEvent&>(in_rMessage));
			default:											return EnemyBase::ProcessMessage(in_rMessage);
			}
		}

		bool ProcMsgDamage(xgame::MsgDamage& in_rMessage)
		{
			in_rMessage.SetReply(GetComponent<fnd::GOCTransform>()->m_Frame.m_Unk3.GetTranslation(), 1);
			ObjUtil::AddScore(*this, ms_pScoreName, in_rMessage);
			enemy::DeadEffectCInfo deadEffectInfo{};
			deadEffectInfo.Owner = this;
			deadEffectInfo.SetMsgDamage(in_rMessage);
			deadEffectInfo.SetYoshiIsland();

			auto* pVisualModel = GetComponent<fnd::GOCVisualModel>();
			if (!pVisualModel)
				return false;

			app::math::Transform spineTransform{};
			if (!pVisualModel->GetNodeTransform(0, "Spine", &spineTransform))
				return false;

			deadEffectInfo.SetTransform(spineTransform.GetTransformMatrix());

			CreateDeadEffect(deadEffectInfo);
			ProcMission(in_rMessage);
			SetStatusRetire();
			Kill();

			return true;
		}

		bool ProcMsgHitEventCollision(xgame::MsgHitEventCollision& in_rMessage)
		{
			SendTouchDamage(in_rMessage);
			
			return true;
		}

		bool ProcMsgKick(xgame::MsgKick& in_rMessage)
		{
			auto* pInfo = ObjUtil::GetObjectInfo<EnemyShyGuyInfo>(*GetDocument());
			
			EnemyBlowOffObjectCInfo blowOffInfo{};
			blowOffInfo.SetParamByMessage(in_rMessage);
			blowOffInfo.Model = pInfo->Model;
			blowOffInfo.Skeleton = pInfo->Skeleton;
			blowOffInfo.Animation = pInfo->Animations[!Flags.test(2)];
			blowOffInfo.CollisionRadius = ms_CollisionRadius;
			blowOffInfo.TrsMatrix = GetComponent<fnd::GOCTransform>()->m_Frame.m_Unk3.m_Mtx;
			blowOffInfo.Offset = { 0.0f, 5.0f, 0.0f };
			blowOffInfo.Size = (EnemyBlowOffObjectCInfo::EffectSize)3;

			CreateEnemyBlowOffObject(blowOffInfo);
			in_rMessage.SetReplyForSucceed();
			ObjUtil::AddScore(*this, "SHYGUY", in_rMessage);
			SetStatusRetire();
			Kill();
			
			return true;
		}

		bool ProcMsgNotifyObjectEvent(xgame::MsgNotifyObjectEvent& in_rMessage)
		{
			if (!Flags.test(0))
				return true;

			if (auto* pEnemyHsm = GetComponent<GOCEnemyHsm>()) pEnemyHsm->Dispatch(in_rMessage);
		}

		void SoundCallback(animation::CharactorAnimation* in_pAnimation, animation::ETriggerValueType in_triggerType, animation::CallbackParam in_param)
		{
			if (in_triggerType)
				return;

			if (auto* pSound = GetComponent<game::GOCSound>())
			{
				pSound->Play3D(ms_pFootStepSoundName, 0.0f);
				pSound->Play3D(ms_pStepSoundNames[in_param.m_Int], 0.0f);
			}
		}

		void NotifyMovementStopCallback()
		{
			Flags.set(1);
		}

		class State
		{
		public:
			class Move : public EnemyState<EnemyShyGuy>
			{
			public:
				typedef EnemyShyGuy context_type;

				Move()
				{

				}

				void OnEnter(EnemyShyGuy& in_rObj, int in_unk) override;
				bool Step(EnemyShyGuy& in_rObj, float in_deltaTime) override;
			};

			class Turnaround : public EnemyState<EnemyShyGuy>
			{
			public:
				typedef EnemyShyGuy context_type;

				enum SubState : byte
				{
					eSubState_Enter,
					eSubState_Turn,
					eSubState_Leave,
					eSubState_MAX
				};

				SubState State;
				float ElapsedTime{};
				int LookCount{};
				csl::math::Quaternion Rotation{};
				bool IsLooking{};

				Turnaround()
				{

				}

				void ChangeSubState(SubState in_subState);
				void OnEnter(EnemyShyGuy& in_rObj, int in_unk) override;
				void OnLeave(EnemyShyGuy& in_rObj, int in_unk) override;
				bool Step(EnemyShyGuy& in_rObj, float in_deltaTime) override;
			};

			class Stop : public EnemyState<EnemyShyGuy>
			{
			public:
				typedef EnemyShyGuy context_type;

				Stop()
				{

				}

				void OnEnter(EnemyShyGuy& in_rObj, int in_unk) override;
				void OnLeave(EnemyShyGuy& in_rObj, int in_unk) override;
				bool Step(EnemyShyGuy& in_rObj, float in_deltaTime) override;
				bool ProcessMessage(GameObject& in_rObj, fnd::Message& in_rMessage) override;
				bool ProcMsgNotifyObjectEvent(GameObject& in_rObj, xgame::MsgNotifyObjectEvent& in_rMessage);
			};
		};

		inline static ut::internal::StateDescImpl States[] =
		{
			{ "Move", (ut::internal::StateCreate_t)&ut::StateCreatorFuncTemplate<EnemyShyGuy::State::Move>::Create, -1 },
			{ "Turnaround", (ut::internal::StateCreate_t)&ut::StateCreatorFuncTemplate<EnemyShyGuy::State::Turnaround>::Create, -1 },
			{ "Stop", (ut::internal::StateCreate_t)&ut::StateCreatorFuncTemplate<EnemyShyGuy::State::Stop>::Create, -1 }
		};

		inline static GOCEnemyHsm::StateDesc StateDescriptors[] =
		{
			{ 0, &States[0] },
			{ 1, &States[1] },
			{ 2, &States[2] },
		};
	};
}