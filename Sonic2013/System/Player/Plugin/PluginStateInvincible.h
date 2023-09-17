#pragma once

namespace app::Player
{
	class PluginStateInvincible : public CStatePlugin
	{
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpStart, ASLR(0x008D39B0), PluginStateInvincible*, CStateGOC&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpEnd, ASLR(0x008D3A90), PluginStateInvincible*, CStateGOC&);

	public:
		inline static float ms_VariantLifeSpans[] = { 10.0f, 15.0f, 20.0f, 30.0f };
		inline static const char* ms_pName = (const char*)ASLR(0x00E006C0);

	protected:
		float LifeSpan{};
		int ItemLevel{ -1 };
		csl::ut::Bitset<byte> Unk2{};
		hh::eff::CInstanceHandle<hh::eff::CEffectInstance> Effect{};
		INSERT_PADDING(4);

	public:
		PluginStateInvincible() : CStatePlugin(ms_pName)
		{

		}

		void RequestStart(CStateGOC& in_rStateGoc, int in_itemLevel)
		{
			if (in_itemLevel < 4)
			{
				ItemLevel = in_itemLevel;
				Unk2.set(0, true);
			}
		}

		void Extend(CStateGOC& in_rStateGoc, int in_itemLevel)
		{
			if (in_itemLevel >= 4)
				return;

			if (Unk2.test(1))
			{
				ItemLevel = in_itemLevel;
				Start(in_rStateGoc);
			}
			else
			{
				if (!Unk2.test(0))
				{
					ItemLevel = in_itemLevel;
					LifeSpan = ms_VariantLifeSpans[in_itemLevel];
				}
			}
		}

		bool IsWaitStart()
		{
			return Unk2.test(0);
		}

		void Start(CStateGOC& in_rStateGoc)
		{
			ms_fpStart(this, in_rStateGoc);
		}

		void End(CStateGOC& in_rStateGoc)
		{
			ms_fpEnd(this, in_rStateGoc);
		}

		void Terminate(CStateGOC& in_rStateGoc)
		{
			End(in_rStateGoc);
			SetStatusEnd();
		}

		void OnLeave(CStateGOC& in_rStateGoc) override
		{
			End(in_rStateGoc);
		}

		bool Update(CStateGOC& in_rStateGoc, float in_deltaTime) override
		{
			if (Unk2.test(0))
			{
				Start(in_rStateGoc);
				Unk2.set(0, false);

				return true;
			}
			else
			{
				if (!Unk2.test(2))
				{
					LifeSpan -= in_deltaTime;
					if (LifeSpan < 0.0f)
					{
						End(in_rStateGoc);
						SetStatusEnd();
					}
				}

				return true;
			}
		}
	};
}