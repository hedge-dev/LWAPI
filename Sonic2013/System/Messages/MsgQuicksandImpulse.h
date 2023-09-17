#pragma once

namespace app::xgame
{
	class MsgQuicksandImpulse : public fnd::Message
	{
	public:
		inline const static unsigned int MessageID = 0x6068;

		csl::math::Vector3 Unk1{};
		csl::math::Vector3 Unk2{};
		float Unk3{};

		MsgQuicksandImpulse() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgQuicksandImpulse(*this);
		}
	};
}