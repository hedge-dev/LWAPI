#pragma once

static inline FUNCTION_PTR(void*, __cdecl, ms_fpHH_ALLOC, ASLR(0x00C1B130), size_t size);
static inline FUNCTION_PTR(void, __cdecl, ms_fpHH_FREE, ASLR(0x00C1B330), void* mem);

static void* __HH_ALLOC(size_t size)
{
	return ms_fpHH_ALLOC(size);
}

static void __HH_FREE(void* mem)
{
	ms_fpHH_FREE(mem);
}

inline void* operator new(size_t size)
{
	return __HH_ALLOC(size);
}

inline void operator delete(void* mem)
{
	__HH_FREE(mem);
}