#pragma once

namespace csl::fnd
{
	template<typename TLock = Mutex>
	class PoolHeapTemplate : public PoolHeapBase
	{
	public:
		TLock m_Lock{};

		PoolHeapTemplate()
		{
			
		}

		void* Alloc(size_t in_size, size_t in_alignment) override
		{
			m_Lock.Lock();
			void* pResult = AllocCore(in_size);
			m_Lock.Unlock();

			return pResult;
		}

		void* AllocBottom(size_t in_size, size_t in_alignment) override
		{
			m_Lock.Lock();
			void* pResult = AllocCore(in_size);
			m_Lock.Unlock();

			return pResult;
		}
	};
}