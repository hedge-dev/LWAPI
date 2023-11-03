#pragma once

namespace app::animation
{
	class PlayingData
	{
	public:
		float Frame{};
		float StartFrame{ -0.0099999998 };
		float Weight{ 1 };
		float Speed{ 1 };
		uint RandomMask{ (uint) - 1};
		csl::ut::Bitset<uint> Flags{ -1 };
	};
}