#pragma once

namespace app::xgame
{
	class MsgDlcZeldaNoticeStopEnemy : public fnd::Message
	{
	public:
		inline const static unsigned int MessageID = 0x611E;

		MsgDlcZeldaNoticeStopEnemy() : Message(MessageID)
		{

		}

		Message* Clone() override
		{
			return new MsgDlcZeldaNoticeStopEnemy(*this);
		}
	};
}