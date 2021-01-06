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
	
	class alignas(16) Vector4 
	{
	public:
		float x, y, z, w;
	};

	class alignas(16) Quaternion
	{
	public:
		static const Quaternion* Identity;
		float x, y, z, w;
	};

	class alignas(16) Matrix34 
	{
	private:
		Vector4 columns[3];

	public:
		Vector4* GetColumn(uint column, Vector4* vec = nullptr) const 
		{
			if (!vec)
				vec = new Vector4();

			*vec = columns[column];
			return vec;
		}

		Vector4* GetTransVector(Vector4* vec = nullptr) const 
		{
			return GetColumn(3, vec);
		}
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