#pragma once

namespace app::SaveData
{
	template<typename T>
	inline bool GetBit(T in_value, int in_bit)
	{
		int mask = 1 << in_bit;

		return (in_value & mask) != 0;
	}

	inline uint CalcIndexFlagMinigameUnlocked(uint in_worldIndex, uint in_minigameIndex)
	{
		return 4 * in_worldIndex + in_minigameIndex + 490;
	}
}