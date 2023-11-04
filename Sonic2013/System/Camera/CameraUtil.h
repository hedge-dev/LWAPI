#pragma once

namespace app
{
	class CameraUtil
	{
	public:
		/// <summary>
		/// Transform a spherical point to cartesian
		/// X - Radius
		/// Y - Theta
		/// Z - Phi
		/// </summary>
		/// <param name="in_rSphere"></param>
		/// <returns></returns>
		inline static csl::math::Vector3 SphericalToCartesian(const csl::math::Vector3& in_rSphere)
		{
			csl::math::Vector3 result{};
			const float& radius = in_rSphere[0];
			const float& theta = in_rSphere[1];
			const float& phi = in_rSphere[2];
			
			result[0] = radius * sinf(MATHF_DEGTORAD(phi)) * cosf(MATHF_DEGTORAD(theta));
			result[1] = radius * sinf(MATHF_DEGTORAD(phi)) * sinf(MATHF_DEGTORAD(theta));
			result[2] = radius * cosf(MATHF_DEGTORAD(phi));
			
			return result;
		}

		inline static csl::math::Vector3 CartesianToSpherical(const csl::math::Vector3& in_rPoint)
		{
			csl::math::Vector3 result{};

			// Radius
			result[0] = in_rPoint.norm();

			// Theta
			result[1] = MATHF_RADTODEG(atan2f(in_rPoint[1], in_rPoint[0]));

			// Phi
			result[2] = MATHF_RADTODEG(acosf(in_rPoint[2] / result[0]));
			
			return result;
		}
	};
}