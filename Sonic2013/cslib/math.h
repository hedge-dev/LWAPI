#pragma once

namespace csl::math 
{
	struct alignas(16) Vector3
	{
		float x;
		float y;
		float z;

		Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
	};
}