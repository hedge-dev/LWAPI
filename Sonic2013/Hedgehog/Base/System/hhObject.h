#pragma once

namespace hh::base
{
	class CObject
	{
	public:
		CObject() = default;

		void* operator new(const size_t in_size)
		{
			return __HH_ALLOC(in_size);
		}

		void* operator new(const size_t in_size, size_t in_alignment)
		{
			return __HH_ALLOCALIGN(in_size, in_alignment);
		}

		void operator delete(void* in_mem)
		{
			__HH_FREE(in_mem);
		}
	};
}