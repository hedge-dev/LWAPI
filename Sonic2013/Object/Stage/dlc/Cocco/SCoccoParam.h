#pragma once

namespace app
{
	struct SCoccoParam
	{
		float MoveRange{};
		TArray<uint, dbg::Allocator<uint>> CoccoList{};
	};

	static void paramMap_ObjCocco(SetEd::CResClass in_rClass)
	{
		FUNCTION_PTR(void, __thiscall, fpparamMap_ObjCocco, ASLR(0x00615AC0), SetEd::CResClass);

		fpparamMap_ObjCocco(in_rClass);
	}
}