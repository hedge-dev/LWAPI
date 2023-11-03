#pragma once

namespace app::game
{
	struct PhysicsSweepOutput
	{
		float Distance{};
		uint Attribute{};
		ColliShape* pShape{};
		uint Actor{};
		csl::math::Vector3 Normal;
		csl::math::Vector3 Point;
	};
}