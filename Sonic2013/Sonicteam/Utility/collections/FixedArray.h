#pragma once

namespace csl::ut
{
	template<typename T, size_t Len>
	class FixedArray
	{
		T m_Items[Len];

	public:
		constexpr size_t size() const
		{
			return Len;
		}

		constexpr const T* begin() const
		{
			return m_Items;
		}

		constexpr const T* end() const
		{
			return &m_Items[Len];
		}

		constexpr T* begin()
		{
			return m_Items;
		}

		constexpr T* end()
		{
			return &m_Items[Len];
		}

		constexpr void assign(const T& in_rValue)
		{
			for (size_t i = 0; i < Len; i++)
			{
				m_Items[i] = in_rValue;
			}
		}
		
		constexpr T operator[] (size_t in_index) const
		{
			return m_Items[in_index];
		}

		constexpr T& operator[] (size_t in_index)
		{
			return m_Items[in_index];
		}
	};
}