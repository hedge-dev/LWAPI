#pragma once

namespace app
{
	class SceneFxDirector : public GameObject
	{
		int Unk1{};
		
	private:
		inline static FUNCTION_PTR(SceneFxDirector*, __thiscall, ms_fpCtor, ASLR(0x00936E30), SceneFxDirector*);
		inline static FUNCTION_PTR(SceneFxDirector*, __thiscall, ms_fpDtor, ASLR(0x00936EA0), SceneFxDirector*);

	public:
		SceneFxDirector()
		{
			ms_fpCtor(this);
		}
		
		~SceneFxDirector() override
		{
			ms_fpDtor(this);
		}

		// Temporary, does not actually exist
		static SceneFxDirector* Create(csl::fnd::IAllocator* in_pAllocator)
		{
			void* mem = in_pAllocator->Alloc(sizeof(SceneFxDirector), 16);
			return ms_fpCtor(static_cast<SceneFxDirector*>(mem));
		}
	};
}