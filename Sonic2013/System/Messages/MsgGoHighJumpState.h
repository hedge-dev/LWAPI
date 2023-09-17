#pragma once

namespace app::Player
{
	class MsgGoHighJumpState : public fnd::Message
	{
	public:
		const xgame::MsgHitEventCollision* pCollisionEventMsg{};
		bool Unk1{};

		inline const static unsigned int MessageID = 0x50AE;

		MsgGoHighJumpState(const xgame::MsgHitEventCollision& in_rMessage) : Message(MessageID), pCollisionEventMsg(&in_rMessage)
		{
			
		}

		Message* Clone() override
		{
			return new MsgGoHighJumpState(*this);
		}
	};
}