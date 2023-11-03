#pragma once

namespace app
{
	struct SStalBabyParam
	{
	public:
		float Speed{};
		float MoveRange{};
		float AppearRange{};
		float SearchRange{};
		float SearchHeight{};
		bool isEventDriven{};
	};

	static void paramMap_EnemyStalBaby(SetEd::CResClass in_rClass)
	{
		FUNCTION_PTR(void, __thiscall, fpparamMap_EnemyStalBaby, ASLR(0x0060FCF0), SetEd::CResClass);
		
		fpparamMap_EnemyStalBaby(in_rClass);
	}
}