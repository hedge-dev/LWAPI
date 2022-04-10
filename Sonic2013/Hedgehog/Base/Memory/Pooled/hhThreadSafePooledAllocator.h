#pragma once

namespace app::fnd
{
	class ThreadSafePooledAllocator : public PooledAllocatorBase
	{
	public:
		ThreadSafePooledAllocator(csl::fnd::LinkHeapTemplate<csl::fnd::Mutex>* in_pHeapList) : PooledAllocatorBase(in_pHeapList)
		{

		}
	};
}