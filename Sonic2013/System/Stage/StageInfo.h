#pragma once

namespace app::StageInfo
{	
	class CStageInfo
	{
	public:
		inline static CStageInfo** ms_ppInstance = reinterpret_cast<CStageInfo**>(ASLR(0x00FEFD38));
		
		struct SZoneInfo
		{
			uint m_Unk1{};
			uint m_Unk2{};

			csl::ut::FixedString<16> m_Missions[5];
		};
		
		csl::fnd::IAllocator* m_pAllocator{};
		csl::ut::ObjectMoveArray<SStageData> m_Stages{ m_pAllocator };
		csl::ut::ObjectMoveArray<WorldNode> m_Worlds[2];
		SZoneInfo m_Zones[19];
		csl::ut::MoveArray<const char*> m_Unk1{ m_pAllocator }; // Levels?

		[[nodiscard]] static CStageInfo* GetInstance()
		{
			return *ms_ppInstance;
		}
	};
}