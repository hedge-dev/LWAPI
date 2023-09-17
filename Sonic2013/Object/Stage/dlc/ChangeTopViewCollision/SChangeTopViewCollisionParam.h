#pragma once

namespace app
{
	struct SChangeTopViewCollisionParam
	{
	public:
		float CollisionWidth;
		float CollisionHeight;
		float CollisionDepth;
	};

	static void paramMap_ObjChangeTopViewCollision(SetEd::CResClass rClass)
	{		
		FUNCTION_PTR(void, __thiscall, ms_fpparamMap_ObjChangeTopViewCollision, ASLR(0x006159D0), SetEd::CResClass);
		
		ms_fpparamMap_ObjChangeTopViewCollision(rClass);
	}
}