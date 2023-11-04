#pragma once

namespace app::dbg
{	
	class Object
	{
	public:
		virtual ~Object();

		inline static csl::fnd::IAllocator* GetAllocator()
		{
			return GetMemoryAllocator();
		}
		
		void* operator new(size_t in_size)
		{
			return GetAllocator()->Alloc(in_size, 16);
		}

		void operator delete(void* in_pMem)
		{
			return GetAllocator()->Free(in_pMem);
		}
	};
}