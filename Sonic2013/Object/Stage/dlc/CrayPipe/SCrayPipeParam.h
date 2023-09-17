#pragma once

namespace app
{
	struct SCrayPipeParam
	{
		enum Direction : uint8
		{
			DOWN,
			UP
		};

	public:
		float CollisionRadius;
		size_t TargetLocater;
		Direction Direction;
	};

	static void paramMap_ObjCrayPipe(SetEd::CResClass rClass)
	{		
		FUNCTION_PTR(void, __thiscall, ms_fpparamMap_ObjCrayPipe, ASLR(0x00615C80), SetEd::CResClass);
		
		ms_fpparamMap_ObjCrayPipe(rClass);
	}
}