#pragma once

namespace app::xgame
{
	class MsgGravitySwitched : public fnd::Message
	{
	public:
		inline const static unsigned int MessageID = 0x50AD;

		MsgGravitySwitched() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgGravitySwitched(*this);
		}
	};
}