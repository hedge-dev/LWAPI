#pragma once

namespace app::Player
{
	class PluginStateRedRingRadar : public CStatePlugin
	{
	public:
		inline static const char* ms_pName = (const char*)ASLR(0x00E00864);

	protected:
		csl::ut::Bitset<byte> Flags{};
		int ItemLevel{};
		int Unk2{};
		float Unk3{};
		float Unk4{ 1.0f };

	public:
		PluginStateRedRingRadar() : CStatePlugin(ms_pName)
		{

		}

		bool IsWaitStart() const
		{
			return Flags.test(1);
		}
		
		void StartRadar(CStateGOC& in_rStateGoc, int in_itemLevel)
		{
			ItemLevel = in_itemLevel;
			Flags.set(1, true);
		}
	};
}