#pragma once

namespace app::xgame
{
	class MsgHoverImpulse : public fnd::Message
	{
	public:
		inline const static unsigned int MessageID = 0x6111;

		csl::math::Vector3 Direction{};
		float OutOfControl{};
		float SpeedDropoffTime{};
		bool Unk3{};

		MsgHoverImpulse() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgHoverImpulse(*this);
		}
	};
}