#pragma once

namespace app
{
	struct SCrayPipeExitParam
	{
		enum Direction : uint8
		{
			UP,
			DOWN
		};

	public:
		Direction Direction;
	};

	static void paramMap_ObjCrayPipeExit(SetEd::CResClass in_rClass)
	{		
		FUNCTION_PTR(void, __thiscall, fpparamMap_ObjCrayPipeExit, ASLR(0x00615D10), SetEd::CResClass);
		
		fpparamMap_ObjCrayPipeExit(in_rClass);
	}
}