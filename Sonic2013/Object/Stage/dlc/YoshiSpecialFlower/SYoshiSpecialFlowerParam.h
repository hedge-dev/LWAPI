#pragma once

namespace app
{
	struct SYoshiSpecialFlowerParam
	{
	public:
		size_t FlowerId;
	};

	static void paramMap_ObjYoshiSpecialFlower(SetEd::CResClass in_rClass)
	{		
		FUNCTION_PTR(void, __thiscall, fpparamMap_ObjYoshiSpecialFlower, ASLR(0x00616E60), SetEd::CResClass);
		
		fpparamMap_ObjYoshiSpecialFlower(in_rClass);
	}
}