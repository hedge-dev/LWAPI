#pragma once

namespace csl::ut
{
	template<typename T>
	class CircularBuffer
	{
	public:
		T* pBuffer{};
		T* pEnd{};
		T* pFirst{};
		T* pLast{};
		size_t Size{};
		csl::fnd::IAllocator* pAllocator{};

		CircularBuffer(csl::fnd::IAllocator* in_pAllocator) : pAllocator(in_pAllocator) { }

		//detail_iterator<CircularBuffer<T>> begin();

		//detail_iterator<CircularBuffer<T>> end();

		constexpr T& at(size_t in_index)
		{
			if (in_index >= (pEnd - pFirst))
			{
				in_index -= capacity();
			}

			return pFirst[in_index];
		}

		constexpr const T& at(size_t in_index) const
		{
			if (in_index >= (pEnd - pFirst))
			{
				in_index -= capacity();
			}

			return pFirst[in_index];
		}

		constexpr T& front()
		{
			return *pFirst;
		}

		constexpr T& back()
		{
			return *((pLast == pBuffer ? pEnd : pLast) - 1);
		}

		constexpr const T& front() const
		{
			return *pFirst;
		}

		constexpr const T& back() const
		{
			return *((pLast == pBuffer ? pEnd : pLast) - 1);
		}

		constexpr size_t size() const
		{
			return Size;
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
			return pEnd - pBuffer;
		}

		constexpr void set_capacity(size_t in_capacity)
		{
			if (in_capacity == capacity())
				return;
		
			T* buff = static_cast<T*>(AllocateMemory(in_capacity));

			size_t size = Size;
			if (in_capacity < size)
				size = in_capacity;

			for (size_t i = 0; i < size; i++)
			{
				size_t index = i;
				if (i >= (pEnd - pFirst) / sizeof(T))
					index = i - capacity();

				*buff = pFirst[index];
				buff++;
			}

			ReleaseMemory();
			
			pFirst = buff;
			pBuffer = buff;
			Size = size;
			pLast = &buff[size];
			pEnd = &buff[in_capacity];
		}

		constexpr void push_back(const T& in_rItem)
		{
			if (full())
			{
				if (empty())
					return;

				*pLast = in_rItem;
				++pLast;

				if (pLast == pEnd)
				{
					pLast = pBuffer;
				}

				pFirst = pLast;
			}
			else
			{
				*pLast = in_rItem;
				++pLast;

				if (pLast == pEnd)
				{
					pLast = pBuffer;
				}

				++Size;
			}
		}

		constexpr void push_front(const T& in_rItem)
		{
			if (full())
			{
				if (empty())
					return;

				if (pFirst == pBuffer)
				{
					pFirst = pEnd;
				}

				--pFirst;
				*pFirst = in_rItem;
				pLast = pFirst;
			}
			else
			{
				if (pFirst == pBuffer)
				{
					pFirst = pEnd;
				}

				--pFirst;
				*pFirst = in_rItem;
				++Size;
			}
		}
		
		constexpr void pop_back()
		{
			if (pLast == pBuffer)
				pLast = pEnd;

			--pLast;
			--Size;
		}

		constexpr void pop_front()
		{
			++pFirst;
			if (pFirst == pEnd)
				pFirst = pBuffer;
			
			--Size;
		}

		constexpr void clear()
		{
			if (Size)
			{
				DestroyContent();
				Size = 0;
			}
		}

		void* AllocateMemory(size_t in_capacity)
		{
			if (pAllocator)
				return pAllocator->Alloc(in_capacity * sizeof(T), 16);
			else
				return { nullptr };
		}

		void ReleaseMemory()
		{
			if (pAllocator && pBuffer)
			{
				pAllocator->Free(pBuffer);
			}

			pBuffer = nullptr;
		}

		void DestroyContent()
		{
			for (size_t i = 0; i < Size; i++)
			{
				pFirst++;

				if (pFirst == pEnd)
					pFirst = pBuffer;
			}
		}
	};
}