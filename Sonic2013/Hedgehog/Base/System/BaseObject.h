#pragma once

namespace app::fnd
{
	class BaseObject
	{
	public:
		virtual ~BaseObject() = default;

		inline void* operator new(size_t in_size)
		{
			return __HH_ALLOC(in_size);
		}

		inline void operator delete(void* in_pMem)
		{
			__HH_FREE(in_pMem);
		}
	};
}