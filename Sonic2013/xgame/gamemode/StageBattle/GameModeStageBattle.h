#pragma once

namespace app
{
	namespace xgame
	{
		typedef int BattleWinner;
	}

	struct GameModeBattleCInfo
	{
		struct Mission
		{
			int Unk1{};
			int Unk2{};
		};

		int Unk1{};
		int RaceType{};
		int Unk3{};
		int Unk4{};
		int Unk5{};
		csl::ut::InplaceMoveArray<xgame::BattleWinner, 5> Winners{ nullptr };
		csl::ut::FixedArray<int, 2> Unk6{};
		int Unk7{};
		int Unk8{};
		bool Unk9{};

		bool IsSingleMatch()
		{
			return Unk4 == 0;
		}
	};

	class GameModeStageBattle :
		public GameMode,
		public TTinyFsm<GameModeStageBattle, GameModeUtil::Event<GameModeStageBattle>, false>,
		TinyFsmSetOption<TiFSM_OPTION_USE_FP_TOP>
	{
	public:
		class MyStageDataListener : public StageDataListener
		{
		public:
			GameModeStageBattle* pOwner{};
		};
		
		INSERT_PADDING(156);
		int Unk1{};
		INSERT_PADDING(60);
		StageInfo::SStageData* pStageData{};
		INSERT_PADDING(12);
		SGameWarpInfo WarpInfo{};
		INSERT_PADDING(8);
		CLevelInfo* pLevelInfo{};
		INSERT_PADDING(184);
	};
}
