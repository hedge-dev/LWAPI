#pragma once
#include <new>

namespace csl::ut
{
	template <typename T>
	class ObjectMoveArray : public MoveArray<T>
	{
	public:
		ObjectMoveArray(fnd::IAllocator* allocator_) : MoveArray<T>(allocator_)
		{
			
		}
		
		void push_back(T& item)
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
					(*this)[i] = T{};
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