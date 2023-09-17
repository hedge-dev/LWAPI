#pragma once

namespace app::xgame
{
	class MsgCameraOff : public fnd::Message
	{
	public:
		float Unk1{};
		bool Unk2{};
		bool Unk3{};
		Camera::EInterpolateType InterpolationType{};
		uint PlayerNo{};

		inline const static unsigned int MessageID = 0x800A;

		MsgCameraOff(float in_unk1, bool in_unk2, bool in_unk3, Camera::EInterpolateType in_interpolationType, uint in_playerNo)
			: Message(MessageID)
			, Unk1(in_unk1)
			, Unk2(in_unk2)
			, Unk3(in_unk3)
			, InterpolationType(in_interpolationType)
			, PlayerNo(in_playerNo)
		{

		}

		Message* Clone() override
		{
			return new MsgCameraOff(*this);
		}
	};
}