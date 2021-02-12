#pragma once

namespace gindows
{
	class KeyboardPad : Keyboard
	{
	public:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpUpdateImpl, ASLR(0x0097A570), KeyboardPad* pThis, KeyboardStatus& rStatus);
		
	protected:
		Pad* m_pPad{};
		
		void UpdateImpl(KeyboardStatus& status) override
		{
			ms_fpUpdateImpl(this, status);
		}

	public:
		void SetPad(Pad* pPad)
		{
			m_pPad = pPad;
		}

		Pad* GetPad() const
		{
			return m_pPad;
		}
	};
}