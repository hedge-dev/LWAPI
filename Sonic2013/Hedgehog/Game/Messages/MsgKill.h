#pragma once

namespace app::xgame
{
	class MsgKill : public fnd::Message
	{
	public:
		inline static unsigned int MessageID = 0x4000;

		MsgKill() : Message(MessageID)
		{
			
		}

		Message* Clone() override 
		{
			return new MsgKill();
		}
	};
}
