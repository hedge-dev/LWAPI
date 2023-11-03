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

	static void paramMap_ObjEventDrowning(SetEd::CResClass in_rClass)
	{		
		FUNCTION_PTR(void, __thiscall, fpparamMap_ObjEventDrowning, ASLR(0x006160B0), SetEd::CResClass);
		
		fpparamMap_ObjEventDrowning(in_rClass);
	}
}