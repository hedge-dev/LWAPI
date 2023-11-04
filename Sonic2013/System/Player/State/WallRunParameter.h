#pragma once

namespace app::Player
{
	struct WallRunParameter : public SStateParameter
	{
	public:
		inline static const char* ms_pName = (const char*)ASLR(0x00DFFF28);

		bool Unk2{};
		bool Unk3{};
		bool Unk4{};
		bool Unk5{};
		bool Unk6{};
		csl::math::Vector3 Unk7{};
		float Unk8{};

		WallRunParameter* Clone(csl::fnd::IAllocator& in_rAlloc) const override
		{
			auto* pClone = (WallRunParameter*)in_rAlloc.Alloc(sizeof(WallRunParameter), 32);
			if (pClone)
				new(pClone) WallRunParameter(*this);

			return pClone;
		}

		const char* GetName() const override
		{
			return ms_pName;
		}
	};
}