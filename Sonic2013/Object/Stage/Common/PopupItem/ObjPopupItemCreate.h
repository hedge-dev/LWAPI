#pragma once

namespace app::popup_item
{
	inline static ObjPopupItem* Create(GameDocument& in_rDocument, const SParam& in_rParam)
	{
		auto* pObject = new ObjPopupItem(in_rParam);
		if (!pObject)
			return { nullptr };

		in_rDocument.AddGameObject(pObject);
		return pObject;
	}
}