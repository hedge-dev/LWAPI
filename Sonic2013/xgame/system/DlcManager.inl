#pragma once
#include "DlcManager.h"

namespace app::xgame
{
	inline DlcManager::DlcManager()
	{
		pImpl = new DlcManagerImpl(m_pAllocator);
	}

	inline bool DlcManager::IsPurchase(ushort in_dlcType) const
	{
		return pImpl->isPurchase(in_dlcType);
	}

	inline void DlcManager::Update()
	{
		return pImpl->update();
	}
}