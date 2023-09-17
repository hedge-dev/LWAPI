#pragma once

namespace app
{
	class CFadeInOutManager
	{
	public:
		typedef size_t ScreenType;

	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpFadeIn, ASLR(0x0090B0C0), CFadeInOutManager*, float, ScreenType);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpWhiteOut, ASLR(0x0090AF30), CFadeInOutManager*, float, ScreenType);
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpIsFinished, ASLR(0x0090A800), const CFadeInOutManager*, ScreenType);

	public:
		INSERT_PADDING(516) {};

		static CFadeInOutManager* GetInstance() { return *static_cast<CFadeInOutManager**>((void*)ASLR(0x00FEFD0C)); }

		void FadeIn(float in_fadeTime, ScreenType in_screenType)
		{
			ms_fpFadeIn(this, in_fadeTime, in_screenType);
		}
		
		void WhiteOut(float in_whiteOutTime, ScreenType in_screenType)
		{
			ms_fpWhiteOut(this, in_whiteOutTime, in_screenType);
		}

		bool IsFinished(ScreenType in_screenType) const
		{
			return ms_fpIsFinished(this, in_screenType);
		}
	};
}