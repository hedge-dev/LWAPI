#pragma once

namespace app::dbg
{
	inline static FUNCTION_PTR(csl::fnd::IAllocator*, __cdecl, ms_fpGetMemoryAllocator, ASLR(0x004438B0));

	inline static csl::fnd::IAllocator* GetMemoryAllocator()
	{
		return ms_fpGetMemoryAllocator();
	}
	
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