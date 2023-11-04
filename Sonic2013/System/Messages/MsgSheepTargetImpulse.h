#pragma once

namespace app::xgame
{
	class MsgSheepTargetImpulse : public fnd::Message
	{
	public:
		csl::math::Vector3 Unk1{};
		csl::math::Vector3 Unk2{};
		float Unk3{};
		float Unk4{};
		float Unk5{};
		bool Unk6{};

		inline const static unsigned int MessageID = 0x6051;

		MsgSheepTargetImpulse() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgSheepTargetImpulse(*this);
		}
	};
}