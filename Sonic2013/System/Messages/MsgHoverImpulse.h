#pragma once

namespace app::xgame
{
	class MsgHoverImpulse : public fnd::Message
	{
	public:
		csl::math::Vector3 Direction{};
		float OutOfControl{};
		float SpeedDropoffTime{};
		bool Unk3{};

		inline const static unsigned int MessageID = 0x6111;

		MsgHoverImpulse() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgHoverImpulse(*this);
		}
	};
}