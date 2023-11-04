#pragma once

namespace app::xgame
{
	class MsgFlipperImpulse : public fnd::Message
	{
	public:
		csl::math::Vector3 Velocity{};
		float Unk2{};
		float Unk3{};
		bool Unk4{};

		inline const static unsigned int MessageID = 0x6006;

		MsgFlipperImpulse() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgFlipperImpulse(*this);
		}
	};
}