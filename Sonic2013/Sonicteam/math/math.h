#pragma once

// We use Eigen as our math library, this file is basically a stub
#include "Eigen/Eigen"

namespace csl::math 
{
	class Vector2 : public Eigen::Vector2f
	{
	public:
		static const Vector2* Zero;
		
		Vector2() : Eigen::Vector2f()
		{

		}
		
		Vector2(float x, float y) : Eigen::Vector2f(x, y)
		{

		}

		float GetX() const { return x(); }
		float GetY() const { return y(); }
	};

	class alignas(16) Vector3 : public Eigen::Vector3f
	{
	public:
		static const Vector3* Zero;
		
		Vector3() : Eigen::Vector3f()
		{

		}
		
		Vector3(float x, float y, float z) : Eigen::Vector3f(x, y, z)
		{
			
		}

		float GetX() const { return x(); }
		float GetY() const { return y(); }
		float GetZ() const { return z(); }
	};

	class alignas(16) Vector4 : public Eigen::Vector4f
	{
	public:
		Vector4() : Eigen::Vector4f()
		{
			
		}
		
		Vector4(float x, float y, float z, float w) : Eigen::Vector4f(x, y, z, w)
		{

		}

		float GetX() const { return x(); }
		float GetY() const { return y(); }
		float GetZ() const { return z(); }
		float GetW() const { return w(); }
	};
	
	class Angle3 : public Eigen::Vector3f
	{
	public:
		Angle3() : Eigen::Vector3f()
		{
			
		}
		
		Angle3(float x, float y, float z) : Eigen::Vector3f(x, y, z)
		{

		}
	};

	class alignas(16) Quaternion : public Eigen::Quaternionf
	{
	public:
		static const Quaternion* Identity;
		
		Quaternion() : Eigen::Quaternionf()
		{
			
		}
		
		Quaternion(float x, float y, float z, float w) : Eigen::Quaternionf(w, x, y, z)
		{

		}
	};

	class alignas(16) Matrix34 : public Eigen::Matrix<float, 3, 4>
	{
	public:
		Vector4* GetColumn(uint column, Vector4* vec = nullptr) const 
		{
			if (!vec)
				vec = new Vector4();

			auto colum = col(column);
			*vec = Vector4{ colum[0], colum[1], colum[2], colum[3] };
			return vec;
		}

		Vector4* GetTransVector(Vector4* vec = nullptr) const 
		{
			return GetColumn(3, vec);
		}
	};

	class alignas(16) Matrix44 : public Eigen::Matrix4f
	{
		
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