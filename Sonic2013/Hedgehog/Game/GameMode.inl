#include "GameMode.h"
#pragma once
#pragma push_macro("CreateService")
#undef CreateService

namespace app
{
	inline void GameMode::OnEnter(CGame& in_game)
	{
		auto* pCache = fnd::FileSystem::GetInstance()->GetCache();
		if (pCache)
			pCache->OnEnterCache();

		CreateService(ms_DefaultServices);
	}

	inline void GameMode::OnLeave(CGame& in_game)
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

	inline void GameMode::LoadFile(const char* in_pName, const fnd::FileLoaderParam& in_param)
	{
		fnd::FileLoader::GetInstance()->LoadFile(in_pName, in_param);
	}

	inline void GameMode::SendToGroup(uint in_group, fnd::Message& in_msg) const
	{
		uint actor = m_pDocument->GetGroupActorID(in_group);
		GetGame()->BroadcastMessageImm(actor, in_msg);
	}

	inline bool GameMode::CreateService(const char* in_pName)
	{
		auto* pRegistry = fnd::GameServiceTypeRegistry::GetInstance();
		auto* pClass = pRegistry->GetClassByName(in_pName);
		if (!pClass)
			return false;

		m_pDocument->CreateService(*pClass);
		return true;
	}

	inline void GameMode::CreateService(const fnd::GameServiceClass** in_ppClasses)
	{
		while(*in_ppClasses)
		{
			m_pDocument->CreateService(*(*in_ppClasses));
			in_ppClasses++;
		}
	}
}

#pragma pop_macro("CreateService")