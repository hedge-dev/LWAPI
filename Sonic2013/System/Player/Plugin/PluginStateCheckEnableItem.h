#pragma once

namespace app::Player
{
	class PluginStateCheckEnableItem : public CStatePlugin
	{
	public:
		typedef int ItemType;

	private:
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpIsItemDisable, ASLR(0x008D2EA0), PluginStateCheckEnableItem*, ItemType);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetItemDisable, ASLR(0x008D2E70), PluginStateCheckEnableItem*, ItemType, bool);

	public:
		inline static const char* ms_pName = (const char*)ASLR(0x00E004F4);
		
		INSERT_PADDING(4)[9]{}; // csl::ut::FixedArray<PlayerUtil::CCounterFlag, 9> CounterFlags{};
		int Unk1{};
		bool IsWait{};
		int ItemLevel{};
		bool Unk4{};

		PluginStateCheckEnableItem() : CStatePlugin(ms_pName)
		{

		}

		bool IsItemDisable(ItemType in_type)
		{
			return ms_fpIsItemDisable(this, in_type);
		}

		void SetItemDisable(ItemType in_type, bool in_disable)
		{
			ms_fpSetItemDisable(this, in_type, in_disable);
		}

		bool IsWaitWarp()
		{
			return IsWait;
		}

		void RequestWarp(CStateGOC& in_rStateGoc, int in_itemLevel)
		{
			IsWait = true;
			ItemLevel = in_itemLevel;

			StateUtil::SetDisableChangePhantom(in_rStateGoc, true);
			StateUtil::SetDisableTransformSuperSonic(in_rStateGoc, true);
			StateUtil::PauseSuperSonicReturnTimer(in_rStateGoc, true);
			StateUtil::SetDisableReturnToSonic(in_rStateGoc, true);
		}

		void DoneWarp(CStateGOC& in_rStateGoc)
		{
			if (!Unk4)
				return;
		
			Unk4 = false;
			StateUtil::SetDisableChangePhantom(in_rStateGoc, false);
			StateUtil::SetDisableTransformSuperSonic(in_rStateGoc, false);
			StateUtil::SetDisableItemAndTransformForPauseAct(in_rStateGoc, false, false);
			StateUtil::PauseSuperSonicReturnTimer(in_rStateGoc, false);
			StateUtil::SetDisableReturnToSonic(in_rStateGoc, false);
		}

		void StateWarpByCollision(CStateGOC& in_rStateGoc, bool in_unk)
		{
			if (!Unk4)
			{
				StateUtil::SetDisableChangePhantom(in_rStateGoc, true);
				StateUtil::SetDisableTransformSuperSonic(in_rStateGoc, true);
				StateUtil::SetDisableItemAndTransformForPauseAct(in_rStateGoc, true, in_unk);
				StateUtil::PauseSuperSonicReturnTimer(in_rStateGoc, true);
				StateUtil::SetDisableReturnToSonic(in_rStateGoc, true);
				
				Unk4 = true;
			}
		}
	};
}