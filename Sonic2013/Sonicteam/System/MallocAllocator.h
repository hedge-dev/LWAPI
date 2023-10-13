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
		
		void* Alloc(size_t size, int alignment) override
		{
			return _aligned_malloc(size, alignment);
		}

		void Free(void* loc) override
		{
			_aligned_free(loc);
		}
	};

	inline MallocAllocator MallocAllocator::ms_Instance{};
}