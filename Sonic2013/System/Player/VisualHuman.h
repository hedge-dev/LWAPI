#pragma once

namespace app::Player
{
	class CVisualHuman : public CPlayerVisual
	{
	public:
		CVisualHuman(CPlayer* in_pPlayer, CVisualGOC* in_pVisualGoc) : CPlayerVisual(in_pPlayer, in_pVisualGoc, "CVisualHuman")
		{
			Setup();
		}

		CVisualHuman(CPlayer* in_pPlayer, CVisualGOC* in_pVisualGoc, const char* in_pVisualName) : CPlayerVisual(in_pPlayer, in_pVisualGoc, in_pVisualName)
		{
			Setup();
		}

		inline void Setup()
		{
			CreateEffectList(16);
			SetFlag(0, true);
			SetFlagSub(3, true);
		}
	};
}