#pragma once

namespace app
{
	class CObjInfoContainer : fnd::GameService
	{
	private:
		inline static FUNCTION_PTR(CObjInfo*, __thiscall, ms_fpGetInfo, ASLR(0x008405C0), const CObjInfoContainer* This, const char* name);
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpRegister, ASLR(0x00840670), CObjInfoContainer* This, const char* name, CObjInfo* info);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpLoadRequestAll, ASLR(0x00840420), const CObjInfoContainer* This);
		inline static fnd::GameServiceClass* ms_pStaticClass = reinterpret_cast<fnd::GameServiceClass*>(ASLR(0x00FEF2B0));

	protected:
		csl::ut::StringMap<CObjInfo*> m_Infos{ GetAllocator() };
		
	public:
		static fnd::GameServiceClass& staticClass()
		{
			return *ms_pStaticClass;
		}

		const csl::ut::StringMap<CObjInfo*>& Infos() const
		{
			return m_Infos;
		}
		
		bool IsRegister(const char* in_pName) const
		{
			const auto result = m_Infos.find(in_pName);

			return result != m_Infos.end();
		}
		
		CObjInfo* GetInfo(const char* in_pName) const
		{
			return ms_fpGetInfo(this, in_pName);
		}

		bool Register(const char* in_pName, CObjInfo* in_pInfo)
		{
			return ms_fpRegister(this, in_pName, in_pInfo);
		}

		void LoadRequestAll() const
		{
			ms_fpLoadRequestAll(this);
		}
	};
}