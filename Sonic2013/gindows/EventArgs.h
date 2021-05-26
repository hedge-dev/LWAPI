#pragma once

namespace gindows
{
	class Canvas;
	
	struct EventArgs
	{
		void* m_Unk1{}; // Sender?
		bool m_Handled{};
	};

	struct MouseEventArgs : EventArgs
	{
		short m_Button{};
	};

	struct KeyEventArgs : EventArgs
	{
		ushort m_KeyCode{};
		char m_ProcessCount;
		INSERT_PADDING(1);
		char m_AltDown;
		char m_ShiftDown;
		char m_CtrlDown;

		KeyEventArgs()
		{
			ASSERT_OFFSETOF(KeyEventArgs, m_ShiftDown, 0xD);
		}
	};

	struct KeyPressEventArgs : EventArgs
	{
		char m_Key{};
	};

	struct ExecuteEventArgs : EventArgs
	{
		float m_Delta;
	};
	
	struct RenderEventArgs : EventArgs
	{
		Canvas* m_pRenderCanvas;
	};
}