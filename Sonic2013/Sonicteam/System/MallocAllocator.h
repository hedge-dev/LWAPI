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
			return malloc(size);
		}

		void Free(void* loc) override
		{
			free(loc);
		}
	};

	inline MallocAllocator MallocAllocator::ms_Instance{};
}