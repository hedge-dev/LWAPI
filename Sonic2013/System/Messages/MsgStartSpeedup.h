#pragma once

namespace app::xgame
{
	class MsgStartSpeedup : public fnd::Message
	{
	public:
		uint PlayerNo{};

		inline const static unsigned int MessageID = 0x3015;

		MsgStartSpeedup() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgStartSpeedup(*this);
		}
	};
}