#pragma once

namespace app::Player
{
	struct GlideParameter : public SStateParameter
	{
	public:
		inline static const char* ms_pName = (const char*)ASLR(0x00DFB070);

		int Unk1{};

		GlideParameter* Clone(csl::fnd::IAllocator& in_rAlloc) const override
		{
			auto* pClone = (GlideParameter*)in_rAlloc.Alloc(sizeof(GlideParameter), 32);
			if (pClone)
				new(pClone) GlideParameter(*this);

			return pClone;
		}

		const char* GetName() const override
		{
			return ms_pName;
		}
	};
}