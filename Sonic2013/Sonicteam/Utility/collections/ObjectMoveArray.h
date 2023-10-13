#pragma once
#include <new>

namespace csl::ut
{
	template <typename T>
	class ObjectMoveArray : public MoveArray<T>
	{
	public:
		ObjectMoveArray() : MoveArray<T>()
		{

		}

		ObjectMoveArray(fnd::IAllocator* allocator_) : MoveArray<T>(allocator_)
		{
			
		}

		ObjectMoveArray(void* in_pBuffer, uint in_length, uint in_capacity, fnd::IAllocator* in_pAllocator, bool in_unk) : MoveArray<T>(in_pAllocator)
		{
			this->p_buffer = static_cast<T*>(in_pBuffer);
			this->m_length = in_length;

			if (in_unk)
				in_capacity |= SIGN_BIT;
			this->m_capacity = in_capacity;
			this->p_allocator = in_pAllocator;

			T* pEnd = (&static_cast<T*>(in_pBuffer)[in_length]);
			T* pStart = static_cast<T*>(in_pBuffer);
			while (pStart != pEnd)
			{
				new(pStart) T();
				pStart++;
			}
		}

		void insert(size_t i, const T& item)
		{
			if (i >= this->size())
			{
				return;
			}

			if (i == this->size() - 1 || (this->size() == 0 && i == 0))
			{
				push_back(item);
				return;
			}

			this->m_length++;
			if (this->m_length > this->capacity())
			{
				this->reserve(this->m_length * 2);
			}

			memmove(&this->p_buffer[i + 1], &this->p_buffer[i], (this->size() - i) * sizeof(T));
			new(&this->p_buffer[i]) T(item);
		}

		void push_back(const T& item)
		{
			this->m_length++;
			if (this->m_length > this->capacity())
			{
				this->reserve(this->m_length * 2);
			}

			new(&this->p_buffer[this->m_length - 1]) T(item);
		}

		void remove(uint i)
		{
			if (i >= this->m_length)
				return;

			this->p_buffer[i].~T();

			if (i != this->m_length - 1)
				this->p_buffer[i] = this->p_buffer[i + 1];

			this->m_length--;
		}

		void erase(T* in_pItem)
		{
			in_pItem->~T();

			T* pEnd = &this->p_buffer[this->m_length];
			if (in_pItem != pEnd)
			{
				for (T* i = in_pItem; i != pEnd; i++)
				{
					memcpy(i, &i[1], sizeof(T));
				}
			}

			this->m_length--;
		}

		void clear()
		{
			for (auto& item : *this)
			{
				item.~T();
			}

			this->m_length = 0;
		}

		void resize(size_t num)
		{
			if (num < this->size())
			{
				for (size_t i = num; i < this->size(); i++)
				{
					(*this)[i].~T();
				}
				
				this->m_length = num;
				return;
			}
			else if (num > this->size())
			{
				this->reserve(num);

				for (size_t i = this->size(); i < num; i++)
				{
					new(&(*this)[i]) T();
				}

				this->m_length = num;
			}
		}

		~ObjectMoveArray()
		{
			for (auto& item : *this)
			{
				item.~T();
			}
		}
	};
}