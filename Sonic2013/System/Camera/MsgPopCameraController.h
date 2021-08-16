#pragma once

namespace app::xgame
{
	class MsgPopCameraController : public app::fnd::Message
	{
	public:
		inline static uint MessageID = 0x8006;
		Camera::CCameraController* m_pController{};
		float m_Easing{};
		bool m_Unk1{};
		Camera::EInterpolateType m_Interpolation{};
		bool m_Unk2{};

		MsgPopCameraController(Camera::CCameraController* pCamera, float easing, bool a3, Camera::EInterpolateType interpolate, bool a4) : Message(MessageID)
		{
			m_pController = pCamera;
			m_Easing = easing;
			m_Unk1 = a3;
			m_Interpolation = interpolate;
			m_Unk2 = a4;
		}

		Message* Clone() override
		{
			return new MsgPopCameraController(*this);
		}
	};
}