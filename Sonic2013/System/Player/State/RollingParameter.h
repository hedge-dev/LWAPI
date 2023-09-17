#pragma once

namespace app::Player
{
	struct RollingParameter : public SStateParameter
	{
	public:
		inline static const char* ms_pName = (const char*)ASLR(0x00DFEA90);

		bool Unk1{};
		float Unk2{};

		RollingParameter* Clone(csl::fnd::IAllocator& in_rAlloc) const override
		{
			auto* pClone = (RollingParameter*)in_rAlloc.Alloc(sizeof(RollingParameter), 32);
			if (pClone)
				new(pClone) RollingParameter(*this);

			return pClone;
		}

		const char* GetName() const override
		{
			return ms_pName;
		}
	};
}