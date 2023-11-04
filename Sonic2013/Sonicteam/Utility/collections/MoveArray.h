#pragma once

namespace csl
{
	namespace ut
	{
		template<typename T>
		class MoveArray : public Array<T>
		{
		protected:
			fnd::IAllocator* m_pAllocator{};

			bool isInplace()
			{
				return this->Capacity & csl::ut::SIGN_BIT;
			}
			
		public:
			void change_allocator(fnd::IAllocator* in_pAllocator)
			{
				if (!in_pAllocator)
				{
					return;
				}

				if (isInplace() || !this->pBuffer)
				{
					m_pAllocator = in_pAllocator;
					return;
				}
				
				if (m_pAllocator == in_pAllocator)
				{
					return;
				}
				
				// Make a new pBuffer
				void* pBuffer = in_pAllocator->Alloc(this->capacity() * sizeof(T), 16);

				// Copy buffers
				memcpy(pBuffer, this->pBuffer, sizeof(T) * this->Length);

				// Free our old pBuffer
				if (m_pAllocator && !isInplace())
				{
					m_pAllocator->Free(this->pBuffer);
				}

				m_pAllocator = in_pAllocator;
				this->pBuffer = static_cast<T*>(pBuffer);
			}
			
			void reserve(size_t in_len)
			{
				// We already have enough reserved, return
				if (in_len <= this->capacity())
					return;

				// Allocate a new pBuffer with the appropriate reserved storage
				void* pBuffer = m_pAllocator->Alloc(sizeof(T) * in_len, 16);

				if (this->pBuffer)
				{
					memcpy(pBuffer, this->pBuffer, sizeof(T) * this->Length);
				}

				// Free our old pBuffer
				if (!isInplace())
				{
					m_pAllocator->Free(this->pBuffer);
				}

				// Assign our new pBuffer and set the new Capacity
				this->Capacity = in_len;
				this->pBuffer = static_cast<T*>(pBuffer);
			}

			void resize(size_t in_len)
			{
				reserve(in_len);
				this->Length = in_len;
			}

			void resize_unchecked(size_t in_len)
			{
				this->Length = in_len;
			}
			
		public:
			MoveArray()
			{
				
			}
			
			MoveArray(fnd::IAllocator* in_pAllocator) : m_pAllocator(in_pAllocator)
			{
				
			}

			MoveArray(size_t in_capacity, fnd::IAllocator* in_pAllocator) : MoveArray(in_pAllocator)
			{
				reserve(in_capacity);
			}
			
			~MoveArray()
			{
				if (m_pAllocator && !isInplace())
					m_pAllocator->Free(this->pBuffer);
			}

			csl::fnd::IAllocator* get_allocator()
			{
				return m_pAllocator;
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
				this->pBuffer[in_index] = in_rItem;
			}

			void push_back(const T& in_rItem)
			{
				this->Length++;
				if (this->Length > this->capacity())
				{
					reserve(this->Length * 2);
				}

				this->pBuffer[this->Length - 1] = in_rItem;
			}

			void push_back_unchecked(const T& in_rItem)
			{
				this->Length++;
				this->pBuffer[this->Length - 1] = in_rItem;
			}

			void remove(uint in_index)
			{
				if (in_index > this->Length)
					return;
				
				this->pBuffer[in_index] = this->pBuffer[in_index + 1];
				this->Length--;
			}

			bool empty() const
			{
				return this->Length == 0;
			}
			
			void clear()
			{
				if (!this->empty())
					this->Length = 0;
			}
			
			void swap(MoveArray& in_rArray)
			{
				auto* tempBuffer = this->pBuffer;
				auto tempLen = this->Length;
				auto tempCap = this->Capacity;
				auto* tempAllocator = this->m_pAllocator;
				
				this->pBuffer = in_rArray.pBuffer;
				this->Length = in_rArray.Length;
				this->Capacity = in_rArray.Capacity;
				this->m_pAllocator = in_rArray.m_pAllocator;

				in_rArray.pBuffer = tempBuffer;
				in_rArray.Length = tempLen;
				in_rArray.Capacity = tempCap;
				in_rArray.m_pAllocator = tempAllocator;
			}

			size_t find(const T& in_rItem) const
			{
				for (size_t i = 0; i < this->Length; i++)
				{
					if (*this->get(i) == in_rItem)
						return i;
				}

				return -1;
			}
			
			const T& operator[] (size_t in_index) const
			{
				return *this->get(in_index);
			}

			T& operator[] (size_t in_index)
			{
				return *this->get(in_index);
			}
		};
	}
}