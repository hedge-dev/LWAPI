#pragma once

namespace app::fnd
{
	class PooledAllocatorBase : public csl::fnd::IAllocator
	{
	public:
		struct PoolInfo
		{
			size_t m_Alignment;
			size_t m_BlockSize;
		};

		csl::fnd::IAllocator* m_pBufferAllocator{};
		void* m_pBuffer{};
		csl::fnd::LinkHeapBase* m_pHeapList{};
		csl::fnd::FreeListHeapTemplate<csl::fnd::DummyLock> m_Heap{};
		csl::fnd::PoolHeapTemplate<csl::fnd::DummyLock>* m_pPools{};
		size_t m_PoolCount{};
		void* m_pUnk1{}; // Never used, probably was used for tracking allocations at some point

		PooledAllocatorBase(csl::fnd::LinkHeapBase* in_pHeapList) : m_pHeapList(in_pHeapList)
		{
			
		}

		void Initialize(csl::fnd::IAllocator* in_pAllocator, size_t in_bufferSize, const PoolInfo* in_pPools, size_t in_poolCount)
		{
			m_pBufferAllocator = in_pAllocator;
			m_pBuffer = m_pBufferAllocator->Alloc(in_bufferSize, 16);
			m_PoolCount = in_poolCount;
			void* pBuffer = m_pBuffer;

			if (in_poolCount)
			{
				m_pPools = (csl::fnd::PoolHeapTemplate<csl::fnd::DummyLock>*)m_pBuffer;

				for (size_t i = 0; i < in_poolCount; i++)
					new(&m_pPools[i]) csl::fnd::PoolHeapTemplate<csl::fnd::DummyLock>();

				pBuffer = &m_pPools[in_poolCount];
			}

			for (size_t i = 0; i < in_poolCount; i++)
			{
				auto& pool = in_pPools[i];
				pBuffer = align_ptr((char*)pBuffer, pool.m_Alignment);
				m_pPools[i].Initialize(pBuffer, pool.m_BlockSize, pool.m_Alignment, pool.m_Alignment);

				pBuffer = (char*)pBuffer + pool.m_BlockSize * pool.m_Alignment;
				m_pHeapList->SetPoolHeap(pool.m_Alignment, &m_pPools[i]);
			}

			pBuffer = align_ptr((char*)pBuffer, 16);
			m_Heap.Initialize(pBuffer, in_bufferSize - ((size_t)pBuffer - (size_t)m_pBuffer));
			m_pHeapList->SetFreelistHeap(&m_Heap);
		}

		void SetName(const char* in_pName)
		{
			m_pHeapList->SetName(in_pName);
			m_Heap.SetName(in_pName);

			for (size_t i = 0; i < m_PoolCount; i++)
				m_pPools[i].SetName(in_pName);
		}

		void* Alloc(size_t in_size, int in_alignment) override
		{
			if (in_alignment >= 0)
				return m_pHeapList->Alloc(in_size, in_alignment);

			return m_pHeapList->AllocBottom(in_size, -in_alignment);
		}

		void Free(void* in_pMemory) override
		{
			m_pHeapList->Free(in_pMemory);
		}

		~PooledAllocatorBase() override
		{
			for (size_t i = 0; i < m_PoolCount; i++)
				m_pPools->~PoolHeapTemplate();

			if (m_pBufferAllocator)
				m_pBufferAllocator->Free(m_pBuffer);

			m_pBuffer = nullptr;
			m_pPools = nullptr;
		}
	};
}