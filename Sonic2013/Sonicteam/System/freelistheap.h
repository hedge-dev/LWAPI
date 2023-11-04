#pragma once

namespace csl::fnd
{
	class FreeListHeapBase : public HeapBase
	{
	private:
		inline static FUNCTION_PTR(void*, __thiscall, ms_fpAllocCore, ASLR(0x0096A450), FreeListHeapBase*, size_t, size_t);
		inline static FUNCTION_PTR(void*, __thiscall, ms_fpAllocBottomCore, ASLR(0x0096A4E0), FreeListHeapBase*, size_t, size_t);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpFree, ASLR(0x0096A140), FreeListHeapBase*, void*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpCollectHeapInformation, ASLR(0x0096A270), const FreeListHeapBase*, HeapInformation*);

	public:
		struct BlockHead
		{
			FreeListHeapBase* pOwner{}; // 0
			size_t Size{}; // 4
			size_t Offset{}; // 8
			size_t Unk1{}; // 12
			BlockHead* pPrev{}; // 16
			BlockHead* pNext{}; // 20
			size_t Unk2{}; // 24
			size_t Padding{ 0x41474553 }; // 28
		};

		DEFINE_RTTI_PTR(ASLR(0x00FBABC8));
		void* pBufferBegin{}; // 56
		void* pBufferEnd{}; // 60
		BlockHead* pRootBlock{}; // 64
		BlockHead* pLastBlock{}; // 68
		size_t TotalFreeSize{}; // 72
		size_t AllocationCount{}; // 76
		size_t BufferFreeSize{}; // 80
		size_t TotalAllocationCalls{}; // 84
		uint Unk3{}; // 88

		FreeListHeapBase()
		{

		}

		~FreeListHeapBase()
		{
			RaiseFinalizeCallback();
			DetachToLinkList();
		}

	public:
		void Initialize(void* in_pBuffer, size_t in_size)
		{
			pBufferBegin = in_pBuffer;
			pBufferEnd = (char*)in_pBuffer + in_size;
			pRootBlock = (BlockHead*)in_pBuffer;
			pLastBlock = pRootBlock;
			InitBlock(pRootBlock);
			pRootBlock->Size = in_size;
			AllocationCount = 0;
			TotalAllocationCalls = 0;

			TotalFreeSize = in_size;
			BufferFreeSize = in_size;
			AttachToLinkList(in_pBuffer);
			RaiseInitializeCallback();
		}

		const csl::ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() override
		{
			return GetRuntimeTypeInfoStatic();
		}

		void* Alloc(size_t in_size, size_t in_alignment) override
		{
			return AllocCore(in_size, in_alignment);
		}

		void* AllocBottom(size_t in_size, size_t in_alignment) override
		{
			return AllocBottomCore(in_size, in_alignment);
		}

		void Free(void* in_pMemory) override
		{
			ms_fpFree(this, in_pMemory);
		}

		bool IsIn(void* in_pMemory) const override
		{
			return in_pMemory >= pBufferBegin && in_pMemory < pBufferEnd;
		}

		size_t GetBlockSize(void* in_pMemory) const override
		{
			BlockHead* pBlock = (BlockHead*)(((char*)in_pMemory) - sizeof(BlockHead));
			return pBlock->Size + pBlock->Offset;
		}

		void CollectHeapInformation(HeapInformation* out_pInfo) const override
		{
			ms_fpCollectHeapInformation(this, out_pInfo);
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
			return TotalAllocationCalls;
		}

		void GetMemorySnapshot(MemorySnapshot& out_snapshot) const override
		{
			return CorrectSnapshotFromDebugInformation(out_snapshot, AllocationCount);
		}

	protected:
		void* AllocCore(size_t in_size, size_t in_alignment)
		{
			// I give up trying to implement this
			return ms_fpAllocCore(this, in_size, in_alignment);
		}

		void* AllocBottomCore(size_t in_size, size_t in_alignment)
		{
			return ms_fpAllocBottomCore(this, in_size, in_alignment);
		}

		BlockHead* InitBlock(BlockHead* in_pBlock)
		{
			*in_pBlock = BlockHead();
			in_pBlock->pOwner = this;

			return in_pBlock;
		}

		BlockHead* SplitBlock(BlockHead* in_pBlock, size_t in_size)
		{
			BlockHead* pNewBlock = (BlockHead*)(((char*)in_pBlock) + in_size);
			InitBlock(pNewBlock);
			pNewBlock->Size = in_pBlock->Size - in_size;
			in_pBlock->Size = in_size;

			return pNewBlock;
		}

		void InsertBlockNext(BlockHead* in_pBlock, BlockHead* in_pNext)
		{
			if (in_pNext->pNext)
			{
				in_pNext->pNext->pPrev = in_pBlock;
				in_pBlock->pNext = in_pNext->pNext;
			}
			else
			{
				pLastBlock = in_pBlock;
				in_pBlock->pNext = nullptr;
			}

			in_pNext->pNext = in_pBlock;
			in_pBlock->pPrev = in_pNext;
		}

		void InsertBlockPrev(BlockHead* in_pBlock, BlockHead* in_pPrev)
		{
			if (in_pPrev->pPrev)
			{
				in_pPrev->pPrev->pNext = in_pBlock;
				in_pBlock->pPrev = in_pPrev->pPrev;
			}
			else
			{
				pRootBlock = in_pBlock;
				in_pBlock->pPrev = nullptr;
			}

			in_pPrev->pPrev = in_pBlock;
			in_pBlock->pNext = in_pPrev;
		}

		void RemoveBlock(BlockHead* in_pBlock)
		{
			if (in_pBlock->pPrev)
			{
				in_pBlock->pPrev->pNext = in_pBlock->pNext;
				if (in_pBlock->pNext)
				{
					in_pBlock->pNext->pPrev = in_pBlock->pPrev;
					in_pBlock->pNext = nullptr;
					in_pBlock->pPrev = nullptr;
					return;
				}
			}
			else
			{
				pRootBlock = in_pBlock->pNext;
				if (in_pBlock->pNext)
				{
					in_pBlock->pNext->pPrev = in_pBlock->pPrev;
					in_pBlock->pNext = nullptr;
					in_pBlock->pPrev = nullptr;
					return;
				}
			}

			pLastBlock = in_pBlock->pPrev;
			in_pBlock->pPrev = nullptr;
			in_pBlock->pNext = nullptr;
		}

		void JJointBlock(BlockHead* in_pBlock, BlockHead* in_pOther)
		{
			if (in_pOther->pNext)
			{
				in_pOther->pNext->pPrev = in_pBlock;
				in_pBlock->pNext = in_pOther->pNext;
			}
			else
			{
				pLastBlock = in_pBlock;
				in_pBlock->pNext = nullptr;
			}

			in_pBlock->Size += in_pOther->Size;
		}
	};
	
	template<typename TLock>
	class FreeListHeapTemplate : public FreeListHeapBase
	{
	public:
		TLock Lock{};

		void* Alloc(size_t in_size, size_t in_alignment) override
		{
			Lock.Lock();
			void* pMemory = FreeListHeapBase::Alloc(in_size, in_alignment);
			Lock.Unlock();

			return pMemory;
		}

		void* AllocBottom(size_t in_size, size_t in_alignment) override
		{
			Lock.Lock();
			void* pMemory = FreeListHeapBase::AllocBottom(in_size, in_alignment);
			Lock.Unlock();

			return pMemory;
		}

		void Free(void* in_pMemory) override
		{
			Lock.Lock();
			FreeListHeapBase::Free(in_pMemory);
			Lock.Unlock();
		}
	};
}