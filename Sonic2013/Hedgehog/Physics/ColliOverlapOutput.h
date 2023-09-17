#pragma once

namespace app::game
{
	struct ColliOverlapOutput
	{
		uint Actor{};
		uint Unk1{};
		ColliShape* pShape{};
		uint Unk2{};
		int Unk3{};
	};
}