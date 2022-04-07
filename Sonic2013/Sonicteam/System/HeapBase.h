#pragma once

namespace csl::fnd
{
	struct HeapInformation
	{
		size_t m_AllocationCount{};
		size_t m_FreeSpace{};
		size_t m_BlockSize{};
		size_t m_AllocationSize{};
	};

	struct MemoryBlockFunction;
	struct MemorySnapshot;

	class HeapBase
	{
	public:
		class CallbackFunc
		{
		public:
			virtual ~CallbackFunc() = default;
			virtual void operator () (HeapBase* in_pHeap) = 0;
		};

		struct Callback
		{
			CallbackFunc* m_pInitCallback{};
			CallbackFunc* m_pFinalizeCallback{};
		};

		DEFINE_RTTI_PTR(ASLR(0x00FF001C));
		inline static FUNCTION_PTR(void, __thiscall, ms_fpAttachToLinkList, ASLR(0x009682D0), HeapBase*, void*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpDetachToLinkList, ASLR(0x009681C0), HeapBase*);
		inline static Callback& ms_Callback = *reinterpret_cast<Callback*>(ASLR(0x00FF0014));

		uint m_Unk1{};
		csl::ut::FixedString<16> m_Name{};
		HeapBase* m_pParent{};
		csl::ut::List m_Children;
		csl::ut::List::Node m_ListNode{};
		bool m_Unk2{};
		uint m_Unk3{};

		HeapBase()
		{
			ut::List_Init(&m_Children, offsetof(HeapBase, m_ListNode));
		}

		virtual DEFINE_RTTI_GETTER;
		virtual ~HeapBase() = default;
		virtual void* Alloc(size_t in_size, size_t in_alignment) = 0;
		virtual void* AllocBottom(size_t in_size, size_t in_alignment) = 0;
		virtual void Free(void* in_pMemory) = 0;
		virtual bool IsIn(void* in_pMemory) const = 0;
		virtual size_t GetBlockSize(void* in_pMemory) const = 0;
		virtual void CollectHeapInformation(csl::fnd::HeapInformation* out_pInfo) const = 0;
		virtual void* GetBufferTop() const = 0;
		virtual void* GetBufferEnd() const = 0;
		virtual size_t GetCurrentAllocateCount() const = 0;
		virtual size_t GetCallAllocateTime() const = 0;
		virtual bool CanHaveChild() const { return true; }
		virtual void ForEachAllocatedBlock(MemoryBlockFunction& in_func) { }
		virtual void PrintDebugInformation() { }
		virtual void GetMemorySnapshot(MemorySnapshot& out_snapshot) const = 0;
		virtual void CorrectSnapshotFromDebugInformation(MemorySnapshot& out_snapshot, size_t in_allocCount) const { }

		void SetName(const char* in_pName)
		{
			m_Name = in_pName;
		}

		const char* GetName() const
		{
			return m_Name.c_str();
		}

		void AttachToLinkList(void* in_pBuffer)
		{
			ms_fpAttachToLinkList(this, in_pBuffer);
		}

		void DetachToLinkList()
		{
			ms_fpDetachToLinkList(this);
		}

		void RaiseInitializeCallback()
		{
			if (ms_Callback.m_pInitCallback)
				(*ms_Callback.m_pInitCallback)(this);
		}

		void RaiseFinalizeCallback()
		{
			if (ms_Callback.m_pFinalizeCallback)
				(*ms_Callback.m_pFinalizeCallback)(this);
		}
	};
}
