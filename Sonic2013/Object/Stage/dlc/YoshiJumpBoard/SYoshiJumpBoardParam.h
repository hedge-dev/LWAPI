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

	static void paramMap_ObjYoshiJumpBoardBig(SetEd::CResClass in_rClass)
	{		
		FUNCTION_PTR(void, __thiscall, fpparamMap_ObjYoshiJumpBoardBig, ASLR(0x00616EC0), SetEd::CResClass);
		
		fpparamMap_ObjYoshiJumpBoardBig(in_rClass);
	}

	static void paramMap_ObjYoshiJumpBoardSmall(SetEd::CResClass in_rClass)
	{
		FUNCTION_PTR(void, __thiscall, fpparamMap_ObjYoshiJumpBoardSmall, ASLR(0x616EC0), SetEd::CResClass);

		fpparamMap_ObjYoshiJumpBoardSmall(in_rClass);
	}
}