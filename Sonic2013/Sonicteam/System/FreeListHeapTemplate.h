#pragma once

namespace csl::fnd
{
	template<typename TLock>
	class FreeListHeapTemplate : public FreeListHeapBase
	{
	public:
		TLock m_Lock{};

		void* Alloc(size_t in_size, size_t in_alignment) override
		{
			m_Lock.Lock();
			void* pMemory = FreeListHeapBase::Alloc(in_size, in_alignment);
			m_Lock.Unlock();

			return pMemory;
		}

		void* AllocBottom(size_t in_size, size_t in_alignment) override
		{
			m_Lock.Lock();
			void* pMemory = FreeListHeapBase::AllocBottom(in_size, in_alignment);
			m_Lock.Unlock();

			return pMemory;
		}

		void Free(void* in_pMemory) override
		{
			m_Lock.Lock();
			FreeListHeapBase::Free(in_pMemory);
			m_Lock.Unlock();
		}
	};
}