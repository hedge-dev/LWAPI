#pragma once

namespace app
{
	struct SYoshiGoalParam
	{
	public:
		size_t Locator{};
		size_t FixCamera{};
	};

	static void paramMap_ObjYoshiGoal(SetEd::CResClass in_rClass)
	{		
		FUNCTION_PTR(void, __thiscall, fpparamMap_ObjYoshiGoal, ASLR(0x00616E20), SetEd::CResClass);
		
		fpparamMap_ObjYoshiGoal(in_rClass);
	}
}