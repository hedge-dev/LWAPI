#pragma once

namespace app
{
	struct SZeldaGoalParam
	{
	public:
		float CollisionWidth{};
		float CollisionHeight{};
		float CollisionDepth{};
		uint FixCamera{};
		float OffsetWidth{};
		float OffsetHeight{};
		float OffsetDepth{};
	};

	static void paramMap_ObjZeldaGoal(SetEd::CResClass in_rClass)
	{
		FUNCTION_PTR(void, __thiscall, fpparamMap_ObjZeldaGoal, ASLR(0x00617090), SetEd::CResClass);

		fpparamMap_ObjZeldaGoal(in_rClass);
	}
}