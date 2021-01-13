#pragma once

namespace csl::ut
{
	template <typename T>
	class Bitset
	{
		T m_dummy{};
		
	public:
		Bitset()
		{
			
		}

		Bitset(T value) : m_dummy(value){}
		
		void reset()
		{
			m_dummy = T();
		}

		void reset(T bit)
		{
			m_dummy &= ~(1 << bit);
		}

		void flip(T bit)
		{
			m_dummy ^= 1 << bit;
		}
		
		void set(T bit)
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
		
		bool test(T bit)
		{
			return m_dummy & (1 << bit);
		}
		
		operator T() const { return m_dummy; }
	};
}
