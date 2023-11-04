#pragma once

namespace app
{
	class EnemyKeese : public EnemyBase
	{
	protected:

	private:
		inline static const size_t ms_ShadowCount = 1;
		inline static const size_t ms_ShapeCount = 2;
		inline static const size_t ms_StateCount = 5;
		inline static const size_t ms_DefaultStateIndex = 0;
		inline static const float ms_ShadowRadius = 4.5f;
		inline static const float ms_HitCollisionRadius = 5.0f;
		inline static const csl::math::Vector3 ms_CenterPosition{ 0.0f, 5.0f, 0.0f };
		inline static const csl::math::Vector3 ms_VisualScale{ 2.0f, 2.0f, 2.0f };
		inline static const char* ms_pScoreName = "KEESE";
		inline static const char* ms_pCenterNodeName = "center";
		inline static const char* ms_pFlySoundName = "enm_keese_fly";

	public:
		MoveEnemyKeese* pMovementController {};
		game::PathEvaluator Path{};
		float MoveRange{ 100.0f };
		float MoveRangeOffset{};
		float PathDistance{};
		float SearchRange{ 100.0f };
		float MoveSpeed{ 30.0f };
		float FallSpeed{ 50.0f };
		float FallDistance{ 50.0f };

		EnemyKeese() : EnemyBase()
		{
			ObjUtil::SetPropertyLockonTarget(this);
		}

		void AddCallback(GameDocument* in_pDocument) override
		{
			fnd::GOComponent::Create<game::GOCGravity>(*this);
			fnd::GOComponent::Create<fnd::GOCVisualModel>(*this);
			fnd::GOComponent::Create<game::GOCAnimationScript>(*this);
			fnd::GOComponent::Create<game::GOCShadow>(*this);
			fnd::GOComponent::Create<game::GOCSound>(*this);
			fnd::GOComponent::Create<game::GOCCollider>(*this);
			fnd::GOComponent::Create<game::GOCMovementComplex>(*this);
			fnd::GOComponent::Create<GOCEnemyTarget>(*this);
			fnd::GOComponent::Create<GOCEnemyHsm>(*this);

			fnd::GOComponent::BeginSetup(*this);

			auto* pInfo = ObjUtil::GetObjectInfo<EnemyKeeseInfo>(*in_pDocument);
			auto* pParam = GetAdapter()->GetData<SKeeseParam>();
			
			MoveSpeed = pParam->MoveSpeed;
			MoveRange = pParam->MoveRange;
			MoveRangeOffset = pParam->MoveRangeOffset;
			FallSpeed = pParam->FallSpeed;
			FallDistance = pParam->FallDistance;
			SearchRange = pParam->SearchRange;

			CreateCenterPositionFrame(ms_CenterPosition);

			game::GOCGravity::SimpleSetup(this, 1);

			if (auto* pVisualGoc = GetComponent<fnd::GOCVisualModel>())
			{
				fnd::GOCVisualModel::Description description{};
				description.Model = pInfo->Model;
				description.Skeleton = pInfo->Skeleton;
				description.Unk2 |= 0x400000;

				pVisualGoc->Setup(description);
				pVisualGoc->SetLocalRotation({ Eigen::AngleAxisf(MATHF_PI, csl::math::Vector3::UnitZ()) });
				pVisualGoc->SetLocalScale(ms_VisualScale);

				if (auto* pAnimationGoc = GetComponent<game::GOCAnimationScript>())
				{
					pAnimationGoc->Setup({ &pInfo->AnimationContainer });
					pVisualGoc->AttachAnimation(pAnimationGoc);

					pAnimationGoc->RegisterCallback(0, animation::CreateAnimCallback<EnemyKeese>(this, &app::EnemyKeese::AnimationCallback, GetAllocator()));
				}
			}

			if (auto* pShadowGoc = GetComponent<game::GOCShadow>())
			{
				pShadowGoc->Setup(ms_ShadowCount);
			
				game::ShadowSphereShapeCInfo shadowInfo{ ms_ShadowRadius };
				shadowInfo.Unk2 = 5;

				if (auto* pShape = pShadowGoc->CreateShape(shadowInfo))
					pShape->SetMaxDownDist(200.0f);
			}

			game::GOCSound::SimpleSetup(this, 0, 0);

			if (auto* pColliderGoc = GetComponent<game::GOCCollider>())
			{
				pColliderGoc->Setup({ ms_ShapeCount });
				game::ColliSphereShapeCInfo hitCollisionInfo{};
				hitCollisionInfo.ShapeType = game::CollisionShapeType::ShapeType::eShapeType_Sphere;
				hitCollisionInfo.MotionType = game::PhysicsMotionType::MotionType::eMotionType_Value2;
				hitCollisionInfo.Unk2 |= 1;
				hitCollisionInfo.Unk3 = 0x20000;
				hitCollisionInfo.ShapeID = 0;
				hitCollisionInfo.Radius = ms_HitCollisionRadius;
				hitCollisionInfo.pParent = GetCenterPositionFrame();
				ObjUtil::SetupCollisionFilter(ObjUtil::eFilter_Unk9, hitCollisionInfo);
				pColliderGoc->CreateShape(hitCollisionInfo);

				game::ColliBoxShapeCInfo searchCollisionInfo{};
				searchCollisionInfo.ShapeType = game::CollisionShapeType::ShapeType::eShapeType_Box;
				searchCollisionInfo.MotionType = game::PhysicsMotionType::MotionType::eMotionType_Value2;
				searchCollisionInfo.Unk2 |= 3;
				searchCollisionInfo.ShapeID = 1;
				searchCollisionInfo.Size = { pParam->SearchRange / 2.0f, pParam->SearchRange / 2.0f, pParam->SearchDistance / 2.0f };
				searchCollisionInfo.SetLocalPosition({ 0.0f, pParam->SearchRange / 2.0f, 0.0f });
				ObjUtil::SetupCollisionFilter(ObjUtil::eFilter_Unk6, searchCollisionInfo);
				pColliderGoc->CreateShape(searchCollisionInfo);
			}

			if (auto* pMovementGoc = GetComponent<game::GOCMovementComplex>())
			{
				if (pMovementController = pMovementGoc->SetMoveController<MoveEnemyKeese>())
				{
					pMovementController->SetNotifyStopCallback(&EnemyKeese::NotifyMovementStopCallback, this);
					pMovementController->SetSpeed(MoveSpeed);
					pMovementController->SetRotateSpeed(FallSpeed);
				}
			}

			if (auto* pEnemyTargetGoc = GetComponent<GOCEnemyTarget>())
			{
				pEnemyTargetGoc->Setup({ 0 });
				pEnemyTargetGoc->SetColliderEyesight(1);
			}

			if (auto* pEnemyHsmGoc = GetComponent<GOCEnemyHsm>())
			{
				GOCEnemyHsm::Description description{ StateDescriptors, ms_StateCount, ms_DefaultStateIndex };
				pEnemyHsmGoc->Setup(description);
			}

			fnd::GOComponent::EndSetup(*this);
		
			if (auto* pGravityGoc = GetComponent<game::GOCGravity>())
				if (auto* pGravityField = pGravityGoc->GetGravityField())
					if (auto* pGravityPath = ObjUtil::GetGravityPathInsideCylinder(pGravityField))
						Path.SetPathObject(pGravityPath);

			UpdateGravityPathDistance(-1.0f);

			if (!Path.Component.IsValid())
				return;

			PathDistance = Path.Distance - MoveRangeOffset;
		
			if (!pMovementController)
				return;

			pMovementController->SetPath(Path.GetPathObject(), Path.Distance);
		}

		bool ProcessMessage(fnd::Message& in_rMessage) override
		{
			if (PreProcessMessage(in_rMessage))
				return true;

			switch (in_rMessage.GetType())
			{
			case xgame::MsgDamage::MessageID:						return ProcMsgDamage(static_cast<xgame::MsgDamage&>(in_rMessage));
			case xgame::MsgKick::MessageID:							return ProcMsgKick(static_cast<xgame::MsgKick&>(in_rMessage));
			case xgame::MsgDlcZeldaNoticeStopEnemy::MessageID:		return ProcMsgDlcZeldaNoticeStopEnemy(static_cast<xgame::MsgDlcZeldaNoticeStopEnemy&>(in_rMessage));
			case xgame::MsgDlcZeldaNoticeActiveEnemy::MessageID:	return ProcMsgDlcZeldaNoticeActiveEnemy(static_cast<xgame::MsgDlcZeldaNoticeActiveEnemy&>(in_rMessage));
			case xgame::MsgHitEventCollision::MessageID:			return ProcMsgHitEventCollision(static_cast<xgame::MsgHitEventCollision&>(in_rMessage));
			case xgame::MsgPLGetHomingTargetInfo::MessageID:		return ProcMsgPLGetHomingTargetInfo(static_cast<xgame::MsgPLGetHomingTargetInfo&>(in_rMessage));
			default:												return EnemyBase::ProcessMessage(in_rMessage);
			}
		}

		bool ProcMsgDamage(xgame::MsgDamage& in_rMessage)
		{
			if (!EnemyUtil::IsDamage(in_rMessage.DefensePower, 0, in_rMessage.AttackType))
				return false;
			
			in_rMessage.SetReply(GetComponent<fnd::GOCTransform>()->Frame.Unk3.GetTranslation(), true);
			ObjUtil::AddScore(*this, ms_pScoreName, in_rMessage);

			enemy::DeadEffectCInfo createInfo{};
			createInfo.Owner = this;
			createInfo.SetMsgDamage(in_rMessage);
			createInfo.SetZeldaKeese();

			CreateDeadEffect(createInfo);
			ProcMission();

			SetStatusRetire();
			Kill();

			return true;
		}

		bool ProcMsgKick(xgame::MsgKick& in_rMessage)
		{
			auto* pInfo = ObjUtil::GetObjectInfo<EnemyKeeseInfo>(*GetDocument());

			auto* pTransformGoc = GetComponent<fnd::GOCTransform>();
			auto* pVisualGoc = GetComponent<fnd::GOCVisualModel>();

			EnemyBlowOffObjectCInfo createInfo{};
			createInfo.SetParamByMessage(in_rMessage);
			createInfo.Model = pInfo->Model;
			createInfo.Skeleton = pInfo->Skeleton;
			createInfo.Animation = pInfo->FlyAnimation;
			createInfo.CollisionRadius = ms_HitCollisionRadius;
			createInfo.Size = EnemyBlowOffObjectCInfo::EffectSize::eEffectSize_ZeldaKeese;

			auto* pEnemyHsmGoc = GetComponent<GOCEnemyHsm>();
			if (pEnemyHsmGoc->GetCurrentStateID())
			{
				createInfo.TrsMatrix = { pTransformGoc->Frame.Unk3.Mtx * pVisualGoc->Transform.Mtx };
			}
			else
			{
				csl::math::Matrix34 rotationMtx{ csl::math::Quaternion(Eigen::AngleAxisf(MATHF_PI, csl::math::Vector3::UnitZ())) };
				createInfo.TrsMatrix = { csl::math::Matrix34(pTransformGoc->Frame.Unk3.Mtx * pVisualGoc->Transform.Mtx) * rotationMtx};
			}

			createInfo.Offset = { 0.0f, 5.0f, 0.0f };
			CreateEnemyBlowOffObject(createInfo);

			in_rMessage.SetReplyForSucceed();

			ObjUtil::AddScore(*this, ms_pScoreName, in_rMessage);

			SetStatusRetire();
			Kill();

			return true;
		}

		bool ProcMsgDlcZeldaNoticeStopEnemy(xgame::MsgDlcZeldaNoticeStopEnemy& in_rMessage)
		{
			GetComponent<fnd::GOCVisualModel>()->SetVisible(false);
			GetComponent<game::GOCAnimationScript>()->SetSpeed(0.0f);
			GetComponent<game::GOCShadow>()->SetVisible(false);
			GetComponent<game::GOCMovementComplex>()->DisableMovementFlag(0);
			GetComponent<game::GOCCollider>()->SetEnable(false);

			return true;
		}

		bool ProcMsgDlcZeldaNoticeActiveEnemy(xgame::MsgDlcZeldaNoticeActiveEnemy& in_rMessage)
		{
			GetComponent<fnd::GOCVisualModel>()->SetVisible(true);
			GetComponent<game::GOCAnimationScript>()->SetSpeed(1.0f);
			GetComponent<game::GOCShadow>()->SetVisible(true);
			GetComponent<game::GOCMovementComplex>()->EnableMovementFlag(0);
			GetComponent<game::GOCCollider>()->SetEnable(true);

			return true;
		}

		bool ProcMsgHitEventCollision(xgame::MsgHitEventCollision& in_rMessage)
		{
			if (ObjUtil::CheckShapeUserID(in_rMessage.pSelf, 0))
				SendTouchDamage(in_rMessage);

			return true;
		}

		bool ProcMsgPLGetHomingTargetInfo(xgame::MsgPLGetHomingTargetInfo& in_rMessage)
		{
			if (!ObjUtil::CheckShapeUserID(in_rMessage.pTargetShape, 0))
				return false;

			math::Transform transform{};
			if (GetComponent<fnd::GOCVisualModel>()->GetNodeTransform(0, ms_pCenterNodeName, &transform))
			{
				in_rMessage.CursorPosition = transform.Position;
				in_rMessage.Flags.set(3);
				return true;
			}

			return false;
		}

		void AnimationCallback(animation::CharactorAnimation* in_pAnimation, animation::ETriggerValueType in_triggerType, animation::CallbackParam in_param)
		{
			if (in_triggerType || in_param.Int)
				return;

			if (auto* pSoundGoc = GetComponent<game::GOCSound>())
				pSoundGoc->Play3D(ms_pFlySoundName, 0.0f);
		}

		void NotifyMovementStopCallback()
		{
			if (auto* pEnemyHsmGoc = GetComponent<GOCEnemyHsm>())
			{
				if (pEnemyHsmGoc->GetCurrentStateID() == 2)
					pEnemyHsmGoc->ChangeState(3);
				else if (pEnemyHsmGoc->GetCurrentStateID() == 3)
					pEnemyHsmGoc->ChangeState(4);
			}
		}

		void UpdateGravityPathDistance(float in_deltaTime)
		{
			if (!Path.Component.IsValid())
				return;

			csl::math::Vector3 position{ GetComponent<fnd::GOCTransform>()->Frame.Transform.GetTranslation() };

			float distance{};
			if (in_deltaTime >= 0.0f)
			{
				Path.GetClosestPositionAlongSpline(position, csl::math::Max(Path.Distance - in_deltaTime * 1.5f, 0.0f), csl::math::Min(Path.Distance + in_deltaTime * 1.5f, Path.GetLength()), &distance);
			}
			else
			{
				Path.GetClosestPositionAlongSpline(position, 0.0f, Path.GetLength(), &distance);
			}

			Path.SetDistance(distance);
		}

		bool IsFindTargetGood(csl::math::Vector3* out_pTargetPosition)
		{
			auto* pEnemyTargetGoc = GetComponent<GOCEnemyTarget>();
			if (!pEnemyTargetGoc || !Path.Component.IsValid() || !pEnemyTargetGoc->IsFindTarget())
				return false;

			auto* pTransformGoc = GetComponent<fnd::GOCTransform>();
			*out_pTargetPosition = { pTransformGoc->Frame.Unk3.Mtx * csl::math::Vector4(0.0f, FallDistance, 10.0f, 1.0f) };
			return true;
		}

		void LostCeiling()
		{
			SetStatusRetire();
			Kill();
		}

		void CheckPoleMove()
		{
			auto* pTransformGoc = GetComponent<fnd::GOCTransform>();
			auto* pGravityGoc = GetComponent<game::GOCGravity>();

			csl::math::Vector3 upVector{ pTransformGoc->Frame.Unk3.Mtx * csl::math::Vector3(csl::math::Vector3::UnitY()) };
			pGravityGoc->GetGravityDirection().dot(upVector);
		}

		class State
		{
		public:
			class Idle : public EnemyState<EnemyKeese>
			{
			private:
				inline static const csl::math::Vector3 ms_CenterPosition{ 0.0f, 5.0f, 0.0f };

			public:
				typedef EnemyKeese context_type;

				Idle()
				{
					
				}

				void OnEnter(EnemyKeese& in_rObj, int in_unk) override;
				bool Step(EnemyKeese& in_rObj, float in_deltaTime) override;
			};

			class FallStart : public EnemyState<EnemyKeese>
			{
			private:
				inline static const char* ms_pAnimationName = "FALL_START";

			public:
				typedef EnemyKeese context_type;

				fnd::GOCVisualModel* pVisualGoc{};
				float RemainingTime{};
				float ElapsedTime{};

				FallStart()
				{

				}

				void OnEnter(EnemyKeese& in_rObj, int in_unk) override;
				bool Step(EnemyKeese& in_rObj, float in_deltaTime) override;
			};

			class Fall : public EnemyState<EnemyKeese>
			{
			public:
				typedef EnemyKeese context_type;

				float ElapsedTime{};

				Fall()
				{

				}

				void OnEnter(EnemyKeese& in_rObj, int in_unk) override;
				bool Step(EnemyKeese& in_rObj, float in_deltaTime) override;
			};

			class Seek : public EnemyState<EnemyKeese>
			{
			private:
				inline static const char* ms_pAnimationName = "MOVING";

			public:
				typedef EnemyKeese context_type;

				int Unk1{};

				Seek()
				{

				}

				void OnEnter(EnemyKeese& in_rObj, int in_unk) override;
				bool Step(EnemyKeese& in_rObj, float in_deltaTime) override;
			};

			class Return : public EnemyState<EnemyKeese>
			{
			private:
				inline static const char* ms_pAnimationName = "MOVE_END";

			public:
				typedef EnemyKeese context_type;

				bool IsCollisionFound{};
				bool Unk2{};
				csl::math::Vector3 HitPoint{};
				float FallDistance{};
				float Unk5{};

				Return()
				{

				}
				
				void OnEnter(EnemyKeese& in_rObj, int in_unk) override;
				bool Step(EnemyKeese& in_rObj, float in_deltaTime) override;
			};
		};

		inline static ut::internal::StateDescImpl States[] =
		{
			{ "Idle", (ut::internal::StateCreate_t)&ut::StateCreatorFuncTemplate<EnemyKeese::State::Idle>::Create, -1 },
			{ "FallStart", (ut::internal::StateCreate_t)&ut::StateCreatorFuncTemplate<EnemyKeese::State::FallStart>::Create, -1 },
			{ "Fall", (ut::internal::StateCreate_t)&ut::StateCreatorFuncTemplate<EnemyKeese::State::Fall>::Create, -1 },
			{ "Seek", (ut::internal::StateCreate_t)&ut::StateCreatorFuncTemplate<EnemyKeese::State::Seek>::Create, -1 },
			{ "Return", (ut::internal::StateCreate_t)&ut::StateCreatorFuncTemplate<EnemyKeese::State::Return>::Create, -1 },
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