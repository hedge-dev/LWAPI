#include "Physics.h"
#pragma once

namespace app::Player
{
	inline void CPhysics::UpdateViewMatrix()
	{
		auto* pCamera = m_pPlayer->GetWorld()->GetCamera(m_Unk1);
		if (pCamera)
		{
			m_CameraViewMtx = pCamera->m_ViewMtx;
		}
		else
		{
			m_CameraViewMtx = math::Matrix34OrthonormalDirection({ 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f });
		}
	}
}