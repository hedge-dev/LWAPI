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

	static void paramMap_ObjRotateLift(SetEd::CResClass in_rClass)
	{		
		FUNCTION_PTR(void, __thiscall, fpparamMap_ObjRotateLift, ASLR(0x00616BE0), SetEd::CResClass);
		
		fpparamMap_ObjRotateLift(in_rClass);
	}
}