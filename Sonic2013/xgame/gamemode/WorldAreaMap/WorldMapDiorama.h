#pragma once

namespace app
{
	struct WorldAreaMapDioramaInfo
	{
	public:
		csl::math::Vector3 Position{};
		INSERT_PADDING(8) {}; // worldmap::MapCoord
		INSERT_PADDING(4) {};
		INSERT_PADDING(4) {};
		char RedRingCount{};
		bool IsActUnlocked{};
		bool IsActCompleted{};
		bool IsOnlyNormalPlay{};
		INSERT_PADDING(1) {};
		INSERT_PADDING(1) {};
		Game::ERank Rank{};
	};
}