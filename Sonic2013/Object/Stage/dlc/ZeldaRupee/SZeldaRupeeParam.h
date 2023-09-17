#pragma once

namespace app
{
	struct SZeldaRupeeParam
	{
	public:
		char CreateItem{};
		bool IsEventOn{};
		bool IsShadowOff{};
	};

	static void paramMap_ObjZeldaRupee(SetEd::CResClass rClass)
	{
		FUNCTION_PTR(void, __thiscall, ms_fpparamMap_ObjZeldaRupee, ASLR(0x00617320), SetEd::CResClass);

		ms_fpparamMap_ObjZeldaRupee(rClass);
	}
}