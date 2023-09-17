#pragma once

namespace app::Player
{
	struct SpringJumpParameter : public SStateParameter
	{
	public:
		inline static const char* ms_pName = (const char*)ASLR(0x00DFC8DC);

		float SpeedDropoffTime{};
		float OutOfParkour{};
		csl::math::Vector3 Direction{};
		csl::ut::Bitset<uint> Flags{};

		SpringJumpParameter* Clone(csl::fnd::IAllocator& in_rAlloc) const override
		{
			auto* pClone = (SpringJumpParameter*)in_rAlloc.Alloc(sizeof(SpringJumpParameter), 32);
			if (pClone)
				new(pClone) SpringJumpParameter(*this);

			return pClone;
		}

		const char* GetName() const override
		{
			return ms_pName;
		}
	};
}