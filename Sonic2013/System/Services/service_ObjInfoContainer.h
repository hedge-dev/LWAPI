#pragma once

namespace app
{
	class CObjInfoContainer : fnd::GameService
	{
	public:
		inline static fnd::GameServiceClass* ms_pStaticClass = reinterpret_cast<fnd::GameServiceClass*>(ASLR(0x00FEF2B0));
		inline static FUNCTION_PTR(CObjInfo*, __thiscall, ms_fpGetInfo, ASLR(0x008405C0), const CObjInfoContainer* This, const char* name);
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpRegister, ASLR(0x00840670), CObjInfoContainer* This, const char* name, CObjInfo* info);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpLoadRequestAll, ASLR(0x00840420), const CObjInfoContainer* This);
		
		static fnd::GameServiceClass& staticClass()
		{
			return *ms_pStaticClass;
		}

		CObjInfo* GetInfo(const char* name) const
		{
			return ms_fpGetInfo(this, name);
		}

		bool Register(const char* name, CObjInfo* info)
		{
			return ms_fpRegister(this, name, info);
		}

		void LoadRequestAll() const
		{
			ms_fpLoadRequestAll(this);
		}
	};
}