#pragma once

namespace app::xgame
{
	class MsgPLQuake : public fnd::Message
	{
	public:
		inline const static unsigned int MessageID = 0x508F;

		MsgPLQuake() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgPLQuake(*this);
		}
	};
}