#pragma once

namespace gindows
{
	class Object
	{
	public:
		virtual ~Object() = default;

		void* operator new(size_t in_size)
		{
			if (!GetMemoryAllocator())
				return nullptr;
			
			return GetMemoryAllocator()->Alloc(in_size, 16);
		}

		void operator delete(void* in_pMem)
		{
			if (!GetMemoryAllocator())
				return;
			
			GetMemoryAllocator()->Free(in_pMem);
		}
	};
}