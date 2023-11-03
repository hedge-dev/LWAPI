#pragma once

namespace app
{
	struct SLoftBirdCollisionParam
	{
	public:
		typedef int EActionType;

		EActionType ActionType{};
	};

	static void paramMap_ObjLoftBirdCollision(SetEd::CResClass in_rClass)
	{		
		FUNCTION_PTR(void, __thiscall, fpparamMap_ObjLoftBirdCollision, ASLR(0x00616390), SetEd::CResClass);
		
		fpparamMap_ObjLoftBirdCollision(in_rClass);
	}
}