#pragma once

namespace app::xgame
{
	class MsgBeltConveyorControlEnd : public fnd::Message
	{
	public:
		inline const static unsigned int MessageID = 0x60AB;
		
		MsgBeltConveyorControlEnd() : Message(MessageID)
		{

		}

		Message* Clone() override
		{
			return new MsgBeltConveyorControlEnd(*this);
		}
	};
}