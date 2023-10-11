#pragma once

namespace app::SaveData
{
	class CSaveData
	{
	private:
		inline static FUNCTION_PTR(CGameData*, __thiscall, ms_fpGetCurrentGameData, ASLR(0x00900C90), const CSaveData*, void*);

	public:
		CGameData* GetCurrentGameData(void* out_pValue) const
		{
			return ms_fpGetCurrentGameData(this, out_pValue);
		}
	};
}