#pragma once

namespace app::xgame
{
	class MsgDlcZeldaNoticeActiveEnemy : public fnd::Message
	{
	public:
		inline const static unsigned int MessageID = 0x611F;

		MsgDlcZeldaNoticeActiveEnemy() : Message(MessageID)
		{

		}

		Message* Clone() override
		{
			return new MsgDlcZeldaNoticeActiveEnemy(*this);
		}
	};
}