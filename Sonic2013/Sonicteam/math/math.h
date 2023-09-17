#pragma once

// We use Eigen as our math library, this file is basically a stub
#include "Eigen/Eigen"
#define MATHF_PI ((float)3.14159265359f)
#define MATHF_RADTODEG(X) (X * ((float)(180.0f / MATHF_PI)))
#define MATHF_DEGTORAD(X) (X * ((float)(MATHF_PI / 180.0f)))

namespace csl::math
{
	class Matrix34;
	class Vector3;
	class Quaternion;
}

namespace app::math
{
	static void Matrix34RotationRollPitchYaw(csl::math::Matrix34* in_pMtx, float in_roll, float in_pitch, float in_yaw);
	static csl::math::Matrix34 Matrix34AffineTransformation(const csl::math::Vector3& in_rPosition, const csl::math::Quaternion& in_rRotation);
	static bool Vector3NormalizeIfNotZero(const csl::math::Vector3& in_rVec, csl::math::Vector3* out_pVec);
}

namespace csl::math 
{
	inline static FUNCTION_PTR(Quaternion*, __cdecl, ms_fpQuaternionRotationBetweenNormals, ASLR(0x00963DA0), Quaternion*, const Vector3&, const Vector3&);

	static bool IsInfinite(float value) { return isinf(value); }
	static bool IsNaN(float value) { return isnan(value); }

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
		if (value >= max)
			return value;

		return max;
	}

	template<typename T>
	inline static const T& Min(const T& value, const T& min)
	{
		if (value <= min)
			return value;

		return min;
	}

	template<typename T>
	inline static const T& Sqrt(const T& value)
	{
		if (value >= 0.0f)
			return sqrt(value);

		return 0.0f;
	}

	template<typename T>
	inline static const T& Lerp(const T& a, const T& b, float t)
	{
		return a + (b - a) * t;
	}

	inline static const float Select(float a, float b, float c)
	{
		return a >= 0.0f ? b : c;
	}

	inline static const float Nabs(float val)
	{
		return -fabs(val);
	}

	class Vector2 : public Eigen::Vector2f
	{
	public:
		static const Vector2* Zero;
		
		Vector2() : Eigen::Vector2f()
		{
			setIdentity();
		}

		Vector2(const Eigen::Vector2f& rVec) : Eigen::Vector2f(rVec.x(), rVec.y())
		{
			
		}
		
		Vector2(float x, float y) : Eigen::Vector2f(x, y)
		{

		}

		float GetX() const { return x(); }
		float GetY() const { return y(); }
		
		float LengthSq() const{ return powf(x(), 2) + powf(y(), 2); }
		float Length() const { return csl::math::Sqrt(LengthSq()); }
		csl::math::Vector2 Normalize()
		{
			float length = Length();
			if (fabs(length) >=  0.0001f)
			{
				return { 0.0f, 0.0f };
			}
			else
			{
				return { *this / length };
			}
		}

		void Set(float in_x, float in_y)
		{
			*this = { in_x, in_y };
		}
	};

	class alignas(16) Vector3 : public Eigen::Vector3f
	{
	public:
		static const Vector3* Zero;
		
		Vector3() : Eigen::Vector3f()
		{
			*this = *Zero;
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

		bool IsInfinite() const { return csl::math::IsInfinite(GetX()) && csl::math::IsInfinite(GetY()) && csl::math::IsInfinite(GetZ()); }
		bool IsNaN() const { return csl::math::IsNaN(GetX()) && csl::math::IsNaN(GetY()) && csl::math::IsNaN(GetZ()); }
		float Length() const { return norm(); }
		
		csl::math::Vector3 Normalize()
		{
			return { *this / Length() };
		}
	};

	class alignas(16) Vector4 : public Eigen::Vector4f
	{
	public:
		Vector4() : Eigen::Vector4f()
		{
			setIdentity();
		}

		Vector4(const Vector3& vec, float w) : Eigen::Vector4f(vec[0], vec[1], vec[2], w)
		{
			
		}

		Vector4(float x, float y, float z, float w) : Eigen::Vector4f(x, y, z, w)
		{

		}

		Vector4(const Eigen::Vector4f& vec) : Eigen::Vector4f(vec.x(), vec.y(), vec.z(), vec.w())
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
			setIdentity();
		}
		
		Angle3(float x, float y, float z) : Eigen::Vector3f(x, y, z)
		{

		}
	};

	class Quaternion;

	class alignas(16) Matrix34 : public Eigen::Matrix4f
	{
	public:
		Matrix34() : Eigen::Matrix4f()
		{
			setIdentity();
		}

		Matrix34(float x, float y, float z) : Eigen::Matrix4f()
		{
			setIdentity();
			SetTransVector({ x, y, z });
		}

		Matrix34(char axis, float rad) : Eigen::Matrix4f()
		{
			setIdentity();

			Eigen::Quaternionf q{};
			if (axis == 'x')
			{
				q = { Eigen::AngleAxisf(rad, csl::math::Angle3::UnitX()) };
			}
			else if (axis == 'y')
			{
				q = { Eigen::AngleAxisf(rad, csl::math::Angle3::UnitY()) };
			}
			else if (axis == 'Z')
			{
				q = { Eigen::AngleAxisf(rad, csl::math::Angle3::UnitZ()) };
			}

			Eigen::Matrix3f mtx = q.toRotationMatrix();
			SetColumn(0, (csl::math::Vector3)mtx.col(0));
			SetColumn(1, (csl::math::Vector3)mtx.col(1));
			SetColumn(2, (csl::math::Vector3)mtx.col(2));
		}

		Matrix34(const Eigen::Quaternionf& in_rRotation) : Eigen::Matrix4f()
		{
			setIdentity();

			Eigen::Matrix3f mtx = in_rRotation.toRotationMatrix();

			SetColumn(0, (csl::math::Vector3)mtx.col(0));
			SetColumn(1, (csl::math::Vector3)mtx.col(1));
			SetColumn(2, (csl::math::Vector3)mtx.col(2));
		}

		Vector3& GetColumn(uint column) const
		{
			return *(Vector3*)col(column).data();
		}

		void SetColumn(uint column, const Vector3& data)
		{
			*(Vector3*)col(column).data() = data;
		}

		Vector3& GetTransVector() const
		{
			return reinterpret_cast<Vector3&>(GetColumn(3));
		}

		Quaternion& GetRotation() const
		{
			Eigen::Matrix3f rotMtx{};
			rotMtx.col(0) = GetColumn(0);
			rotMtx.col(1) = GetColumn(1);
			rotMtx.col(2) = GetColumn(2);

			Eigen::Quaternionf q(rotMtx);
			return reinterpret_cast<Quaternion&>(q);
		}

		void SetTransVector(const Vector3& translation)
		{
			SetColumn(3, translation);
		}

		bool Invert(Matrix34* out_pMatrix)
		{
			bool isInvertible;
			float determinant;

			Eigen::Matrix4f inverse{};
			computeInverseAndDetWithCheck(inverse, determinant, isInvertible);
			if (out_pMatrix)
				*out_pMatrix = *static_cast<Matrix34*>(&inverse);

			return isInvertible != false;
		}

		Vector3 operator*(const Vector3& in_rVec)
		{
			Eigen::Matrix3f mtx{};
			mtx.col(0) = GetColumn(0);
			mtx.col(1) = GetColumn(1);
			mtx.col(2) = GetColumn(2);

			return { mtx * in_rVec };
		}

		Vector3 operator*(const Vector4& in_rVec)
		{
			return { (Eigen::Matrix4f(*this) * in_rVec).head<3>() };
		}

		Matrix34 operator*(const Matrix34 in_rOther)
		{
			Eigen::Matrix4f mtx = Eigen::Matrix4f(*this) * Eigen::Matrix4f(in_rOther);
			
			setIdentity();
			SetColumn(0, { mtx.col(0).head<3>() });
			SetColumn(1, { mtx.col(1).head<3>() });
			SetColumn(2, { mtx.col(2).head<3>() });
			SetColumn(3, { mtx.col(3).head<3>() });

			return *this;
		}

		Vector3 operator*(const Vector4& in_rVec) const
		{
			return { (Eigen::Matrix4f(*this) * in_rVec).head<3>() };
		}
	};
	
	class alignas(16) Quaternion : public Eigen::Quaternionf
	{
	public:
		static const Quaternion Identity;
		
		Quaternion() : Eigen::Quaternionf(0.0f, 0.0f, 0.0f, 1.0f)
		{
			setIdentity();
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

		Quaternion(const Eigen::AngleAxisf& angleAxis) : Eigen::Quaternionf(angleAxis)
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

		csl::math::Quaternion Normalize()
		{
			return { normalized() };
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

	class Segment3
	{
	public:
		Vector3 m_Start{};
		Vector3 m_End{};

		Segment3() {}
		Segment3(const Vector3& start, const Vector3& end) : m_Start(start), m_End(end) {}
		
		bool Intersects(const Sphere& sphere) const
		{
			Vector3 closestPoint = m_Start;
			float distance = (m_End - m_Start).norm();
			float t = 0.0f;
			
			if (distance > 0.0f)
			{
				t = (sphere.m_Origin - m_Start).dot(m_End - m_Start) / distance;
				
				if (t < 0.0f)
				{
					t = 0.0f;
				}
				else if (t > 1.0f)
				{
					t = 1.0f;
				}
				
				closestPoint = Vector3(m_Start + t * (m_End - m_Start));
			}
			
			return (sphere.m_Origin - closestPoint).squaredNorm() <= sphere.m_Radius * sphere.m_Radius;
		}
	};

	class Capsule
	{
	public:
		Segment3 m_Segment{};
		float m_Radius{};

		Capsule() {}
		Capsule(const Segment3& segment, float rad) : m_Segment(segment), m_Radius(rad) {}

		bool Intersects(const Sphere& sphere) const
		{
			Vector3 closestPoint = m_Segment.m_Start;
			float distance = (m_Segment.m_End - m_Segment.m_Start).norm();
			float t = 0.0f;
			
			if (distance > 0.0f)
			{
				t = (sphere.m_Origin - m_Segment.m_Start).dot(m_Segment.m_End - m_Segment.m_Start) / distance;
				
				if (t < 0.0f)
				{
					t = 0.0f;
				}
				else if (t > 1.0f)
				{
					t = 1.0f;
				}
				
				closestPoint = Vector3(m_Segment.m_Start + t * (m_Segment.m_End - m_Segment.m_Start));
			}
			
			return (sphere.m_Origin - closestPoint).squaredNorm() <= sphere.m_Radius * sphere.m_Radius;
		}
	};
	
	class Aabb
	{
	public:
		Vector3 m_Min{};
		Vector3 m_Max{};

		Aabb() {}
		Aabb(const Vector3& min, const Vector3& max) : m_Min(min), m_Max(max) {}
		void Add(const Vector3& point)
		{
			m_Min = { m_Min.cwiseMin(point) };
			m_Max = { m_Max.cwiseMax(point) };
		}
	};

	class Plane
	{
	public:
		Vector3 Normal{};
		float Distance{};
		
		Plane() {}
		
		bool IsValid()
		{
			// Sonic Team's implementation of this is entirely invalid, but it's kept here to have it immortalized.
			// if (!Direction.IsInfinite() && !Direction.IsNaN() && IsInfinite(Angle))

			if (!Normal.IsInfinite() && !Normal.IsNaN() && !IsInfinite(Distance))
				return true;

			return false;
		}

		static Plane& FromPointNormal(const Vector3& in_rPoint, const Vector3& in_rNormal)
		{
			Plane plane{};
			plane.Normal = in_rNormal;
			plane.Distance = -in_rPoint.dot(in_rNormal);

			return plane;
		}
	};

	inline static bool Matrix34Inverse(const Matrix34& in_rMatrix, Matrix34* out_pMatrix)
	{
		Matrix34 mtx = in_rMatrix;
		if (mtx.Invert(out_pMatrix))
			return true;

		return false;
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

	static bool Vector3NearZero(const Vector3& in_rVec)
	{
		return fabs(powf(in_rVec.x(), 2.0f) + powf(in_rVec.y(), 2.0f) + powf(in_rVec.z(), 2.0f)) <= 0.0001f;
	}

	static float Vector3Length(const Vector3& in_rVec)
	{
		return in_rVec.norm();
	}

	static Vector3 Vector3Cross(const Vector3& in_rLeft, const Vector3& in_rRight)
	{
		return in_rLeft.cross(in_rRight);
	}

	static Quaternion* QuaternionRotationBetweenNormals(Quaternion* out_pRotation, const Vector3& in_rLeft, const Vector3& in_rRight)
	{
		return ms_fpQuaternionRotationBetweenNormals(out_pRotation, in_rLeft, in_rRight);
	}

	static Quaternion QuaternionNormalize(Quaternion in_rotation)
	{
		return in_rotation.normalized();
	}

	static csl::math::Quaternion QuaternionMultiply(const Quaternion& in_rLeft, const Quaternion& in_rRight)
	{
		return in_rLeft * in_rRight;
	}
}

namespace app::math
{
	inline bool Vector2Normalize(const csl::math::Vector2& in_rVec, csl::math::Vector2* out_pVec, float* out_pFloat)
	{
		float length = powf(in_rVec.x(), 2) + powf(in_rVec.y(), 2);
		if (length < 0.001f)
		{
			*out_pVec = in_rVec;
			*out_pFloat = 0.0f;
			return false;
		}

		*out_pVec = in_rVec;
		out_pVec->Normalize();
		*out_pFloat = csl::math::Sqrt(length);
		return true;
	}

	inline bool Vector3Normalize(const csl::math::Vector3& in_rVec, csl::math::Vector3* out_pVec)
	{
		if (in_rVec.squaredNorm() < 0.000001f)
		{
			*out_pVec = in_rVec;
			return false;
		}

		*out_pVec = in_rVec;
		out_pVec->Normalize();

		return true;
	}

	inline void Vector3NormalizeZero(const csl::math::Vector3& in_rVec, csl::math::Vector3* out_pVec)
	{
		if (in_rVec.squaredNorm() < 0.0001f)
		{
			*out_pVec = *csl::math::Vector3::Zero;
			return;
		}

		*out_pVec = in_rVec.normalized();
	}

	inline float Vector3NormalizeWithLength(const csl::math::Vector3& in_rVec, csl::math::Vector3* out_pVec)
	{
		float squaredNorm = in_rVec.squaredNorm();
		if (squaredNorm < 0.0001f)
		{
			*out_pVec = *csl::math::Vector3::Zero;
			return false;
		}

		*out_pVec = in_rVec.normalized();
		return csl::math::Sqrt(squaredNorm);
	}

	inline csl::math::Vector3 Vector3Rotate(const csl::math::Quaternion& in_rQuat, const csl::math::Vector3& in_rDir)
	{
		auto rotMtx = in_rQuat.toRotationMatrix();
		return csl::math::Vector3(rotMtx * in_rDir);
	}

	inline csl::math::Vector3 Vector3RotateX(float angle, const csl::math::Vector3& in_rDir)
	{
		csl::math::Quaternion rot(Eigen::AngleAxisf(angle, csl::math::Vector3::UnitX()));
		auto rotMtx = rot.toRotationMatrix();
		return csl::math::Vector3(rotMtx * in_rDir);
	}

	inline csl::math::Vector3 Vector3RotateY(float angle, const csl::math::Vector3& in_rDir)
	{
		csl::math::Quaternion rot(Eigen::AngleAxisf(angle, csl::math::Vector3::UnitY()));
		auto rotMtx = rot.toRotationMatrix();
		return csl::math::Vector3(rotMtx * in_rDir);
	}

	inline csl::math::Matrix34& Matrix34OrthonormalDirection(const csl::math::Vector3& in_rU, const csl::math::Vector3& in_rV)
	{
		csl::math::Vector3 cross{ in_rV.cross(in_rU)};
		if (!math::Vector3Normalize(cross, &cross))
			cross = { 1.0f, 0.0f, 0.0f };
	
		csl::math::Vector3 ortho{ in_rU.cross(cross) };

		csl::math::Matrix34 mtx{};
		mtx.SetColumn(0, cross);
		mtx.SetColumn(1, ortho);
		mtx.SetColumn(2, in_rU);
		mtx.SetColumn(3, { 0.0f, 0.0f, 0.0f });

		return mtx;
	}

	inline void Matrix34RotationRollPitchYaw(csl::math::Matrix34* out_pMtx, float in_roll, float in_pitch, float in_yaw)
	{
		csl::math::Quaternion q
		(
			Eigen::AngleAxisf(in_roll, csl::math::Angle3::UnitX())
			* Eigen::AngleAxisf(in_pitch, csl::math::Angle3::UnitY())
			* Eigen::AngleAxisf(in_yaw, csl::math::Angle3::UnitZ())
		);

		auto rotMtx = q.toRotationMatrix();
		out_pMtx->SetColumn(0, (csl::math::Vector3)rotMtx.col(0));
		out_pMtx->SetColumn(1, (csl::math::Vector3)rotMtx.col(1));
		out_pMtx->SetColumn(2, (csl::math::Vector3)rotMtx.col(2));
	}
	
	inline csl::math::Matrix34 Matrix34AffineTransformation(const csl::math::Vector3& in_rPosition, const csl::math::Quaternion& in_rRotation)
	{
		csl::math::Matrix34 mtx{};
		auto rotMtx = in_rRotation.toRotationMatrix();
		mtx.SetColumn(0, (csl::math::Vector3)rotMtx.col(0));
		mtx.SetColumn(1, (csl::math::Vector3)rotMtx.col(1));
		mtx.SetColumn(2, (csl::math::Vector3)rotMtx.col(2));
		mtx.SetTransVector(in_rPosition);

		return mtx;
	}

	inline bool Vector3NormalizeIfNotZero(const csl::math::Vector3& in_rVec, csl::math::Vector3* out_pVec)
	{
		if (in_rVec.squaredNorm() < 0.0001)
		{
			if (out_pVec)
				*out_pVec = *csl::math::Vector3::Zero;
			
			return false;
		}

		if (out_pVec)
			*out_pVec = in_rVec.normalized();
		
		return true;
	}

	class CalculatedTransform
	{
	public:
		csl::math::Matrix34 m_Mtx;
		csl::math::Vector3 m_Scale;
		size_t m_Flags;

		csl::math::Vector3 GetTranslation() const
		{
			return m_Mtx.GetTransVector();
		}

		void SetTranslation(const csl::math::Vector3& translation)
		{
			m_Mtx.SetTransVector(translation);
			SetFlag(1);
		}

		void SetRotation(const csl::math::Quaternion& in_rRotation)
		{
			Eigen::Matrix3f mtx = in_rRotation.toRotationMatrix();

			m_Mtx.SetColumn(0, (csl::math::Vector3)mtx.col(0));
			m_Mtx.SetColumn(1, (csl::math::Vector3)mtx.col(1));
			m_Mtx.SetColumn(2, (csl::math::Vector3)mtx.col(2));

			SetFlag(1);
		}

		void SetRotationXYZ(float in_roll, float in_pitch, float in_yaw)
		{
			app::math::Matrix34RotationRollPitchYaw(&m_Mtx, in_roll, in_pitch, in_yaw);
			SetFlag(1);
		}

		csl::math::Quaternion GetRotationQuaternion() const
		{
			return m_Mtx.GetRotation();
		}

		void SetFlag(size_t value)
		{
			m_Flags |= value;
		}
	};

	class Transform
	{
	public:
		csl::math::Vector3 m_Position;
		csl::math::Quaternion m_Rotation;
		csl::math::Vector3 m_Scale;
		bool m_IsDirty;

		csl::math::Matrix34 GetTransformMatrix() const
		{
			return Matrix34AffineTransformation(m_Position, m_Rotation);
		}

		void SetFlag(size_t flag)
		{
			m_IsDirty |= flag;
		}
	};
}