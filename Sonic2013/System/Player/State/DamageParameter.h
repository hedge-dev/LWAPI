#pragma once

namespace app::Player
{
	struct DamageParameter : public SStateParameter
	{
	public:
		inline static const char* ms_pName = (const char*)ASLR(0x00DFB9D4);

		int Unk2{};
		int Unk3{};
		csl::math::Vector3 Unk4{};
		bool Unk5{};

		DamageParameter()
		{
			Unk1 = 1;
		}

		DamageParameter* Clone(csl::fnd::IAllocator& in_rAlloc) const override
		{
			auto* pClone = (DamageParameter*)in_rAlloc.Alloc(sizeof(DamageParameter), 32);
			if (pClone)
				new(pClone) DamageParameter(*this);

			return pClone;
		}

		const char* GetName() const override
		{
			return ms_pName;
		}
	};
}