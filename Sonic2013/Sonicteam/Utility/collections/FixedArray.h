#pragma once

namespace csl::ut
{
	template<typename T, size_t Len>
	class FixedArray
	{
		T m_Items[Len];

	public:
		T* begin()
		{
			return &m_Items[0];
		}

		T* end()
		{
			return &m_Items[Len];
		}
		
		T operator[] (size_t i) const
		{
			return m_Items[i];
		}

		T& operator[] (size_t i)
		{
			return m_Items[i];
		}
	};
}