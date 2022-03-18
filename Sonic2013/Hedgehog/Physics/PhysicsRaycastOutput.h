#pragma once

namespace app::game
{
	using namespace csl::math;
	struct PhysicsRaycastOutput
	{
		Vector3 m_HitPoint{};
		Vector3 m_Normal{};
		uint m_Actor{};
		uint m_Attribute{};
		float m_Distance{};
		ColliShape* m_pShape{};
		uint m_ShapeKey{};
	};
}