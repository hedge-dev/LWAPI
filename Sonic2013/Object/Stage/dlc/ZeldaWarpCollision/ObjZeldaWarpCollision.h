#pragma once

namespace app
{
	class ObjZeldaWarpCollision : public CSetObjectListener
	{
	private:
		inline static const size_t ms_ShapeCount = 1;

	public:
		ObjZeldaWarpCollision() : CSetObjectListener()
		{
			
		}

		void AddCallback(GameDocument& in_rDocument) override
		{
			fnd::GOComponent::Create<game::GOCCollider>(*this);
			
			fnd::GOComponent::BeginSetup(*this);

			auto* pParam = GetAdapter()->GetData<SZeldaWarpCollisionParam>();

			if (auto* pCollider = GetComponent<game::GOCCollider>())
			{
				pCollider->Setup({ ms_ShapeCount });

				game::ColliBoxShapeCInfo collisionInfo{};
				collisionInfo.m_ShapeType = game::CollisionShapeType::ShapeType::ShapeType_Box;
				collisionInfo.m_MotionType = game::PhysicsMotionType::MotionType::MotionType_VALUE2;
				collisionInfo.m_Unk2 |= 1;
				collisionInfo.m_Size = { pParam->CollisionWidth, pParam->CollisionHeight, pParam->CollisionDepth };
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
			case xgame::MsgHitEventCollision::MessageID:			return ProcMsgHitEventCollision(static_cast<xgame::MsgHitEventCollision&>(in_rMessage));
			default:												return CSetObjectListener::ProcessMessage(in_rMessage);
			}
		}

		bool ProcMsgHitEventCollision(xgame::MsgHitEventCollision& in_rMessage)
		{
			auto* pParam = GetAdapter()->GetData<SZeldaWarpCollisionParam>();

			csl::math::Vector3 targetPosition{};
			csl::math::Quaternion targetRotation{};
			if (!ObjUtil::GetSetObjectTransform(*GetDocument(), pParam->TargetLocate, &targetPosition, &targetRotation))
				return false;

			xgame::MsgWarpNewArea msg{};
			msg.PlayerNo = ObjUtil::GetPlayerNo(*GetDocument(), in_rMessage.m_Sender);
			msg.ToSideView = pParam->IsSideView;
			msg.TargetPosition = targetPosition;
			msg.TargetRotation = targetRotation;
			msg.Unk3 = 1;

			ObjUtil::SendMessageImmToGameActor(*this, msg);

			return true;
		}
	};
}