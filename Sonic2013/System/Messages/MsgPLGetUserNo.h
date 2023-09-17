#pragma once

namespace app::xgame
{
	class MsgPLGetUserNo : public fnd::Message
	{
	public:
		size_t PlayerNo{ static_cast<size_t>(-1) };
		
		inline const static unsigned int MessageID = 0x5058;
		
		MsgPLGetUserNo() : Message(MessageID)
		{

		}

		Message* Clone() override
		{
			return new MsgPLGetUserNo(*this);
		}
	};
}