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
		void releaseMemory(void* in_pMem)
		{
			if (in_pMem != nullptr)
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

		T* allocateMemory(size_t in_num)
		{
			TAllocator memAlloc{};
			return memAlloc.allocate(in_num);
		}

		void copy(T* in_pDest, const T* in_pSrc, size_t in_count)
		{
			for (size_t i = 0; i < in_count; i++)
			{
				in_pDest[i] = in_pSrc[i];
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

		const T& operator[](size_t in_index) const
		{
			return *get(in_index);
		}
		
		T& operator[](size_t in_index)
		{
			return *get(in_index);
		}
		
		void reserve(size_t in_cap)
		{
			if (in_cap < capacity())
				return;

			T* pMem = allocateMemory(in_cap);
			copy(pMem, m_pBuffer, m_Length);
			releaseMemory();
			m_pBuffer = pMem;
		}

		void push_back(const T& in_rItem)
		{
			if (size() == capacity())
			{
				size_t len = 1;
				if (m_Length)
					len = m_Length * 2;
				
				reserve(len);
			}

			m_pBuffer[m_Length++] = in_rItem;
		}
	};
}