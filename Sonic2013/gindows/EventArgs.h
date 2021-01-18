#pragma once

namespace gindows
{
	struct EventArgs
	{
		void* m_Unk1;
		bool m_Handled;
	};

	struct MouseEventArgs : EventArgs
	{
		// TODO
	};

	struct KeyEventArgs : EventArgs
	{
		// TODO
	};

	struct KeyPressEventArgs : EventArgs
	{
		// TODO
	};
}