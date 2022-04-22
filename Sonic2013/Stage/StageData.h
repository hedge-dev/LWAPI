#pragma once

namespace app::StageInfo
{
	class alignas(16) SStageData : public fnd::ReferencedObject
	{
		enum ClearCondition
		{
			CONDITION_GOAL,
			CONDITION_TIMEOUT,
		};
		
		struct TimeData
		{
			float m_Limit{};
			csl::ut::FixedArray<float, 4> m_RankIntervals{};
		};

	public:
		csl::ut::FixedString<16> m_Name{};
		csl::ut::FixedString<16> m_Directory{};
		csl::ut::FixedString<16> m_PathData{};
		csl::ut::FixedString<16> m_Unk1{};
		csl::ut::FixedArray <csl::math::Vector3, 2> m_PlayerPositions{};
		csl::ut::FixedArray <csl::math::Angle3, 2> m_PlayerRotations{};
		char m_Unk2;
		char m_Unk3;
		csl::ut::Bitset<ushort> m_PlayerFlags{};
		csl::ut::Bitset<ushort> m_StageFlags{};
		csl::ut::InplaceMoveArray<app::Game::EPhantomType, app::Game::EPhantomType::PHANTOM_MAX> m_Phantoms{ nullptr };
		csl::ut::InplaceMoveArray<app::Game::EPhantomType, app::Game::EPhantomType::PHANTOM_MAX> m_Unk4{ nullptr };
		csl::ut::FixedString<32> m_Bgm{};
		csl::ut::FixedString<32> m_BgmSv{};
		csl::ut::FixedString<32> m_Amb{};
		csl::ut::FixedString<32> m_AmbIn{};
		float m_Reverb{};
		TimeData m_TimeData{};
		csl::ut::InplaceMoveArray<app::animal::AnimalType, 3> m_Animals{ nullptr };
		uint m_RequiredAnimals{};
		csl::ut::Enum<ClearCondition, char> m_ClearCondition{};
		float m_EagleAltitude{};
		
		SStageData()
		{
			ASSERT_OFFSETOF(SStageData, m_PlayerRotations, 112);
			ASSERT_OFFSETOF(SStageData, m_StageFlags, 140);
			ASSERT_OFFSETOF(SStageData, m_Phantoms, 144);
		}
	};
}