#pragma once

namespace gindows
{
	template<typename _Ty>
	class Allocator
	{
	public:
		using _From_primary = std::dummy::allocator;

		using value_type = _Ty;

		_CXX17_DEPRECATE_OLD_ALLOCATOR_MEMBERS typedef _Ty* pointer;
		_CXX17_DEPRECATE_OLD_ALLOCATOR_MEMBERS typedef const _Ty* const_pointer;

		_CXX17_DEPRECATE_OLD_ALLOCATOR_MEMBERS typedef _Ty& reference;
		_CXX17_DEPRECATE_OLD_ALLOCATOR_MEMBERS typedef const _Ty& const_reference;

		using size_type = size_t;
		using difference_type = ptrdiff_t;
		
		_Ty* allocate(size_t in_num)
		{
			if (!in_num)
				return nullptr;

			auto* pAlloc = GetMemoryAllocator();
			return reinterpret_cast<_Ty*>(pAlloc->Alloc(sizeof(_Ty) * in_num, alignof(_Ty)));
		}

		void deallocate(_Ty* in_pPtr, size_t in_num)
		{
			GetMemoryAllocator()->Free(in_pPtr);
		}
	};
}