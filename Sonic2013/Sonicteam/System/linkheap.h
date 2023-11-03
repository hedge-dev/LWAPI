#pragma once

namespace csl::fnd
{
	class LinkHeapBase : public HeapBase
	{
	public:
		DEFINE_RTTI_PTR(ASLR(0x00FBABC4));

		typedef size_t HeapIndex;
		csl::ut::FixedArray<HeapBase*, 12> m_Heaps{};

		LinkHeapBase()
		{
			for (auto& pHeap : m_Heaps)
				pHeap = nullptr;

			AttachToLinkList(nullptr);
			RaiseInitializeCallback();
		}

		~LinkHeapBase()
		{
			RaiseFinalizeCallback();
			DetachToLinkList();
		}

		const csl::ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() override
		{
			return GetRuntimeTypeInfoStatic();
		}

		void* Alloc(size_t in_size, size_t in_alignment) override
		{
			return AllocCore(in_size, in_alignment, false);
		}

		void* AllocBottom(size_t in_size, size_t in_alignment) override
		{
			return AllocCore(in_size, in_alignment, true);
		}

		void Free(void* in_pMemory) override
		{
			for (const auto& pHeap : m_Heaps)
			{
				if (pHeap && pHeap->IsIn(in_pMemory))
				{
					pHeap->Free(in_pMemory);
					return;
				}
			}
		}

		bool IsIn(void* in_pMemory) const override
		{
			for (const auto& pHeap : m_Heaps)
			{
				if (pHeap && pHeap->IsIn(in_pMemory))
					return true;
			}

			return false;
		}

		size_t GetBlockSize(void* in_pMemory) const override
		{
			for (const auto& pHeap : m_Heaps)
			{
				if (pHeap && pHeap->IsIn(in_pMemory))
					return pHeap->GetBlockSize(in_pMemory);
			}

			return 0;
		}

		void CollectHeapInformation(csl::fnd::HeapInformation* out_pInfo) const override
		{
			out_pInfo->m_LargestBlockSize = 0;
			for (const auto& pHeap : m_Heaps)
			{
				if (pHeap)
				{
					HeapInformation info{};
					pHeap->CollectHeapInformation(&info);

					out_pInfo->m_AllocationCount += info.m_AllocationCount;
					out_pInfo->m_FreeSpace += info.m_FreeSpace;
					out_pInfo->m_AllocationSize += info.m_AllocationSize;

					if (info.m_LargestBlockSize > out_pInfo->m_LargestBlockSize)
						out_pInfo->m_LargestBlockSize = info.m_LargestBlockSize;
				}
			}
		}

		void* GetBufferTop() const override
		{
			return nullptr;
		}

		void* GetBufferEnd() const override
		{
			return nullptr;
		}

		size_t GetCurrentAllocateCount() const override
		{
			size_t count{};

			for (const auto& pHeap : m_Heaps)
			{
				if (pHeap)
					count += pHeap->GetCurrentAllocateCount();
			}

			return count;
		}

		size_t GetCallAllocateTime() const override
		{
			size_t count{};

			for (const auto& pHeap : m_Heaps)
			{
				if (pHeap)
					count += pHeap->GetCallAllocateTime();
			}

			return count;
		}

		bool CanHaveChild() const override
		{
			return false;
		}

		void ForEachAllocatedBlock(MemoryBlockFunction& in_func) override
		{
			for (const auto& pHeap : m_Heaps)
			{
				if (pHeap)
					pHeap->ForEachAllocatedBlock(in_func);
			}
		}

		void PrintDebugInformation() override
		{
			for (const auto& pHeap : m_Heaps)
			{
				if (pHeap)
					pHeap->PrintDebugInformation();
			}
		}

		void GetMemorySnapshot(MemorySnapshot& out_snapshot) const override
		{
			out_snapshot.Reset();
			size_t totalAllocations{};

			for (const auto& pHeap : m_Heaps)
			{
				if (pHeap && pHeap->m_pAllocations)
					totalAllocations += pHeap->GetCallAllocateTime();
			}

			if (!totalAllocations)
				return;

			out_snapshot.Allocate(totalAllocations);

			size_t idx{};
			for (const auto& pHeap : m_Heaps)
			{
				if (!pHeap || !pHeap->m_pAllocations)
					continue;

				HeapBase::Allocation* pAllocation = pHeap->m_pAllocations;

				while (pAllocation)
				{
					out_snapshot.m_pProviders[idx].m_pHeap = pAllocation->m_pSource;

					out_snapshot.m_pAllocations[idx].m_Name = pAllocation->m_Name;
					out_snapshot.m_pAllocations[idx].m_pBlock = pAllocation->m_pBlock;

					idx++;
					pAllocation = pAllocation->m_pNextAllocation;
				}
			}
		}

		virtual void* AllocCore(size_t in_size, size_t in_alignment, bool in_bottom)
		{
			HeapIndex idx = GetHeapIndex(in_size);
			HeapBase* pHeap = m_Heaps[idx];
			void* pMemory = nullptr;

			if (idx != 11 && pHeap)
			{
				pMemory = in_bottom ? pHeap->AllocBottom(in_size, in_alignment) : pHeap->Alloc(in_size, in_alignment);
				if (pMemory)
					return pMemory;
			}

			pHeap = m_Heaps[11];
			pMemory = in_bottom ? pHeap->AllocBottom(in_size, in_alignment) : pHeap->Alloc(in_size, in_alignment);

			return pMemory;
		}

		inline void SetHeap(HeapIndex in_idx, HeapBase* in_pHeap)
		{
			m_Heaps[in_idx] = in_pHeap;
		}

		inline void SetPoolHeap(size_t in_size, PoolHeapBase* in_pHeap)
		{
			SetHeap(GetHeapIndex(in_size), in_pHeap);
		}

		inline void SetFreelistHeap(FreeListHeapBase* in_pHeap)
		{
			SetHeap(11, in_pHeap);
		}

		inline HeapIndex GetHeapIndex(size_t in_size) const
		{
			size_t blockSize = 2 * in_size - 1;
			HeapIndex idx{};

			if (blockSize >= 0x100)
			{
				idx = 8;
				blockSize >>= 8;
			}
			if (blockSize >= 0x10)
			{
				idx |= 4;
				blockSize >>= 4;
			}
			if (blockSize >= 4)
			{
				idx |= 2;
				blockSize >>= 2;
			}
			if (blockSize >= 2)
				idx |= 1;

			if (idx > 10)
				idx = 11;

			return idx;
		}
	};
}
