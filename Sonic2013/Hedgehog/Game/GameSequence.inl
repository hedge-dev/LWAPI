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

	inline StageInfo::SStageData* CGameSequence::GetStageDataByWorldStageID(int in_worldIndex, int in_stageIndex)
	{
		auto* pStageInfo = StageInfo::CStageInfo::GetInstance();
		int advStageIndex = pStageInfo->GetAdvStageIndex(in_worldIndex, in_stageIndex);
		if (advStageIndex >= 0)
			return pStageInfo->GetAdvStageData(advStageIndex);

		return { nullptr };
	}

	inline void CGameSequence::OnMinigameOpened(uint in_worldIndex, uint in_minigameIndex)
	{
		WorldAreaMapCInfo::Event event{};
		event.EventType = WorldAreaMapCInfo::Event::EEventType::eEventType_MinigameOpened;
		event.Unk1 = in_worldIndex;
		event.RewardType = in_minigameIndex;
		WorldMapInfo.AddEvent(event);

		GetFlagSet()->SetMiniGameOpened(in_worldIndex, in_minigameIndex, true);
	}
}

inline app::SaveData::CGameData* app::GetGameData()
{
	int save{};

	return csl::fnd::Singleton<app::SaveData::CSaveManager>::GetInstance()->GetSaveData(&save)->GetCurrentGameData(&save);
}

inline app::SaveData::CFlagSet* app::GetFlagSet()
{
	int save{};

	return GetGameData()->GetFlagSet(&save);
}