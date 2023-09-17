#pragma once

namespace app::egg
{
	inline ObjEgg* CreateEgg(GameDocument& in_rDocument, const EggCInfo& in_rInfo)
	{
		auto* pObject = new ObjEgg(&in_rInfo);
		if (!pObject)
			return { nullptr };

		in_rDocument.AddGameObject(pObject);
		return pObject;
	}
}