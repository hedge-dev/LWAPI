#pragma once

namespace app
{
	class GameModeMinigame :
		public GameMode,
		public TTinyFsm<GameModeMinigame, GameModeUtil::Event<GameModeMinigame>, false>,
		TinyFsmSetOption<TiFSM_OPTION_USE_FP_TOP>
	{
	public:
		csl::ut::FixedString<16> Name{};

		INSERT_PADDING(172) {};
	};
}