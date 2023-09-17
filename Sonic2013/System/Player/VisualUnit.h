#pragma once

namespace app::Player
{
	class CVisualUnit : public fnd::ReferencedObject, public CVisualBase
	{
	public:
		CPlayerVisual* pPlayerVisual{};
		const char* pUnitName{};

		CVisualUnit(CPlayer* in_pPlayer, CVisualGOC* in_pVisualGoc, CPlayerVisual* in_pPlayerVisual, const char* in_pUnitName)
			: CVisualBase(in_pPlayer, in_pVisualGoc)
			, pPlayerVisual(in_pPlayerVisual)
			, pUnitName(in_pUnitName)
		{

		}
	};
}