#pragma once

namespace app::Player
{
	class CPhysics;
}

namespace app::PlayerUtil
{
	struct Hermite3Parameter
	{
		csl::math::Vector3 Unk1{};
		csl::math::Vector3 Unk2{};
		csl::math::Vector3 Unk3{};
		csl::math::Vector3 Unk4{};
	};

	struct Hermite3
	{
		Hermite3Parameter Parameter{};
		csl::math::Vector3 Unk1[4]{};
		float Unk2{};
	};

	static bool IsEnablePhantomDig(int in_groundAttribute)
	{
		return in_groundAttribute == 5 || in_groundAttribute == 6 || in_groundAttribute == 33;
	}

	bool SetDirection(Player::CPhysics* in_pPhysics, const csl::math::Vector3& in_rUnk1, const csl::math::Vector3& in_rGravityUpDir);

	bool RaycastPhantom(game::PhysicsRaycastOutput& in_rOutput, Player::CPlayer* in_pPlayer, const csl::math::Vector3& in_rFrom, const csl::math::Vector3& in_rTo, uint in_filter);
}