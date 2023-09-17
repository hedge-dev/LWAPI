#pragma once

namespace app::xgame
{
	class MsgHudAirMeter : public fnd::Message
	{
	public:
		int Unk1{};

		inline const static unsigned int MessageID = 0xC011;

		MsgHudAirMeter(int in_unk) : Message(MessageID), Unk1(in_unk)
		{
			
		}

		Message* Clone() override
		{
			return new MsgHudAirMeter(*this);
		}
	};
}