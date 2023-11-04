#pragma once

namespace app::xgame
{
	class MsgPLEnterDivingVolume : public fnd::Message
	{
	public:
		float Unk1{};
		int Unk2{};
		csl::math::Vector3 Unk3{};
		csl::math::Vector3 Unk4{};
		csl::math::Vector3 Unk5{};
		bool Unk6{};

		inline const static unsigned int MessageID = 0x506E;

		MsgPLEnterDivingVolume() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgPLEnterDivingVolume(*this);
		}
	};
}