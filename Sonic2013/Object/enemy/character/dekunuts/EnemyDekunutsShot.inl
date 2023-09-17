#pragma once

namespace app::dekunuts_shot
{
	EnemyDekunutsShot* Create(const CreateInfo& in_rCreateInfo, GameDocument* in_pDocument, csl::fnd::IAllocator* in_pAllocator)
	{
		auto* pObject = new(in_pAllocator) EnemyDekunutsShot(in_rCreateInfo);
		if (!pObject)
			return { nullptr };

		in_pDocument->AddGameObject(pObject);
		return pObject;
	}
}
