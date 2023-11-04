#pragma once

namespace app::dbg
{
	inline static FUNCTION_PTR(csl::fnd::IAllocator*, __cdecl, ms_fpGetMemoryAllocator, ASLR(0x004438B0));

	inline static csl::fnd::IAllocator* GetMemoryAllocator()
	{
		return ms_fpGetMemoryAllocator();
	}
	
	template<typename T>
	class Allocator
	{
	public:
		T* allocate(size_t in_num)
		{
			if (!in_num)
				return nullptr;
			
			auto* pAlloc = GetMemoryAllocator();
			return reinterpret_cast<T*>(pAlloc->Alloc(sizeof(T) * in_num, alignof(T)));
		}

		void deallocate(T* in_pPtr, size_t in_num)
		{
			GetMemoryAllocator()->Free(in_pPtr);
		}
	};
}