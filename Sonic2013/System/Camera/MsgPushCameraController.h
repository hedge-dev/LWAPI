#pragma once

namespace app::xgame
{
	class MsgPushCameraController : public app::fnd::Message
	{
	public:
		inline static uint MessageID = 0x8005;
		Camera::CCameraController* m_pController{};
		float m_Easing{};
		bool m_Unk1{};
		size_t m_Priority{};
		Camera::EInterpolateType m_Interpolation{};
		bool m_Unk2{};
		
		MsgPushCameraController(Camera::CCameraController* pCamera, float easing, bool a3, size_t prio, Camera::EInterpolateType interpolate, bool a5) : Message(MessageID)
		{
			m_pController = pCamera;
			m_Easing = easing;
			m_Unk1 = a3;
			m_Priority = prio;
			m_Interpolation = interpolate;
			m_Unk2 = a5;
		}

		Message* Clone() override
		{
			return new MsgPushCameraController(*this);
		}
	};
}
