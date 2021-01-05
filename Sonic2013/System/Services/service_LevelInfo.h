#pragma once

namespace app
{
	class CLevelInfo : fnd::GameService
	{
	public:
		inline static fnd::GameServiceClass* ms_pStaticClass = reinterpret_cast<fnd::GameServiceClass*>(ASLR(0x00FEFD1C));

		inline static FUNCTION_PTR(void*, __thiscall, ms_fpGetPlayerInfo, ASLR(0x009125A0), void* This, uint playerNum);
		inline static FUNCTION_PTR(uint, __thiscall, ms_fpGetPlayerID, ASLR(0x00912550), const void* This, const uint playerNo);

		[[nodiscard]] uint GetPlayerID(const uint playerNo) const
		{
			return ms_fpGetPlayerID(this, playerNo);
		}

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