#pragma once

namespace app::dev
{
	class CReflectionEditControl : public S13VariableEditControl
	{
	protected:
		S13VariableGroup* m_pGroup{};
		
	public:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetup, ASLR(0x004590A0), CReflectionEditControl* pThis, fnd::DataResource* pResource);
		
		CReflectionEditControl(fnd::DataResource* pResource)
		{
			m_pGroup = S13VariableGroup::Create("Reflection Edit");
			if (m_pGroup)
			{
				SetDock(1);
				SetGroup(m_pGroup);
				Setup(pResource);
			}
		}

		void Setup(fnd::DataResource* pResource)
		{
			ms_fpSetup(this, pResource);
		}

		void Reset()
		{
			ClearGroup();
			delete m_pGroup;

			m_pGroup = S13VariableGroup::Create("Reflection Edit");
			if (m_pGroup)
			{
				SetGroup(m_pGroup);
			}
		}
	};
}