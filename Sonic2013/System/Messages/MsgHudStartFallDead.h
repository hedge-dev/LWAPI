#pragma once

namespace app::xgame
{
	class MsgHudStartFallDead : public fnd::Message
	{
	public:
		float Unk1{};
		byte Unk2{};
		byte Unk3{};

		inline const static unsigned int MessageID = 0xC02E;

		MsgHudStartFallDead(float in_unk1, bool in_unk2) : Message(MessageID), Unk1(in_unk1), Unk2(in_unk2)
		{
			
		}

		Message* Clone() override
		{
			return new MsgHudStartFallDead(*this);
		}
	};
}