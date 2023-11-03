#pragma once

namespace app::game
{
	inline GameObject* ColliShapeBase::GetGameObject() const
	{
		if (pOwner)
			return pOwner->GetGameObject();

		return pPhysicsOwner->GetGameObject();
	}

}