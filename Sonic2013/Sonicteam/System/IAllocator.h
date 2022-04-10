#pragma once
namespace csl
{
	namespace fnd
	{
		class IAllocator
		{
		public:
			virtual ~IAllocator() = default;
			
			virtual void* Alloc(size_t in_size, int in_alignment) = 0;
			virtual void Free(void* in_pMemory) = 0;
		};
	}
}