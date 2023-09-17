#pragma once

namespace csl::ut
{
	template<typename T>
	class CircularBuffer
	{
	public:
		T* m_pBuffer{};
		T* m_pEnd{};
		T* m_pFirst{};
		T* m_pLast{};
		size_t m_Size{};
		csl::fnd::IAllocator* m_pAllocator{};

		CircularBuffer(csl::fnd::IAllocator* in_pAllocator) : m_pAllocator(in_pAllocator) { }

		//detail_iterator<CircularBuffer<T>> begin();

		//detail_iterator<CircularBuffer<T>> end();

		constexpr T& at(size_t in_index)
		{
			if (in_index >= (m_pEnd - m_pFirst))
			{
				in_index -= capacity();
			}

			return m_pFirst[in_index];
		}

		constexpr const T& at(size_t in_index) const
		{
			if (in_index >= (m_pEnd - m_pFirst))
			{
				in_index -= capacity();
			}

			return m_pFirst[in_index];
		}

		constexpr T& front()
		{
			return *m_pFirst;
		}

		constexpr T& back()
		{
			return *((m_pLast == m_pBuffer ? m_pEnd : m_pLast) - 1);
		}

		constexpr const T& front() const
		{
			return *m_pFirst;
		}

		constexpr const T& back() const
		{
			return *((m_pLast == m_pBuffer ? m_pEnd : m_pLast) - 1);
		}

		constexpr size_t size() const
		{
			return m_Size;
		}

		constexpr bool empty() const
		{
			return size() == 0;
		}

		constexpr bool full() const
		{
			return capacity() == size();
		}

		constexpr size_t capacity() const
		{
			return m_pEnd - m_pBuffer;
		}

		constexpr void set_capacity(size_t in_capacity)
		{
			if (in_capacity == capacity())
				return;
		
			T* buff = static_cast<T*>(AllocateMemory(in_capacity));

			size_t size = m_Size;
			if (in_capacity < size)
				size = in_capacity;

			for (size_t i = 0; i < size; i++)
			{
				size_t index = i;
				if (i >= (m_pEnd - m_pFirst) / sizeof(T))
					index = i - capacity();

				*buff = m_pFirst[index];
				buff++;
			}

			ReleaseMemory();
			
			m_pFirst = buff;
			m_pBuffer = buff;
			m_Size = size;
			m_pLast = &buff[size];
			m_pEnd = &buff[in_capacity];
		}

		constexpr void push_back(const T& in_rItem)
		{
			if (full())
			{
				if (empty())
					return;

				*m_pLast = in_rItem;
				++m_pLast;

				if (m_pLast == m_pEnd)
				{
					m_pLast = m_pBuffer;
				}

				m_pFirst = m_pLast;
			}
			else
			{
				*m_pLast = in_rItem;
				++m_pLast;

				if (m_pLast == m_pEnd)
				{
					m_pLast = m_pBuffer;
				}

				++m_Size;
			}
		}

		constexpr void push_front(const T& in_rItem)
		{
			if (full())
			{
				if (empty())
					return;

				if (m_pFirst == m_pBuffer)
				{
					m_pFirst = m_pEnd;
				}

				--m_pFirst;
				*m_pFirst = in_rItem;
				m_pLast = m_pFirst;
			}
			else
			{
				if (m_pFirst == m_pBuffer)
				{
					m_pFirst = m_pEnd;
				}

				--m_pFirst;
				*m_pFirst = in_rItem;
				++m_Size;
			}
		}
		
		constexpr void pop_back()
		{
			if (m_pLast == m_pBuffer)
				m_pLast = m_pEnd;

			--m_pLast;
			--m_Size;
		}

		constexpr void pop_front()
		{
			++m_pFirst;
			if (m_pFirst == m_pEnd)
				m_pFirst = m_pBuffer;
			
			--m_Size;
		}

		constexpr void clear()
		{
			if (m_Size)
			{
				DestroyContent();
				m_Size = 0;
			}
		}

		void* AllocateMemory(size_t in_capacity)
		{
			if (m_pAllocator)
				return m_pAllocator->Alloc(in_capacity * sizeof(T), 16);
			else
				return { nullptr };
		}

		void ReleaseMemory()
		{
			if (m_pAllocator && m_pBuffer)
			{
				m_pAllocator->Free(m_pBuffer);
			}

			m_pBuffer = nullptr;
		}

		void DestroyContent()
		{
			for (size_t i = 0; i < m_Size; i++)
			{
				m_pFirst++;

				if (m_pFirst == m_pEnd)
					m_pFirst = m_pBuffer;
			}
		}
	};
}