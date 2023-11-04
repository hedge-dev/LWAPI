#include "Physics.h"
#pragma once

namespace app::Player
{
	inline void CPhysics::UpdateViewMatrix()
	{
		auto* pCamera = pPlayer->GetWorld()->GetCamera(Unk1);
		if (pCamera)
		{
			CameraViewMtx = pCamera->ViewMtx;
		}
		else
		{
			CameraViewMtx = math::Matrix34OrthonormalDirection({ 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f });
		}
	}
}