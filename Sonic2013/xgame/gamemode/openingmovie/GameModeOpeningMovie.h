#pragma once

namespace app
{
	struct GameModeOpeningMovieCinfo;

	class GameModeOpeningMovie :
		public GameMode,
		public TTinyFsm<GameModeOpeningMovie, GameModeUtil::Event<GameModeOpeningMovie>, false>,
		TinyFsmSetOption<TiFSM_OPTION_USE_FP_TOP>
	{
	public:
		INSERT_PADDING(20) {};
	};
}