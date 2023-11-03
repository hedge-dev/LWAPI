#pragma once

namespace app
{
	struct SZeldaBushParam
	{
	public:
		int CreateType{};
	};

	static void paramMap_ObjZeldaBush(SetEd::CResClass in_rClass)
	{
		FUNCTION_PTR(void, __thiscall, fpparamMap_ObjZeldaBush, ASLR(0x00617050), SetEd::CResClass);

		fpparamMap_ObjZeldaBush(in_rClass);
	}
}