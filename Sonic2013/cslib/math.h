#pragma once

namespace csl::math 
{
	class alignas(16) Vector3
	{
	public:
		static const Vector3* Zero;
		float x, y, z;

		Vector3() : x(0), y(0), z(0) {}
		Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
	};
	
	class alignas(16) Quaternion
	{
	public:
		static const Quaternion* Identity;
		float x, y, z, w;
	};

	class Constants
	{
	public:
		inline static const Vector3 Vector3Zero{ 0, 0, 0 };
		inline static const Quaternion QuaternionIdentity{ 0, 0, 0, 1 };
	};

	inline const Vector3* Vector3::Zero = &Constants::Vector3Zero;
	inline const Quaternion* Quaternion::Identity = &Constants::QuaternionIdentity;
}