#pragma once

namespace app::game
{
	struct PhysicsOverlapOutput
	{
		uint Actor{};
		uint Attribute{};
		ColliShape* pShape{};
		uint Unk1{}; // Shape key?
	};
}