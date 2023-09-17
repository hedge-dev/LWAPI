#pragma once

namespace app::xgame
{
	class MsgDlcZeldaTakeHeartContainer : public fnd::Message
	{
	public:
		inline const static unsigned int MessageID = 0x611C;

		MsgDlcZeldaTakeHeartContainer() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgDlcZeldaTakeHeartContainer(*this);
		}
	};
}