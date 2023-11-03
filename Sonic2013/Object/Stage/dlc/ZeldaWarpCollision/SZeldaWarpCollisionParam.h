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

	static void paramMap_ObjZeldaWarpCollision(SetEd::CResClass in_rClass)
	{		
		FUNCTION_PTR(void, __thiscall, fpparamMap_ObjZeldaWarpCollision, ASLR(0x00608000), SetEd::CResClass);
		
		fpparamMap_ObjZeldaWarpCollision(in_rClass);
	}
}