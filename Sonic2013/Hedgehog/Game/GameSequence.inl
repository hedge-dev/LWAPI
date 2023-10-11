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
		
		int save{};
		GetFlagSet(&save)->SetMiniGameOpened(in_worldIndex, in_minigameIndex, true);
	}

	inline void CGameSequence::OnChaosEmeraldUnlocked(uint in_worldIndex)
	{
		WorldAreaMapCInfo::Event event{};
		event.EventType = WorldAreaMapCInfo::Event::EEventType::eEventType_EmeraldUnlocked;
		event.Unk1 = in_worldIndex;
		WorldMapInfo.AddEvent(event);

		int save{};
		GetFlagSet(&save)->SetChaosEmeraldUnlocked(in_worldIndex, true);
	}

	inline void CGameSequence::OnSuperSonicUnlocked()
	{
		WorldAreaMapCInfo::Event event{};
		event.EventType = WorldAreaMapCInfo::Event::EEventType::eEventType_SuperSonicUnlocked;
		WorldMapInfo.AddEvent(event);

		int save{};
		GetFlagSet(&save)->SetSuperSonicUnlocked(true);
	}
}

inline app::SaveData::CGameData* app::GetGameData(void* out_pValue)
{
	return csl::fnd::Singleton<app::SaveData::CSaveManager>::GetInstance()->GetSaveData(out_pValue)->GetCurrentGameData(out_pValue);
}

inline app::SaveData::CFlagSet* app::GetFlagSet(void* out_pValue)
{
	return GetGameData(out_pValue)->GetFlagSet(out_pValue);
}