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

		Bitset(T in_value) : m_dummy(in_value){}

		// This doesn't actually exist, i just want to make bits easily
		template<typename... TArgs>
		constexpr Bitset(TArgs... in_bits)
		{
			reset();
			(set(in_bits), ...);
		}
		
		constexpr void reset()
		{
			m_dummy = T();
		}

		constexpr void reset(T in_bit)
		{
			m_dummy &= ~(1 << in_bit);
		}

		constexpr void flip(T in_bit)
		{
			m_dummy ^= 1 << in_bit;
		}

		constexpr void Flip(T in_bit)
		{
			flip(in_bit);
		}

		constexpr void set()
		{
			m_dummy = -1;
		}
		
		constexpr void set(T in_bit)
		{
			m_dummy |= 1 << in_bit;
		}

		void set(T in_bit, bool in_flag)
		{
			if (in_flag)
				set(in_bit);
			else
				reset(in_bit);
		}

		void Set(T in_bit)
		{
			set(in_bit);
		}

		void Set(T in_bit, bool in_flag)
		{
			set(in_bit, in_flag);
		}

		constexpr T value() const
		{
			return m_dummy;
		}
		
		constexpr bool test(T in_bit) const
		{
			return m_dummy & (1 << in_bit);
		}

		constexpr bool Test(T in_bit) const
		{
			return test(in_bit);
		}
		
		operator T() const { return m_dummy; }
	};
}
