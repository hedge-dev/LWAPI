#pragma once

namespace app::Player
{
	struct SweptBySandParameter : public SStateParameter
	{
	public:
		inline static const char* ms_pName = (const char*)ASLR(0x00DFFDD8);

		csl::math::Vector3 Unk2{};
		csl::math::Vector3 Unk3{};
		int Sender{};
		bool Unk4{};
		bool Unk5{};

		SweptBySandParameter* Clone(csl::fnd::IAllocator& in_rAlloc) const override
		{
			auto* pClone = (SweptBySandParameter*)in_rAlloc.Alloc(sizeof(SweptBySandParameter), 32);
			if (pClone)
				new(pClone) SweptBySandParameter(*this);

			return pClone;
		}

		const char* GetName() const override
		{
			return ms_pName;
		}
	};
}