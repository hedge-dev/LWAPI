#pragma once

namespace csl
{
	namespace ut
	{
		template<typename T>
		class MoveArray : public Array<T>
		{
		protected:
			fnd::IAllocator* p_allocator{};

			bool isInplace()
			{
				return this->m_capacity & (1u << ((sizeof(size_t) * CHAR_BIT) - 1));
			}

		public:
			void change_allocator(fnd::IAllocator* new_allocator)
			{
				if (!new_allocator)
				{
					return;
				}

				if (isInplace())
				{
					p_allocator = new_allocator;
					return;
				}
				
				if (p_allocator == new_allocator)
				{
					return;
				}
				
				// Make a new p_buffer
				void* new_buffer = new_allocator->Alloc(this->m_capacity * sizeof(T), 16);

				// Copy buffers
				memcpy(new_buffer, this->p_buffer, sizeof(T) * this->m_length);

				// Free our old p_buffer
				if (p_allocator && !isInplace())
				{
					p_allocator->Free(this->p_buffer);
				}

				p_allocator = new_allocator;
				this->p_buffer = static_cast<T*>(new_buffer);
			}
			
			void reserve(size_t len)
			{
				// We already have enough reserved, return
				if (len <= this->m_capacity)
					return;

				// Allocate a new p_buffer with the appropriate reserved storage
				void* new_buffer = p_allocator->Alloc(sizeof(T) * len, 16);

				if (this->p_buffer)
				{
					memcpy(new_buffer, this->p_buffer, sizeof(T) * this->m_length);
				}

				// Free our old p_buffer
				if (!isInplace())
				{
					p_allocator->Free(this->p_buffer);
				}

				// Assign our new p_buffer and set the new m_capacity
				this->m_capacity = len;
				this->p_buffer = static_cast<T*>(new_buffer);
			}
			
		public:
			MoveArray(fnd::IAllocator* allocator_) : p_allocator(allocator_)
			{
				
			}

			MoveArray(size_t capacity, fnd::IAllocator* allocator_) : MoveArray(allocator_)
			{
				reserve(capacity);
			}
			
			~MoveArray()
			{
				if (p_allocator && !isInplace())
					p_allocator->Free(this->p_buffer);
			}
			
			void push_back(T item)
			{
				this->m_length++;
				if (this->m_length > this->m_capacity)
				{
					reserve(this->m_length * 2);
				}

				this->p_buffer[this->m_length - 1] = item;
			}

			void remove(uint i)
			{
				this->p_buffer[i] = this->p_buffer[i + 1];
				this->m_length--;
			}
			
			T operator[] (size_t i) const
			{
				return *this->get(i);
			}
		};
	}
}