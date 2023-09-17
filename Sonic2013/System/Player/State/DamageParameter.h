#pragma once

namespace app::Player
{
	struct DamageParameter : public SStateParameter
	{
	public:
		inline static const char* ms_pName = (const char*)ASLR(0x00DFB9D4);

		int Unk1{};
		int Unk2{};
		csl::math::Vector3 Unk3{};
		bool Unk4{};

		DamageParameter()
		{
			m_Unk1 = 1;
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