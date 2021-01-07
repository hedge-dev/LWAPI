#pragma once
namespace app::game
{
	class GlobalAllocator
	{
		inline static csl::fnd::IAllocator** ms_ppAllocators = reinterpret_cast<csl::fnd::IAllocator**>(ASLR(0x000FD7C34));

	public:
		static csl::fnd::IAllocator* GetAllocator(uint id)
		{
			return ms_ppAllocators[id];
		}

		static void SetAllocator(uint id, csl::fnd::IAllocator* allocator)
		{
			ms_ppAllocators[id] = allocator;
		}
		
		static csl::fnd::IAllocator* GetSingletonAllocator()
		{
			return GetAllocator(2);
		}
	};
}