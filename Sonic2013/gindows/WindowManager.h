#pragma once

namespace gindows
{
	class WindowManager : Object
	{
	protected:
		csl::ut::Bitset<uint> m_Flags{};
		csl::ut::LinkList<void*> m_Forms{ 604 };
		csl::ut::LinkList<void*> m_Forms2{ 612 };
		Control* m_pUnk1;
		INSERT_PADDING(16){};

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