#pragma once

namespace app::Player
{
	struct PipeMoveParameter : public SStateParameter
	{
	public:
		inline static const char* ms_pName = (const char*)ASLR(0x00DFE914);

		int Unk1{};
		int Unk2{};
		csl::math::Vector3 Unk3{};

		PipeMoveParameter* Clone(csl::fnd::IAllocator& in_rAlloc) const override
		{
			auto* pClone = (PipeMoveParameter*)in_rAlloc.Alloc(sizeof(PipeMoveParameter), 32);
			if (pClone)
				new(pClone) PipeMoveParameter(*this);

			return pClone;
		}

		const char* GetName() const override
		{
			return ms_pName;
		}
	};
}