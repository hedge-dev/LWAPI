#pragma once

namespace SurfRide
{
	class MemoryAllocator
	{
	public:
		virtual ~MemoryAllocator() = default;

		virtual void* Allocate(size_t size)
		{
			return nullptr;
		}

		virtual void* Allocate(size_t size, size_t alignment) = 0;

		virtual void Free(void* memory) = 0;
	};

	inline void SrFree(void* mem)
	{
		FUNCTION_PTR(void, __cdecl, fpSrFree, ASLR(0x00C5F500), void*);
		fpSrFree(mem);
	}
}

namespace app::HUD
{
	class CAppMemoryAlloc : public SurfRide::MemoryAllocator
	{

	};
}

namespace SurfRide
{
	inline app::HUD::CAppMemoryAlloc* GetMemoryAllocatorSystem()
	{
		return *(app::HUD::CAppMemoryAlloc**)ASLR(0x011D7E80);
	}
}