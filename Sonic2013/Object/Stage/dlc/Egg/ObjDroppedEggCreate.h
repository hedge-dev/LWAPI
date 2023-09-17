#pragma once

namespace app::egg
{
	inline ObjDroppedEgg* CreateDroppedEgg(GameDocument& in_rDocument, const DroppedEggCInfo& in_rInfo)
	{
		auto* pObject = new ObjDroppedEgg(&in_rInfo);
		if (!pObject)
			return { nullptr };

		in_rDocument.AddGameObject(pObject);
		return pObject;
	}
}