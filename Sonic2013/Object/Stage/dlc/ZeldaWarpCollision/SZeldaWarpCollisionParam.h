#pragma once

namespace app
{
	struct SZeldaWarpCollisionParam
	{
	public:
		CSetObjectID TargetLocate;
		bool IsSideView;
		float CollisionWidth;
		float CollisionHeight;
		float CollisionDepth;
	};

	static void paramMap_ObjZeldaWarpCollision(SetEd::CResClass rClass)
	{		
		FUNCTION_PTR(void, __thiscall, ms_fpparamMap_ObjZeldaWarpCollision, ASLR(0x00608000), SetEd::CResClass);
		
		ms_fpparamMap_ObjZeldaWarpCollision(rClass);
	}
}