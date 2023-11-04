#pragma once

namespace csl::ut
{
	class StringMapOperation
	{
		inline static constexpr size_t HASH_MASK = 0x7FFFFFFF;
		inline static constexpr size_t HASH_MAGIC = 31;

	protected:
		size_t m_Dummy;

	public:
		size_t hash(size_t in_key)
		{
			if (!in_key)
				return 0;
			
			const char* pStr = reinterpret_cast<const char*>(in_key);
			size_t hashResult{};
			size_t i = 0;
			char c = *pStr;

			if (*pStr)
			{
				do
				{
					++i;
					hashResult = HASH_MAGIC * hashResult + c;
					c = pStr[i];
				} while (pStr[i]);
			}

			return hashResult & HASH_MASK;
		}

		bool compare(size_t in_key, size_t in_other)
		{
			return strcmp(reinterpret_cast<const char*>(in_key), reinterpret_cast<const char*>(in_other)) == 0;
		}
	};

	template<typename TValue>
	class StringMap : public HashMap<StringMapOperation>
	{
		size_t keyCast(const char* in_pKey) const
		{
			return (size_t)in_pKey;
		}

		size_t valueCast(TValue in_value) const
		{
			return (size_t)in_value;
		}

	public:
		class iterator
		{
			friend StringMap;
			const StringMap* m_pOwner;
			size_t m_CurIdx;

			iterator(const StringMap* pOwner, size_t index) : m_pOwner(pOwner), m_CurIdx(index)
			{
				
			}
			
		public:
			friend bool operator==(const iterator& in_rA, const iterator& in_rB) { return in_rA.m_CurIdx == in_rB.m_CurIdx; }
			friend bool operator!=(const iterator& in_rA, const iterator& in_rB) { return in_rA.m_CurIdx != in_rB.m_CurIdx; }

			iterator& operator++() { m_CurIdx = m_pOwner->GetNext(m_CurIdx); return *this; }
			iterator operator++(int) { iterator tmp = *this; m_CurIdx = m_pOwner->GetNext(m_CurIdx); return tmp; }
			
			const char* key() const
			{
				return reinterpret_cast<const char*>(m_pOwner->GetKey(HashMap<StringMapOperation>::iterator{ m_pOwner, m_CurIdx }));
			}
			
			TValue get() const
			{
				return reinterpret_cast<TValue>(m_pOwner->GetValue(HashMap<StringMapOperation>::iterator{ m_pOwner, m_CurIdx }));
			}

			TValue& operator*() const
			{
				return *reinterpret_cast<TValue*>(m_pOwner->GetValuePtr(HashMap<StringMapOperation>::iterator{ m_pOwner, m_CurIdx }));
			}
			
			TValue operator->() const
			{
				return get();
			}

			operator TValue() const
			{
				return get();
			}

			operator TValue&()
			{
				return operator*();
			}
		};

		StringMap(fnd::IAllocator* in_pAllocator) : HashMap<csl::ut::StringMapOperation>(in_pAllocator)
		{

		}

		iterator begin() const
		{
			return iterator(this, GetBegin());
		}
		
		iterator end() const
		{
			return iterator(this, m_CapacityMax + 1);
		}

		void insert(const char* in_pKey, TValue in_value)
		{
			Insert(keyCast(in_pKey), valueCast(in_value));
		}

		void erase(const char* in_pKey)
		{
			Erase(keyCast(in_pKey));
		}

		void erase(const iterator& in_rIter)
		{
			Erase({ in_rIter.m_pOwner, in_rIter.m_CurIdx });
		}
		
		iterator find(const char* in_pKey) const
		{
			auto result = Find(keyCast(in_pKey));
			return iterator(this, result.CurIdx);
		}

		iterator operator[](const char* in_pKey) const
		{
			return find(in_pKey);
		}
	};
}