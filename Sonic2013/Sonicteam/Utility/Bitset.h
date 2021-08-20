#pragma once
#define CHAR_BIT 8

namespace csl::ut
{
	template <typename T, size_t BitSize = sizeof(T) * CHAR_BIT>
	class Bitset
	{
		T m_dummy : BitSize;
		
	public:
		Bitset()
		{
			reset();
		}

		Bitset(T value) : m_dummy(value){}

		// This doesn't actually exist, i just want to make bits easily
		template<typename... TArgs>
		constexpr Bitset(TArgs... bits)
		{
			reset();
			(set(bits), ...);
		}
		
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

		constexpr T value() const
		{
			return m_dummy;
		}
		
		constexpr bool test(T bit) const
		{
			return m_dummy & (1 << bit);
		}
		
		operator T() const { return m_dummy; }
	};
}
