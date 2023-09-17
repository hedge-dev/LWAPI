#pragma once

namespace app::xgame
{
	class MsgAppeareKnockback : public fnd::Message
	{
	public:
		inline const static unsigned int MessageID = 0x610E;

		csl::math::Vector3 Velocity{};
		bool Unk1{};

		MsgAppeareKnockback() : Message(MessageID)
		{

		}

		Message* Clone() override
		{
			return new MsgAppeareKnockback(*this);
		}
	};
}