#pragma once

namespace app::zelda_popupitem
{
	inline ObjZeldaPopupItem* CreateZeldaPopupItem(csl::fnd::IAllocator* in_pAllocator, GameDocument& in_rDocument, const ZeldaPopupItemCinfo& in_rCreateInfo)
	{
		auto* pObject = new(in_pAllocator) ObjZeldaPopupItem(&in_rCreateInfo);
		if (!pObject)
			return { nullptr };

		in_rDocument.AddGameObject(pObject);
		return pObject;
	}
}