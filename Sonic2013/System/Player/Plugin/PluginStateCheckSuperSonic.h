#pragma once

namespace app::Player
{
	struct alignas(4) SuperSonicCheckParameter
	{
		csl::ut::Bitset<byte> Flags{};
	};

	struct alignas(4) SuperSonicTransParameter
	{
		float Unk1{};
		csl::ut::Bitset<byte> Flags{};
	};

	class PluginStateCheckSuperSonic : public CStatePlugin
	{
	public:
		inline static const char* ms_pName = (const char*)ASLR(0x00E009E0);

		enum EMode
		{

		};

	protected:
		csl::ut::Bitset<byte> Unk1{};
		csl::ut::Enum<EMode, char> Unk2{};
		SuperSonicCheckParameter CheckParam{};
		int Unk3{};
		SuperSonicTransParameter TransParam{};
		int DisableFlag{};
		int Unk5{};

	public:
		PluginStateCheckSuperSonic() : CStatePlugin(ms_pName)
		{

		}

		void AddDisableFlag()
		{
			DisableFlag++;
		}

		void DecDisableFlag()
		{
			if (DisableFlag)
				DisableFlag--;
		}

		void PauseTimer(CStateGOC& in_rStateGoc, bool in_pause)
		{
			if ((char)Unk2 != 1)
				return;
		
			TransParam.Flags.set(1, in_pause);
		}

		void SetDisableReturn(bool in_disable)
		{
			if ((char)Unk2 != 1)
				return;

			TransParam.Flags.set(3, in_disable);
		}

		void SetTransImmediate(bool in_enable)
		{
			int unk = Unk5;

			if (in_enable)
			{
				Unk5++;
			}
			else if (unk)
			{
				Unk5--;
			}
		}
	};
}