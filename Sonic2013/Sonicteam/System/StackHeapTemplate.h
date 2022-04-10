#pragma once

namespace csl::fnd
{
	template<typename TLock>
	class StackHeapTemplate : public StackHeapBase
	{
		TLock m_Lock{};

	public:
		void* Alloc(size_t in_size, size_t in_alignment) override
		{
			m_Lock.Lock();
			void* pMemory = StackHeapBase::Alloc(in_size, in_alignment);
			m_Lock.Unlock();

			return pMemory;
		}

		void* AllocBottom(size_t in_size, size_t in_alignment) override
		{
			m_Lock.Lock();
			void* pMemory = StackHeapBase::AllocBottom(in_size, in_alignment);
			m_Lock.Unlock();

			return pMemory;
		}

		void FreeAll(FreeMode in_mode) override
		{
			m_Lock.Lock();
			StackHeapBase::FreeAll(in_mode);
			m_Lock.Unlock();
		}
	};
}