#pragma once
#include "Form.h"

namespace gindows
{
	class WindowManager : public Object
	{
	protected:
		csl::ut::Bitset<uint> m_Flags{};
		csl::ut::LinkList<Form> m_Forms{ &Form::m_FormsNode };
		csl::ut::LinkList<Form> m_ActiveForms{ &Form::m_ActiveFormsNode };
		Control* m_pDesktop{};
		Form* m_pActiveForm{};
		INSERT_PADDING(8){};

	public:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpDraw, ASLR(0x0097A7B0), void* This);

		void AddForm(Form* pForm)
		{
			m_Forms.push_back(pForm);
			m_ActiveForms.push_back(pForm);
			m_pActiveForm = pForm;
		}

		void EraseForm(Form* pForm)
		{
			m_Forms.erase(pForm);
			m_ActiveForms.erase(pForm);

			if (m_pActiveForm == pForm)
				m_pActiveForm = nullptr;
		}
		
		bool IsVisible() const
		{
			return m_Flags.test(0);
		}
		
		void SetVisibility(bool visible)
		{
			m_Flags.set(0, visible);
		}
		
		void Draw()
		{
			if (!IsVisible())
				return;

			m_pDesktop->Render();
			for (auto& form : m_Forms)
			{
				if (!form.IsShow())
					continue;

				form.Render();
			}
		}
	};
}
