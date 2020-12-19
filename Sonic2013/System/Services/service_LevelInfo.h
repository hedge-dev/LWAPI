#pragma once

namespace app
{
	class CLevelInfo : fnd::GameService
	{
	public:
		inline static fnd::GameServiceClass* ms_pStaticClass = reinterpret_cast<fnd::GameServiceClass*>(ASLR(0x00FEFD1C));


		inline static FUNCTION_PTR(void*, __thiscall, ms_fpGetPlayerInfo, ASLR(0x009125A0), void* This, uint playerNum);

		void* GetPlayerInfo(uint playerNum)
		{
			return ms_fpGetPlayerInfo(this, playerNum);
		}

		static fnd::GameServiceClass& staticClass()
		{
			return *ms_pStaticClass;
		}
	};
}