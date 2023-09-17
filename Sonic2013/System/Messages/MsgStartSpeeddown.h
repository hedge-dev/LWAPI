#pragma once

namespace app::xgame
{
	class MsgStartSpeeddown : public fnd::Message
	{
	public:
		uint PlayerNo{};

		inline const static unsigned int MessageID = 0x3017;

		MsgStartSpeeddown() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgStartSpeeddown(*this);
		}
	};
}