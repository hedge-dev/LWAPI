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
		
		constexpr T operator[] (size_t i) const
		{
			return m_Items[i];
		}

		constexpr T& operator[] (size_t i)
		{
			return m_Items[i];
		}
	};
}