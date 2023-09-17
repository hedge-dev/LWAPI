#pragma once

namespace app::Player
{
	class MsgAfterWarpOtherSide : public fnd::Message
	{
	public:
		inline const static unsigned int MessageID = 0x50BC;

		MsgAfterWarpOtherSide() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgAfterWarpOtherSide(*this);
		}
	};
}