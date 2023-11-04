#pragma once

namespace app::xgame
{
	class MsgPopCameraController : public app::fnd::Message
	{
	public:
		Camera::CCameraController* pController{};
		float Easing{};
		bool Unk1{};
		Camera::EInterpolateType Interpolation{};
		bool Unk2{};

		inline const static unsigned int MessageID = 0x8006;

		MsgPopCameraController(Camera::CCameraController* in_pCamera, float in_easing, bool in_a3, Camera::EInterpolateType in_interpolate, bool in_a4) : Message(MessageID)
		{
			pController = in_pCamera;
			Easing = in_easing;
			Unk1 = in_a3;
			Interpolation = in_interpolate;
			Unk2 = in_a4;
		}

		Message* Clone() override
		{
			return new MsgPopCameraController(*this);
		}
	};
}