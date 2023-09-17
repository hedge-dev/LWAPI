#pragma once

namespace app
{
	namespace egg
	{
		struct DroppedEggCInfo
		{
			csl::math::Matrix34 Mtx{};
			csl::math::Vector3 DropDirection{};
			game::PathEvaluator PathEvaluator{};
			size_t Type{};
			float ZIndex{};
		};
	}

	class ObjDroppedEgg : public GameObject3D, public TTinyFsm<ObjDroppedEgg>
	{
	private:
		inline static const csl::math::Vector3 ms_PositionOffset = { 0.0f, -3.0f, 0.0f };
		inline static const size_t ms_ShapeCount = 1;
		inline static const float ms_CollisionRadius = 3.0f;

	public:
		class BoundListener : public game::MoveBound::Listener
		{
		public:
			ObjDroppedEgg* pOwner{};
			
			void OnBound(const csl::math::Plane& in_rPlane) override
			{
				if (pOwner)
					pOwner->BoundCallback();
			}
		};
		
		const egg::DroppedEggCInfo* pCreateInfo{};
		size_t Type{};
		float ElapsedTime{};
		game::MoveBound* pMoveBound{};
		INSERT_PADDING(4);
		BoundListener Listener{};
		fnd::Handle<game::ColliShape> ColliHandle{};
		csl::math::Vector3 ColliPosition{};

		ObjDroppedEgg(const egg::DroppedEggCInfo* in_pInfo) : GameObject3D(), TTinyFsm<ObjDroppedEgg>(&ObjDroppedEgg::StateFall)
		{
			Type = in_pInfo->Type;
			pCreateInfo = in_pInfo;
		}

		void AddCallback(GameDocument& in_rDocument) override
		{
			fnd::GOComponent::Create<fnd::GOCVisualModel>(*this);
			fnd::GOComponent::Create<game::GOCCollider>(*this);
			fnd::GOComponent::Create<game::GOCMovementComplex>(*this);

			fnd::GOComponent::BeginSetup(*this);

			if (auto* pTransform = GetComponent<fnd::GOCTransform>())
			{
				pTransform->SetLocalTranslation(pCreateInfo->Mtx.GetTransVector());
				pTransform->SetLocalRotation(pCreateInfo->Mtx.GetRotation());
			}

			auto* pInfo = ObjUtil::GetObjectInfo<ObjEggInfo>(in_rDocument);

			if (auto* pVisualModel = GetComponent<fnd::GOCVisualModel>())
			{
				fnd::GOCVisualModel::Description description{};
				description.m_Model = pInfo->ModelContainer.Models[Type];
				description.field_0C |= 0x400000u;
				description.zOffset = -0.2f * pCreateInfo->ZIndex;

				pVisualModel->Setup(description);
				pVisualModel->SetLocalTranslation(ms_PositionOffset);
			}

			if (auto* pCollider = GetComponent<game::GOCCollider>())
			{
				pCollider->Setup({ ms_ShapeCount });

				game::ColliSphereShapeCInfo collisionInfo{};
				collisionInfo.m_ShapeType = game::CollisionShapeType::ShapeType::ShapeType_Sphere;
				collisionInfo.m_MotionType = game::PhysicsMotionType::MotionType::MotionType_VALUE2;
				collisionInfo.m_Unk2 |= 1;
				collisionInfo.m_Radius = ms_CollisionRadius;
				ObjUtil::SetupCollisionFilter(ObjUtil::eFilter_Unk8, collisionInfo);
				pCollider->CreateShape(collisionInfo);
			}

			if (auto* pMovementComplex = GetComponent<game::GOCMovementComplex>())
			{
				if (pMoveBound = pMovementComplex->SetMoveController<game::MoveBound>())
				{
					game::MoveBound::Desc description{};
					description.Velocity = pCreateInfo->DropDirection;

					if (pCreateInfo->PathEvaluator.Component.IsValid())
					{
						description.PathEvaluator.SetPathObject(pCreateInfo->PathEvaluator.GetPathObject());
						description.PathEvaluator.SetDistance(pCreateInfo->PathEvaluator.Distance);
					}

					description.Flags.set(0);
					description.Flags.set(1);

					pMoveBound->Setup(description);
				}
			}

			Listener.pOwner = this;
			pMoveBound->ResetListener(&Listener);

			fnd::GOComponent::EndSetup(*this);

			pCreateInfo = nullptr;
			InitFSM();
		}

		bool ProcessMessage(fnd::Message& in_rMessage) override
		{
			if (PreProcessMessage(in_rMessage))
				return true;

			switch (in_rMessage.GetType())
			{
			case xgame::MsgHitEventCollision::MessageID:				return ProcMsgHitEventCollision(static_cast<xgame::MsgHitEventCollision&>(in_rMessage));
			default:													return GameObject3D::ProcessMessage(in_rMessage);
			}
		}

		void Update(const fnd::SUpdateInfo& in_rUpdateInfo) override
		{
			DispatchFSM(TiFsmBasicEvent<ObjDroppedEgg>::CreateUpdate(in_rUpdateInfo.deltaTime));
		}

		bool ProcMsgHitEventCollision(xgame::MsgHitEventCollision& in_rMessage)
		{
			if (auto* pTransform = GetComponent<fnd::GOCTransform>())
			{
				egg::EggCInfo createInfo{};
				createInfo.Mtx = { pTransform->m_Frame.m_Unk3.m_Mtx * csl::math::Matrix34(0.0f, -3.0f, 0.0f) };
				createInfo.Type = Type;
				
				if (!ObjUtil::GetPlayerNo(*GetDocument(), in_rMessage.m_Sender))
					egg::CreateEgg(*GetDocument(), createInfo);
				
				Kill();
			}

			return true;
		}

		void UpdateFollow()
		{
			if (!ColliHandle.IsValid())
				return;
		
			auto* colliShape = ColliHandle.Get();
			if (!colliShape)
				return;

			auto* pTransform = GetComponent<fnd::GOCTransform>();
			if (!pTransform)
				return;

			pTransform->SetLocalTranslation({ pTransform->m_Frame.m_Unk3.GetTranslation() + (colliShape->m_Transform.GetTransVector() - ColliPosition) });
			ColliPosition = colliShape->m_Transform.GetTransVector();
		}
		
		void BoundCallback()
		{
			if (auto* pMovementComplex = GetComponent<game::GOCMovementComplex>())
				pMovementComplex->DisableMovementFlag(0);

			if (auto* pTransform = GetComponent<fnd::GOCTransform>())
			{
				csl::math::Matrix34 objectMtx = pTransform->m_Frame.m_Unk3.m_Mtx;
				csl::math::Vector3 rayFrom{ objectMtx * csl::math::Vector4(0.0f, 3.0f, 0.0f, 1.0f) };
				csl::math::Vector3 rayTo{ objectMtx * csl::math::Vector4(0.0f, 10.0f, 0.0f, 1.0f) };

				game::PhysicsRaycastOutput raycastOut{};
				if (ObjUtil::RaycastNearestCollision(&raycastOut, *GetDocument(), rayFrom, rayTo, 0xC996) &&
					raycastOut.m_pShape && (raycastOut.m_pShape->m_Unk3 & 0x4000) != 0)
				{
					ColliHandle = raycastOut.m_pShape;
					ColliPosition = raycastOut.m_pShape->m_Transform.GetTransVector();
				}
			}
		}

		void ChangeState(TiFsmState_t in_state)
		{
			FSM_TRAN(in_state);
		}

		TiFsmState_t StateFall(const TiFsmBasicEvent<ObjDroppedEgg>& in_rEvent)
		{
			switch (in_rEvent.getSignal())
			{
			case TiFSM_SIGNAL_UPDATE:
			{
				if (pMoveBound->Flags.test(0))
				{
					pMoveBound->ResetFlag(game::MoveController::FlagType::eFlagType_1);
					ChangeState(&ObjDroppedEgg::StateLanding);
				}

				return {};
			}
			case TiFSM_SIGNAL_ENTER:
				return {};
			default:
				return FSM_TOP();
			}
		}

		TiFsmState_t StateLanding(const TiFsmBasicEvent<ObjDroppedEgg>& in_rEvent)
		{
			switch (in_rEvent.getSignal())
			{
			case TiFSM_SIGNAL_ENTER:
			{
				ElapsedTime = 0.0f;

				return {};
			}
			case TiFSM_SIGNAL_UPDATE:
			{
				UpdateFollow();

				if (auto* pVisualModel = GetComponent<fnd::GOCVisualModel>())
				{
					if (ElapsedTime >= 0.35)
						pVisualModel->SetLocalScale({ 1.0f, 1.0f, 1.0f });
					else
						pVisualModel->SetLocalScale(egg::CalcSlipperyScale(ElapsedTime, 0.7f, 0.4f, 0.2f));
				}

				if (ElapsedTime > 0.55)
					ChangeState(&ObjDroppedEgg::StateWait);

				ElapsedTime += in_rEvent.getFloat();

				return {};
			}
			default:
				return FSM_TOP();
			}
		}

		TiFsmState_t StateWait(const TiFsmBasicEvent<ObjDroppedEgg>& in_rEvent)
		{
			switch (in_rEvent.getSignal())
			{
			case TiFSM_SIGNAL_ENTER:
			{
				ElapsedTime = 0.0f;

				return {};
			}
			case TiFSM_SIGNAL_UPDATE:
			{
				UpdateFollow();

				ElapsedTime += in_rEvent.getFloat();
				if (auto* pVisualModel = GetComponent<fnd::GOCVisualModel>())
				{
					pVisualModel->SetLocalScale(egg::CalcSlipperyScale(ElapsedTime, 1.6f, 0.1f, 0.1f));
					
					auto* pPlayerInfo = ObjUtil::GetPlayerInformation(*GetDocument(), 0);
					if (!pPlayerInfo)
						return {};

					if (auto* pTransform = GetComponent<fnd::GOCTransform>())
					{
						csl::math::Vector3 distance{ pPlayerInfo->Position - pTransform->m_Transform.m_Position };
						if (distance.squaredNorm() > 1000000.0f)
							Kill();
					}
				}

				return {};
			}
			default:
				return FSM_TOP();
			}
		}
	};
}