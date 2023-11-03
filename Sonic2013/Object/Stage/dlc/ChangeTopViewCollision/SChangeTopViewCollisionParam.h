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

	static void paramMap_ObjChangeTopViewCollision(SetEd::CResClass in_rClass)
	{		
		FUNCTION_PTR(void, __thiscall, fpparamMap_ObjChangeTopViewCollision, ASLR(0x006159D0), SetEd::CResClass);
		
		fpparamMap_ObjChangeTopViewCollision(in_rClass);
	}
}