#pragma once

namespace app
{
	struct SPlayerInfo
	{
		INSERT_PADDING(28) {};
	};
	
	class CLevelInfo : public fnd::GameService
	{
	protected:
		inline static fnd::GameServiceClass* ms_pStaticClass = reinterpret_cast<fnd::GameServiceClass*>(ASLR(0x00FEFD1C));

		inline static FUNCTION_PTR(SPlayerInfo*, __thiscall, ms_fpGetPlayerInfo, ASLR(0x009125A0), void* This, uint playerNum);
		inline static FUNCTION_PTR(uint, __thiscall, ms_fpGetPlayerID, ASLR(0x00912550), const void* This, const uint playerNo);
	public:
		csl::ut::FixedArray<SPlayerInfo, 2> m_Players{};
		size_t m_PlayerNum{};
		csl::ut::FixedArray<size_t, 2> m_Cameras{};
		size_t m_UnkRc{};
		size_t m_HudActor{};
		size_t m_RcActor{};
		const char* m_Level{};
		csl::ut::Bitset<uint> m_StageFlags{};
		csl::ut::Bitset<uint> m_UnkFlags{};
		INSERT_PADDING(20){};

		size_t GetCameraActor(size_t i) const
		{
			if (i > m_PlayerNum)
				return 0;

			return m_Cameras[i];
		}
		
		[[nodiscard]] uint GetPlayerID(const uint playerNo) const
		{
			return ms_fpGetPlayerID(this, playerNo);
		}

		SPlayerInfo* GetPlayerInfo(uint playerNum)
		{
			return ms_fpGetPlayerInfo(this, playerNum);
		}

		static fnd::GameServiceClass& staticClass()
		{
			return *ms_pStaticClass;
		}
	};
}