#pragma once

namespace app::xgame
{
	class MsgPlayerPassPointMarker : public fnd::Message
	{
	public:
		csl::math::Vector3 Position{};
		csl::math::Quaternion Rotation{};
		bool Unk1{};
		bool Unk2{};
		int Unk3{};
		int Unk4{};

		inline const static unsigned int MessageID = 0x6017;

		MsgPlayerPassPointMarker(const csl::math::Vector3& in_rPosition, const csl::math::Quaternion& in_rRotation, bool in_unk1, bool in_unk2, uint in_unk3)
			: Message(MessageID)
			, Position(in_rPosition)
			, Rotation(in_rRotation)
			, Unk1(in_unk1)
			, Unk2(in_unk2)
			, Unk3(in_unk3)
		{
			
		}

		Message* Clone() override
		{
			return new MsgPlayerPassPointMarker(*this);
		}
	};
}