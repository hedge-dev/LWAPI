#pragma once

namespace app::xgame
{
	class MsgPLFinishAutorun : public fnd::Message
	{
	public:
		inline const static unsigned int MessageID = 0x5071;

		MsgPLFinishAutorun() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgPLFinishAutorun(*this);
		}
	};
}