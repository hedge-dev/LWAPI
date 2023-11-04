#pragma once

namespace csl::ut
{
	class PointerMapOperation
	{
		inline static constexpr size_t HASH_MAGIC = 0x9E3779B1;

	protected:
		size_t m_Dummy;
		
	public:
		size_t hash(size_t in_key)
		{
			return HASH_MAGIC * in_key;
		}

		bool compare(size_t in_key, size_t in_other)
		{
			return in_key == in_other;
		}
	};

	template<typename TKey, typename TValue>
	class PointerMap : public HashMap<PointerMapOperation>
	{
		size_t keyCast(TKey in_key) const
		{
			return (size_t)in_key;
		}

		size_t valueCast(TValue in_value) const
		{
			return (size_t)in_value;
		}
		
	public:
		class iterator
		{
			friend PointerMap;
			const PointerMap* m_pOwner;
			size_t m_CurIdx;

			iterator(const PointerMap* in_pOwner, size_t in_index) : m_pOwner(in_pOwner), m_CurIdx(in_index)
			{

			}

		public:
			friend bool operator==(const iterator& in_rA, const iterator& in_rB) { return in_rA.m_CurIdx == in_rB.m_CurIdx; }
			friend bool operator!=(const iterator& in_rA, const iterator& in_rB) { return in_rA.m_CurIdx != in_rB.m_CurIdx; }

			iterator& operator++() { m_CurIdx = m_pOwner->GetNext(m_CurIdx); return *this; }
			iterator operator++(int) { iterator tmp = *this; m_CurIdx = m_pOwner->GetNext(m_CurIdx); return tmp; }

			TKey key() const
			{
				return reinterpret_cast<TKey>(m_pOwner->GetKey(HashMap<PointerMapOperation>::iterator{ m_pOwner, m_CurIdx }));
			}

			TValue get() const
			{
				return reinterpret_cast<TValue>(m_pOwner->GetValue(HashMap<PointerMapOperation>::iterator{ m_pOwner, m_CurIdx }));
			}

			TValue& operator*() const
			{
				return *reinterpret_cast<TValue*>(m_pOwner->GetValuePtr(HashMap<PointerMapOperation>::iterator{ m_pOwner, m_CurIdx }));
			}

			TValue operator->() const
			{
				return get();
			}

			operator TValue() const
			{
				return get();
			}

			operator TValue& ()
			{
				return operator*();
			}
		};
		
		PointerMap(fnd::IAllocator* in_pAllocator) : HashMap<csl::ut::PointerMapOperation>(in_pAllocator)
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
		
		void insert(TKey in_key, TValue in_value)
		{
			Insert(keyCast(in_key), valueCast(in_value));
		}

		void erase(TKey in_key)
		{
			Erase(keyCast(in_key));
		}
		
		iterator find(const TKey in_key) const
		{
			auto result = Find(keyCast(in_key));
			return iterator(this, result.CurIdx);
		}
	};
}