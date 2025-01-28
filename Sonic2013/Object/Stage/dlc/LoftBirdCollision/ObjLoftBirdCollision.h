#pragma once

namespace app
{
	inline static const char* ms_pLoftBirdActionTypeComments[] = { "羽ばたきアニメ再生", "鳴き声再生", "リンクアニメ1(木)", "リンクアニメ2(洞窟)" };
	inline static const int ms_LoftBirdActionTypes[] = { 0, 1, 2, 3 };

	class ObjLoftBirdCollision : public CSetObjectListener
	{
	private:
		inline static const size_t ms_ShapeCount = 1;
		inline static const csl::math::Vector3 ms_CollisionSize = { 10.0f, 10.0f, 10.0f };

	public:
		ObjLoftBirdCollision() : CSetObjectListener()
		{
			
		}

		void AddCallback(GameDocument* in_pDocument) override
		{
			fnd::GOComponent::Create<game::GOCBoxCollider>(*this);
			
			auto* pParam = GetAdapter()->GetData<SLoftBirdCollisionParam>();

			fnd::GOComponent::BeginSetup(*this);

			if (auto* pCollider = GetComponent<game::GOCBoxCollider>())
			{
				game::GOCBoxColliderCinfo collisionInfo{};
				collisionInfo.Size = ms_CollisionSize;
				collisionInfo.Unk2 = 1;
				collisionInfo.MotionType = game::PhysicsMotionType::MotionType::eMotionType_Value0;
				ObjUtil::SetupCollisionFilter(ObjUtil::eFilter_Unk2, collisionInfo);

				pCollider->Setup(collisionInfo);
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
			auto* pParam = GetAdapter()->GetData<SLoftBirdCollisionParam>();

			xgame::MsgLoftBirdCollision msg{};
			if (pParam->ActionType <= 3)
				msg.ActionType = ms_LoftBirdActionTypes[pParam->ActionType];
			
			SendMessageImm(in_rMessage.Sender, msg);

			return true;
		}

		const char* GetDebugDrawComment()
		{
			auto* pParam = GetAdapter()->GetData<SLoftBirdCollisionParam>();

			if (pParam->ActionType <= 3)
				return ms_pLoftBirdActionTypeComments[pParam->ActionType];
			else
				return "無効なアクションです";
		}
	};
}