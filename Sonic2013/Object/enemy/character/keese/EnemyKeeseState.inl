#include "EnemyKeese.h"
#pragma once

namespace app
{
	inline void EnemyKeese::State::Idle::OnEnter(EnemyKeese& in_rObj, int in_unk)
	{
		in_rObj.GetCenterPositionFrame()->SetLocalTranslation(ms_CenterPosition);
		in_rObj.GetComponent<game::GOCAnimationScript>()->ChangeAnimation("IDLE");
	}

	inline bool EnemyKeese::State::Idle::Step(EnemyKeese& in_rObj, float in_deltaTime)
	{
		csl::math::Vector3 targetPosition{};
		
		auto* pTransformGoc = in_rObj.GetComponent<fnd::GOCTransform>();
		if (!in_rObj.GetComponent<GOCEnemyTarget>() || !in_rObj.Path.Component.IsValid() || !in_rObj.IsFindTargetGood(&targetPosition) || !pTransformGoc)
			return false;

		csl::math::Vector3 position{ pTransformGoc->Frame.Unk3.Mtx.GetTransVector() };

		csl::math::Vector3 point{}, normal{}, tangent{};
		in_rObj.Path.GetPNT(in_rObj.Path.Distance, &point, &normal, &tangent);

		csl::math::Vector3 offset{ csl::math::Vector3(position - point).Normalize() };
		csl::math::Vector3 targetOffset{ csl::math::Vector3(targetPosition - point).Normalize() };

		csl::math::Matrix34 centerMtx{ in_rObj.GetCenterPositionFrame()->Unk3.Mtx };
		csl::math::Vector3 frontVector{ centerMtx.GetColumn(2) };
		csl::math::Vector3 centerPosition{ centerMtx.GetTransVector() };
		csl::math::Vector3 centerOffset{ targetPosition - centerPosition };

		float scalar = csl::math::Select(centerOffset.dot(frontVector), fabs(10.0f), csl::math::Nabs(10.0f));
		frontVector* scalar;

		csl::math::Vector3 rayOffset{ csl::math::Vector3(centerOffset - tangent * centerOffset.dot(tangent)).Normalize() };

		csl::math::Vector3 from{ centerPosition + rayOffset * 9.0f };
		csl::math::Vector3 to{ centerPosition + rayOffset + centerOffset };

		if (csl::math::Vector3(from - to).squaredNorm() <= 0.000001f || ObjUtil::RaycastHitCollision(*in_rObj.GetDocument(), from, to, 0xC996))
			return false;

		auto* pPhysicsWorld = in_rObj.GetDocument()->GetService<CPhysicsWorld>();
		if (!pPhysicsWorld->CheckSphere({ { centerPosition + rayOffset + centerOffset }, 4.5f }, 0xC996) && in_rObj.pMovementController)
		{
			in_rObj.pMovementController->SetTargetDirection(targetPosition, in_rObj.Path.Distance);
			in_rObj.pMovementController->StopMove();

			ChangeState(in_rObj, 1);
		}

		return false;
	}

	inline void EnemyKeese::State::FallStart::OnEnter(EnemyKeese& in_rObj, int in_unk)
	{
		in_rObj.GetComponent<game::GOCAnimationScript>()->ChangeAnimation(ms_pAnimationName);

		pVisualGoc = in_rObj.GetComponent<fnd::GOCVisualModel>();

		RemainingTime = 0.2f;
		ElapsedTime = 0.0f;
	}

	inline bool EnemyKeese::State::FallStart::Step(EnemyKeese& in_rObj, float in_deltaTime)
	{
		if (RemainingTime > 0.0f)
		{
			RemainingTime -= in_deltaTime;
			if (RemainingTime <= 0.0f && in_rObj.pMovementController)
				in_rObj.pMovementController->StartMove();
		}

		ElapsedTime += in_deltaTime;

		pVisualGoc->SetLocalTranslation({ -csl::math::Vector3::UnitY() * 5.0f * sinf(csl::math::Clamp(ElapsedTime / (2.0f / 3.0f), 0.0f, 1.0f) * MATHF_PI) });

		if (!in_rObj.GetComponent<game::GOCAnimationScript>()->IsCurrentAnimation(ms_pAnimationName))
			ChangeState(in_rObj, 2);

		return false;
	}

	inline void EnemyKeese::State::Fall::OnEnter(EnemyKeese& in_rObj, int in_unk)
	{
		ElapsedTime = 0.0f;

		if (in_rObj.pMovementController)
			in_rObj.pMovementController->StartMove();
	}

	inline bool EnemyKeese::State::Fall::Step(EnemyKeese& in_rObj, float in_deltaTime)
	{
		ElapsedTime += in_deltaTime;

		in_rObj.GetCenterPositionFrame()->SetLocalTranslation({ 0.0f, 5.0f * (1.0f - csl::math::Clamp(ElapsedTime / 0.2f, 0.0f, 1.0f)), 0.0f });

		return false;
	}

	inline void EnemyKeese::State::Seek::OnEnter(EnemyKeese& in_rObj, int in_unk)
	{
		in_rObj.GetComponent<game::GOCAnimationScript>()->ChangeAnimation(ms_pAnimationName);
		
		auto* pTransformGoc = in_rObj.GetComponent<fnd::GOCTransform>();
		if (!pTransformGoc || in_rObj.pMovementController)
		{
			csl::math::Vector3 point{}, normal{}, tangent{};
			in_rObj.Path.GetPNT(in_rObj.Path.Distance, &point, &normal, &tangent);

			float scalar = csl::math::Select(tangent.dot(pTransformGoc->Frame.Unk3.Mtx.GetColumn(2)), fabs(1.0f), csl::math::Nabs(1.0f));
			in_rObj.pMovementController->SetTargetDistance((in_rObj.MoveRange * 0.5f - (in_rObj.Path.Distance - in_rObj.PathDistance) * scalar) * scalar);
			in_rObj.pMovementController->StartMove();
		}
	}

	inline bool EnemyKeese::State::Seek::Step(EnemyKeese& in_rObj, float in_deltaTime)
	{
		in_rObj.UpdateGravityPathDistance(in_rObj.MoveSpeed * in_deltaTime);
		return false;
	}

	inline void EnemyKeese::State::Return::OnEnter(EnemyKeese& in_rObj, int in_unk)
	{
		IsCollisionFound = false;
		Unk2 = false;

		HitPoint = { 0.0f, 0.0f, 0.0f };

		FallDistance = 0.0f;
		Unk5 = 0.0f;

		if (auto* pEnemyTargetGoc = in_rObj.GetComponent<GOCEnemyTarget>())
			pEnemyTargetGoc->SetEnableEyesight(false);
	}

	inline bool EnemyKeese::State::Return::Step(EnemyKeese& in_rObj, float in_deltaTime)
	{
		float fallSpeed{};

		in_rObj.UpdateGravityPathDistance(in_rObj.MoveSpeed * in_deltaTime);

		auto* pTransformGoc = in_rObj.GetComponent<fnd::GOCTransform>();
		csl::math::Matrix34 transformMtx{ pTransformGoc->Frame.Unk3.Mtx };

		if (!Unk2)
		{
			float fallSpeed = in_rObj.FallSpeed * in_deltaTime;
		
			if (IsCollisionFound)
			{
				float offset = csl::math::Vector3(HitPoint - transformMtx.GetTransVector()).squaredNorm();
				if (offset < powf(fallSpeed, 2.0f))
				{
					fallSpeed = csl::math::Sqrt(offset);
					Unk2 = true;
				}
			}

			pTransformGoc->SetLocalTranslation({ transformMtx * csl::math::Vector4({ -csl::math::Vector3::UnitY() * fallSpeed }, 1.0f) });
		
			FallDistance += fallSpeed;
			if (300.0f < FallDistance)
			{
				in_rObj.LostCeiling();
				return false;
			}
		}

		auto* pAnimationGoc = in_rObj.GetComponent<game::GOCAnimationScript>();

		if (pAnimationGoc->IsFinished() && Unk2)
		{
			if (in_rObj.pMovementController)
				in_rObj.pMovementController->ResetCurrent();
		
			ChangeState(in_rObj, 0);
			return false;
		}
		else
		{
			if (!IsCollisionFound)
			{
				csl::math::Vector3 to{ transformMtx * csl::math::Vector4({-csl::math::Vector3::UnitY() * 45.0f}, 1.0f) };
				
				game::PhysicsRaycastOutput output{};
				if (ObjUtil::RaycastNearestCollision(&output, *in_rObj.GetDocument(), transformMtx.GetTransVector(), to, 0xC992))
				{
					IsCollisionFound = true;
					HitPoint = output.HitPoint;
					pAnimationGoc->ChangeAnimation(ms_pAnimationName);
				}
			}
		}

		return false;
	}
}