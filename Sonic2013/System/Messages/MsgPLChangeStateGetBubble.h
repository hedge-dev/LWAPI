#pragma once

namespace app::Player
{
	class MsgPLChangeStateGetBubble : public fnd::Message
	{
	public:
		inline const static unsigned int MessageID = 0x50B3;

		MsgPLChangeStateGetBubble() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgPLChangeStateGetBubble(*this);
		}
	};
}