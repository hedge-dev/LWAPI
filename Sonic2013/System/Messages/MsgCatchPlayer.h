#pragma once

namespace app::xgame
{
	class MsgCatchPlayer : public fnd::Message
	{
	public:
		csl::ut::Bitset<char> m_Unk1{};
		csl::math::Matrix34 m_Unk2{};
		int m_Unk3{};
		bool m_Unk4{};

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