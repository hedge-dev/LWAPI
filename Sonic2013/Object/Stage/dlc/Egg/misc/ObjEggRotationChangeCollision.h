#pragma once

namespace app
{
	class ObjEggRotationChangeCollision : public CSetObjectListener
	{
	private:
		inline static const size_t ms_ShapeCount = 1;

	public:
		ObjEggRotationChangeCollision() : CSetObjectListener()
		{

		}

	protected:
		void AddCallback(GameDocument& in_rDocument) override
		{
			fnd::GOComponent::Create<game::GOCCollider>(*this);

			fnd::GOComponent::BeginSetup(*this);

			auto* pParam = GetAdapter()->GetData<SEggRotationChangeCollisionParam>();

			if (auto* pCollider = GetComponent<game::GOCCollider>())
			{
				pCollider->Setup({ ms_ShapeCount });

				game::ColliBoxShapeCInfo collisionInfo{};
				collisionInfo.m_ShapeType = game::CollisionShapeType::ShapeType::ShapeType_Box;
				collisionInfo.m_MotionType = game::PhysicsMotionType::MotionType::MotionType_VALUE2;
				collisionInfo.m_Size = { pParam->Width, pParam->Height, pParam->Depth };
				collisionInfo.m_Unk2 |= 3;

				ObjUtil::SetupCollisionFilter(ObjUtil::eFilter_Unk2, collisionInfo);
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
			case xgame::MsgHitEventCollision::MessageID:				return ProcMsgHitEventCollision(static_cast<xgame::MsgHitEventCollision&>(in_rMessage));
			case xgame::MsgLeaveEventCollision::MessageID:				return ProcMsgLeaveEventCollision(static_cast<xgame::MsgLeaveEventCollision&>(in_rMessage));
			default:													return CSetObjectListener::ProcessMessage(in_rMessage);
			}
		}

		bool ProcMsgHitEventCollision(xgame::MsgHitEventCollision& in_rMessage)
		{
			xgame::MsgDlcChangeEggRotation msg{};
			msg.IsEnter = true;

			SendMessageImm(in_rMessage.m_Sender, msg);
			return true;
		}

		bool ProcMsgLeaveEventCollision(xgame::MsgLeaveEventCollision& in_rMessage)
		{
			xgame::MsgDlcChangeEggRotation msg{};
			msg.IsEnter = false;

			SendMessageImm(in_rMessage.m_Sender, msg);
			return true;
		}
	};
}
