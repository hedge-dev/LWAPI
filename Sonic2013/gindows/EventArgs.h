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
		// TODO
	};

	struct KeyEventArgs : EventArgs
	{
		ushort m_KeyCode{};
		bool modifiers[3]{}; // Not sure
	};

	struct KeyPressEventArgs : EventArgs
	{
		char m_Key{};
	};

	struct RenderEventArgs : EventArgs
	{
		Canvas* m_pRenderCanvas;
	};
}