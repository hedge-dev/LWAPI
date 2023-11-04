#pragma once

namespace app::Player
{
	struct StateHangOnParameter : public SStateParameter
	{
		typedef char EType;

	public:
		inline static const char* ms_pName = (const char*)ASLR(0x00DFBD78);

		int Unk2{};
		EType HangType{};
		csl::ut::Bitset<char> Unk3{};

		StateHangOnParameter* Clone(csl::fnd::IAllocator& in_rAlloc) const override
		{
			auto* pClone = (StateHangOnParameter*)in_rAlloc.Alloc(sizeof(StateHangOnParameter), 32);
			if (pClone)
				new(pClone) StateHangOnParameter(*this);

			return pClone;
		}

		const char* GetName() const override
		{
			return ms_pName;
		}
	};
}