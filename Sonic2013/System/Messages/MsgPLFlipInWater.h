#pragma once

namespace app::xgame
{
	class MsgPLFlipInWater : public fnd::Message
	{
	public:
		inline const static unsigned int MessageID = 0x5029;

		MsgPLFlipInWater() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgPLFlipInWater(*this);
		}
	};
}