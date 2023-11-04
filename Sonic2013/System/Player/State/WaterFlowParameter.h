#pragma once

namespace app::Player
{
	struct WaterFlowParameter : public SStateParameter
	{
	public:
		inline static const char* ms_pName = (const char*)ASLR(0x00E00244);

		csl::math::Vector3 Unk2{};
		csl::math::Vector3 Unk3{};

		WaterFlowParameter* Clone(csl::fnd::IAllocator& in_rAlloc) const override
		{
			auto* pClone = (WaterFlowParameter*)in_rAlloc.Alloc(sizeof(WaterFlowParameter), 32);
			if (pClone)
				new(pClone) WaterFlowParameter(*this);

			return pClone;
		}

		const char* GetName() const override
		{
			return ms_pName;
		}
	};
}