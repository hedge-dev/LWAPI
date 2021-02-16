#pragma once

namespace csl::ut
{
	class PointerMapOperation
	{
		inline static constexpr size_t HASH_MAGIC = 0x9E3779B1;

	protected:
		size_t m_Dummy;
		
	public:
		size_t hash(size_t key)
		{
			return HASH_MAGIC * key;
		}
	};

	template<typename TKey, typename TValue>
	class PointerMap : public HashMap<PointerMapOperation>
	{
		size_t keyCast(TKey key) const
		{
			return (size_t)key;
		}

		size_t valueCast(TValue value) const
		{
			return (size_t)value;
		}
		
	public:
		struct iterator
		{
			const PointerMap* m_pOwner;
			size_t m_CurIdx;

			friend bool operator==(const iterator& a, const iterator& b) { return a.m_CurIdx == b.m_CurIdx; }
			friend bool operator!=(const iterator& a, const iterator& b) { return a.m_CurIdx != b.m_CurIdx; }

			TValue get()
			{
				return reinterpret_cast<TValue>(m_pOwner->GetValue(HashMap<PointerMapOperation>::iterator{ m_pOwner, m_CurIdx }));
			}
			
			TValue operator->()
			{
				return get();
			}
		};
		
		PointerMap(fnd::IAllocator* pAllocator) : HashMap<csl::ut::PointerMapOperation>(pAllocator)
		{
			
		}

		iterator end() const
		{
			return iterator{ this, m_CapacityMax + 1 };
		}
		
		void insert(TKey key, TValue value)
		{
			Insert(keyCast(key), valueCast(value));
		}

		void erase(TKey key)
		{
			Erase(keyCast(key));
		}
		
		iterator find(const TKey key) const
		{
			auto result = Find(keyCast(key));
			return iterator{ this, result.m_CurIdx };
		}
	};
}