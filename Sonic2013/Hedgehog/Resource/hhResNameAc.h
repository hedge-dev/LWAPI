#pragma once

namespace hh::gfx::res
{
	struct ResNameData
	{
		size_t m_Hash{};
		const char* m_pValue{};
	};

	class ResName : public hh::ut::ResCommon<ResNameData>
	{
		
	};
}