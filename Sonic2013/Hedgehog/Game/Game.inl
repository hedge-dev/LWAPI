#include "Game.h"
#pragma once

namespace app
{
	inline void CGame::InitGameMode(GameMode* in_pMode)
	{
		m_rpMode = in_pMode;
		if (in_pMode)
		{
			in_pMode->m_pGame = this;
			in_pMode->InitializeGameMode(*this);
			in_pMode->OnEnter(*this);
		}
	}

	inline void CGame::ShutdownGameMode()
	{
		if (!m_rpMode)
			return;

		m_rpMode->OnLeave(*this);
		m_rpMode->Destroy(*this);
		fnd::SoundSystem::GetInstance()->Update(0);
		fnd::CMovieSystem::GetInstance()->Update();
		fnd::MessageManager::GetInstance()->Update();
		m_rpMode->ReleaseGameMode();

		m_rpMode = nullptr;
	}
}