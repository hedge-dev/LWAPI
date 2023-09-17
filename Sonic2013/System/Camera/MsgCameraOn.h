#pragma once

namespace app::xgame
{
	class MsgCameraOn : public fnd::Message
	{
	public:
		float Unk1{};
		bool Unk2{};
		size_t Unk3{};
		app::Camera::EInterpolateType Type{};
		uint PlayerNo{};
		bool Unk5{};

		inline const static unsigned int MessageID = 0x8009;
		
		MsgCameraOn(float in_unk1, bool in_unk2, size_t in_unk3, app::Camera::EInterpolateType in_type, uint in_playerNo, bool in_unk5) : Message(MessageID)
		{
			Unk1 = in_unk1;
			Unk2 = in_unk2;
			Unk3 = in_unk3;
			PlayerNo = in_playerNo;
			Unk5 = in_unk5;
		}

		Message* Clone() override
		{
			return new MsgCameraOn(*this);
		}
	};
}