#pragma once

namespace app
{
	struct SYoshiSpecialFlowerParam
	{
	public:
		size_t FlowerId;
	};

	static void paramMap_ObjYoshiSpecialFlower(SetEd::CResClass rClass)
	{		
		FUNCTION_PTR(void, __thiscall, ms_fpparamMap_ObjYoshiSpecialFlower, ASLR(0x00616E60), SetEd::CResClass);
		
		ms_fpparamMap_ObjYoshiSpecialFlower(rClass);
	}
}