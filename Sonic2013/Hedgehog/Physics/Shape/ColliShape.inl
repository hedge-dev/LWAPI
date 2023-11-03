#pragma once

namespace app::game
{
	inline GameObject* ColliShapeBase::GetGameObject() const
	{
		if (m_pOwner)
			return m_pOwner->GetGameObject();

		return m_pPhysicsOwner->GetGameObject();
	}

}