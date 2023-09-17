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

	static void paramMap_ObjEggRotationChangeCollision(SetEd::CResClass rClass)
	{		
		FUNCTION_PTR(void, __thiscall, ms_fpparamMap_ObjEggRotationChangeCollision, ASLR(0x00615EE0), SetEd::CResClass);
		
		ms_fpparamMap_ObjEggRotationChangeCollision(rClass);
	}
}