#pragma once

namespace csl::fnd
{
	class StackHeapBase : public HeapBase
	{
	public:
		struct State
		{
			void* m_pTopBlock{};
			void* m_pBottomBlock{};
			size_t m_TopAllocationCount;
			size_t m_BottomAllocationCount;
		};

		enum FreeMode
		{
			FreeMode_Top = 1,
			FreeMode_Bottom = 2,
			FreeMode_All = FreeMode_Top | FreeMode_Bottom
		};

		void* m_pBufferBegin{}; // 56
		void* m_pBufferEnd{}; // 60
		void* m_pTopBlock{}; // 64
		void* m_pBottomBlock{}; // 68
		size_t m_AllocationCount{}; // 72
		size_t m_TopAllocationCount{}; // 76
		size_t m_BottomAllocationCount{}; // 80
		size_t m_MaxAllocationCount{}; // 84
		size_t m_FreeSpace{}; // 88
		size_t m_AllocationCallCount{}; // 92

		StackHeapBase()
		{
			
		}

		void Initialize(void* in_pBuffer, size_t in_size)
		{
			m_pBufferBegin = in_pBuffer;
			m_pBufferEnd = (void*)((size_t)in_pBuffer + in_size);
			m_pTopBlock = m_pBufferBegin;
			m_pBottomBlock = m_pBufferEnd;

			m_AllocationCount = 0;
			m_AllocationCallCount = 0;
			m_TopAllocationCount = 0;
			m_BottomAllocationCount = 0;
			m_MaxAllocationCount = 0;
			m_FreeSpace = (size_t)m_pBottomBlock - (size_t)m_pTopBlock;

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
			return { m_pTopBlock, m_pBottomBlock, m_TopAllocationCount, m_BottomAllocationCount };
		}
		void RestoreState(const State& in_state)
		{
			m_pTopBlock = in_state.m_pTopBlock;
			m_pBottomBlock = in_state.m_pBottomBlock;
			m_TopAllocationCount = in_state.m_TopAllocationCount;
			m_BottomAllocationCount = in_state.m_BottomAllocationCount;

			m_AllocationCount = m_TopAllocationCount + m_BottomAllocationCount;
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
			return in_pMemory >= m_pBufferBegin && in_pMemory < m_pBufferEnd;
		}

		size_t GetBlockSize(void* in_pMemory) const override
		{
			return 0;
		}

		void CollectHeapInformation(HeapInformation* out_pInfo) const override
		{
			out_pInfo->m_AllocationCount = m_AllocationCount;
			out_pInfo->m_FreeSpace = (size_t)m_pBottomBlock - (size_t)m_pTopBlock;
			out_pInfo->m_LargestBlockSize = (size_t)m_pBottomBlock - (size_t)m_pTopBlock;
			out_pInfo->m_AllocationSize = (size_t)m_pBufferEnd - (size_t)m_pBufferBegin;
		}

		void* GetBufferTop() const override
		{
			return m_pBufferBegin;
		}

		void* GetBufferEnd() const override
		{
			return m_pBufferEnd;
		}

		size_t GetCurrentAllocateCount() const override
		{
			return m_AllocationCount;
		}

		size_t GetCallAllocateTime() const override
		{
			return m_AllocationCallCount;
		}

		void GetMemorySnapshot(MemorySnapshot& out_snapshot) const override
		{
			
		}

		virtual void FreeAll(FreeMode in_mode)
		{
			if (in_mode & FreeMode_Top)
			{
				m_AllocationCount -= m_TopAllocationCount;
				m_pTopBlock = m_pBufferBegin;
				m_TopAllocationCount = 0;
			}

			if (in_mode & FreeMode_Bottom)
			{
				m_AllocationCount -= m_BottomAllocationCount;
				m_pBottomBlock = m_pBufferEnd;
				m_BottomAllocationCount = 0;
			}
		}

		virtual void* AllocCore(size_t in_size, size_t in_alignment)
		{
			++m_AllocationCallCount;

			size_t blockStart = csl::ut::RoundUp((size_t)m_pTopBlock, in_alignment);
			if (blockStart + in_size > (size_t)m_pBottomBlock)
				return nullptr;

			++m_AllocationCount;
			++m_TopAllocationCount;

			m_pTopBlock = (void*)(blockStart + in_size);
			size_t freeSpace = (size_t)m_pBottomBlock - (size_t)m_pTopBlock;

			if (m_MaxAllocationCount < m_AllocationCount)
				m_MaxAllocationCount = m_AllocationCount;

			if (m_FreeSpace > freeSpace)
				m_FreeSpace = freeSpace;

			return (void*)blockStart;
		}

		virtual void* AllocBottomCore(size_t in_size, size_t in_alignment)
		{
			++m_AllocationCallCount;
			size_t blockStart = csl::ut::RoundUp((size_t)m_pBottomBlock - in_size, in_alignment);
			if (blockStart >= (size_t)m_pTopBlock)
				return nullptr;

			++m_AllocationCount;
			++m_BottomAllocationCount;

			m_pBottomBlock = (void*)blockStart;
			size_t freeSpace = (size_t)m_pBottomBlock - (size_t)m_pTopBlock;

			if (m_MaxAllocationCount < m_AllocationCount)
				m_MaxAllocationCount = m_AllocationCount;

			if (m_FreeSpace > freeSpace)
				m_FreeSpace = freeSpace;

			return (void*)blockStart;
		}
	};
}