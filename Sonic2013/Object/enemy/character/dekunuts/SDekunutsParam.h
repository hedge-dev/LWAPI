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

	static void paramMap_EnemyDekunuts(SetEd::CResClass in_rClass)
	{
		FUNCTION_PTR(void, __thiscall, fpparamMap_EnemyDekunuts, ASLR(0x0060A940), SetEd::CResClass);
		
		fpparamMap_EnemyDekunuts(in_rClass);
	}
}