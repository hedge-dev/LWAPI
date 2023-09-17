#pragma once

namespace app::xgame
{
	class MsgHudAirTimer : public fnd::Message
	{
	public:
		float Unk1{};
		bool Unk2{};

		inline const static unsigned int MessageID = 0xC010;

		MsgHudAirTimer(bool in_unk1, float in_unk2) : Message(MessageID), Unk1(in_unk2), Unk2(in_unk1)
		{
			
		}

		Message* Clone() override
		{
			return new MsgHudAirTimer(*this);
		}
	};
}