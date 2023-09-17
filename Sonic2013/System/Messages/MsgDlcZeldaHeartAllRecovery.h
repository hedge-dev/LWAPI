#pragma once

namespace app::xgame
{
	class MsgDlcZeldaHeartAllRecovery : public fnd::Message
	{
	public:
		inline const static unsigned int MessageID = 0x6120;

		MsgDlcZeldaHeartAllRecovery() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgDlcZeldaHeartAllRecovery(*this);
		}
	};
}