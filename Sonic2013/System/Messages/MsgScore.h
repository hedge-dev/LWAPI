#pragma once

namespace app::xgame
{
	class MsgScore : public fnd::Message
	{
	public:
		const char* m_pName{};
		csl::math::Vector3 m_Position{};
		int m_PlayerNo{};
		MsgDamageBase::BonusData m_BonusData{};
		bool m_Unk1{};
		int m_Unk2{};

		inline const static unsigned int MessageID = 0x4006;

		MsgScore() : Message(MessageID)
		{

		}

		Message* Clone() override
		{
			return new MsgScore(*this);
		}
	};
}