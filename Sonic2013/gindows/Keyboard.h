#pragma once

namespace gindows
{	
	class Keyboard : public Object
	{
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpUpdate, ASLR(0x0097A410), Keyboard*);

	protected:
		struct KeyboardStatus
		{
			bool DownKeys[256]{};
			bool UpKeys[256]{};
			uint Unk1; // Handled? Finished?
		};
		
		bool m_KeyStates[256]{};
		uint m_ButtonTrig{};
		uint m_ModifierKeyHold{};
		uint m_ModifierKeyTrig{};
		size_t m_KeyDownCount{};
		ushort m_DownKeys[8]{};
		size_t m_KeyUpCount{};
		ushort m_UpKeys[8]{};

		virtual void UpdateImpl(KeyboardStatus& in_rStatus) = 0;
		
		void Update()
		{
			ms_fpUpdate(this);
		}
	};
}