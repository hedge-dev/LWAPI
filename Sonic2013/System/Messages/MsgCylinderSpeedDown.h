#pragma once

namespace app::xgame
{
	class MsgCylinderSpeedDown : public fnd::Message
	{
	public:
		inline const static unsigned int MessageID = 0x5064;

		MsgCylinderSpeedDown() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgCylinderSpeedDown(*this);
		}
	};
}