#pragma once

namespace app::Player
{
	struct PinBallParameter : public SStateParameter
	{
	public:
		inline static const char* ms_pName = (const char*)ASLR(0x00DFE878);

		bool Unk1{};
		bool Unk2{};
		bool IsMode2D{};
		int Unk4{};
		int Unk5{};
		csl::math::Vector3 Unk6{};
		csl::math::Vector3 Unk7{};
		float Unk8{};
		float Unk9{};

		PinBallParameter* Clone(csl::fnd::IAllocator& in_rAlloc) const override
		{
			auto* pClone = (PinBallParameter*)in_rAlloc.Alloc(sizeof(PinBallParameter), 32);
			if (pClone)
				new(pClone) PinBallParameter(*this);

			return pClone;
		}

		const char* GetName() const override
		{
			return ms_pName;
		}
	};
}