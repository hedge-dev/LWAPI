#pragma once

namespace csl::ut
{
	template <typename T>
	class Bitset
	{
		T dummy{};
		
	public:
		void reset()
		{
			dummy = T();
		}

		void set(T bit, T value)
		{
			dummy |= 1 << bit;
		}
		
		void flip(T bit)
		{
			dummy ^= 1 << bit;
		}
		
		bool test(T bit)
		{
			return dummy & (1 << bit);
		}

		operator T() const { return dummy; }
	};
}
