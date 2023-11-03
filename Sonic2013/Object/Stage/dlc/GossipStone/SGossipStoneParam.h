#pragma once

namespace app
{
	struct SGossipStoneParam
	{
	public:
		float CheckRadius{};
	};

	static void paramMap_ObjGossipStone(SetEd::CResClass in_rClass)
	{
		FUNCTION_PTR(void, __thiscall, fpparamMap_ObjGossipStone, ASLR(0x00616210), SetEd::CResClass);

		fpparamMap_ObjGossipStone(in_rClass);
	}
}