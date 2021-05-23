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
		char m_Unk2;
		char m_Unk3;
		char m_Unk4;
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