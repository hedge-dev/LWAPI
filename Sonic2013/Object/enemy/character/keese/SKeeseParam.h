#pragma once

namespace app
{
	struct SKeeseParam
	{
	public:
		float MoveSpeed{};
		float FallSpeed{};
		float FallDistance{};
		float MoveRange{};
		float MoveRangeOffset{};
		float SearchDistance{};
		float SearchRange{};
	};

	static void paramMap_EnemyKeese(SetEd::CResClass in_rClass)
	{
		FUNCTION_PTR(void, __thiscall, fpparamMap_EnemyKeese, ASLR(0x0060D4C0), SetEd::CResClass);
		
		fpparamMap_EnemyKeese(in_rClass);
	}
}