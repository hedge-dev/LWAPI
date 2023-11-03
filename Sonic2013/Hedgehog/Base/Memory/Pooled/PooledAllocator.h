#pragma once

namespace app::fnd
{
	class PooledAllocator : public PooledAllocatorBase
	{
	public:
		PooledAllocator(csl::fnd::LinkHeapBase* in_pHeapList) : PooledAllocatorBase(in_pHeapList)
		{

		}
	};
}