#pragma once

namespace app::Player
{
	struct LaunthToPathParameter : public SStateParameter
	{
	public:
		inline static const char* ms_pName = (const char*)ASLR(0x00DFCDDC);

		int Sender{};
		fnd::Handle<game::PathComponent> PathComponent{};
		float Unk2{};
		float Unk3{};

		LaunthToPathParameter()
		{
			m_Unk1 = 1;
		}

		LaunthToPathParameter* Clone(csl::fnd::IAllocator& in_rAlloc) const override
		{
			auto* pClone = (LaunthToPathParameter*)in_rAlloc.Alloc(sizeof(LaunthToPathParameter), 32);
			if (pClone)
				new(pClone) LaunthToPathParameter(*this);

			return pClone;
		}

		const char* GetName() const override
		{
			return ms_pName;
		}
	};

	typedef LaunthToPathParameter LaunchToPathParameter;
}