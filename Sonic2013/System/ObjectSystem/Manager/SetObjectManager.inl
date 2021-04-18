#pragma once
#pragma push_macro("SendMessage")
#undef SendMessage
#include "../SetObjectListener.h"
#include "SetObjectManager.h"

namespace app
{
	inline void CSetObjectManager::KillAllObject()
	{
		for (auto& obj : m_Objects)
		{
			xgame::MsgKill killMsg{};
			obj.SendMessage(killMsg);
		}
	}

	inline CSetAdapter* CSetObjectManager::FindAdapter(CSetObjectID id)
	{
		auto* pPack = m_pActorManager->FindPack(id);
		if (!pPack)
			return nullptr;

		auto* pActor = pPack->GetActors().front();
		return CSetAdapter::GetPointerFromActor(*pActor);
	}

	inline SetEd::CResObject CSetObjectManager::FindObjectResource(app::CSetObjectID id)
	{
		ASSERT_OFFSETOF(SetEd::SResObjectData, m_pParam, 48);
		auto* pPack = m_pActorManager->FindPack(id);
		if (!pPack)
			return SetEd::CResObject{ nullptr };

		return pPack->GetObjectResource();
	}

	inline CSetObjectListener* CSetObjectManager::CreateObjectBySetObjectID(CSetObjectID id)
	{
		auto* pPack = m_pActorManager->FindPack(id);
		if (!pPack)
			return nullptr;

		auto* pActor = pPack->GetActors().front();
		auto* pAdapter = CSetAdapter::GetPointerFromActor(*pActor);

		auto* pObject = CreateObjectExtrinsic(pAdapter);

		if (pObject)
			return pObject;

		if (pAdapter->GetStatusFlags() & 1)
			return pAdapter->GetListener();
		
		return nullptr;
	}
}

#pragma pop_macro("SendMessage")