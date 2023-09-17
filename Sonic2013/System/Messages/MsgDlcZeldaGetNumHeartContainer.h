#pragma once

namespace app::xgame
{
	class MsgDlcZeldaGetNumHeartContainer : public fnd::Message
	{
	public:
		int HeartContainerNo{};

		inline const static unsigned int MessageID = 0x611D;

		MsgDlcZeldaGetNumHeartContainer() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgDlcZeldaGetNumHeartContainer(*this);
		}
	};
}