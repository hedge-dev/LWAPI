#pragma once

namespace gindows
{
	class Pad : Object
	{
	public:
		size_t m_Unk1;
		size_t m_Unk2;
		size_t m_Unk3;
		size_t m_Unk4;
		uint m_ButtonStates[14]{};
		size_t m_Unk5;
	};
}