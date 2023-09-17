#pragma once

namespace app::Player
{
	class PluginStateBarrier : public CStatePlugin
	{
	public:
		inline static int ms_BarrierUseCount[] = { 1, 2, 3, 4 };

		enum EType
		{
			eType_Barrier,
			eType_ThunderBarrier,
			eType_WaterBarrier
		};

	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpEnd, ASLR(0x008D3C80), PluginStateBarrier*, CStateGOC&);

	public:
		inline static const char* ms_pName = (const char*)ASLR(0x00E006AC);
		
		csl::ut::Bitset<byte> Flags{};
		csl::ut::Enum<EType, char> Type{};
		int UseCount{};

		PluginStateBarrier() : CStatePlugin(ms_pName)
		{

		}
		
		void End(CStateGOC& in_rStateGoc)
		{
			ms_fpEnd(this, in_rStateGoc);
		}

		void StartRequest(CStateGOC& in_rStateGoc, EType in_type, int in_itemLevel)
		{
			if (in_itemLevel >= 4)
				return;
		
			if (Type == in_type)
			{
				UseCount = ms_BarrierUseCount[in_itemLevel];
				return;
			}

			if ((char)Type != -1)
				End(in_rStateGoc);

			Type = in_type;
			UseCount = ms_BarrierUseCount[in_itemLevel];
			Flags.set(0, true);
		}

		bool IsWaitStart() const
		{
			return Flags.test(0);
		}

		bool IsPause() const
		{
			return Flags.test(1);
		}

		bool ReduceBarrier(CStateGOC& in_rStateGoc)
		{
			UseCount -= 1;
			if (UseCount > 0)
				return true;
		
			SetStatusEnd();
			return false;
		}

		void Terminate(CStateGOC& in_rStateGoc)
		{
			SetStatusEnd();
		}
	};
}