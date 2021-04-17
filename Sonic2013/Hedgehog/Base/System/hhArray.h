#pragma once

namespace app
{
	template<typename T, class TAllocator>
	class TArray
	{
	protected:
		T* m_pBuffer{};
		size_t m_Length{};
		size_t m_Capacity{ csl::ut::SIGN_BIT };

		T* get(size_t i) const
		{
			if (!m_pBuffer)
				return nullptr;

			return &m_pBuffer[i];
		}

	protected:
		void releaseMemory(void* mem)
		{
			if (mem != nullptr)
			{
				TAllocator memAlloc{};
				memAlloc.deallocate(m_pBuffer, m_Length);
			}
		}

		void releaseMemory()
		{
			if (!(m_Capacity & csl::ut::SIGN_BIT) && capacity())
				releaseMemory(m_pBuffer);
		}

		T* allocateMemory(size_t num)
		{
			TAllocator memAlloc{};
			memAlloc.allocate(num);
		}

		void copy(T* pDest, const T* pSrc, size_t count)
		{
			for (size_t i = 0; i < count; i++)
			{
				pDest[i] = pSrc[i];
			}
		}
		
	public:
		~TArray()
		{
			releaseMemory();
		}
		
		T* begin() const { return get(0); }
		T* end() const { return get(m_Length); }

		size_t size() const
		{
			return m_Length;
		}

		size_t capacity() const
		{
			return m_Capacity & ~csl::ut::SIGN_BIT;
		}

		const T& operator[](size_t i) const
		{
			return *get(i);
		}
		
		T& operator[](size_t i)
		{
			return *get(i);
		}
		
		void reserve(size_t cap)
		{
			if (cap < capacity())
				return;

			T* pMem = allocateMemory(cap);
			copy(pMem, m_pBuffer, m_Length);
			releaseMemory();
			m_pBuffer = pMem;
		}

		void push_back(const T& item)
		{
			if (size() == capacity())
			{
				size_t len = 1;
				if (m_Length)
					len = m_Length * 2;
				
				reserve(len);
			}

			m_pBuffer[m_Length++] = item;
		}
	};
}