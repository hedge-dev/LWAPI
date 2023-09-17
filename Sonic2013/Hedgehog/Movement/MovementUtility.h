#pragma once

namespace app::game::MovementUtility
{
	struct SideviewInterpolateInfo
	{
		csl::math::Vector3 Unk1{};
		csl::math::Vector3 Unk2{};
		PathEvaluator Path{};
	};
}