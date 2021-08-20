#pragma once

// We use Eigen as our math library, this file is basically a stub
#include "Eigen/Eigen"
#define MATHF_PI ((float)3.14159265359f)
#define MATHF_RADTODEG(X) (X * ((float)(180.0f / MATHF_PI)))
#define MATHF_DEGTORAD(X) (X * ((float)(MATHF_PI / 180.0f)))

namespace csl::math 
{
	class Vector2 : public Eigen::Vector2f
	{
	public:
		static const Vector2* Zero;
		
		Vector2() : Eigen::Vector2f()
		{

		}

		Vector2(const Eigen::Vector2f& rVec) : Eigen::Vector2f(rVec.x(), rVec.y())
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
		
		Vector3(const Eigen::Vector3f& vec) : Eigen::Vector3f(vec.x(), vec.y(), vec.z())
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

	class alignas(16) Matrix34 : public Eigen::Matrix4f
	{
	public:
		Vector4& GetColumn(uint column) const
		{
			return *(Vector4*)col(column).data();
		}

		Vector3& GetTransVector() const
		{
			return reinterpret_cast<Vector3&>(GetColumn(3));
		}
	};
	
	class alignas(16) Quaternion : public Eigen::Quaternionf
	{
	public:
		static const Quaternion Identity;
		
		Quaternion() : Eigen::Quaternionf()
		{
			
		}

		Quaternion(const Eigen::Quaternionf& quat) : Eigen::Quaternionf(quat)
		{
			
		}

		Quaternion(const Matrix34& matrix) : Eigen::Quaternionf(matrix.topLeftCorner<3, 3>())
		{
			
		}
		
		Quaternion(float x, float y, float z, float w) : Eigen::Quaternionf(w, x, y, z)
		{

		}
		
		friend bool operator==(const Quaternion& lhs, const Quaternion& rhs)
		{
			return lhs.isApprox(rhs);
		}

		friend bool operator!=(const Quaternion& lhs, const Quaternion& rhs)
		{
			return !lhs.isApprox(rhs);
		}
	};

	class alignas(16) Matrix44 : public Eigen::Matrix4f
	{
		
	};

	class Sphere
	{
	public:
		Vector3 m_Origin{};
		float m_Radius{};

		Sphere() {}
		Sphere(const Vector3& origin, float rad) : m_Origin(origin), m_Radius(rad) {}
		
		bool Intersects(const Vector3& point) const
		{
			return (m_Origin - point).squaredNorm() <= m_Radius * m_Radius;
		}
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
		Vector3 m_Unk;
		size_t m_Flags;

		Vector3 GetTranslation() const
		{
			return m_Mtx.GetTransVector();
		}
	};

	template<typename T>
	inline static const T& Clamp(const T& value, const T& min, const T& max)
	{
		if (value < min)
			return min;
		
		if (value > max)
			return max;
		
		return value;
	}

	template<typename T>
	inline static const T& Max(const T& value, const T& max)
	{
		if (value > max)
			return value;

		return max;
	}

	template<typename T>
	inline static const T& Min(const T& value, const T& min)
	{
		if (value < min)
			return value;

		return min;
	}
	
	class Constants
	{
	public:
		inline static const Vector2 Vector2Zero{ 0, 0 };
		inline static const Vector3 Vector3Zero{ 0, 0, 0 };
		inline static const Quaternion QuaternionIdentity{ 0, 0, 0, 1 };
	};

	inline const Vector2* Vector2::Zero = &Constants::Vector2Zero;
	inline const Vector3* Vector3::Zero = &Constants::Vector3Zero;
	inline const Quaternion Quaternion::Identity = Constants::QuaternionIdentity;
}