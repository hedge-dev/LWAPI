#pragma once

namespace app::Player
{
	class CPlayer;

	class CPlayerVehicle : public GameObject3D
	{
	public:
		GameObjectHandle<CPlayer> Owner{};
		csl::math::Matrix34 Transform{};
		int VehicleType{};

		CPlayerVehicle(CPlayer* in_pPlayer, int in_type);

		bool HaveOwner()
		{
			return Owner.IsValid();
		}

		CPlayer* GetOwner()
		{
			return Owner.Get();
		}
	};
}