#pragma once

namespace csl::ut
{
	class VariableString
	{
	protected:
		const char* p_str{};
		fnd::IAllocator* p_allocator{};
	};
}