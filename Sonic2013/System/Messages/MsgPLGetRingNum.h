#pragma once

namespace app::xgame
{
	class MsgPLGetRingNum : public fnd::Message
	{
	public:
		size_t RingCount{};
		
		inline const static unsigned int MessageID = 0x5014;
		
		MsgPLGetRingNum() : Message(MessageID)
		{

		}

		Message* Clone() override
		{
			return new MsgPLGetRingNum(*this);
		}
	};
}