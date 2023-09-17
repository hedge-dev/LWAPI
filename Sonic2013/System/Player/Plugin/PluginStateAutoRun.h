#pragma once

namespace app::Player
{
	class PluginStateAutoRun : public CStatePlugin
	{
	private:
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpSetup, ASLR(0x008D1840), PluginStateAutoRun*, CStateGOC&, uint, float);

	public:
		inline static const char* ms_pName = (const char*)ASLR(0x00E00338);

		fnd::SoundHandle SoundHandle{};
		Effect::CEffectHandle<hh::eff::CEffectInstance> EffectHandle{};
		csl::ut::Bitset<byte> Flags{};

		PluginStateAutoRun() : CStatePlugin(ms_pName)
		{

		}

		bool Setup(CStateGOC& in_rStateGoc, uint in_unk1, float in_unk2)
		{
			return ms_fpSetup(this, in_rStateGoc, in_unk1, in_unk2);
		}
	};
}