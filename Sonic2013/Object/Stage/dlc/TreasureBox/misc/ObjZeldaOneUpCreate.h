#pragma once

namespace app
{
	inline ObjZeldaOneUp* ObjZeldaOneUp::Create(GameDocument& in_rDocument, const ObjZeldaOneUp::CInfo& in_rInfo)
	{
		auto* pObject = new ObjZeldaOneUp(in_rInfo);
		if (!pObject)
			return { nullptr };

		in_rDocument.AddGameObject(pObject);
		return pObject;
	}
}