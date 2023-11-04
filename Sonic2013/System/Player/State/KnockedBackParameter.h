#pragma once

namespace app::Player
{
	struct KnockedBackParameter : public SStateParameter
	{
	public:
		inline static const char* ms_pName = (const char*)ASLR(0x00DF9BB4);

		csl::math::Vector3 Velocity{};

		KnockedBackParameter()
		{
			
			Unk1 = 1;
		}

		KnockedBackParameter* Clone(csl::fnd::IAllocator& in_rAlloc) const override
		{
			auto* pClone = (KnockedBackParameter*)in_rAlloc.Alloc(sizeof(KnockedBackParameter), 32);
			if (pClone)
				new(pClone) KnockedBackParameter(*this);

			return pClone;
		}

		const char* GetName() const override
		{
			return ms_pName;
		}
	};
}