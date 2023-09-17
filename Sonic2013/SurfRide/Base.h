#pragma once

namespace SurfRide
{
	class Base
	{
	public:
		void* operator new (size_t in_size, size_t in_alignment)
		{
			return GetMemoryAllocatorSystem()->Allocate(in_size, in_alignment);
		}

		void* operator new (size_t in_size)
		{
			return GetMemoryAllocatorSystem()->Allocate(in_size);
		}

		void operator delete (void* loc)
		{
			GetMemoryAllocatorSystem()->Free(loc);
		}
	};
}
