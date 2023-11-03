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

	static void paramMap_ObjZeldaRupee(SetEd::CResClass in_rClass)
	{
		FUNCTION_PTR(void, __thiscall, fpparamMap_ObjZeldaRupee, ASLR(0x00617320), SetEd::CResClass);

		fpparamMap_ObjZeldaRupee(in_rClass);
	}
}