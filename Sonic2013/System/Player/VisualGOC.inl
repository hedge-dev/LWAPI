#include "VisualGOC.h"
#pragma once

namespace app::Player
{
	inline CEffectGOC* CVisualGOC::GetEffectGoc()
	{
		return pPlayer->GetPlayerGOC<CEffectGOC>();
	}

	inline game::GOCAnimationScript* CVisualGOC::GetHumanAnimationPtr() const
	{
		auto* pVisual = GetHumanVisual();
		if (!pVisual && !pVisual->pGocHolder)
			return nullptr;

		return pVisual->pGocHolder->GetUnit(0).m_rpAnimScript.get();
	}

	inline game::GOCAnimationScript& CVisualGOC::GetHumanAnimation() const
	{
		return *GetHumanVisual()->pGocHolder->GetUnit(0).m_rpAnimScript.get();
	}

	inline const char* CVisualGOC::GetCurrentVisualName() const
	{
		if (m_rpHumanVisual)
			return m_rpHumanVisual->pVisualName;

		return { nullptr };
	}

	inline void CVisualGOC::EndBlink()
	{
		Flags.set(2, false);
		Unk1 = 0.0f;
		m_rpCurrentVisual->SetBlinkVisible(true);
	}
}
