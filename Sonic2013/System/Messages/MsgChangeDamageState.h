#pragma once

namespace app::Player
{
	class MsgChangeDamageState : public fnd::Message
	{
	public:
		csl::math::Vector3 Unk1{};
		xgame::MsgDamage* pDamageMsg{};

		inline const static unsigned int MessageID = 0x50AA;

		MsgChangeDamageState(const csl::math::Vector3& in_rVector) : Message(MessageID), Unk1(in_rVector)
		{
			
		}

		Message* Clone() override
		{
			return new MsgChangeDamageState(*this);
		}
	};
}