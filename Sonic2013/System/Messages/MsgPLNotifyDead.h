#pragma once

namespace app::xgame
{
	class MsgPLNotifyDead : public fnd::Message
	{
	public:
		inline const static unsigned int MessageID = 0x5003;

		MsgPLNotifyDead() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgPLNotifyDead(*this);
		}
	};
}