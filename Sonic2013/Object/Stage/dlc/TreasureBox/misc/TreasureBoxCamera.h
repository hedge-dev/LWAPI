#pragma once

namespace app::Camera
{
	class TreasureBoxCamera : public CCameraController
	{
	public:
		TreasureBoxCamera() : CCameraController()
		{

		}
		
		void OnEnter(const EnterEventArgs& in_rArgs) override
		{
			SetActive(true);
		}

		void SetFovy(float in_value)
		{
			CCameraController::SetFovy(in_value);
		}

		void SetCameraParameter(const csl::math::Vector3& in_rPosition, const csl::math::Vector3& in_rUp, const csl::math::Vector3& in_rLookAt)
		{
			SetCameraParam(in_rPosition, in_rUp, in_rLookAt);
		}
	};
}