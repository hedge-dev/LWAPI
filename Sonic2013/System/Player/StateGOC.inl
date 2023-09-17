#include "StateGOC.h"
#pragma once

namespace app::Player
{
	inline fnd::SoundHandle CStateGOC::PlaySE(const char* in_pName, bool in_unk)
	{
		if (!in_unk)
		{
			return pSound->Play(in_pName, 0.0f);
		}
		else if (StateUtil::IsBattleMode(*this))
		{
			game::SoundPlayInfo playInfo{ in_pName, { HH_SOUND_DEVICE_AUTO }, 0.0f };
			if (!GetPlayerNo())
				playInfo.Device.m_Device = 32;

			return pSound->Play(playInfo);
		}
		else
		{
			game::SoundPlayInfo playInfo{ in_pName, 33, 0.0f };
			return pSound->Play(playInfo);
		}
	}

	inline void CStateGOC::SetMoveCylinderTimer(float in_timer)
	{
		MoveCylinderTimer = in_timer;
		StateUtil::SetTerrainCollisionDisable(*this, true);
	}
}
