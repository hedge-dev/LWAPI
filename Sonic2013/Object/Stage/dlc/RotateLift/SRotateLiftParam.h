#pragma once

namespace app
{
	struct SRotateLiftParam
	{
	public:
		float omega;
		float offset;
		bool useGlobalTime;
		bool isEventDriven;
	};

	static void paramMap_ObjRotateLift(SetEd::CResClass rClass)
	{		
		FUNCTION_PTR(void, __thiscall, ms_fpparamMap_ObjRotateLift, ASLR(0x00616BE0), SetEd::CResClass);
		
		ms_fpparamMap_ObjRotateLift(rClass);
	}
}