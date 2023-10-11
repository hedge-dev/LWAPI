#pragma once

namespace app
{
	struct SFlagSetData
	{
		csl::ut::Bitset<uint> Flags[21];
	};
}

namespace app::SaveData
{
	template<typename T = uint>
	bool GetBit(T in_value, int in_bit);
	template<typename T = uint>
	void SetBit(T in_value, int in_bit, bool in_isEnable);
	uint CalcIndexFlagMinigameUnlocked(uint in_worldIndex, uint in_minigameIndex);

	class CFlagSet : CResCommon<SFlagSetData>
	{
	private:
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpGetFlagZoneUnlocked, ASLR(0x008FFDC0), const CFlagSet*, uint);
		inline static FUNCTION_PTR(int, __thiscall, ms_fpCountRedRingZone, ASLR(0x00900080), const CFlagSet*, uint, int);

	public:
		bool GetBitFlag(uint in_flag) const
		{
			return ref().Flags[(((in_flag >> 3) & 0x1FFFFFFC) + 16) / 4].test(in_flag & 0x1F);
		}
		
		void SetBitFlag(uint in_flag, bool in_isEnable)
		{
			ref().Flags[(((in_flag >> 3) & 0x1FFFFFFC) + 16) / 4].set(in_flag & 0x1F, in_isEnable);
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

		void SetMiniGameOpened(uint in_worldIndex, uint in_minigameIndex, bool in_isEnable)
		{
			SetBitFlag(CalcIndexFlagMinigameUnlocked(in_worldIndex, in_minigameIndex), in_isEnable);
		}

		bool GetChaosEmeraldUnlocked(uint in_worldIndex) const
		{
			return GetBitFlag(in_worldIndex + 470);
		}

		void SetChaosEmeraldUnlocked(uint in_worldIndex, bool in_isUnlocked)
		{
			SetBitFlag(in_worldIndex + 470, in_isUnlocked);
		}

		bool GetSuperSonicUnlocked() const
		{
			return GetBitFlag(484);
		}

		void SetSuperSonicUnlocked(bool in_isUnlocked)
		{
			SetBitFlag(484, in_isUnlocked);
		}
	};
}