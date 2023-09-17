#pragma once

namespace app::xgame
{
	class MsgGetBubble : public fnd::Message
	{
	public:
		inline const static unsigned int MessageID = 0x6072;

		MsgGetBubble() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgGetBubble(*this);
		}
	};
}