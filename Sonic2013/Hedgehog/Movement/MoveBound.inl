#include "MoveBound.h"
#pragma once

inline bool app::game::SearchPlane(csl::math::Plane* out_pPlane, app::GameDocument& in_rDocument, const csl::math::Vector3& in_rFrom, const csl::math::Vector3& in_rTo)
{
	app::game::PhysicsRaycastOutput raycastOutput{};
	if (app::ObjUtil::RaycastNearestCollision(&raycastOutput, in_rDocument, in_rFrom, in_rTo, 0xC992))
	{
		*out_pPlane = csl::math::Plane::FromPointNormal(raycastOutput.HitPoint, raycastOutput.Normal);
		return true;
	}

	return false;
}

inline bool app::game::SerachPlaneAndGrindPath(csl::math::Plane* out_pPlane, app::GameDocument& in_rDocument, const csl::math::Vector3& in_rFrom, const csl::math::Vector3& in_rTo)
{
	csl::ut::Bitset<uint8> flags{};
	app::game::PathEvaluator pathEvaluator{};

	app::game::PhysicsRaycastOutput raycastOutput{};
	if (app::ObjUtil::RaycastNearestCollision(&raycastOutput, in_rDocument, in_rFrom, in_rTo, 0xC992))
		flags.set(0);

	app::game::PathRaycastOutput pathRaycastOutput{};
	csl::math::Vector3 distance(in_rTo - in_rFrom);
	if (app::ObjUtil::SearchNearestGrindPath(in_rDocument, in_rFrom, distance, &pathRaycastOutput))
	{
		flags.set(1);
		pathEvaluator.SetPathObject(pathRaycastOutput.pComponent);
		pathEvaluator.SetDistance(pathRaycastOutput.Distance);
	}

	if (flags.test(0) && flags.test(1))
	{
		auto worldPos = pathEvaluator.GetWorldPosition(pathEvaluator.Distance);
		flags.reset(pathEvaluator.Distance <= (worldPos - in_rFrom).norm());
	}

	if (flags.test(0))
	{
		csl::math::Plane plane{};
		plane.FromPointNormal(raycastOutput.HitPoint, raycastOutput.Normal);
		plane.Distance = raycastOutput.Distance;
		return true;
	}

	if (flags.test(1))
	{
		auto worldPos = pathEvaluator.GetWorldPosition(pathEvaluator.Distance);

		csl::math::Plane plane{};
		plane.FromPointNormal(worldPos, raycastOutput.Normal);
		plane.Distance = raycastOutput.Distance;
		return true;
	}

	return false;
}