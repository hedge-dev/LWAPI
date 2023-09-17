#pragma once

namespace app::xgame
{
	class alignas(4) StageSoundGuidePathControl
	{
	public:
		game::PathEvaluator Path{};
		int Unk1{};
		bool Unk2{};
	};
}