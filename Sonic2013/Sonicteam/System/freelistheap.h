#pragma once

namespace csl::fnd
{
	class FreeListHeapBase : public HeapBase
	{
		struct BlockHead
		{
			FreeListHeapBase* m_pOwner{}; // 0
			size_t m_Size{}; // 4
			size_t m_Offset{}; // 8
			size_t m_Unk1{}; // 12
			BlockHead* m_pPrev{}; // 16
			BlockHead* m_pNext{}; // 20
			size_t m_Unk2{}; // 24
			size_t m_Padding{ 0x41474553 }; // 28
		};

	public:
		DEFINE_RTTI_PTR(ASLR(0x00FBABC8));
		void* m_pBufferBegin{}; // 56
		void* m_pBufferEnd{}; // 60
		BlockHead* m_pRootBlock{}; // 64
		BlockHead* m_pLastBlock{}; // 68
		size_t m_TotalFreeSize{}; // 72
		size_t m_AllocationCount{}; // 76
		size_t m_BufferFreeSize{}; // 80
		size_t m_TotalAllocationCalls{}; // 84
		uint m_Unk3{}; // 88

		inline static FUNCTION_PTR(void*, __thiscall, ms_fpAllocCore, ASLR(0x0096A450), FreeListHeapBase*, size_t, size_t);
		inline static FUNCTION_PTR(void*, __thiscall, ms_fpAllocBottomCore, ASLR(0x0096A4E0), FreeListHeapBase*, size_t, size_t);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpFree, ASLR(0x0096A140), FreeListHeapBase*, void*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpCollectHeapInformation, ASLR(0x0096A270), const FreeListHeapBase*, HeapInformation*);

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
			m_pBufferBegin = in_pBuffer;
			m_pBufferEnd = (char*)in_pBuffer + in_size;
			m_pRootBlock = (BlockHead*)in_pBuffer;
			m_pLastBlock = m_pRootBlock;
			InitBlock(m_pRootBlock);
			m_pRootBlock->m_Size = in_size;
			m_AllocationCount = 0;
			m_TotalAllocationCalls = 0;

			m_TotalFreeSize = in_size;
			m_BufferFreeSize = in_size;
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
			return in_pMemory >= m_pBufferBegin && in_pMemory < m_pBufferEnd;
		}

		size_t GetBlockSize(void* in_pMemory) const override
		{
			BlockHead* pBlock = (BlockHead*)(((char*)in_pMemory) - sizeof(BlockHead));
			return pBlock->m_Size + pBlock->m_Offset;
		}

		void CollectHeapInformation(HeapInformation* out_pInfo) const override
		{
			ms_fpCollectHeapInformation(this, out_pInfo);
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
			return CorrectSnapshotFromDebugInformation(out_snapshot, m_AllocationCount);
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
			in_pBlock->m_pOwner = this;

			return in_pBlock;
		}

		BlockHead* SplitBlock(BlockHead* in_pBlock, size_t in_size)
		{
			BlockHead* pNewBlock = (BlockHead*)(((char*)in_pBlock) + in_size);
			InitBlock(pNewBlock);
			pNewBlock->m_Size = in_pBlock->m_Size - in_size;
			in_pBlock->m_Size = in_size;

			return pNewBlock;
		}

		void InsertBlockNext(BlockHead* in_pBlock, BlockHead* in_pNext)
		{
			if (in_pNext->m_pNext)
			{
				in_pNext->m_pNext->m_pPrev = in_pBlock;
				in_pBlock->m_pNext = in_pNext->m_pNext;
			}
			else
			{
				m_pLastBlock = in_pBlock;
				in_pBlock->m_pNext = nullptr;
			}

			in_pNext->m_pNext = in_pBlock;
			in_pBlock->m_pPrev = in_pNext;
		}

		void InsertBlockPrev(BlockHead* in_pBlock, BlockHead* in_pPrev)
		{
			if (in_pPrev->m_pPrev)
			{
				in_pPrev->m_pPrev->m_pNext = in_pBlock;
				in_pBlock->m_pPrev = in_pPrev->m_pPrev;
			}
			else
			{
				m_pRootBlock = in_pBlock;
				in_pBlock->m_pPrev = nullptr;
			}

			in_pPrev->m_pPrev = in_pBlock;
			in_pBlock->m_pNext = in_pPrev;
		}

		void RemoveBlock(BlockHead* in_pBlock)
		{
			if (in_pBlock->m_pPrev)
			{
				in_pBlock->m_pPrev->m_pNext = in_pBlock->m_pNext;
				if (in_pBlock->m_pNext)
				{
					in_pBlock->m_pNext->m_pPrev = in_pBlock->m_pPrev;
					in_pBlock->m_pNext = nullptr;
					in_pBlock->m_pPrev = nullptr;
					return;
				}
			}
			else
			{
				m_pRootBlock = in_pBlock->m_pNext;
				if (in_pBlock->m_pNext)
				{
					in_pBlock->m_pNext->m_pPrev = in_pBlock->m_pPrev;
					in_pBlock->m_pNext = nullptr;
					in_pBlock->m_pPrev = nullptr;
					return;
				}
			}

			m_pLastBlock = in_pBlock->m_pPrev;
			in_pBlock->m_pPrev = nullptr;
			in_pBlock->m_pNext = nullptr;
		}

		void JJointBlock(BlockHead* in_pBlock, BlockHead* in_pOther)
		{
			if (in_pOther->m_pNext)
			{
				in_pOther->m_pNext->m_pPrev = in_pBlock;
				in_pBlock->m_pNext = in_pOther->m_pNext;
			}
			else
			{
				m_pLastBlock = in_pBlock;
				in_pBlock->m_pNext = nullptr;
			}

			in_pBlock->m_Size += in_pOther->m_Size;
		}
	};
}