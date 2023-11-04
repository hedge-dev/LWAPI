#pragma once

namespace csl::fnd
{
	class PoolHeapBase : public HeapBase
	{
	public:
		DEFINE_RTTI_PTR(ASLR(0x00FBABC0));

		void* m_pBufferBegin{}; // 56
		void* m_pBufferEnd{}; // 60
		void* m_pCurBlock{}; // 64
		size_t m_BlockSize{}; // 68
		size_t m_Alignment{}; // 72
		size_t m_AllocationCount{}; // 76
		size_t m_MaxAllocationCount{}; // 80
		size_t m_TotalAllocationCalls{}; // 84
		size_t m_BlockCount{}; // 88
		size_t m_DbgBufferOffset{}; // 92

		PoolHeapBase()
		{

		}

		~PoolHeapBase() override
		{
			RaiseFinalizeCallback();
			DetachToLinkList();
		}

		void Initialize(void* in_pBuffer, size_t in_blockCount, size_t in_blockSize, size_t in_alignment)
		{
			m_pBufferBegin = in_pBuffer;
			m_pBufferEnd = ((char*)in_pBuffer) + CalcBufferSize(in_blockSize, in_blockCount);
			m_pCurBlock = in_pBuffer;
			m_BlockCount = in_blockCount;
			m_Alignment = in_alignment;
			m_BlockSize = in_blockSize;
			m_AllocationCount = 0;
			m_TotalAllocationCalls = 0;

			void** pCurBlock = (void**)m_pBufferBegin;
			if (in_blockCount != -1)
			{
				void* pNextBlock = nullptr;
				for (size_t i = in_blockCount - 1; i; --i)
				{
					pNextBlock = ((char*)pCurBlock) + m_BlockSize;
					*pCurBlock = pNextBlock;
					pCurBlock = (void**)pNextBlock;
				}
			}

			*pCurBlock = nullptr;
			AttachToLinkList(m_pBufferBegin);
			RaiseInitializeCallback();
		}

		const csl::ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() override
		{
			return GetRuntimeTypeInfoStatic();
		}

		void* Alloc(size_t in_size, size_t in_alignment) override
		{
			return AllocCore(in_size);
		}

		void* AllocBottom(size_t in_size, size_t in_alignment) override
		{
			return AllocCore(in_size);
		}

		void Free(void* in_pMemory) override
		{
			--m_AllocationCount;

			*((void**)in_pMemory) = m_pCurBlock;
			m_pCurBlock = in_pMemory;
		}

		bool IsIn(void* in_pMemory) const override
		{
			return in_pMemory >= m_pBufferBegin && in_pMemory < m_pBufferEnd;
		}

		size_t GetBlockSize(void* in_pMemory) const override
		{
			return m_BlockSize;
		}

		void CollectHeapInformation(csl::fnd::HeapInformation* out_pInfo) const override
		{
			out_pInfo->m_AllocationCount = m_AllocationCount;
			out_pInfo->m_FreeSpace = (m_BlockCount * m_BlockSize) - (m_AllocationCount * m_BlockSize);
			out_pInfo->m_LargestBlockSize = m_BlockSize;
			out_pInfo->m_AllocationSize = (m_BlockCount * m_BlockSize);
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
			return m_TotalAllocationCalls;
		}

		void GetMemorySnapshot(MemorySnapshot& out_snapshot) const override
		{
			CorrectSnapshotFromDebugInformation(out_snapshot, m_AllocationCount);
		}

	protected:
		virtual void* AllocCore(size_t in_size)
		{
			++m_TotalAllocationCalls;
			if (!m_pCurBlock || in_size > m_BlockSize)
				return nullptr;

			auto* pBlock = m_pCurBlock;
			++m_AllocationCount;
			m_pCurBlock = *((void**)pBlock);

			if (m_MaxAllocationCount < m_AllocationCount)
				m_MaxAllocationCount = m_AllocationCount;

			return pBlock;
		}

	public:
		inline static size_t CalcBufferSize(size_t in_elemSize, size_t in_count)
		{
			if (in_count < 4)
				in_count = 4;

			return in_elemSize * in_count;
		}
	};
	
	template<typename TLock = Mutex>
	class PoolHeapTemplate : public PoolHeapBase
	{
	public:
		TLock Lock{};

		PoolHeapTemplate()
		{
			
		}

		void* Alloc(size_t in_size, size_t in_alignment) override
		{
			Lock.Lock();
			void* pMemory = PoolHeapBase::Alloc(in_size, in_alignment);
			Lock.Unlock();

			return pMemory;
		}

		void* AllocBottom(size_t in_size, size_t in_alignment) override
		{
			Lock.Lock();
			void* pMemory = PoolHeapBase::AllocBottom(in_size, in_alignment);
			Lock.Unlock();

			return pMemory;
		}

		void Free(void* in_pMemory) override
		{
			Lock.Lock();
			PoolHeapBase::Free(in_pMemory);
			Lock.Unlock();
		}
	};
}