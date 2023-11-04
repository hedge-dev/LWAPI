#pragma once

namespace app::fnd
{
	class PooledAllocatorBase : public csl::fnd::IAllocator
	{
	public:
		struct PoolInfo
		{
			size_t Alignment;
			size_t BlockSize;
		};

		csl::fnd::IAllocator* pBufferAllocator{};
		void* pBuffer{};
		csl::fnd::LinkHeapBase* pHeapList{};
		csl::fnd::FreeListHeapTemplate<csl::fnd::DummyLock> Heap{};
		csl::fnd::PoolHeapTemplate<csl::fnd::DummyLock>* pPools{};
		size_t PoolCount{};
		void* pUnk1{}; // Never used, probably was used for tracking allocations at some point

		PooledAllocatorBase(csl::fnd::LinkHeapBase* in_pHeapList) : pHeapList(in_pHeapList)
		{
			
		}

		void Initialize(csl::fnd::IAllocator* in_pAllocator, size_t in_bufferSize, const PoolInfo* in_pPools, size_t in_poolCount)
		{
			pBufferAllocator = in_pAllocator;
			pBuffer = pBufferAllocator->Alloc(in_bufferSize, 16);
			PoolCount = in_poolCount;
			void* pNewBuffer = pBuffer;

			if (in_poolCount)
			{
				pPools = (csl::fnd::PoolHeapTemplate<csl::fnd::DummyLock>*)pBuffer;

				for (size_t i = 0; i < in_poolCount; i++)
					new(&pPools[i]) csl::fnd::PoolHeapTemplate<csl::fnd::DummyLock>();

				pNewBuffer = &pPools[in_poolCount];
			}

			for (size_t i = 0; i < in_poolCount; i++)
			{
				auto& pool = in_pPools[i];
				pNewBuffer = align_ptr((char*)pNewBuffer, pool.Alignment);
				pPools[i].Initialize(pNewBuffer, pool.BlockSize, pool.Alignment, pool.Alignment);

				pNewBuffer = (char*)pNewBuffer + pool.BlockSize * pool.Alignment;
				pHeapList->SetPoolHeap(pool.Alignment, &pPools[i]);
			}

			pNewBuffer = align_ptr((char*)pNewBuffer, 16);
			Heap.Initialize(pNewBuffer, in_bufferSize - ((size_t)pNewBuffer - (size_t)pBuffer));
			pHeapList->SetFreelistHeap(&Heap);
		}

		void SetName(const char* in_pName)
		{
			pHeapList->SetName(in_pName);
			Heap.SetName(in_pName);

			for (size_t i = 0; i < PoolCount; i++)
				pPools[i].SetName(in_pName);
		}

		void* Alloc(size_t in_size, int in_alignment) override
		{
			if (in_alignment >= 0)
				return pHeapList->Alloc(in_size, in_alignment);

			return pHeapList->AllocBottom(in_size, -in_alignment);
		}

		void Free(void* in_pMemory) override
		{
			pHeapList->Free(in_pMemory);
		}

		~PooledAllocatorBase() override
		{
			for (size_t i = 0; i < PoolCount; i++)
				pPools->~PoolHeapTemplate();

			if (pBufferAllocator)
				pBufferAllocator->Free(pBuffer);

			pBuffer = nullptr;
			pPools = nullptr;
		}
	};

	class PooledAllocator : public PooledAllocatorBase
	{
	public:
		PooledAllocator(csl::fnd::LinkHeapBase* in_pHeapList) : PooledAllocatorBase(in_pHeapList)
		{

		}
	};
	
	class ThreadSafePooledAllocator : public PooledAllocatorBase
	{
	public:
		ThreadSafePooledAllocator(csl::fnd::LinkHeapTemplate<csl::fnd::Mutex>* in_pHeapList) : PooledAllocatorBase(in_pHeapList)
		{

		}
	};
}