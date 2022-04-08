#pragma once

namespace csl::fnd
{
	class HeapBase;
	class MemorySnapshot
	{
	public:
		struct Provider
		{
			HeapBase* m_pHeap;
		};

		struct Allocation
		{
			const void* m_pBlock{};
			csl::ut::FixedString<64> m_Name{};
		};

		csl::fnd::IAllocator* m_pAllocator{};
		Provider* m_pProviders{};
		Allocation* m_pAllocations{};
		size_t m_Count{};

		MemorySnapshot(csl::fnd::IAllocator* in_pAllocator)
		{
			m_pAllocator = in_pAllocator;
		}

		virtual ~MemorySnapshot()
		{
			Reset();
		}

		void Allocate(size_t in_count)
		{
			if (m_pProviders)
			{
				m_pAllocator->Free(m_pProviders);
				m_pAllocator->Free(m_pAllocations);
			}

			m_Count = in_count;
			m_pProviders = static_cast<Provider*>(m_pAllocator->Alloc(sizeof(Provider) * in_count, alignof(Provider)));
			m_pAllocations = static_cast<Allocation*>(m_pAllocator->Alloc(sizeof(Allocation) * in_count, alignof(Allocation)));
		}

		void Reset()
		{
			if (m_pProviders)
			{
				m_pAllocator->Free(m_pProviders);
				m_pAllocator->Free(m_pAllocations);
			}

			m_pProviders = nullptr;
			m_pAllocations = nullptr;
			m_Count = 0;
		}
	};
}