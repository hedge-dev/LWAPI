#include "GameMode.h"
#pragma once
#pragma push_macro("CreateService")
#undef CreateService

namespace app
{
	inline void GameMode::OnEnter(CGame& in_rGame)
	{
		auto* pCache = fnd::FileSystem::GetInstance()->GetCache();
		if (pCache)
			pCache->OnEnterCache();

		CreateService(ms_DefaultServices);
	}

	inline void GameMode::OnLeave(CGame& in_rGame)
	{
		auto* pCache = fnd::FileSystem::GetInstance()->GetCache();
		if (pCache)
			pCache->OnLeaveCache();
	}

	inline void GameMode::PreLoadFile(const char* in_pName, int in_priority)
	{
		fnd::FileLoader::GetInstance()->PreLoadFile(in_pName, in_priority);
	}

	inline bool GameMode::IsLoadEnd()
	{
		return fnd::FileLoader::GetInstance()->IsSyncCompleteAll();
	}

	inline void GameMode::LoadFile(const char* in_pName, const fnd::FileLoaderParam& in_rParam)
	{
		fnd::FileLoader::GetInstance()->LoadFile(in_pName, in_rParam);
	}

	inline void GameMode::SendToGroup(uint in_group, fnd::Message& in_rMessage) const
	{
		uint actor = pDocument->GetGroupActorID(in_group);
		GetGame()->BroadcastMessageImm(actor, in_rMessage);
	}

	inline bool GameMode::CreateService(const char* in_pName)
	{
		auto* pRegistry = fnd::GameServiceTypeRegistry::GetInstance();
		auto* pClass = pRegistry->GetClassByName(in_pName);
		if (!pClass)
			return false;

		pDocument->CreateService(*pClass);
		return true;
	}

	inline void GameMode::CreateService(const fnd::GameServiceClass** in_ppClasses)
	{
		while(*in_ppClasses)
		{
			pDocument->CreateService(*(*in_ppClasses));
			in_ppClasses++;
		}
	}
}

#pragma pop_macro("CreateService")