#pragma once

namespace app
{
	struct SFlagSetData
	{
		INSERT_PADDING(16);
		char Unk1{};
		INSERT_PADDING(40);
	};
}

namespace app::SaveData
{
	template<typename T = uint>
	bool GetBit(T in_value, int in_bit);
	uint CalcIndexFlagMinigameUnlocked(uint in_worldIndex, uint in_minigameIndex);

	class CFlagSet : CResCommon<SFlagSetData>
	{
	private:
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpGetFlagZoneUnlocked, ASLR(0x008FFDC0), const CFlagSet*, uint);
		inline static FUNCTION_PTR(int, __thiscall, ms_fpCountRedRingZone, ASLR(0x00900080), const CFlagSet*, uint, int);

	public:
		bool GetBitFlag(uint in_flag) const
		{
			return GetBit(*(int*)(*(int*)this + ((in_flag >> 3) & 0x1FFFFFFC) + 16), in_flag & 0x1F);
		}

		bool GetFlagZoneUnlocked(uint in_worldIndex) const
		{
			return ms_fpGetFlagZoneUnlocked(this, in_worldIndex);
		}

		int CountRedRingZone(uint in_worldIndex, int in_limit) const
		{
			return ms_fpCountRedRingZone(this, in_worldIndex, in_limit);
		}

		bool GetMiniGameOpened(uint in_worldIndex, uint in_minigameIndex) const
		{
			return GetBitFlag(CalcIndexFlagMinigameUnlocked(in_worldIndex, in_minigameIndex));
		}
	};
}