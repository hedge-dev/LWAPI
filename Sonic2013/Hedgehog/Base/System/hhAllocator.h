#pragma once

static inline FUNCTION_PTR(void*, __cdecl, fp_HH_ALLOC, ASLR(0x00C1B130), size_t size);
static inline FUNCTION_PTR(void, __cdecl, fp_HH_FREE, ASLR(0x00C1B330), void* mem);

static void* __HH_ALLOC(size_t size)
{
	return fp_HH_ALLOC(size);
}

static void __HH_FREE(void* mem)
{
	fp_HH_FREE(mem);
}