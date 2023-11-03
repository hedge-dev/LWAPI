#pragma once

namespace app::animation
{
	class PlayingData
	{
	public:
		float m_Frame{};
		float m_StartFrame{ -0.0099999998 };
		float m_Weight{ 1 };
		float m_Speed{ 1 };
		uint m_RandomMask{ (uint) - 1};
		csl::ut::Bitset<uint> m_Flags{ -1 };
	};
}