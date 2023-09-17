#include "PlayerVehicle.h"
#pragma once

namespace app::Player
{
	inline CPlayerVehicle::CPlayerVehicle(CPlayer* in_pPlayer, int in_type)
	{
		VehicleType = in_type;

		SetObjectCategory(6);
		if (in_pPlayer)
		{
			in_pPlayer->SetPlayerVehicle(this);
		}
	}
}