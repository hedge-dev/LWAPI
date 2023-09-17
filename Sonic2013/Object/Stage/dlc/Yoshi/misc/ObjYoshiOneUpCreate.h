#pragma once

namespace app
{
	inline ObjYoshiOneUp* ObjYoshiOneUp::Create(GameDocument& in_rDocument, const ObjYoshiOneUp::CInfo& in_rInfo)
	{
		auto* pObject = new ObjYoshiOneUp(in_rInfo);
		if (!pObject)
			return { nullptr };

		in_rDocument.AddGameObject(pObject);
		return pObject;
	}
}