#pragma once

namespace app::Player
{
	struct GoalParameter : public SStateParameter
	{
	public:
		inline static const char* ms_pName = (const char*)ASLR(0x00DFF374);

		int Unk1{};
		csl::math::Vector3 Unk2{};
		float Unk3{};

		GoalParameter() : SStateParameter()
		{
			m_Unk1 = 1;
		}

		GoalParameter* Clone(csl::fnd::IAllocator& in_rAlloc) const override
		{
			auto* pParam = static_cast<GoalParameter*>(in_rAlloc.Alloc(sizeof(GoalParameter), 32));
			*pParam = { *this };

			return pParam;
		}

		const char* GetName() const override
		{
			return (const char*)ASLR(0x00DFF374);
		}
	};
}