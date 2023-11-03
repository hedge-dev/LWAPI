#pragma once

namespace app::game
{
	struct PhysicsRaycastOutput
	{
		csl::math::Vector3 HitPoint{};
		csl::math::Vector3 Normal{};
		uint Actor{};
		uint Attribute{};
		float Distance{};
		ColliShape* pShape{};
		uint ShapeKey{};
	};
}