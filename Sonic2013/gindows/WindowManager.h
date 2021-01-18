#pragma once

namespace gindows
{
	class WindowManager : Object
	{
	protected:
		csl::ut::Bitset<uint> m_Flags{};
		csl::ut::LinkList<void*> m_Forms{ 604 };
		csl::ut::LinkList<void*> m_Forms2{ 612 };
		INSERT_PADDING(20){};
	};
}