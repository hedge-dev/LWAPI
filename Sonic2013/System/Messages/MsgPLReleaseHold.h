#pragma once

namespace app::xgame
{
	class MsgPLReleaseHold : public fnd::Message
	{
	public:
		inline const static unsigned int MessageID = 0x507A;

		MsgPLReleaseHold() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgPLReleaseHold(*this);
		}
	};
}