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

		return pVisual->pGocHolder->GetUnit(0).rpAnimScript.get();
	}

	inline game::GOCAnimationScript& CVisualGOC::GetHumanAnimation() const
	{
		return *GetHumanVisual()->pGocHolder->GetUnit(0).rpAnimScript.get();
	}

	inline const char* CVisualGOC::GetCurrentVisualName() const
	{
		if (rpHumanVisual)
			return rpHumanVisual->pVisualName;

		return { nullptr };
	}

	inline void CVisualGOC::EndBlink()
	{
		Flags.set(2, false);
		Unk1 = 0.0f;
		rpCurrentVisual->SetBlinkVisible(true);
	}
}
