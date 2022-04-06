#include "GameSequence.h"
#pragma once

namespace app
{
	inline void CGameSequence::InitGameMode(GameMode* in_pMode)
	{
		m_pGameMode = in_pMode;
		m_pGame->InitGameMode(in_pMode);
	}

	inline void CGameSequence::ShutdownGameMode()
	{
		m_pGame->ShutdownGameMode();
		m_pGameMode = nullptr;
	}
}