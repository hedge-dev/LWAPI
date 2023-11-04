#pragma once

namespace app
{
	namespace golon_rock
	{
		struct GolonRockCreateInfo
		{
			csl::math::Matrix34 TransformMtx{};
			float Speed{};
			bool IsCheckFall{};
		};
	}

	class ObjGolonRock : public GameObject3D, public TTinyFsm<ObjGolonRock>
	{
	protected:
		inline static const size_t ms_ModelCount = 2;
		inline static const size_t ms_AnimationCount = 1;
		inline static const size_t ms_ShapeCount = 2;
		inline static const float ms_HitCollisionSize = 20.0f;
		inline static const float ms_CollisionSize = 20.0f;
		inline static const float ms_ShadowRadius = 20.0f;
		inline static const csl::math::Vector3 ms_ShadowOffset = { 0.0f, -20.0f, 0.0f };
		inline static csl::math::Vector3 ms_EffectOffset = { 0.0f, -22.0f, 0.0f };
		inline static const char* ms_pAnimationName = "APPEARE";
		inline static const char* ms_pSoundName = "obj_goron_rolling";
		inline static const char* ms_pEffectName = "ef_dl3_goron_roll";

	public:
		const golon_rock::GolonRockCreateInfo* pCreateInfo{};
		float DisabledTime{};
		float ElapsedTime{};
		fnd::SoundHandle SoundHandle{};
		Effect::CEffectHandle<> EffectHandle{};
		fnd::GOCVisualModel* pRockVisualGoc{};
		game::MoveObjGolonRock* pMovementController{};

		ObjGolonRock(const golon_rock::GolonRockCreateInfo& in_rCreateInfo) : GameObject3D(), TTinyFsm<ObjGolonRock>(&ObjGolonRock::StateShoot)
			, pCreateInfo(&in_rCreateInfo)
		{
			
		}

		void AddCallback(GameDocument* in_pDocument) override
		{
			fnd::GOComponent::Create<fnd::GOCVisualContainer>(*this);
			fnd::GOComponent::Create<game::GOCAnimationSimple>(*this);
			fnd::GOComponent::Create<game::GOCGravity>(*this);
			fnd::GOComponent::Create<game::GOCCollider>(*this);
			fnd::GOComponent::Create<game::GOCMovementComplex>(*this);
			fnd::GOComponent::Create<game::GOCSound>(*this);
			fnd::GOComponent::Create<game::GOCEffect>(*this);
			fnd::GOComponent::Create<game::GOCShadowSimple>(*this);
			
			fnd::GOComponent::BeginSetup(*this);

			auto* pInfo = ObjUtil::GetObjectInfo<ObjGolonRockGeneratorInfo>(*in_pDocument);

			if (auto* pTransformGoc = GetComponent<fnd::GOCTransform>())
			{
				csl::math::Quaternion rotation{ pCreateInfo->TransformMtx };

				pTransformGoc->SetLocalTranslation({ pCreateInfo->TransformMtx.GetTransVector() + math::Vector3Rotate(rotation, { -csl::math::Vector3::UnitY() }) * 20.0f });
				pTransformGoc->SetLocalRotation(rotation);
			}

			if (auto* pVisualContainerGoc = GetComponent<fnd::GOCVisualContainer>())
			{
				pVisualContainerGoc->Setup({ ms_ModelCount });

				if (auto* pVisualGoc = fnd::GOComponent::CreateSingle<fnd::GOCVisualModel>(*this))
				{
					fnd::GOCVisualModel::Description description{};
					description.Model = pInfo->ModelContainer.Models[0];
					description.Skeleton = pInfo->Skeleton;
					description.Unk2 |= 0x400000;
					
					pVisualGoc->Setup(description);
					pVisualContainerGoc->Add(pVisualGoc);
					pVisualGoc->SetLocalRotation({ Eigen::AngleAxisf(MATHF_PI, csl::math::Vector3::UnitY()) });

					if (auto* pAnimationGoc = GetComponent<game::GOCAnimationSimple>())
					{
						pAnimationGoc->Setup({ ms_AnimationCount });
						pVisualGoc->AttachAnimation(pAnimationGoc);

						pAnimationGoc->Add(ms_pAnimationName, pInfo->Animation, game::PlayPolicy::Once);
					}
				}

				if (pRockVisualGoc = fnd::GOComponent::CreateSingle<fnd::GOCVisualModel>(*this))
				{
					fnd::GOCVisualModel::Description description{};
					description.Model = pInfo->ModelContainer.Models[1];
					description.Unk2 |= 0x400000;

					pRockVisualGoc->Setup(description);
					pVisualContainerGoc->Add(pRockVisualGoc);
					pRockVisualGoc->SetVisible(false);
				}
			}

			if (auto* pColliderGoc = GetComponent<game::GOCCollider>())
			{
				pColliderGoc->Setup({ ms_ShapeCount });

				game::ColliSphereShapeCInfo hitCollisionInfo{};
				hitCollisionInfo.ShapeType = game::CollisionShapeType::ShapeType::eShapeType_Sphere;
				hitCollisionInfo.MotionType = game::PhysicsMotionType::MotionType::eMotionType_Value2;
				hitCollisionInfo.Unk2 |= 1;
				hitCollisionInfo.Radius = ms_HitCollisionSize;
				hitCollisionInfo.ShapeID = 0;
				ObjUtil::SetupCollisionFilter(ObjUtil::EFilter::eFilter_Default, hitCollisionInfo);
				pColliderGoc->CreateShape(hitCollisionInfo);

				game::ColliSphereShapeCInfo collisionInfo{};
				collisionInfo.ShapeType = game::CollisionShapeType::ShapeType::eShapeType_Sphere;
				collisionInfo.MotionType = game::PhysicsMotionType::MotionType::eMotionType_Value0;
				collisionInfo.Unk2 |= 0x100;
				collisionInfo.Unk3 = 3;
				collisionInfo.Radius = ms_CollisionSize;
				collisionInfo.ShapeID = 1;
				pColliderGoc->CreateShape(collisionInfo);
			}

			if (auto* pMovementGoc = GetComponent<game::GOCMovementComplex>())
			{
				if (pMovementController = pMovementGoc->SetMoveController<game::MoveObjGolonRock>())
				{
					game::MoveObjGolonRock::SetupParam setupParam{};
					setupParam.Position = GetComponent<fnd::GOCTransform>()->Transform.Position;
					setupParam.YOffset = 20.0f;
					setupParam.PopupTime = 0.3f;
					setupParam.RollWaitTime = 0.4f;
					setupParam.Speed = pCreateInfo->Speed;
					setupParam.Unk1 = MATHF_PI / 90.0f;
					setupParam.Unk2 = MATHF_PI / 2.0f;
					setupParam.Unk5 = 300.0f;
					setupParam.Unk6 = 1.0f;
					setupParam.MoveEndMemFunc = static_cast<void (app::GameObject::*)()>(&ObjGolonRock::NotifyMoveEndCallback);
					setupParam.PassPlayerMemFunc = static_cast<void (app::GameObject::*)()>(&ObjGolonRock::NotifyPassPlayerCallback);
					setupParam.pOwner = this;
					
					setupParam.IsCheckFall = pCreateInfo->IsCheckFall;

					pMovementController->Setup(setupParam);
				}
			}

			if (auto* pShadowGoc = GetComponent<game::GOCShadowSimple>())
			{
				game::ShadowSphereShapeCInfo shadowInfo{ ms_ShadowRadius };
				shadowInfo.Unk2 = 5;
				shadowInfo.ShadowQuality = 3;

				game::GOCShadowSimple::Description description{ &shadowInfo };
				pShadowGoc->Setup(description);
				pShadowGoc->SetLocalOffsetPosition(ms_ShadowOffset);
				pShadowGoc->SetVisible(false);
			}

			game::GOCSound::SimpleSetup(this, 1, 1);

			if (GetComponent<game::GOCEffect>())
				game::GOCEffect::SimpleSetup(this, 1, false);

			fnd::GOComponent::EndSetup(*this);

			InitFSM();

			pCreateInfo = nullptr;
		}

		void Update(const fnd::SUpdateInfo& in_rUpdateInfo) override
		{
			DispatchFSM(TiFsmEvent_t::CreateUpdate(in_rUpdateInfo.DeltaTime));
		}

		bool ProcessMessage(fnd::Message& in_rMessage) override
		{
			if (PreProcessMessage(in_rMessage))
				return true;

			switch (in_rMessage.GetType())
			{
			case xgame::MsgBreakRollingStone::MessageID:			return ProcMsgBreakRollingStone(static_cast<xgame::MsgBreakRollingStone&>(in_rMessage));
			case xgame::MsgHitEventCollision::MessageID:			return ProcMsgHitEventCollision(static_cast<xgame::MsgHitEventCollision&>(in_rMessage));
			case xgame::MsgDlcZeldaNoticeStopEnemy::MessageID:		return ProcMsgDlcZeldaNoticeStopEnemy(static_cast<xgame::MsgDlcZeldaNoticeStopEnemy&>(in_rMessage));
			default:												return GameObject3D::ProcessMessage(in_rMessage);
			}
		}

		bool ProcMsgBreakRollingStone(xgame::MsgBreakRollingStone& in_rMessage)
		{
			if (FSM_STATE() == &ObjGolonRock::StateDisappear)
				return false;

			ChangeState(&ObjGolonRock::StateDisappear);
			return false;
		}

		bool ProcMsgHitEventCollision(xgame::MsgHitEventCollision& in_rMessage)
		{
			if (FSM_STATE() == &ObjGolonRock::StateDisappear)
				return false;
		
			csl::math::Vector3 movementDir{ pMovementController->GetWorldMoveDir() * -1.0f };
		
			xgame::MsgDamage msg{ 2, 8, 3, in_rMessage, movementDir };
			SendMessageImm(in_rMessage.Sender, msg);
			if (msg.IsComingReply())
			{
				ObjUtil::SetEnableColliShape(GetComponent<game::GOCCollider>(), 1, false);
				DisabledTime = 0.8f;
			}

			return false;
		}

		bool ProcMsgDlcZeldaNoticeStopEnemy(xgame::MsgDlcZeldaNoticeStopEnemy& in_rMessage)
		{
			Kill();
			return false;
		}

		void CheckOnPhysics(float in_deltaTime)
		{
			if (DisabledTime <= 0.0f)
				return;
		
			DisabledTime -= in_deltaTime;
			if (DisabledTime >= 0.0f)
				return;
		
			ObjUtil::SetEnableColliShape(GetComponent<game::GOCCollider>(), 1, true);
		}

		void RotateStoneModel()
		{
			pRockVisualGoc->SetLocalRotation(pMovementController->GetLocalRotate());
		}

		void NotifyMoveEndCallback()
		{
			if (FSM_STATE() == &ObjGolonRock::StateShoot)
				ChangeState(&ObjGolonRock::StateAppear);
			else if (FSM_STATE() == &ObjGolonRock::StateMove)
				ChangeState(&ObjGolonRock::StateFall);
			else if (FSM_STATE() == &ObjGolonRock::StateFall)
				ChangeState(&ObjGolonRock::StateDisappear);
		}

		void NotifyPassPlayerCallback()
		{
			if (FSM_STATE() == &ObjGolonRock::StateMove)
				ChangeState(&ObjGolonRock::StateDisappear);
		}

		void ChangeState(TiFsmState_t in_state)
		{
			FSM_TRAN(in_state);
		}

		TiFsmState_t StateShoot(const TiFsmEvent_t& in_rEvent)
		{
			switch (in_rEvent.getSignal())
			{
			case TiFSM_SIGNAL_ENTER:
			{
				pMovementController->StartMode(game::MoveObjGolonRock::Mode::eMode_Shoot);
				GetComponent<game::GOCAnimationSimple>()->SetAnimation(ms_pAnimationName);

				break;
			}
			case TiFSM_SIGNAL_UPDATE:
			{
				CheckOnPhysics(in_rEvent.getFloat());

				return {};
			}
			}

			return FSM_TOP();
		}

		TiFsmState_t StateAppear(const TiFsmEvent_t& in_rEvent)
		{
			switch (in_rEvent.getSignal())
			{
			case TiFSM_SIGNAL_ENTER:
			{
				ElapsedTime = 0.0f;
				pMovementController->ResetFlag(game::MoveController::eFlagType_1);

				return {};
			}
			case TiFSM_SIGNAL_UPDATE:
			{
				ElapsedTime += in_rEvent.getFloat();
				if (ElapsedTime > 0.6f)
				{
					GetComponent<fnd::GOCVisualContainer>()->Visuals[0]->SetVisible(false);
					pRockVisualGoc->SetVisible(true);

					GetComponent<game::GOCShadowSimple>()->SetVisible(true);

					ChangeState(&ObjGolonRock::StateMove);
				}

				return {};
			}
			}

			return FSM_TOP();
		}

		TiFsmState_t StateMove(const TiFsmEvent_t& in_rEvent)
		{
			switch (in_rEvent.getSignal())
			{
			case TiFSM_SIGNAL_ENTER:
			{
				game::SoundFollowFrameInfo followInfo{};
				followInfo.TransType = 1;
				followInfo.pCueName = ms_pSoundName;
				SoundHandle = GetComponent<game::GOCSound>()->Play3D(followInfo);

				game::EffectCreateInfo effectInfo{};
				effectInfo.pName = ms_pEffectName;
				effectInfo.Unk1 = 1.0f;
				effectInfo.Unk3 = true;
				effectInfo.Position = ms_EffectOffset;

				GetComponent<game::GOCEffect>()->CreateEffectLoopEx(&EffectHandle, effectInfo);

				pMovementController->SetFlag(game::MoveController::eFlagType_1);

				pMovementController->StartMode(game::MoveObjGolonRock::Mode::eMode_Move);

				return {};
			}
			case TiFSM_SIGNAL_LEAVE:
			{
				if (SoundHandle.IsValid())
					SoundHandle.Stop(0.0f);

				if (EffectHandle.IsValid())
					EffectHandle.Stop(false);

				return {};
			}
			case TiFSM_SIGNAL_UPDATE:
			{
				CheckOnPhysics(in_rEvent.getFloat());
				RotateStoneModel();

				return {};
			}
			}

			return FSM_TOP();
		}

		TiFsmState_t StateFall(const TiFsmEvent_t& in_rEvent)
		{
			switch (in_rEvent.getSignal())
			{
			case TiFSM_SIGNAL_ENTER:
			{
				pMovementController->StartMode(game::MoveObjGolonRock::Mode::eMode_Fall);

				break;
			}
			case TiFSM_SIGNAL_UPDATE:
			{
				CheckOnPhysics(in_rEvent.getFloat());
				RotateStoneModel();

				return {};
			}
			}

			return FSM_TOP();
		}

		TiFsmState_t StateDisappear(const TiFsmEvent_t& in_rEvent)
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
				if (pRockVisualGoc)
					pRockVisualGoc->SetVisible(!pRockVisualGoc->IsVisible());

				ElapsedTime += in_rEvent.getFloat();
				if (ElapsedTime > 0.5f)
					Kill();

				return {};
			}
			}

			return FSM_TOP();
		}
	};

	namespace golon_rock
	{
		static ObjGolonRock* CreateGolonRock(csl::fnd::IAllocator* in_pAllocator, GameDocument* in_pDocument, GolonRockCreateInfo& in_rCreateInfo)
		{
			auto* pObject = new ObjGolonRock(in_rCreateInfo);
			if (!pObject)
				return { nullptr };

			in_pDocument->AddGameObject(pObject);
			return pObject;
		}
	}
}