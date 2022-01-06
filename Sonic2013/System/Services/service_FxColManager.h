#pragma once

namespace app
{
	class FxColManager : public fnd::GameService
	{
	protected:
		inline static fnd::GameServiceClass* ms_pStaticClass = reinterpret_cast<fnd::GameServiceClass*>(ASLR(0x00FEFC84));
		inline static FxColManager** ms_pInstance = reinterpret_cast<FxColManager**>(ASLR(0x00FEFC80));
		
		INSERT_PADDING(76) {};
		uint m_Flags;
		INSERT_PADDING(76);
	public:
		hh::ut::PackFile m_Resources{ nullptr };
		void* m_pUnk1;
		app::FxParameter m_CurrentParameter;
		
	protected:
		INSERT_PADDING(64);
		
	public:
		FxColManager() : GameService(0)
		{
			ASSERT_OFFSETOF(FxColManager, m_Flags, 136);
		}

		void EditingFxParam()
		{
			m_Flags |= 0x400;
		}

		bool IsEditingFxParam() const
		{
			return m_Flags & 0x400;
		}
		
		static FxColManager* GetInstance()
		{
			return *ms_pInstance;
		}

		static fnd::GameServiceClass& staticClass()
		{
			return *ms_pStaticClass;
		}
	};
}
