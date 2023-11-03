#pragma once

namespace app::StageInfo
{
	class alignas(16) SStageData : public fnd::ReferencedObject
	{
	public:
		enum ClearCondition
		{
			eClearCondition_Goal,
			eClearCondition_Timeout,
		};
		
		struct TimeData
		{
			float Limit{};
			csl::ut::FixedArray<float, 4> RankIntervals{};
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

		csl::ut::FixedString<16> Name{};
		csl::ut::FixedString<16> Directory{};
		csl::ut::FixedString<16> PathData{};
		csl::ut::FixedString<16> Unk1{};
		csl::ut::FixedArray <csl::math::Vector3, 2> PlayerPositions{};
		csl::ut::FixedArray <csl::math::Angle3, 2> PlayerRotations{};
		char Zone{};
		char Act{};
		csl::ut::Bitset<ushort> PlayerFlags{};
		csl::ut::Bitset<ushort> StageFlags{};
		csl::ut::InplaceMoveArray<app::Game::EPhantomType, app::Game::EPhantomType::ePhantom_Max> Phantoms{ nullptr };
		csl::ut::InplaceMoveArray<app::Game::EPhantomType, app::Game::EPhantomType::ePhantom_Max> Unk4{ nullptr };
		csl::ut::FixedString<32> Bgm{};
		csl::ut::FixedString<32> BgmSv{};
		csl::ut::FixedString<32> Amb{};
		csl::ut::FixedString<32> AmbIn{};
		float Reverb{};
		TimeData TimeData{};
		csl::ut::InplaceMoveArray<app::animal::AnimalType, 3> Animals{ nullptr };
		int RequiredAnimals{};
		csl::ut::Enum<ClearCondition, char> ClearCondition{};
		float EagleAltitude{};
		
		SStageData()
		{
			ASSERT_OFFSETOF(SStageData, PlayerRotations, 112);
			ASSERT_OFFSETOF(SStageData, StageFlags, 140);
			ASSERT_OFFSETOF(SStageData, Phantoms, 144);
		}

		const char* GetBaseStageName() const
		{
			if (IsBattle())
				return Directory.c_str();
			else
				return Name.c_str();
		}

		const csl::ut::InplaceMoveArray<app::Game::EPhantomType, app::Game::EPhantomType::ePhantom_Max>* GetPhantoms() const
		{
			return &Phantoms;
		}

		csl::math::Vector3 GetPlayerPos(int in_playerNo) const
		{
			return PlayerPositions[in_playerNo];
		}

		csl::math::Angle3 GetDirection(int in_playerNo) const
		{
			return PlayerRotations[in_playerNo];
		}

		bool GetReverb(float* out_pReverb) const
		{
			if (Reverb < 0.0f)
				return false;
		
			*out_pReverb = Reverb;
			return true;
		}

		bool IsMinigame() const
		{
			return StageFlags.test(STAGE_FLAG_IS_MINIGAME);
		}

		bool IsBattle() const
		{
			return StageFlags.test(STAGE_FLAG_IS_BATTLE);
		}

		bool IsNoRedRing() const
		{
			return StageFlags.test(STAGE_FLAG_IS_NO_REDRING);
		}

		bool IsOnlyNormalPlay() const
		{
			return StageFlags.test(STAGE_FLAG_IS_ONLY_NORMALPLAY);
		}

		bool IsSecretStage() const
		{
			return StageFlags.test(STAGE_FLAG_IS_SECRET_STAGE);
		}

		bool IsBakuBakuStage() const
		{
			return StageFlags.test(STAGE_FLAG_IS_BAKUBAKU_STAGE);
		}

		bool IsDrawReflect() const
		{
			return StageFlags.test(STAGE_FLAG_IS_DRAW_REFLECT);
		}

		bool IsDisableRandomBoxQuake() const
		{
			return StageFlags.test(STAGE_FLAG_IS_DISABLE_RANDOMBOX_QUAKE);
		}

		bool IsLastBossStage() const
		{
			return StageFlags.test(STAGE_FLAG_IS_LASTBOSS);
		}

		bool IsDLCStage() const
		{
			return StageFlags.test(STAGE_FLAG_IS_DLC_STAGE);
		}

		bool IsYoshiIslandStage() const
		{
			return StageFlags.test(STAGE_FLAG_IS_YOSHIISLAND_STAGE);
		}

		bool IsZeldaStage() const
		{
			return StageFlags.test(STAGE_FLAG_IS_ZELDA_STAGE);
		}
	};
}