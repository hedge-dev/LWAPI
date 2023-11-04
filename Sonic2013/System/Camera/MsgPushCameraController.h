#pragma once

namespace app::xgame
{
	class MsgPushCameraController : public app::fnd::Message
	{
	public:
		Camera::CCameraController* pController{};
		float Easing{};
		bool Unk1{};
		size_t Priority{};
		Camera::EInterpolateType Interpolation{};
		bool Unk2{};
		
		inline const static unsigned int MessageID = 0x8005;

		MsgPushCameraController(Camera::CCameraController* in_pCamera, float in_easing, bool in_a3, size_t in_prio, Camera::EInterpolateType in_interpolate, bool in_a5) : Message(MessageID)
		{
			pController = in_pCamera;
			Easing = in_easing;
			Unk1 = in_a3;
			Priority = in_prio;
			Interpolation = in_interpolate;
			Unk2 = in_a5;
		}

		Message* Clone() override
		{
			return new MsgPushCameraController(*this);
		}
	};
}
