#pragma once

namespace app::Player
{
	struct GoTargetParameter : public SStateParameter
	{
	public:
		inline static const char* ms_pName = (const char*)ASLR(0x00DFB108);

		csl::math::Matrix34 Target{};
		float Unk1{};
		float Unk2{};
		bool Unk3{};

		GoTargetParameter()
		{
			m_Unk1 = 1;
		}

		GoTargetParameter* Clone(csl::fnd::IAllocator& in_rAlloc) const override
		{
			auto* pClone = (GoTargetParameter*)in_rAlloc.Alloc(sizeof(GoTargetParameter), 32);
			if (pClone)
				new(pClone) GoTargetParameter(*this);

			return pClone;
		}

		const char* GetName() const override
		{
			return ms_pName;
		}
	};
}