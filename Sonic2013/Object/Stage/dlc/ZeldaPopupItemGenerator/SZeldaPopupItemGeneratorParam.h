#pragma once

namespace app
{
	struct SZeldaPopupItemGeneratorParam
	{
	public:
		float ColliRadius{};
		char CreateItem{};
	};

	static void paramMap_ObjZeldaPopupItemGenerator(SetEd::CResClass rClass)
	{		
		FUNCTION_PTR(void, __thiscall, ms_fpparamMap_ObjZeldaPopupItemGenerator, ASLR(0x006172A0), SetEd::CResClass);
		
		ms_fpparamMap_ObjZeldaPopupItemGenerator(rClass);
	}
}