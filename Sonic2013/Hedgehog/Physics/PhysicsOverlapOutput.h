#pragma once

namespace app::game
{
	struct PhysicsOverlapOutput
	{
		uint m_Actor{};
		uint m_Attribute{};
		ColliShape* m_pShape{};
		uint m_Unk1{}; // Shape key?
	};
}