#pragma once

namespace app::PlayerUtil
{
	inline bool SetDirection(Player::CPhysics* in_pPhysics, const csl::math::Vector3& in_rUnk1, const csl::math::Vector3& in_rGravityUpDir)
	{
		csl::math::Vector3 cross{ in_rGravityUpDir.cross(in_rUnk1) };
		if (!math::Vector3NormalizeIfNotZero(cross, &cross))
			return false;
		
		csl::math::Vector3 forward{ cross.cross(in_rGravityUpDir) };
		
		csl::math::Matrix34 rotationMatrix{};
		rotationMatrix.SetColumn(0, forward);
		rotationMatrix.SetColumn(1, in_rGravityUpDir);
		rotationMatrix.SetColumn(2, { forward / forward.Length() });
		rotationMatrix.SetColumn(3, *csl::math::Vector3::Zero);

		in_pPhysics->SetRotation(rotationMatrix);
		return true;
	}
	
	inline bool RaycastPhantom(game::PhysicsRaycastOutput& in_rOutput, Player::CPlayer* in_pPlayer, const csl::math::Vector3& in_rFrom, const csl::math::Vector3& in_rTo, uint in_filter)
	{
		auto* pCollisionGoc = in_pPlayer->GetPlayerGOC<Player::CCollisionGOC>();
		if (!pCollisionGoc)
			return false;

		return pCollisionGoc->Collision.Raycast(in_rFrom, in_rTo, in_filter, &in_rOutput);
	}
}