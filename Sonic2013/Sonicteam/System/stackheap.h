#pragma once

namespace csl::fnd
{
	class StackHeapBase : public HeapBase
	{
	public:
		struct State
		{
			void* pTopBlock{};
			void* pBottomBlock{};
			size_t TopAllocationCount;
			size_t BottomAllocationCount;
		};

		enum FreeMode
		{
			eFreeMode_Top = 1,
			eFreeMode_Bottom = 2,
			eFreeMode_All = eFreeMode_Top | eFreeMode_Bottom
		};

		void* pBufferBegin{}; // 56
		void* pBufferEnd{}; // 60
		void* pTopBlock{}; // 64
		void* pBottomBlock{}; // 68
		size_t AllocationCount{}; // 72
		size_t TopAllocationCount{}; // 76
		size_t BottomAllocationCount{}; // 80
		size_t MaxAllocationCount{}; // 84
		size_t FreeSpace{}; // 88
		size_t AllocationCallCount{}; // 92

		StackHeapBase()
		{
			
		}

		void Initialize(void* in_pBuffer, size_t in_size)
		{
			pBufferBegin = in_pBuffer;
			pBufferEnd = (void*)((size_t)in_pBuffer + in_size);
			pTopBlock = pBufferBegin;
			pBottomBlock = pBufferEnd;

			AllocationCount = 0;
			AllocationCallCount = 0;
			TopAllocationCount = 0;
			BottomAllocationCount = 0;
			MaxAllocationCount = 0;
			FreeSpace = (size_t)pBottomBlock - (size_t)pTopBlock;

			AttachToLinkList(in_pBuffer);
			RaiseInitializeCallback();
		}

		~StackHeapBase()
		{
			DetachToLinkList();
			RaiseFinalizeCallback();
		}

		State SaveState()
		{
			return { pTopBlock, pBottomBlock, TopAllocationCount, BottomAllocationCount };
		}
		void RestoreState(const State& in_state)
		{
			pTopBlock = in_state.pTopBlock;
			pBottomBlock = in_state.pBottomBlock;
			TopAllocationCount = in_state.TopAllocationCount;
			BottomAllocationCount = in_state.BottomAllocationCount;

			AllocationCount = TopAllocationCount + BottomAllocationCount;
		}

		void* Alloc(size_t in_size, size_t in_alignment) override
		{
			return AllocCore(in_size, in_alignment);
		}

		void* AllocBottom(size_t in_size, size_t in_alignment) override
		{
			return AllocBottomCore(in_size, in_alignment);
		}

		void Free(void* in_pMemory) override { }

		bool IsIn(void* in_pMemory) const override
		{
			return in_pMemory >= pBufferBegin && in_pMemory < pBufferEnd;
		}

		size_t GetBlockSize(void* in_pMemory) const override
		{
			return 0;
		}

		void CollectHeapInformation(HeapInformation* out_pInfo) const override
		{
			out_pInfo->m_AllocationCount = AllocationCount;
			out_pInfo->m_FreeSpace = (size_t)pBottomBlock - (size_t)pTopBlock;
			out_pInfo->m_LargestBlockSize = (size_t)pBottomBlock - (size_t)pTopBlock;
			out_pInfo->m_AllocationSize = (size_t)pBufferEnd - (size_t)pBufferBegin;
		}

		void* GetBufferTop() const override
		{
			return pBufferBegin;
		}

		void* GetBufferEnd() const override
		{
			return pBufferEnd;
		}

		size_t GetCurrentAllocateCount() const override
		{
			return AllocationCount;
		}

		size_t GetCallAllocateTime() const override
		{
			return AllocationCallCount;
		}

		void GetMemorySnapshot(MemorySnapshot& out_rSnapshot) const override
		{
			
		}

		virtual void FreeAll(FreeMode in_mode)
		{
			if (in_mode & eFreeMode_Top)
			{
				AllocationCount -= TopAllocationCount;
				pTopBlock = pBufferBegin;
				TopAllocationCount = 0;
			}

			if (in_mode & eFreeMode_Bottom)
			{
				AllocationCount -= BottomAllocationCount;
				pBottomBlock = pBufferEnd;
				BottomAllocationCount = 0;
			}
		}

		virtual void* AllocCore(size_t in_size, size_t in_alignment)
		{
			++AllocationCallCount;

			size_t blockStart = csl::ut::RoundUp((size_t)pTopBlock, in_alignment);
			if (blockStart + in_size > (size_t)pBottomBlock)
				return nullptr;

			++AllocationCount;
			++TopAllocationCount;

			pTopBlock = (void*)(blockStart + in_size);
			size_t freeSpace = (size_t)pBottomBlock - (size_t)pTopBlock;

			if (MaxAllocationCount < AllocationCount)
				MaxAllocationCount = AllocationCount;

			if (FreeSpace > freeSpace)
				FreeSpace = freeSpace;

			return (void*)blockStart;
		}

		virtual void* AllocBottomCore(size_t in_size, size_t in_alignment)
		{
			++AllocationCallCount;
			size_t blockStart = csl::ut::RoundUp((size_t)pBottomBlock - in_size, in_alignment);
			if (blockStart >= (size_t)pTopBlock)
				return nullptr;

			++AllocationCount;
			++BottomAllocationCount;

			pBottomBlock = (void*)blockStart;
			size_t freeSpace = (size_t)pBottomBlock - (size_t)pTopBlock;

			if (MaxAllocationCount < AllocationCount)
				MaxAllocationCount = AllocationCount;

			if (FreeSpace > freeSpace)
				FreeSpace = freeSpace;

			return (void*)blockStart;
		}
	};

	template<typename TLock>
	class StackHeapTemplate : public StackHeapBase
	{
		TLock Lock{};

	public:
		void* Alloc(size_t in_size, size_t in_alignment) override
		{
			Lock.Lock();
			void* pMemory = StackHeapBase::Alloc(in_size, in_alignment);
			Lock.Unlock();

			return pMemory;
		}

		void* AllocBottom(size_t in_size, size_t in_alignment) override
		{
			Lock.Lock();
			void* pMemory = StackHeapBase::AllocBottom(in_size, in_alignment);
			Lock.Unlock();

			return pMemory;
		}

		void FreeAll(FreeMode in_mode) override
		{
			Lock.Lock();
			StackHeapBase::FreeAll(in_mode);
			Lock.Unlock();
		}
	};
}