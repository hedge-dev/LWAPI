#pragma once

namespace app
{
	struct SEventDrowningParam
	{
	public:
		float CollisionWidth;
		float CollisionHeight;
		float CollisionDepth;
		float EffectOffset;
	};

	static void paramMap_ObjEventDrowning(SetEd::CResClass rClass)
	{		
		FUNCTION_PTR(void, __thiscall, ms_fpparamMap_ObjEventDrowning, ASLR(0x006160B0), SetEd::CResClass);
		
		ms_fpparamMap_ObjEventDrowning(rClass);
	}
}