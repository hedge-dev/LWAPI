#pragma once

namespace app::xgame
{
	class MsgGetDeathTornadoInfo : public fnd::Message
	{
	public:
		inline const static unsigned int MessageID = 0x607E;

		MsgGetDeathTornadoInfo() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgGetDeathTornadoInfo(*this);
		}
	};
}