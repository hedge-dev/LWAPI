#pragma once

namespace app::Player
{
	class CPluginStateCheckSandHole : public CStatePlugin
	{
	public:
		inline static const char* ms_pName = (const char*)ASLR(0x00E00908);

		csl::ut::Bitset<uint> Flags{};
		int Sender{};
		csl::math::Vector3 Unk2{};
		float Unk3{};
		float Unk4{};
		float Unk5{};
		hh::eff::CInstanceHandle<hh::eff::CEffectInstance> EffectHandle{};

		CPluginStateCheckSandHole() : CStatePlugin(ms_pName)
		{

		}

		void SetHoleInfo(CStateGOC& in_rStateGoc, uint in_sender, const csl::math::Vector3 in_rUnk1, float in_unk2)
		{
			Sender = in_sender;
			Unk2 = in_rUnk1;
			Unk3 = in_unk2;

			Flags.set(1, true);
			in_rStateGoc.GetPhysics()->SetDrawnPosition(in_rUnk1);
		}
	};
}