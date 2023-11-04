#pragma once

namespace app
{
	class CGame;
	
	class ApplicationWin : public Application
	{
	protected:
		inline static ApplicationWin** ms_ppApplicationWin = reinterpret_cast<ApplicationWin**>(ASLR(0x00FD3CA8));

		INSERT_PADDING(4) {};
		uint m_WindowHandle{};
		INSERT_PADDING(12) {};
		CGame* m_pGame{};
		
		ApplicationWin() : Application()
		{
			ASSERT_OFFSETOF(ApplicationWin, m_WindowHandle, 228);
			ASSERT_OFFSETOF(ApplicationWin, m_pGame, 244);
		}

	public:
		[[nodiscard]] uint GetWindowHandle() const
		{
			return m_WindowHandle;
		}

		[[nodiscard]] CGame* GetGame() const
		{
			return m_pGame;
		}
		
		[[nodiscard]] static ApplicationWin* GetInstance()
		{
			return *ms_ppApplicationWin;
		}
	};
}