#pragma once

namespace app::xgame
{
	class MsgPLNotifyDying : public fnd::Message
	{
	public:
		inline const static unsigned int MessageID = 0x5002;

		MsgPLNotifyDying() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgPLNotifyDying(*this);
		}
	};
}