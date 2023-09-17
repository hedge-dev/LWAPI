#pragma once

namespace SurfRide
{
	struct SRS_CAMERA
	{
		const char* pName{};
		int ID{};
		Math::Vector3 Position{};
		Math::Vector3 Target{};
		int Flags{};
		float NearPlane{};
		float FarPlane{};
		INSERT_PADDING(8);
	};

	class Camera
	{
	public:
		const char* pName{};
		int ID{};
		Math::Vector3 Position{};
		Math::Vector3 Target{};
		int FieldOfView{};
		float NearPlane{};
		float FarPlane{};
		INSERT_PADDING(8);
		INSERT_PADDING(48);
	};
}