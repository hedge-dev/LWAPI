#pragma once

namespace app::xgame
{
	class MsgBumperImpulse : public fnd::Message
	{
	public:
		inline const static unsigned int MessageID = 0x6005;

		csl::math::Vector3 Velocity{};
		float Unk2{};
		float Unk3{};
		bool Unk4{};
		bool Unk5{};
		bool Unk6{};

		MsgBumperImpulse() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgBumperImpulse(*this);
		}
	};
}