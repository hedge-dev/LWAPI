#pragma once

namespace app::xgame
{
	class MsgPLGetWaterLimitTime : public fnd::Message
	{
	public:
		inline const static unsigned int MessageID = 0x505B;

		float WaterLimitTime{};

		MsgPLGetWaterLimitTime() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgPLGetWaterLimitTime(*this);
		}
	};
}