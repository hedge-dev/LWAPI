#pragma once

namespace app::Player
{
	inline game::PathManager* CPathService::GetPathManager()
	{
		return pPlayer->GetDocument()->GetService<game::PathManager>();
	}
}