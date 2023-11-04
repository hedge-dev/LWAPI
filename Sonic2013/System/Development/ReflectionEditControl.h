#pragma once

namespace app::dev
{
	class CReflectionEditControl : public S13VariableEditControl
	{
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetup, ASLR(0x004590A0), CReflectionEditControl*, fnd::DataResource*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetData, ASLR(0x00458FC0), CReflectionEditControl*, const fnd::Variant&);

	protected:
		S13VariableGroup* m_pGroup{};
		
	public:
		CReflectionEditControl(fnd::DataResource* in_pResource)
		{
			ASSERT_OFFSETOF(CReflectionEditControl, m_pGroup, 584);
			
			m_pGroup = S13VariableGroup::Create("Reflection Edit");
			if (m_pGroup)
			{
				SetDock(1);
				SetGroup(m_pGroup);
				Setup(in_pResource);
			}
		}

		void Setup(fnd::DataResource* in_pResource)
		{
			ms_fpSetup(this, in_pResource);
		}

		void SetData(const fnd::Variant& in_rData)
		{
			ms_fpSetData(this, in_rData);
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