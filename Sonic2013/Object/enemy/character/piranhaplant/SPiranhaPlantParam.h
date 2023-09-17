#pragma once

namespace app
{
	struct SPiranhaPlantParam
	{
		enum Direction : uint8
		{
			LEFT,
			RIGHT
		};

	public:
		float searchRadius{};
		Direction Direction{};
	};

	static void paramMap_EnemyPiranhaPlant(SetEd::CResClass rClass)
	{
		FUNCTION_PTR(void, __thiscall, ms_fpparamMap_EnemyPiranhaPlant, ASLR(0x0060F0F0), SetEd::CResClass);
		
		ms_fpparamMap_EnemyPiranhaPlant(rClass);
	}
}