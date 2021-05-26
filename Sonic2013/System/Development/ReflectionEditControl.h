#pragma once

namespace app::dev
{
	class CReflectionEditControl : public S13VariableEditControl
	{
	protected:
		S13VariableGroup* m_pGroup{};
		
	public:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetup, ASLR(0x004590A0), CReflectionEditControl* pThis, fnd::DataResource* pResource);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetData, ASLR(0x00458FC0), CReflectionEditControl* pThis, const fnd::Variant& rData);
		
		CReflectionEditControl(fnd::DataResource* pResource)
		{
			ASSERT_OFFSETOF(CReflectionEditControl, m_pGroup, 584);
			
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

		void SetData(const fnd::Variant& rData)
		{
			ms_fpSetData(this, rData);
		}

		void ReadValue()
		{
			if (m_pGroup)
				m_pGroup->ReadValue();
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