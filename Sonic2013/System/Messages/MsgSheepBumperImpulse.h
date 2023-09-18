#pragma once

namespace app::xgame
{
	class MsgSheepBumperImpulse : public fnd::Message
	{
	public:
		inline const static unsigned int MessageID = 0x604D;

		csl::math::Vector3 Unk1{};
		csl::math::Vector3 Unk2{};
		float Unk3{};
		float Unk4{};
		int Unk5{};

		MsgSheepBumperImpulse() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgSheepBumperImpulse(*this);
		}
	};
}