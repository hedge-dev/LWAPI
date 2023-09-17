#pragma once

namespace app::xgame
{
	class MsgStopForGoal : public fnd::Message
	{
	public:
		inline const static unsigned int MessageID = 0x602E;

		MsgStopForGoal() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgStopForGoal(*this);
		}
	};
}