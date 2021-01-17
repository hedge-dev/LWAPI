#pragma once

namespace gindows
{
	class Object
	{
	public:
		virtual ~Object() = default;

		void* operator new(size_t size)
		{
			if (!GetMemoryAllocator())
				return nullptr;
			
			return GetMemoryAllocator()->Alloc(size, 16);
		}

		void operator delete(void* mem)
		{
			if (!GetMemoryAllocator())
				return;
			
			GetMemoryAllocator()->Free(mem);
		}
	};
}