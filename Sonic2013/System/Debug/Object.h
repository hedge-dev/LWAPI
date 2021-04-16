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
		
		void* operator new(size_t size)
		{
			return GetAllocator()->Alloc(size, 16);
		}

		void operator delete(void* mem)
		{
			return GetAllocator()->Free(mem);
		}
	};
}