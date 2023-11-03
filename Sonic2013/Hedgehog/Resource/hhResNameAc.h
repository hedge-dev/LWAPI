#pragma once

namespace hh::gfx::res
{
	struct ResNameData
	{
		size_t Hash{};
		const char* pValue{};
	};

	class ResName : public hh::ut::ResCommon<ResNameData>
	{
		
	};
}