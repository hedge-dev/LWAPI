#pragma once

namespace app::xgame
{
	class MsgExitLoop : public fnd::Message
	{
	public:
		inline const static unsigned int MessageID = 0x606E;

		MsgExitLoop() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgExitLoop(*this);
		}
	};
}