#pragma once

namespace app::Player
{
	struct StopBySandParameter : public SStateParameter
	{
	public:
		inline static const char* ms_pName = (const char*)ASLR(0x00DFFBD4);

		csl::math::Vector3 Unk1{};

		StopBySandParameter* Clone(csl::fnd::IAllocator& in_rAlloc) const override
		{
			auto* pClone = (StopBySandParameter*)in_rAlloc.Alloc(sizeof(StopBySandParameter), 32);
			if (pClone)
				new(pClone) StopBySandParameter(*this);

			return pClone;
		}

		const char* GetName() const override
		{
			return ms_pName;
		}
	};
}