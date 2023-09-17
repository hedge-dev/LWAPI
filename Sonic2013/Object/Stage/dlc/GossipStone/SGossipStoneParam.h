#pragma once

namespace app
{
	struct SGossipStoneParam
	{
	public:
		float CheckRadius{};
	};

	static void paramMap_ObjGossipStone(SetEd::CResClass rClass)
	{
		FUNCTION_PTR(void, __thiscall, ms_fpparamMap_ObjGossipStone, ASLR(0x00616210), SetEd::CResClass);

		ms_fpparamMap_ObjGossipStone(rClass);
	}
}