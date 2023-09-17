#pragma once

namespace app
{
	struct STreasureBoxParam
	{
	public:
		enum EItemType : char
		{
			eItemType_HeartContainer,
			eItemType_RupeePurple,
			eItemType_RupeeGold,
			eItemType_MAX
		};
		char ItemType{};
	};

	static void paramMap_ObjTreasureBox(SetEd::CResClass rClass)
	{
		FUNCTION_PTR(void, __thiscall, fpparamMap_ObjTreasureBox, ASLR(0x00616CC0), SetEd::CResClass);

		fpparamMap_ObjTreasureBox(rClass);
	}
}