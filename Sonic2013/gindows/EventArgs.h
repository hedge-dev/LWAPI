#pragma once

namespace gindows
{
	class Canvas;
	
	struct EventArgs
	{
		void* m_Unk1; // Sender?
		bool m_Handled;
	};

	struct MouseEventArgs : EventArgs
	{
		// TODO
	};

	struct KeyEventArgs : EventArgs
	{
		// TODO
		ushort m_KeyCode{};
		// 3 bools go here
		// then a pointer to itself???
	};

	struct KeyPressEventArgs : EventArgs
	{
		// TODO
	};

	struct RenderEventArgs : EventArgs
	{
		Canvas* m_pRenderCanvas;
	};
}