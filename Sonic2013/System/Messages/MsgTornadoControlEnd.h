#pragma once

namespace app::xgame
{
	class MsgTornadoControlEnd : public fnd::Message
	{
	public:
		inline const static unsigned int MessageID = 0x605C;

		MsgTornadoControlEnd() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgTornadoControlEnd(*this);
		}
	};
}