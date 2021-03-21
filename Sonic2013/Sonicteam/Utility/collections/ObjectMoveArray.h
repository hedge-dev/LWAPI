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
	};
}