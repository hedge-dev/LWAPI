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

		ObjectMoveArray(fnd::IAllocator* in_pAllocator) : MoveArray<T>(in_pAllocator)
		{
			
		}

		ObjectMoveArray(void* in_pBuffer, uint in_length, uint in_capacity, fnd::IAllocator* in_pAllocator, bool in_unk) : MoveArray<T>(in_pAllocator)
		{
			this->pBuffer = static_cast<T*>(in_pBuffer);
			this->Length = in_length;

			if (in_unk)
				in_capacity |= SIGN_BIT;
			this->Capacity = in_capacity;
			this->m_pAllocator = in_pAllocator;

			T* pEnd = (&static_cast<T*>(in_pBuffer)[in_length]);
			T* pStart = static_cast<T*>(in_pBuffer);
			while (pStart != pEnd)
			{
				new(pStart) T();
				pStart++;
			}
		}

		void insert(size_t in_index, const T& in_rItem)
		{
			if (in_index >= this->size())
			{
				return;
			}

			if (in_index == this->size() - 1 || (this->size() == 0 && in_index == 0))
			{
				push_back(in_rItem);
				return;
			}

			this->Length++;
			if (this->Length > this->capacity())
			{
				this->reserve(this->Length * 2);
			}

			memmove(&this->pBuffer[in_index + 1], &this->pBuffer[in_index], (this->size() - in_index) * sizeof(T));
			new(&this->pBuffer[in_index]) T(in_rItem);
		}

		void push_back(const T& in_rItem)
		{
			this->Length++;
			if (this->Length > this->capacity())
			{
				this->reserve(this->Length * 2);
			}

			new(&this->pBuffer[this->Length - 1]) T(in_rItem);
		}

		void remove(uint in_index)
		{
			if (in_index >= this->Length)
				return;

			this->Length[in_index].~T();

			if (in_index != this->Length - 1)
				this->pBuffer[in_index] = this->pBuffer[in_index + 1];

			this->Length--;
		}

		void erase(T* in_pItem)
		{
			in_pItem->~T();

			T* pEnd = &this->pBuffer[this->Length];
			if (in_pItem != pEnd)
			{
				for (T* i = in_pItem; i != pEnd; i++)
				{
					memcpy(i, &i[1], sizeof(T));
				}
			}

			this->Length--;
		}

		void clear()
		{
			for (auto& item : *this)
			{
				item.~T();
			}

			this->Length = 0;
		}

		void resize(size_t in_num)
		{
			if (in_num < this->size())
			{
				for (size_t i = in_num; i < this->size(); i++)
				{
					(*this)[i].~T();
				}
				
				this->Length = in_num;
				return;
			}
			else if (in_num > this->size())
			{
				this->reserve(in_num);

				for (size_t i = this->size(); i < in_num; i++)
				{
					new(&(*this)[i]) T();
				}

				this->Length = in_num;
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