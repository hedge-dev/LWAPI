#pragma once

namespace app::Player
{
	struct DivingParameter : public SStateParameter
	{
	public:
		inline static const char* ms_pName = (const char*)ASLR(0x00DFAD5C);

		int Unk1{};
		float Unk2{};
		float Unk3{};
		float Unk4{};
		float Unk5{};
		float Unk6{};
		csl::math::Vector3 Unk7{};
		csl::math::Vector3 Unk8{};
		csl::math::Vector3 Unk9{};

		DivingParameter* Clone(csl::fnd::IAllocator& in_rAlloc) const override
		{
			auto* pClone = (DivingParameter*)in_rAlloc.Alloc(sizeof(DivingParameter), 32);
			if (pClone)
				new(pClone) DivingParameter(*this);

			return pClone;
		}

		const char* GetName() const override
		{
			return ms_pName;
		}
	};
}