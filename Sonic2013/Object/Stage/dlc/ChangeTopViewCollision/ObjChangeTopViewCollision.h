#pragma once

namespace app
{
	class ObjChangeTopViewCollision : public CSetObjectListener
	{
	private:
		inline static const size_t ms_ShapeCount = 1;

	public:
		ObjChangeTopViewCollision() : CSetObjectListener()
		{
			
		}

		void AddCallback(GameDocument& in_rDocument) override
		{
			fnd::GOComponent::Create<game::GOCCollider>(*this);
			
			fnd::GOComponent::BeginSetup(*this);

			auto* pParam = GetAdapter()->GetData<SChangeTopViewCollisionParam>();

			if (auto* pCollider = GetComponent<game::GOCCollider>())
			{
				pCollider->Setup({ ms_ShapeCount });
				game::ColliBoxShapeCInfo collisionInfo{};
				collisionInfo.m_ShapeType = game::CollisionShapeType::ShapeType::ShapeType_Box;
				collisionInfo.m_MotionType = game::PhysicsMotionType::MotionType::MotionType_VALUE2;
				collisionInfo.m_Unk2 |= 3;
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
			case xgame::MsgLeaveEventCollision::MessageID:			return ProcMsgLeaveEventCollision(static_cast<xgame::MsgLeaveEventCollision&>(in_rMessage));
			default:												return CSetObjectListener::ProcessMessage(in_rMessage);
			}
		}

		bool ProcMsgHitEventCollision(xgame::MsgHitEventCollision& in_rMessage)
		{
			xgame::MsgPLChangeAreaTopView msg{};
			msg.IsTopView = true;

			ObjUtil::SendMessageImmToPlayer(*this, 0, msg);
			return true;
		}

		bool ProcMsgLeaveEventCollision(xgame::MsgLeaveEventCollision& in_rMessage)
		{
			xgame::MsgPLChangeAreaTopView msg{};
			msg.IsTopView = false;

			ObjUtil::SendMessageImmToPlayer(*this, 0, msg);
			return true;
		}
	};
}