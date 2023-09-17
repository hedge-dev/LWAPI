#pragma once

namespace app
{
	struct SZeldaBushParam
	{
	public:
		int CreateType{};
	};

	static void paramMap_ObjZeldaBush(SetEd::CResClass rClass)
	{
		FUNCTION_PTR(void, __thiscall, ms_fpparamMap_ObjZeldaBush, ASLR(0x00617050), SetEd::CResClass);

		ms_fpparamMap_ObjZeldaBush(rClass);
	}
}