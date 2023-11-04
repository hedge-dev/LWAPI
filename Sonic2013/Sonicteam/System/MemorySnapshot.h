#pragma once

namespace csl::fnd
{
	class HeapBase;
	class MemorySnapshot
	{
	public:
		struct Provider
		{
			HeapBase* pHeap;
		};

		struct Allocation
		{
			const void* pBlock{};
			csl::ut::FixedString<64> Name{};
		};

		csl::fnd::IAllocator* pAllocator{};
		Provider* pProviders{};
		Allocation* pAllocations{};
		size_t Count{};

		MemorySnapshot(csl::fnd::IAllocator* in_pAllocator)
		{
			pAllocator = in_pAllocator;
		}

		virtual ~MemorySnapshot()
		{
			Reset();
		}

		void Allocate(size_t in_count)
		{
			if (pProviders)
			{
				pAllocator->Free(pProviders);
				pAllocator->Free(pAllocations);
			}

			Count = in_count;
			pProviders = static_cast<Provider*>(pAllocator->Alloc(sizeof(Provider) * in_count, alignof(Provider)));
			pAllocations = static_cast<Allocation*>(pAllocator->Alloc(sizeof(Allocation) * in_count, alignof(Allocation)));
		}

		void Reset()
		{
			if (pProviders)
			{
				pAllocator->Free(pProviders);
				pAllocator->Free(pAllocations);
			}

			pProviders = nullptr;
			pAllocations = nullptr;
			Count = 0;
		}
	};
}