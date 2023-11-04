#pragma once

namespace app::xgame
{
	class MsgCatchPlayer : public fnd::Message
	{
	public:
		csl::ut::Bitset<char> Unk1{};
		csl::math::Matrix34 Unk2{};
		int Unk3{};
		bool Unk4{};

		inline const static unsigned int MessageID = 0x601C;
		
		MsgCatchPlayer() : Message(MessageID)
		{

		}

		Message* Clone() override
		{
			return new MsgCatchPlayer(*this);
		}
	};
}