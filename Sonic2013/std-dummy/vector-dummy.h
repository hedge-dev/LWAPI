#pragma once

namespace std::dummy
{
	template<typename T>
	class vector
	{
	protected:
		T* m_pFirst{};
		T* m_pLast{};
		T* m_pCapacityLast{};
		void* m_pPad{};

	public:
		T* begin() const
		{
			return m_pFirst;
		}

		T* end() const
		{
			return m_pLast;
		}

		size_t size() const
		{
			return (reinterpret_cast<const size_t>(m_pLast) - reinterpret_cast<const size_t>(m_pFirst)) / sizeof(T);
		}

		size_t capacity() const
		{
			return (reinterpret_cast<const size_t>(m_pCapacityLast) - reinterpret_cast<const size_t>(m_pFirst)) / sizeof(T);
		}
	};
}