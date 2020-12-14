#pragma once

namespace csl::math 
{
	struct alignas(16) Vector3
	{
		float x, y, z;

		Vector3() : x(0), y(0), z(0) {}
		Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
	};

	struct alignas(16) Quaternion
	{
		float x, y, z, w;
	};
}