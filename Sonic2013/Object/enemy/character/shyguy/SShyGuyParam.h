#pragma once

namespace app
{
	struct SShyGuyParam
	{
		enum Direction : uint8
		{
			LEFT,
			RIGHT
		};

	public:
		float Speed;
		float MaxMoveDistance;
		bool IsEventDriven;
		Direction Direction;
		float DepthOffset;
	};

	static void paramMap_EnemyShyGuy(SetEd::CResClass in_rClass)
	{
		FUNCTION_PTR(void, __thiscall, fpparamMap_EnemyShyGuy, ASLR(0x0060FBC0), SetEd::CResClass);
		
		fpparamMap_EnemyShyGuy(in_rClass);
	}
}