#pragma once

namespace app::StageInfo
{
	class alignas(16) SStageData : public fnd::ReferencedObject
	{
	public:
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
		inline static constexpr int STAGE_FLAG_IS_MINIGAME = 0;
		inline static constexpr int STAGE_FLAG_IS_BATTLE = 1;
		inline static constexpr int STAGE_FLAG_IS_NO_REDRING = 2;
		inline static constexpr int STAGE_FLAG_IS_ONLY_NORMALPLAY = 3;
		inline static constexpr int STAGE_FLAG_IS_SECRET_STAGE = 4;
		inline static constexpr int STAGE_FLAG_IS_BAKUBAKU_STAGE = 5;
		inline static constexpr int STAGE_FLAG_IS_DRAW_REFLECT = 6;
		inline static constexpr int STAGE_FLAG_IS_DISABLE_RANDOMBOX_QUAKE = 7;
		inline static constexpr int STAGE_FLAG_IS_LASTBOSS = 9;
		inline static constexpr int STAGE_FLAG_IS_DLC_STAGE = 10;
		inline static constexpr int STAGE_FLAG_IS_YOSHIISLAND_STAGE = 11;
		inline static constexpr int STAGE_FLAG_IS_ZELDA_STAGE = 12;

		csl::ut::FixedString<16> m_Name{};
		csl::ut::FixedString<16> m_Directory{};
		csl::ut::FixedString<16> m_PathData{};
		csl::ut::FixedString<16> m_Unk1{};
		csl::ut::FixedArray <csl::math::Vector3, 2> m_PlayerPositions{};
		csl::ut::FixedArray <csl::math::Angle3, 2> m_PlayerRotations{};
		char m_Zone{};
		char m_Act{};
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
		int m_RequiredAnimals{};
		csl::ut::Enum<ClearCondition, char> m_ClearCondition{};
		float m_EagleAltitude{};
		
		SStageData()
		{
			ASSERT_OFFSETOF(SStageData, m_PlayerRotations, 112);
			ASSERT_OFFSETOF(SStageData, m_StageFlags, 140);
			ASSERT_OFFSETOF(SStageData, m_Phantoms, 144);
		}

		const char* GetBaseStageName() const
		{
			if (IsBattle())
				return m_Directory.c_str();
			else
				return m_Name.c_str();
		}

		const csl::ut::InplaceMoveArray<app::Game::EPhantomType, app::Game::EPhantomType::PHANTOM_MAX>* GetPhantoms() const
		{
			return &m_Phantoms;
		}

		csl::math::Vector3 GetPlayerPos(int in_playerNo) const
		{
			return m_PlayerPositions[in_playerNo];
		}

		csl::math::Angle3 GetDirection(int in_playerNo) const
		{
			return m_PlayerRotations[in_playerNo];
		}

		bool GetReverb(float* out_pReverb) const
		{
			if (m_Reverb < 0.0f)
				return false;
		
			*out_pReverb = m_Reverb;
			return true;
		}

		bool IsMinigame() const
		{
			return m_StageFlags.test(STAGE_FLAG_IS_MINIGAME);
		}

		bool IsBattle() const
		{
			return m_StageFlags.test(STAGE_FLAG_IS_BATTLE);
		}

		bool IsNoRedRing() const
		{
			return m_StageFlags.test(STAGE_FLAG_IS_NO_REDRING);
		}

		bool IsOnlyNormalPlay() const
		{
			return m_StageFlags.test(STAGE_FLAG_IS_ONLY_NORMALPLAY);
		}

		bool IsSecretStage() const
		{
			return m_StageFlags.test(STAGE_FLAG_IS_SECRET_STAGE);
		}

		bool IsBakuBakuStage() const
		{
			return m_StageFlags.test(STAGE_FLAG_IS_BAKUBAKU_STAGE);
		}

		bool IsDrawReflect() const
		{
			return m_StageFlags.test(STAGE_FLAG_IS_DRAW_REFLECT);
		}

		bool IsDisableRandomBoxQuake() const
		{
			return m_StageFlags.test(STAGE_FLAG_IS_DISABLE_RANDOMBOX_QUAKE);
		}

		bool IsLastBossStage() const
		{
			return m_StageFlags.test(STAGE_FLAG_IS_LASTBOSS);
		}

		bool IsDLCStage() const
		{
			return m_StageFlags.test(STAGE_FLAG_IS_DLC_STAGE);
		}

		bool IsYoshiIslandStage() const
		{
			return m_StageFlags.test(STAGE_FLAG_IS_YOSHIISLAND_STAGE);
		}

		bool IsZeldaStage() const
		{
			return m_StageFlags.test(STAGE_FLAG_IS_ZELDA_STAGE);
		}
	};
}