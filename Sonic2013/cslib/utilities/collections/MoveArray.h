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
			
			void push_back(T item)
			{
				length++;
				if (length > maxLength)
				{
					reserve(length * 2);
				}

				buffer[length - 1] = item;
			}

			T operator[] (size_t i) const
			{
				return *buffer[i];
			}

			T* begin() const { return get(0); }

			T* end() const { return get(length); }
			
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