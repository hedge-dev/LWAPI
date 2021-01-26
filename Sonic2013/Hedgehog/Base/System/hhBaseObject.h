#pragma once

namespace app::fnd
{
	class BaseObject
	{
	public:
		virtual ~BaseObject() = default;

		inline void* operator new(size_t size)
		{
			return __HH_ALLOC(size);
		}

		inline void operator delete(void* mem)
		{
			__HH_FREE(mem);
		}
	};
}