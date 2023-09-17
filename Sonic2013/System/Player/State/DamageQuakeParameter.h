#pragma once

namespace app::Player
{
	struct DamageQuakeParameter : public SStateParameter
	{
	public:
		inline static const char* ms_pName = (const char*)ASLR(0x00DFB9A4);

		float Unk1{};
		float Unk2{};

		DamageQuakeParameter* Clone(csl::fnd::IAllocator& in_rAlloc) const override
		{
			auto* pClone = (DamageQuakeParameter*)in_rAlloc.Alloc(sizeof(DamageQuakeParameter), 32);
			if (pClone)
				new(pClone) DamageQuakeParameter(*this);

			return pClone;
		}

		const char* GetName() const override
		{
			return ms_pName;
		}
	};
}