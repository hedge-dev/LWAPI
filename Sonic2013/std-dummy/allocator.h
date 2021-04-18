#pragma once

namespace std::dummy
{
	template<typename T>
	class allocator
	{
	public:
		T* allocate(size_t num)
		{
			if (!num)
				return nullptr;

			return reinterpret_cast<T*>(__HH_ALLOCALIGN(sizeof(T) * num, alignof(T)));
		}

		void deallocate(T* ptr, size_t num)
		{
			__HH_FREE(ptr);
		}
	};
}