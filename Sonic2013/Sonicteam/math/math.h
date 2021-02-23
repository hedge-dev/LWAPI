#pragma once

namespace csl::math 
{
	class Vector2
	{
	public:
		static const Vector2* Zero;
		float x, y;

		Vector2() : x(0), y(0) {}
		Vector2(float _x, float _y) : x(_x), y(_y) {}

		float GetX() const { return x; }
		float GetY() const { return y; }

		Vector2 operator +(const Vector2& v2) const
		{
			return Vector2{ GetX() + v2.GetX(), GetY() + v2.GetY() };
		}

		Vector2 operator -(const Vector2& v2) const
		{
			return Vector2{ GetX() - v2.GetX(), GetY() - v2.GetY() };
		}
	};
	
	class alignas(16) Vector3
	{
	public:
		static const Vector3* Zero;
		float x, y, z;

		Vector3() : x(0), y(0), z(0) {}
		Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
	};
	
	class Angle3
	{
	public:
		float x, y, z;
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

	class alignas(16) Matrix44 
	{
	public:
		Vector4 columns[4];
	};

	class Transform
	{
	public:
		Vector3 m_Position;
		Quaternion m_Rotation;
		Vector3 m_Scale;
		bool m_IsDirty;
	};

	class CalculatedTransform
	{
	public:
		Matrix34 m_Mtx;
		Vector4 m_Unk1[2];
		size_t m_Flags;

		Vector4* GetTranslation(Vector4* vec = nullptr) const
		{
			return m_Mtx.GetTransVector(vec);
		}
	};
	
	class Constants
	{
	public:
		inline static const Vector2 Vector2Zero{ 0, 0 };
		inline static const Vector3 Vector3Zero{ 0, 0, 0 };
		inline static const Quaternion QuaternionIdentity{ 0, 0, 0, 1 };
	};
	
	inline const Vector2* Vector2::Zero = &Constants::Vector2Zero;
	inline const Vector3* Vector3::Zero = &Constants::Vector3Zero;
	inline const Quaternion* Quaternion::Identity = &Constants::QuaternionIdentity;
}