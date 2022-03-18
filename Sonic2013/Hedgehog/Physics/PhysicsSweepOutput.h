#pragma once

namespace app::game
{
	using namespace csl::math;

	struct PhysicsSweepOutput
	{
		float m_Distance{};
		uint m_Attribute{};
		ColliShape* m_pShape{};
		uint m_Actor{};
		Vector3 m_Normal;
		Vector3 m_Point;
	};
}