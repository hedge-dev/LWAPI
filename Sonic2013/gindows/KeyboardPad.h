#pragma once

namespace gindows
{
	class KeyboardPad : Keyboard
	{
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpUpdateImpl, ASLR(0x0097A570), KeyboardPad*, KeyboardStatus&);
		
	protected:
		Pad* m_pPad{};
		
		void UpdateImpl(KeyboardStatus& in_rStatus) override
		{
			ms_fpUpdateImpl(this, in_rStatus);
		}

	public:
		void SetPad(Pad* in_pPad)
		{
			m_pPad = in_pPad;
		}

		Pad* GetPad() const
		{
			return m_pPad;
		}
	};
}