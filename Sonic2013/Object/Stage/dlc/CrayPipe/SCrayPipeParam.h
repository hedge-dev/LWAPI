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

	static void paramMap_ObjCrayPipe(SetEd::CResClass in_rClass)
	{		
		FUNCTION_PTR(void, __thiscall, fpparamMap_ObjCrayPipe, ASLR(0x00615C80), SetEd::CResClass);
		
		fpparamMap_ObjCrayPipe(in_rClass);
	}
}