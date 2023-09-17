#pragma once

namespace app::xgame
{
	class MsgPinBallStarter : public fnd::Message
	{
	public:
		inline const static unsigned int MessageID = 0x6083;

		MsgPinBallStarter() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgPinBallStarter(*this);
		}
	};
}