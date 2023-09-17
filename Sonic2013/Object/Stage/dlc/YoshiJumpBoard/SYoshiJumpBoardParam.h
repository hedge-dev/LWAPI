#pragma once

namespace app
{
	struct SYoshiJumpBoardParam
	{
	public:
		float FirstSpeed;
		float OutOfControl;
		float KeepVelocityDistance;
		bool IsPathChange;
		bool IsChangeCameraWhenChange;
		bool IsUpdateYaw;
		float OutOfParkour;
	};

	static void paramMap_ObjYoshiJumpBoardBig(SetEd::CResClass rClass)
	{		
		FUNCTION_PTR(void, __thiscall, ms_fpparamMap_ObjYoshiJumpBoardBig, ASLR(0x00616EC0), SetEd::CResClass);
		
		ms_fpparamMap_ObjYoshiJumpBoardBig(rClass);
	}

	static void paramMap_ObjYoshiJumpBoardSmall(SetEd::CResClass rClass)
	{
		FUNCTION_PTR(void, __thiscall, ms_fpparamMap_ObjYoshiJumpBoardSmall, ASLR(0x616EC0), SetEd::CResClass);

		ms_fpparamMap_ObjYoshiJumpBoardSmall(rClass);
	}
}