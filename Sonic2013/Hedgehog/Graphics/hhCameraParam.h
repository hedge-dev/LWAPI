#pragma once

namespace app::Render
{
	struct CameraParam
	{
		csl::math::Matrix34 m_ViewMtx{};
		csl::math::Matrix34 m_UnkMtx{}; // Projection?
		csl::math::Vector3 m_UnkVec1{}; // ???
		csl::math::Vector3 m_UnkVec2{}; // ???
		csl::math::Vector3 m_UnkVec3{}; // ???
	};
}