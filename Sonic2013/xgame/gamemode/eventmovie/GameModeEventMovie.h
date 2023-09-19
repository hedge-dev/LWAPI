#pragma once

namespace app
{
	struct GameModeEventMovieCinfo;

	class GameModeEventMovie :
		public GameMode,
		public TTinyFsm<GameModeEventMovie, GameModeUtil::Event<GameModeEventMovie>, false>,
		TinyFsmSetOption<TiFSM_OPTION_USE_FP_TOP>
	{
	public:
		INSERT_PADDING(44);
	};
}