#pragma once

namespace app::Player
{
	class MsgHitDamage : public fnd::Message
	{
	public:
		const xgame::MsgDamage* pDamageMsg{};
		GameObject* pObject{};

		inline const static unsigned int MessageID = 0x50B6;

		MsgHitDamage(const xgame::MsgDamage& in_rMessage) : Message(MessageID), pDamageMsg(&in_rMessage)
		{
			
		}

		Message* Clone() override
		{
			return new MsgHitDamage(*this);
		}
	};
}