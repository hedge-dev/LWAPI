#pragma once

namespace app::xgame
{
	class MsgEndSpeedup : public fnd::Message
	{
	public:
		uint PlayerNo{};

		inline const static unsigned int MessageID = 0x3016;

		MsgEndSpeedup() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgEndSpeedup(*this);
		}
	};
}