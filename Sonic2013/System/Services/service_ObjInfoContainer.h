#pragma once

namespace app
{
	class CObjInfoContainer : fnd::GameService
	{
	protected:
		csl::ut::StringMap<CObjInfo*> m_Infos{ GetAllocator() };
		
	public:
		inline static fnd::GameServiceClass* ms_pStaticClass = reinterpret_cast<fnd::GameServiceClass*>(ASLR(0x00FEF2B0));
		inline static FUNCTION_PTR(CObjInfo*, __thiscall, ms_fpGetInfo, ASLR(0x008405C0), const CObjInfoContainer* This, const char* name);
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpRegister, ASLR(0x00840670), CObjInfoContainer* This, const char* name, CObjInfo* info);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpLoadRequestAll, ASLR(0x00840420), const CObjInfoContainer* This);
		
		static fnd::GameServiceClass& staticClass()
		{
			return *ms_pStaticClass;
		}

		const csl::ut::StringMap<CObjInfo*>& Infos() const
		{
			return m_Infos;
		}
		
		bool IsRegister(const char* pName) const
		{
			const auto result = m_Infos.find(pName);

			return result != m_Infos.end();
		}
		
		CObjInfo* GetInfo(const char* pName) const
		{
			return ms_fpGetInfo(this, pName);
		}

		bool Register(const char* pName, CObjInfo* pInfo)
		{
			return ms_fpRegister(this, pName, pInfo);
		}

		void LoadRequestAll() const
		{
			ms_fpLoadRequestAll(this);
		}
	};
}