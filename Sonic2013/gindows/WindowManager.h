#pragma once

namespace gindows
{
	class WindowManager : Object
	{
	protected:
		csl::ut::Bitset<uint> m_Flags{};
		csl::ut::LinkList<void*> m_Forms{ 608 };
		csl::ut::LinkList<void*> m_Forms2{ 616 };
		INSERT_PADDING(20){};
	};
}