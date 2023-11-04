#pragma once

namespace gindows
{
	class Canvas;
	
	struct EventArgs
	{
		void* Unk1{}; // Sender?
		bool Handled{};
	};

	struct MouseEventArgs : EventArgs
	{
		short Button{};
	};

	struct KeyEventArgs : EventArgs
	{
		ushort KeyCode{};
		char ProcessCount;
		INSERT_PADDING(1);
		char AltDown;
		char ShiftDown;
		char CtrlDown;

		KeyEventArgs()
		{
			ASSERT_OFFSETOF(KeyEventArgs, ShiftDown, 0xD);
		}
	};

	struct KeyPressEventArgs : EventArgs
	{
		char Key{};
	};

	struct ExecuteEventArgs : EventArgs
	{
		float Delta;
	};
	
	struct RenderEventArgs : EventArgs
	{
		Canvas* pRenderCanvas;
	};
}