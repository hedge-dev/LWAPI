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
		/// <param name="sphere"></param>
		/// <returns></returns>
		inline static csl::math::Vector3 SphericalToCartesian(const csl::math::Vector3& sphere)
		{
			csl::math::Vector3 result{};
			const float& radius = sphere[0];
			const float& theta = sphere[1];
			const float& phi = sphere[2];
			
			result[0] = radius * sinf(MATHF_DEGTORAD(phi)) * cosf(MATHF_DEGTORAD(theta));
			result[1] = radius * sinf(MATHF_DEGTORAD(phi)) * sinf(MATHF_DEGTORAD(theta));
			result[2] = radius * cosf(MATHF_DEGTORAD(phi));
			
			return result;
		}

		inline static csl::math::Vector3 CartesianToSpherical(const csl::math::Vector3& point)
		{
			csl::math::Vector3 result{};

			// Radius
			result[0] = point.norm();

			// Theta
			result[1] = MATHF_RADTODEG(atan2f(point[1], point[0]));

			// Phi
			result[2] = MATHF_RADTODEG(acosf(point[2] / result[0]));
			
			return result;
		}
	};
}