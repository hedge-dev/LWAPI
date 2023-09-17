#pragma once

namespace app
{
	struct SYoshiGoalParam
	{
	public:
		size_t Locator{};
		size_t FixCamera{};
	};

	static void paramMap_ObjYoshiGoal(SetEd::CResClass rClass)
	{		
		FUNCTION_PTR(void, __thiscall, ms_fpparamMap_ObjYoshiGoal, ASLR(0x00616E20), SetEd::CResClass);
		
		ms_fpparamMap_ObjYoshiGoal(rClass);
	}
}