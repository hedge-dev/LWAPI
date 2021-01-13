#pragma once

namespace app
{
	class ApplicationWin : public Application
	{
	protected:
		inline static ApplicationWin** ms_ppApplicationWin = reinterpret_cast<ApplicationWin**>(ASLR(0x00FD3CA8));

		INSERT_PADDING(4) {};
		uint windowHandle{};

		ApplicationWin() : Application()
		{
			ASSERT_OFFSETOF(ApplicationWin, windowHandle, 228);
		}

	public:
		[[nodiscard]] uint GetWindowHandle() const
		{
			return windowHandle;
		}

		[[nodiscard]] static ApplicationWin* GetInstance()
		{
			return *ms_ppApplicationWin;
		}
	};
}