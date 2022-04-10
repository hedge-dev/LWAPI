#pragma once

namespace app
{
	namespace ut
	{
		template<typename T>
		T RoundUp(T in_value, uint in_round)
		{
			return (in_value + in_round - 1) & ~(in_round - 1);
		}
	}

	namespace fnd
	{
		inline static char* align_ptr(char* in_ptr, uint in_alignment)
		{
			return (char*)ut::RoundUp((size_t)in_ptr, in_alignment);
		}
	}
}