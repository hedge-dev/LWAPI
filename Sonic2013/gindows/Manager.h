#pragma once

namespace gindows
{
	class Manager : Object, csl::ut::NonCopyable
	{
	protected:
		ManagerImpl* m_pImpl{};
		WindowManager* m_pWindowManager{};
	};
}