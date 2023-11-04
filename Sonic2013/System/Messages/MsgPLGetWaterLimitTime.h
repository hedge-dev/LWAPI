#pragma once

namespace app::xgame
{
	class MsgPLGetWaterLimitTime : public fnd::Message
	{
	public:
		float WaterLimitTime{};

		inline const static unsigned int MessageID = 0x505B;

		MsgPLGetWaterLimitTime() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgPLGetWaterLimitTime(*this);
		}
	};
}