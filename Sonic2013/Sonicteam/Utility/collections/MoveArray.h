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
				return this->m_capacity & csl::ut::SIGN_BIT;
			}
			
		public:
			void change_allocator(fnd::IAllocator* new_allocator)
			{
				if (!new_allocator)
				{
					return;
				}

				if (isInplace() || !this->p_buffer)
				{
					p_allocator = new_allocator;
					return;
				}
				
				if (p_allocator == new_allocator)
				{
					return;
				}
				
				// Make a new p_buffer
				void* new_buffer = new_allocator->Alloc(this->capacity() * sizeof(T), 16);

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
				if (len <= this->capacity())
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
			MoveArray()
			{
				
			}
			
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

			csl::fnd::IAllocator* get_allocator()
			{
				return p_allocator;
			}
			
			void push_back(T item)
			{
				this->m_length++;
				if (this->m_length > this->capacity())
				{
					reserve(this->m_length * 2);
				}

				this->p_buffer[this->m_length - 1] = item;
			}
			
			void remove(uint i)
			{
				if (i > this->m_length)
					return;
				
				this->p_buffer[i] = this->p_buffer[i + 1];
				this->m_length--;
			}

			bool empty()
			{
				return this->m_length == 0;
			}
			
			void clear()
			{
				if (!empty())
					this->m_length = 0;
			}
			
			void swap(MoveArray& rArray)
			{
				auto* tempBuffer = this->p_buffer;
				auto tempLen = this->m_length;
				auto tempCap = this->m_capacity;
				auto* tempAllocator = this->p_allocator;
				
				this->p_buffer = rArray.p_buffer;
				this->m_length = rArray.m_length;
				this->m_capacity = rArray.m_capacity;
				this->p_allocator = rArray.p_allocator;

				rArray.p_buffer = tempBuffer;
				rArray.m_length = tempLen;
				rArray.m_capacity = tempCap;
				rArray.p_allocator = tempAllocator;
			}

			size_t find(const T& item) const
			{
				for (size_t i = 0; i < this->m_length; i++)
				{
					if (*this->get(i) == item)
						return i;
				}

				return -1;
			}
			
			const T& operator[] (size_t i) const
			{
				return *this->get(i);
			}

			T& operator[] (size_t i)
			{
				return *this->get(i);
			}
		};
	}
}