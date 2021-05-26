#pragma once
namespace app
{
	namespace game
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
		};
	}

	namespace fnd
	{
		inline static FUNCTION_PTR(csl::fnd::IAllocator*, __cdecl, ms_fpGetTempAllocator, ASLR(0x00499EB0));
		
		inline static csl::fnd::IAllocator* GetSingletonAllocator()
		{
			return game::GlobalAllocator::GetAllocator(2);
		}

		inline static csl::fnd::IAllocator* GetTempAllocator()
		{
			return ms_fpGetTempAllocator();
		}
	}
}