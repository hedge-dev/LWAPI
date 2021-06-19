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
		size_t hash(size_t key)
		{
			if (!key)
				return 0;
			
			const char* pStr = reinterpret_cast<const char*>(key);
			size_t hashResult{};

			for (size_t i = 0; pStr[i]; i++)
			{
				hashResult = HASH_MAGIC * hashResult + pStr[i];
			}

			return hashResult & HASH_MASK;
		}

		bool compare(size_t key, size_t other)
		{
			return strcmp(reinterpret_cast<const char*>(key), reinterpret_cast<const char*>(other)) == 0;
		}
	};

	template<typename TValue>
	class StringMap : public HashMap<StringMapOperation>
	{
		size_t keyCast(const char* key) const
		{
			return (size_t)key;
		}

		size_t valueCast(TValue value) const
		{
			return (size_t)value;
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
			friend bool operator==(const iterator& a, const iterator& b) { return a.m_CurIdx == b.m_CurIdx; }
			friend bool operator!=(const iterator& a, const iterator& b) { return a.m_CurIdx != b.m_CurIdx; }

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

		StringMap(fnd::IAllocator* pAllocator) : HashMap<csl::ut::StringMapOperation>(pAllocator)
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

		void insert(const char* key, TValue value)
		{
			Insert(keyCast(key), valueCast(value));
		}

		void erase(const char* key)
		{
			Erase(keyCast(key));
		}

		void erase(const iterator& iter)
		{
			Erase({ iter.m_pOwner, iter.m_CurIdx });
		}
		
		iterator find(const char* key) const
		{
			auto result = Find(keyCast(key));
			return iterator(this, result.m_CurIdx);
		}

		iterator operator[](const char* key) const
		{
			return find(key);
		}
	};
}