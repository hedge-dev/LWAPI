#pragma once

namespace app
{
	class ObjColorParamChanger : public GameObject
	{
	private:
		inline static FUNCTION_PTR(ObjColorParamChanger*, __thiscall, ms_fpCtor, ASLR(0x0075BDF0), ObjColorParamChanger*);
		inline static FUNCTION_PTR(ObjColorParamChanger*, __thiscall, ms_fpDtor, ASLR(0x0075BE30), ObjColorParamChanger*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpRestart, ASLR(0x0075BF50), ObjColorParamChanger*);

	public:
		enum State : byte
		{

		};

		csl::ut::Enum<State, byte> CurrentState{};
		char Unk1{};
		char Unk2{};
		float Unk3{};

		ObjColorParamChanger()
		{
			ms_fpCtor(this);
		}

		~ObjColorParamChanger() override
		{
			ms_fpDtor(this);
		}

		void Restart()
		{
			ms_fpRestart(this);
		}

		// Temporary, does not actually exist
		static ObjColorParamChanger* Create(csl::fnd::IAllocator* in_pAllocator)
		{
			void* pMem = in_pAllocator->Alloc(sizeof(ObjColorParamChanger), 16);
			return ms_fpCtor(static_cast<ObjColorParamChanger*>(pMem));
		}

		/*ObjColorParamChanger() : GameObject()
		{
			SetObjectCategory(13);
		}*/
	};
}