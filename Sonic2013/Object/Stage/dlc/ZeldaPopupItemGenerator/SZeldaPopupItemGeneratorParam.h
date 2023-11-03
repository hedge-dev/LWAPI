#pragma once

namespace app
{
	struct SZeldaPopupItemGeneratorParam
	{
	public:
		float ColliRadius{};
		char CreateItem{};
	};

	static void paramMap_ObjZeldaPopupItemGenerator(SetEd::CResClass in_rClass)
	{		
		FUNCTION_PTR(void, __thiscall, fpparamMap_ObjZeldaPopupItemGenerator, ASLR(0x006172A0), SetEd::CResClass);
		
		fpparamMap_ObjZeldaPopupItemGenerator(in_rClass);
	}
}