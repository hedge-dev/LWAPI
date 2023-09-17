#pragma once

namespace app::xgame
{
	class MsgStopGameTimer : public fnd::Message
	{
	public:
		inline const static unsigned int MessageID = 0x6118;
		
		MsgStopGameTimer() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgStopGameTimer(*this);
		}
	};
}