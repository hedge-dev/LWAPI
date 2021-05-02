#pragma once
#include "Form.h"

namespace gindows
{
	class WindowManager : public Object
	{
	protected:
		csl::ut::Bitset<uint> m_Flags{};
		csl::ut::LinkList<Form> m_Forms{ &Form::m_FormsNode };
		csl::ut::LinkList<Form> m_Forms2{ &Form::m_ActiveFormsNode };
		Control* m_pUnk1{};
		Form* m_pActiveForm{};
		INSERT_PADDING(8){};

	public:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpDraw, ASLR(0x0097A7B0), void* This);

		void SetVisibility(bool visible)
		{
			m_Flags.set(0, visible);
		}
		
		void Draw()
		{
			return ms_fpDraw(this);
		}
	};
}
