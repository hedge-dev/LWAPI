#pragma once

namespace app
{
	struct SEggBlockParam
	{
	public:
		uint PopEggNum{};
		float PopEggRandomAddSpeed{};
	};

	static void paramMap_ObjEggBlock(SetEd::CResClass rClass)
	{		
		FUNCTION_PTR(void, __thiscall, ms_fpparamMap_ObjEggBlock, ASLR(0x00615FE0), SetEd::CResClass);
		
		ms_fpparamMap_ObjEggBlock(rClass);
	}
}