#pragma once

namespace app
{
	struct SDekunutsParam
	{
	public:
		bool MessageBoot{};
		float AppearRange{};
		float SearchRange{};
		float RangeAddX{};
		float RangeAddY{};
		float RangeAddZ{};
	};

	static void paramMap_EnemyDekunuts(SetEd::CResClass rClass)
	{
		FUNCTION_PTR(void, __thiscall, ms_fpparamMap_EnemyDekunuts, ASLR(0x0060A940), SetEd::CResClass);
		
		ms_fpparamMap_EnemyDekunuts(rClass);
	}
}