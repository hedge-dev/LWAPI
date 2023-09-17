#pragma once

namespace app::xgame
{
	class MsgPLSetNumRing : public fnd::Message
	{
	public:
		int RingCount{};

		inline const static unsigned int MessageID = 0x508C;

		MsgPLSetNumRing() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgPLSetNumRing(*this);
		}
	};
}