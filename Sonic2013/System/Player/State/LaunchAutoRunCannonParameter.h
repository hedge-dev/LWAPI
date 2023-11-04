#pragma once

namespace app::Player
{
	struct LaunchAutoRunCannonParameter : public SStateParameter
	{
	public:
		inline static const char* ms_pName = (const char*)ASLR(0x00DFA0A8);

		float Unk2{};
		csl::math::Vector3 Unk3{};

		LaunchAutoRunCannonParameter* Clone(csl::fnd::IAllocator& in_rAlloc) const override
		{
			auto* pClone = (LaunchAutoRunCannonParameter*)in_rAlloc.Alloc(sizeof(LaunchAutoRunCannonParameter), 32);
			if (pClone)
				new(pClone) LaunchAutoRunCannonParameter(*this);

			return pClone;
		}

		const char* GetName() const override
		{
			return ms_pName;
		}
	};
}