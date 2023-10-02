#pragma once

namespace app::SaveData
{
	class CGameData
	{
	private:
		inline static FUNCTION_PTR(CFlagSet*, __thiscall, ms_fpGetFlagSet, ASLR(0x00900B10), const CGameData*, void*);

	public:
		CFlagSet* GetFlagSet(void* out_pValue) const
		{
			return ms_fpGetFlagSet(this, out_pValue);
		}
	};
}