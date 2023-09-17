#pragma once

namespace app
{
	struct SLoftBirdParam
	{
	public:
		typedef int PointLightType;

		uint ObjPathId;
		float StartDist;
		float EndDist;
		float MoveSpeed;
		PointLightType PointLight;
	};

	static void paramMap_ObjLoftBird(SetEd::CResClass rClass)
	{		
		FUNCTION_PTR(void, __thiscall, ms_fpparamMap_ObjLoftBird, ASLR(0x00616270), SetEd::CResClass);
		
		ms_fpparamMap_ObjLoftBird(rClass);
	}
}