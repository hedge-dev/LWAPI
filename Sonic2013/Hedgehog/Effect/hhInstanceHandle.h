#pragma once

namespace hh::eff
{
	class CEffectInstance // : public CInstance
	{
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpStop, ASLR(0x0047EEA0), CEffectInstance*, bool);
		
		INSERT_PADDING(752);

	public:
		void Stop(bool in_unk)
		{
			ms_fpStop(this, in_unk);
		}
	};

	struct EffectHandleTableEntry
	{
		CEffectInstance* pHandle{};
		size_t Effect{};
	};

	template <class T = CEffectInstance>
	class CInstanceHandle
	{
	public:
		EffectHandleTableEntry* pEntry{};
		size_t EffectHandle{};
	};
}