#pragma once

namespace csl::fnd
{
	class MallocAllocator : public IAllocator, public Singleton<MallocAllocator>
	{
	public:
		static MallocAllocator ms_Instance;
		
		MallocAllocator()
		{
			ReplaceInstance(this);
		}
		
		void* Alloc(size_t in_size, int in_alignment) override
		{
			return _aligned_malloc(in_size, in_alignment);
		}

		void Free(void* in_pLoc) override
		{
			_aligned_free(in_pLoc);
		}
	};

	inline MallocAllocator MallocAllocator::ms_Instance{};
}