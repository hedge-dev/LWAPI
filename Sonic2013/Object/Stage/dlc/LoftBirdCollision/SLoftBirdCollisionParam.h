#pragma once

namespace app
{
	struct SLoftBirdCollisionParam
	{
	public:
		typedef int EActionType;

		EActionType ActionType{};
	};

	static void paramMap_ObjLoftBirdCollision(SetEd::CResClass rClass)
	{		
		FUNCTION_PTR(void, __thiscall, ms_fpparamMap_ObjLoftBirdCollision, ASLR(0x00616390), SetEd::CResClass);
		
		ms_fpparamMap_ObjLoftBirdCollision(rClass);
	}
}