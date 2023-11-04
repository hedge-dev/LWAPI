#pragma once

namespace csl::ut
{
	template<typename TOp>
	class HashMap
	{
		inline static constexpr size_t INVALID_KEY = static_cast<size_t>(-1);
		
	protected:
		struct Elem
		{
			size_t Hash;
			size_t Key;
			size_t Value;
		};
		
		Elem* m_pElements{};
		size_t m_Length{};
		size_t m_Capacity{};
		size_t m_CapacityMax{};
		fnd::IAllocator* m_pAllocator{};
		TOp m_Operation{};
		
	protected:
		size_t CalcResize(size_t in_capacity)
		{
			size_t result;
			for (result = 16; result < in_capacity; result *= 2);

			if (result < 16)
				result = 16;

			return result;
		}

		Elem* AllocateMemory(size_t in_count)
		{
			return static_cast<Elem*>(m_pAllocator->Alloc(sizeof(Elem) * in_count, alignof(Elem)));
		}

		void ReleaseMemory()
		{
			if (!(m_Capacity & csl::ut::SIGN_BIT) && m_pAllocator && m_pElements)
			{
				m_pAllocator->Free(m_pElements);
			}
		}
		
		size_t GetCapacity()
		{
			return m_Capacity & ~csl::ut::SIGN_BIT;
		}

		void ResizeTbl(size_t in_capacity)
		{
			size_t oldCap = GetCapacity();
			Elem* oldElements = m_pElements;

			m_Capacity = in_capacity;
			m_CapacityMax = in_capacity - 1;
			m_Length = 0;

			m_pElements = AllocateMemory(in_capacity);
			memset(m_pElements, INVALID_KEY, sizeof(Elem) * in_capacity);

			if (oldElements)
			{
				for (size_t i = 0; i < oldCap; i++)
				{
					const Elem* pElem = &oldElements[i];

					if (pElem->m_Hash != INVALID_KEY)
					{
						Insert(pElem->m_Key, pElem->m_Value);
					}
				}

				if (m_pAllocator)
					m_pAllocator->Free(oldElements);
			}
		}

		void Reserve(size_t in_capacity)
		{
			size_t cap = CalcResize(in_capacity);
			if (GetCapacity() < cap)
				ResizeTbl(cap);
		}
		
		HashMap(fnd::IAllocator* in_pAllocator)
		{
			m_pAllocator = in_pAllocator;
		}

	public:
		void reserve(size_t in_capacity)
		{
			Reserve(in_capacity);
		}

		~HashMap()
		{
			ReleaseMemory();
			m_Length = 0;
			m_Capacity = 0;
			m_CapacityMax = 0;
			m_pElements = nullptr;
		}
		
	protected:
		void Insert(size_t in_key, size_t in_value)
		{
			size_t hash = m_Operation.hash(in_key);
			if (m_Length || GetCapacity())
			{
				if (2 * m_Length >= GetCapacity())
				{
					ResizeTbl(2 * GetCapacity());
				}
			}
			else
			{
				ResizeTbl(CalcResize(GetCapacity()));
			}

			size_t idx = hash & m_CapacityMax;
			Elem* pElem = &m_pElements[idx];

			if (pElem->Hash == INVALID_KEY)
			{
				pElem->Hash = hash;
				pElem->Key = in_key;
				pElem->Value = in_value;
				m_Length++;
			}
			else
			{
				while (pElem->Hash != hash || pElem->Key != key)
				{
					idx = m_CapacityMax & (idx + 1);
					pElem = &m_pElements[idx];

					if (pElem->Hash == INVALID_KEY)
					{
						pElem->Hash = hash;
						pElem->Key = key;
						pElem->Value = value;
						m_Length++;
						break;
					}
				}
			}
		}

		size_t GetBegin() const
		{
			for (size_t i = 0; i < m_CapacityMax; i++)
			{
				if (m_pElements[i].Hash != INVALID_KEY)
					return i;
			}
			
			return m_CapacityMax + 1;
		}

		size_t GetNext(size_t in_idx) const
		{
			for (size_t i = in_idx + 1; i < m_CapacityMax; i++)
			{
				if (m_pElements[i].Hash != INVALID_KEY)
					return i;
			}

			return m_CapacityMax + 1;
		}
		
	public:
		struct iterator
		{
			const HashMap* pOwner;
			size_t CurIdx;

			friend bool operator==(const iterator& a, const iterator& b) { return a.CurIdx == b.CurIdx; }
			friend bool operator!=(const iterator& a, const iterator& b) { return a.CurIdx != b.CurIdx; }
		};

		iterator begin() const
		{
			return iterator{ this, GetBegin() };
		}

		iterator end() const
		{
			return iterator{ this, m_CapacityMax + 1 };
		}

		void clear()
		{
			m_Length = 0;
			for (size_t i = 0; i < m_CapacityMax + 1; ++i)
			{
				auto& element = m_pElements[i];
				element.Hash = INVALID_KEY;
			}
		}

	protected:
		iterator Find(size_t in_key) const
		{
			if (!m_pElements)
				return end();

			TOp& op = const_cast<TOp&>(m_Operation);
			
			const size_t hash = op.hash(in_key);
			size_t idx = hash & m_CapacityMax;
			const Elem* pElem = &m_pElements[idx];
			
			if (pElem->Hash == INVALID_KEY)
				return end();
			
			while (pElem->Hash != hash || !op.compare(in_key, pElem->Key))
			{
				idx = m_CapacityMax & (idx + 1);
				pElem = &m_pElements[idx];

				if (pElem->Hash == INVALID_KEY)
					return end();
			}

			return iterator{ this, idx };
		}

		size_t GetKey(iterator in_iter) const
		{
			return in_iter.pOwner->m_pElements[in_iter.CurIdx].Key;
		}
		
		size_t GetValue(iterator in_iter) const
		{
			return in_iter.pOwner->m_pElements[in_iter.CurIdx].Value;
		}

		size_t* GetValuePtr(iterator in_iter) const
		{
			return &in_iter.pOwner->m_pElements[in_iter.CurIdx].Value;
		}
		
		void Erase(size_t in_key)
		{
			auto result = Find(in_key);

			if (result == end())
				return;

			Elem* pElem = &m_pElements[result.CurIdx];
			pElem->Hash = INVALID_KEY;
			pElem->Key = INVALID_KEY;
			pElem->Value = INVALID_KEY;
			m_Length--;
		}

		void Erase(const iterator& in_rIter)
		{
			if (in_rIter == end())
				return;

			Elem* pElem = &m_pElements[in_rIter.CurIdx];
			pElem->Hash = INVALID_KEY;
			pElem->Key = INVALID_KEY;
			pElem->Value = INVALID_KEY;
			m_Length--;
		}
	};
}