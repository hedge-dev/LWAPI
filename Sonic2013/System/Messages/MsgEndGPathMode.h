#pragma once

namespace app::xgame
{
	class MsgEndGPathMode : public fnd::Message
	{
	public:
		inline const static unsigned int MessageID = 0x604A;

		MsgEndGPathMode() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgEndGPathMode(*this);
		}
	};
}