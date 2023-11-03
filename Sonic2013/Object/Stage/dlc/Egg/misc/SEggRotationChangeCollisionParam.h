#pragma once

namespace app
{
	struct SEggRotationChangeCollisionParam
	{
	public:
		float Width{};
		float Height{};
		float Depth{};
	};

	static void paramMap_ObjEggRotationChangeCollision(SetEd::CResClass in_rClass)
	{		
		FUNCTION_PTR(void, __thiscall, fpparamMap_ObjEggRotationChangeCollision, ASLR(0x00615EE0), SetEd::CResClass);
		
		fpparamMap_ObjEggRotationChangeCollision(in_rClass);
	}
}