#pragma once
namespace app
{
	namespace game
	{
		class GlobalAllocator
		{
			inline static csl::fnd::IAllocator** ms_ppAllocators = reinterpret_cast<csl::fnd::IAllocator**>(ASLR(0x000FD7C34));

		public:
			static csl::fnd::IAllocator* GetAllocator(uint in_id)
			{
				return ms_ppAllocators[in_id];
			}

			static void SetAllocator(uint in_id, csl::fnd::IAllocator* in_pAllocator)
			{
				ms_ppAllocators[in_id] = in_pAllocator;
			}
		};
	}

	namespace fnd
	{
		inline static csl::fnd::IAllocator* GetSingletonAllocator()
		{
			return game::GlobalAllocator::GetAllocator(2);
		}

		inline static csl::fnd::IAllocator* GetTempAllocator()
		{
			FUNCTION_PTR(csl::fnd::IAllocator*, __cdecl, fpGetTempAllocator, ASLR(0x00499EB0));
			return fpGetTempAllocator();
		}

		template <typename T>
		T* AllocateTemp(uint in_count)
		{
			return static_cast<T*>(GetTempAllocator()->Alloc(sizeof(T) * in_count, 16));
		}

		template <typename T>
		void DeallocateTemp(T* in_pMemory)
		{
			GetTempAllocator()->Free(static_cast<void*>(in_pMemory));
		}
	}
}