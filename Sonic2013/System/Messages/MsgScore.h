#pragma once

namespace app::xgame
{
	class MsgScore : public fnd::Message
	{
	public:
		const char* pName{};
		csl::math::Vector3 Position{};
		int PlayerNo{};
		MsgDamageBase::BonusData BonusData{};
		bool Unk1{};
		int Unk2{};

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