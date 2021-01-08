#pragma once

namespace csl
{
	namespace ut
	{
		template<typename T>
		class MoveArray
		{
		protected:
			T* buffer{};
			size_t length{};
			size_t maxLength{};
			fnd::IAllocator* allocator{};

			bool isInplace()
			{
				return maxLength & (1u << ((sizeof(size_t) * CHAR_BIT) - 1));
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
					allocator = new_allocator;
					return;
				}
				
				if (allocator == new_allocator)
				{
					return;
				}
				
				// Make a new buffer
				void* new_buffer = new_allocator->Alloc(maxLength * sizeof(T), 16);

				// Copy buffers
				memcpy(new_buffer, buffer, sizeof(T) * length);

				// Free our old buffer
				if (allocator && !isInplace())
				{
					allocator->Free(buffer);
				}

				allocator = new_allocator;
				buffer = static_cast<T*>(new_buffer);
			}
			
			void reserve(size_t len)
			{
				// We already have enough reserved, return
				if (len <= maxLength)
					return;

				// Allocate a new buffer with the appropriate reserved storage
				void* newBuffer = allocator->Alloc(sizeof(T) * len, 16);

				if (buffer)
				{
					memcpy(newBuffer, buffer, sizeof(T) * length);
				}

				// Free our old buffer
				if (!isInplace())
				{
					allocator->Free(buffer);
				}

				// Assign our new buffer and set the new maxLength
				maxLength = len;
				buffer = static_cast<T*>(newBuffer);
			}

		protected:
			T* get(size_t i) const
			{
				if (!buffer)
					return nullptr;

				return &buffer[i];
			}
			
		public:
			MoveArray(fnd::IAllocator* allocator_) : allocator(allocator_)
			{
				
			}

			MoveArray(size_t capacity, fnd::IAllocator* allocator_) : MoveArray(allocator_)
			{
				reserve(capacity);
			}
			
			~MoveArray()
			{
				if (allocator && !isInplace())
					allocator->Free(buffer);
			}

			T* begin() const { return get(0); }

			T* end() const { return get(length); }
			
			void push_back(T item)
			{
				length++;
				if (length > maxLength)
				{
					reserve(length * 2);
				}

				buffer[length - 1] = item;
			}

			void remove(uint i)
			{
				buffer[i] = buffer[i + 1];
				length--;
			}
			
			T operator[] (size_t i) const
			{
				return *get(i);
			}
			
			size_t size() const
			{
				return length;
			}

			size_t capacity() const
			{
				return maxLength & ~(1u << ((sizeof(size_t) * CHAR_BIT) - 1));
			}
		};
	}
}