#pragma once

namespace app::xgame
{
	class MsgResumeGameTimer : public fnd::Message
	{
	public:
		inline const static unsigned int MessageID = 0x6119;
		
		MsgResumeGameTimer() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgResumeGameTimer(*this);
		}
	};
}