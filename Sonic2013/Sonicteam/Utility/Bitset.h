#pragma once
#define CHAR_BIT 8

namespace csl::ut
{
	template <typename T, size_t BitSize = sizeof(T) * CHAR_BIT>
	class Bitset
	{
		T m_dummy : BitSize{};
		
	public:
		Bitset()
		{
			
		}

		Bitset(T value) : m_dummy(value){}
		
		constexpr void reset()
		{
			m_dummy = T();
		}

		constexpr void reset(T bit)
		{
			m_dummy &= ~(1 << bit);
		}

		constexpr void flip(T bit)
		{
			m_dummy ^= 1 << bit;
		}
		
		constexpr void set(T bit)
		{
			m_dummy |= 1 << bit;
		}

		void set(T bit, bool flag)
		{
			if (flag)
				set(bit);
			else
				reset(bit);
		}
		
		constexpr bool test(T bit) const
		{
			return m_dummy & (1 << bit);
		}
		
		operator T() const { return m_dummy; }
	};
}
