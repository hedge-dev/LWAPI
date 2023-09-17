#pragma once

namespace app::xgame
{
	class MsgSetupDamageAndBonus : public fnd::Message
	{
	public:
		GameObject* pOwner{};
		MsgDamage* pDamageMsg{};

		inline const static unsigned int MessageID = 0x50BA;

		MsgSetupDamageAndBonus(GameObject* in_pOwner, MsgDamage& in_rDamageMsg)
			: Message(MessageID)
			, pOwner(in_pOwner)
			, pDamageMsg(&in_rDamageMsg)
		{

		}

		Message* Clone() override
		{
			return new MsgSetupDamageAndBonus(*this);
		}
	};
}