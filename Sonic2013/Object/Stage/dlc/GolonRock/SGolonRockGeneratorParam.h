#pragma once

namespace app
{
	struct SGolonRockGeneratorParam
	{
	public:
		float Speed{};
		float CreateInterval{};
		bool IsEventOn{};
		bool IsCheckFall{};
	};

	static void paramMap_ObjGolonRockGenerator(SetEd::CResClass in_rClass)
	{		
		FUNCTION_PTR(void, __thiscall, fpparamMap_ObjGolonRockGenerator, ASLR(0x00624360), SetEd::CResClass);
		
		fpparamMap_ObjGolonRockGenerator(in_rClass);
	}
}