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
	static bool IsInfinite(float in_value) { return isinf(in_value); }
	static bool IsNaN(float in_value) { return isnan(in_value); }

	template<typename T>
	inline static const T& Clamp(const T& in_value, const T& in_min, const T& in_max)
	{
		if (in_value < in_min)
			return min;

		if (in_value > in_max)
			return max;

		return in_value;
	}

	template<typename T>
	inline static const T& Max(const T& in_value, const T& in_max)
	{
		if (in_value >= in_max)
			return in_value;

		return in_max;
	}

	template<typename T>
	inline static const T& Min(const T& in_value, const T& in_min)
	{
		if (in_value <= in_min)
			return in_value;

		return in_min;
	}

	template<typename T>
	inline static const T Sqrt(const T& in_value)
	{
		if (in_value >= 0.0f)
			return sqrt(in_value);

		return 0.0f;
	}

	template<typename T>
	inline static const T Lerp(const T& in_a, const T& in_b, float in_t)
	{
		return in_a + (in_b - in_a) * in_t;
	}

	inline static const float Select(float in_a, float in_b, float in_c)
	{
		return in_a >= 0.0f ? in_b : in_c;
	}

	inline static const float Nabs(float in_val)
	{
		return -fabs(in_val);
	}

	class Vector2 : public Eigen::Vector2f
	{
	public:
		static const Vector2* Zero;
		
		Vector2() : Eigen::Vector2f()
		{
			setIdentity();
		}

		Vector2(const Eigen::Vector2f& in_rVec) : Eigen::Vector2f(in_rVec.x(), in_rVec.y())
		{
			
		}
		
		Vector2(float in_x, float in_y) : Eigen::Vector2f(in_x, in_y)
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
		
		Vector3(float in_x, float in_y, float in_z) : Eigen::Vector3f(in_x, in_y, in_z)
		{
			
		}
		
		Vector3(const Eigen::Vector3f& in_rVec) : Eigen::Vector3f(in_rVec.x(), in_rVec.y(), in_rVec.z())
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

		Vector4(const Vector3& in_rVec, float in_w) : Eigen::Vector4f(in_rVec[0], in_rVec[1], in_rVec[2], in_w)
		{
			
		}

		Vector4(float in_x, float in_y, float in_z, float in_w) : Eigen::Vector4f(in_x, in_y, in_z, in_w)
		{

		}

		Vector4(const Eigen::Vector4f& in_rVec) : Eigen::Vector4f(in_rVec.x(), in_rVec.y(), in_rVec.z(), in_rVec.w())
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
		
		Angle3(float in_x, float in_y, float in_z) : Eigen::Vector3f(in_x, in_y, in_z)
		{

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

		Quaternion(const Eigen::Quaternionf& in_rQuat) : Eigen::Quaternionf(in_rQuat)
		{

		}

		Quaternion(const Matrix34& in_rMatrix);

		Quaternion(float in_x, float in_y, float in_z, float in_w) : Eigen::Quaternionf(in_w, in_x, in_y, in_z)
		{

		}

		Quaternion(const Eigen::AngleAxisf& in_rAngleAxis) : Eigen::Quaternionf(in_rAngleAxis)
		{

		}

		friend bool operator==(const Quaternion& in_rLhs, const Quaternion& in_rRhs)
		{
			return in_rLhs.isApprox(in_rRhs);
		}

		friend bool operator!=(const Quaternion& in_rLhs, const Quaternion& in_rRhs)
		{
			return !in_rLhs.isApprox(in_rRhs);
		}

		csl::math::Quaternion Normalize()
		{
			return { normalized() };
		}
	};

	class alignas(16) Matrix34 : public Eigen::Matrix4f
	{
	public:
		Matrix34() : Eigen::Matrix4f()
		{
			setIdentity();
		}

		Matrix34(float in_x, float in_y, float in_z) : Eigen::Matrix4f()
		{
			setIdentity();
			SetTransVector({ in_x, in_y, in_z });
		}

		Matrix34(char in_axis, float in_rad) : Eigen::Matrix4f()
		{
			setIdentity();

			Eigen::Quaternionf q{};
			if (in_axis == 'x')
			{
				q = { Eigen::AngleAxisf(in_rad, csl::math::Angle3::UnitX()) };
			}
			else if (in_axis == 'y')
			{
				q = { Eigen::AngleAxisf(in_rad, csl::math::Angle3::UnitY()) };
			}
			else if (in_axis == 'Z')
			{
				q = { Eigen::AngleAxisf(in_rad, csl::math::Angle3::UnitZ()) };
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

		Vector3& GetColumn(uint in_column) const
		{
			return *(Vector3*)col(in_column).data();
		}

		void SetColumn(uint in_column, const Vector3& in_rData)
		{
			*(Vector3*)col(in_column).data() = in_rData;
		}

		Vector3& GetTransVector() const
		{
			return reinterpret_cast<Vector3&>(GetColumn(3));
		}

		Quaternion GetRotation() const
		{
			Eigen::Matrix3f rotMtx{};
			rotMtx.col(0) = GetColumn(0);
			rotMtx.col(1) = GetColumn(1);
			rotMtx.col(2) = GetColumn(2);

			Eigen::Quaternionf q(rotMtx);
			return Quaternion(q);
		}

		void SetTransVector(const Vector3& in_rTranslation)
		{
			SetColumn(3, in_rTranslation);
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

		Vector3 operator*(const Vector3& in_rVec) const
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

	class alignas(16) Matrix44 : public Eigen::Matrix4f
	{
		
	};

	class Sphere
	{
	public:
		Vector3 Origin{};
		float Radius{};

		Sphere() {}
		Sphere(const Vector3& in_rOrigin, float in_rad) : Origin(in_rOrigin), Radius(in_rad) {}
		
		bool Intersects(const Vector3& in_rPoint) const
		{
			return (Origin - in_rPoint).squaredNorm() <= Radius * Radius;
		}
	};

	class Segment3
	{
	public:
		Vector3 Start{};
		Vector3 End{};

		Segment3() {}
		Segment3(const Vector3& in_rStart, const Vector3& in_rEnd) : Start(in_rStart), End(in_rEnd) {}
		
		bool Intersects(const Sphere& in_rSphere) const
		{
			Vector3 closestPoint = Start;
			float distance = (End - Start).norm();
			float t = 0.0f;
			
			if (distance > 0.0f)
			{
				t = (in_rSphere.Origin - Start).dot(End - Start) / distance;
				
				if (t < 0.0f)
				{
					t = 0.0f;
				}
				else if (t > 1.0f)
				{
					t = 1.0f;
				}
				
				closestPoint = Vector3(Start + t * (End - Start));
			}
			
			return (in_rSphere.Origin - closestPoint).squaredNorm() <= in_rSphere.Radius * in_rSphere.Radius;
		}
	};

	class Capsule
	{
	public:
		Segment3 Segment{};
		float Radius{};

		Capsule() {}
		Capsule(const Segment3& in_rSegment, float in_rad) : Segment(in_rSegment), Radius(in_rad) {}

		bool Intersects(const Sphere& in_rSphere) const
		{
			Vector3 closestPoint = Segment.Start;
			float distance = (Segment.End - Segment.Start).norm();
			float t = 0.0f;
			
			if (distance > 0.0f)
			{
				t = (in_rSphere.Origin - Segment.Start).dot(Segment.End - Segment.Start) / distance;
				
				if (t < 0.0f)
				{
					t = 0.0f;
				}
				else if (t > 1.0f)
				{
					t = 1.0f;
				}
				
				closestPoint = Vector3(Segment.Start + t * (Segment.End - Segment.Start));
			}
			
			return (in_rSphere.Origin - closestPoint).squaredNorm() <= in_rSphere.Radius * in_rSphere.Radius;
		}
	};
	
	class Aabb
	{
	public:
		Vector3 Min{};
		Vector3 Max{};

		Aabb() {}
		Aabb(const Vector3& in_rMin, const Vector3& in_Max) : Min(in_rMin), Max(in_Max) {}
		void Add(const Vector3& in_rPoint)
		{
			Min = { Min.cwiseMin(in_rPoint) };
			Max = { Max.cwiseMax(in_rPoint) };
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
		FUNCTION_PTR(Quaternion*, __cdecl, fpQuaternionRotationBetweenNormals, ASLR(0x00963DA0), Quaternion*, const Vector3&, const Vector3&);
		return fpQuaternionRotationBetweenNormals(out_pRotation, in_rLeft, in_rRight);
	}

	static Quaternion QuaternionNormalize(Quaternion in_rotation)
	{
		return in_rotation.normalized();
	}

	static csl::math::Quaternion QuaternionMultiply(const Quaternion& in_rLeft, const Quaternion& in_rRight)
	{
		return in_rLeft * in_rRight;
	}

	inline Quaternion::Quaternion(const Matrix34& in_rMatrix) : Eigen::Quaternionf(in_rMatrix.topLeftCorner<3, 3>())
	{

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

	inline csl::math::Vector3 Vector3RotateX(float in_angle, const csl::math::Vector3& in_rDir)
	{
		csl::math::Quaternion rot(Eigen::AngleAxisf(in_angle, csl::math::Vector3::UnitX()));
		auto rotMtx = rot.toRotationMatrix();
		return csl::math::Vector3(rotMtx * in_rDir);
	}

	inline csl::math::Vector3 Vector3RotateY(float in_angle, const csl::math::Vector3& in_rDir)
	{
		csl::math::Quaternion rot(Eigen::AngleAxisf(in_angle, csl::math::Vector3::UnitY()));
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
		csl::math::Matrix34 Mtx;
		csl::math::Vector3 Scale;
		size_t Flags;

		csl::math::Vector3 GetTranslation() const
		{
			return Mtx.GetTransVector();
		}

		void SetTranslation(const csl::math::Vector3& in_rTranslation)
		{
			Mtx.SetTransVector(in_rTranslation);
			SetFlag(1);
		}

		void SetRotation(const csl::math::Quaternion& in_rRotation)
		{
			Eigen::Matrix3f mtx = in_rRotation.toRotationMatrix();

			Mtx.SetColumn(0, (csl::math::Vector3)mtx.col(0));
			Mtx.SetColumn(1, (csl::math::Vector3)mtx.col(1));
			Mtx.SetColumn(2, (csl::math::Vector3)mtx.col(2));

			SetFlag(1);
		}

		void SetRotationXYZ(float in_roll, float in_pitch, float in_yaw)
		{
			app::math::Matrix34RotationRollPitchYaw(&Mtx, in_roll, in_pitch, in_yaw);
			SetFlag(1);
		}

		csl::math::Quaternion GetRotationQuaternion() const
		{
			return Mtx.GetRotation();
		}

		void SetFlag(size_t in_value)
		{
			Flags |= in_value;
		}
	};

	class Transform
	{
	public:
		csl::math::Vector3 Position;
		csl::math::Quaternion Rotation;
		csl::math::Vector3 Scale;
		bool IsDirty;

		csl::math::Matrix34 GetTransformMatrix() const
		{
			return Matrix34AffineTransformation(Position, Rotation);
		}

		void SetFlag(size_t in_flag)
		{
			IsDirty |= in_flag;
		}
	};
}