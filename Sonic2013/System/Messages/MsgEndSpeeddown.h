#pragma once

namespace app::xgame
{
	class MsgEndSpeeddown : public fnd::Message
	{
	public:
		uint PlayerNo{};

		inline const static unsigned int MessageID = 0x3018;

		MsgEndSpeeddown() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgEndSpeeddown(*this);
		}
	};
}