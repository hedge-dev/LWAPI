#pragma once
#include "Form.h"

namespace gindows
{
	class WindowManager : public Object
	{
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpDraw, ASLR(0x0097A7B0), WindowManager*);

	protected:
		csl::ut::Bitset<uint> m_Flags{};
		csl::ut::LinkList<Form> m_Forms{ &Form::m_FormsNode };
		csl::ut::LinkList<Form> m_ActiveForms{ &Form::m_ActiveFormsNode };
		Control* m_pDesktop{};
		Form* m_pActiveForm{};
		INSERT_PADDING(8){};

		void AddForm(Form* in_pForm)
		{
			m_Forms.push_back(in_pForm);
			m_ActiveForms.push_back(in_pForm);
			m_pActiveForm = in_pForm;
		}

		void EraseForm(Form* in_pForm)
		{
			m_Forms.erase(in_pForm);
			m_ActiveForms.erase(in_pForm);

			if (m_pActiveForm == in_pForm)
				m_pActiveForm = nullptr;
		}
		
		bool IsVisible() const
		{
			return m_Flags.test(0);
		}
		
		void SetVisibility(bool in_visible)
		{
			m_Flags.set(0, in_visible);
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
