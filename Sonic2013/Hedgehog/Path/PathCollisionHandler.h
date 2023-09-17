#pragma once

namespace app::game
{
	struct PathRaycastInput
	{
		csl::math::Vector3 From{};
		csl::math::Vector3 To{};
		char Unk1{};
		int Unk2{};
	};

	struct PathRaycastOutput
	{
		PathComponent* pComponent{};
		float Distance{};
		float Unk3{};
		float Unk4{ 1.0f };
		csl::math::Vector3 HitPoint{};
	};

	class PathCollisionInput;
	class PathCollisionOutput;
	class PathOverlapAabbInput;
	class PathComponent;
	class PathComponentCollector;
	class PathSegmentCollector;

	class PathCollisionHandler : public fnd::ReferencedObject
	{
	public:
		virtual ~PathCollisionHandler() = default;
		virtual void AddObject(PathComponent* in_pComponent) = 0;
		virtual void RemoveObject(PathComponent* in_pComponent) = 0;
		virtual bool CastRayOnWorld(const PathRaycastInput& in_rInput, PathRaycastOutput* out_pOutput) const = 0;
		virtual bool CastRay(const csl::math::Vector3& in_rFrom, const csl::math::Vector3& in_rTo, PathComponent* in_pComponent, PathRaycastOutput* out_pOutput) const = 0;
		virtual void OverlapAabb(const PathOverlapAabbInput& in_rAabb, csl::ut::MoveArray<PathComponent*>& in_rComponents) const = 0;
		virtual void OverlapSphereOnWorld(const csl::math::Sphere& in_rSphere, PathComponentCollector& in_rCollector) const = 0;
		virtual void OverlapSphereSegments(const csl::math::Sphere& in_rSphere, PathComponent* in_pComponent, PathSegmentCollector& in_rCollector) const = 0;
		virtual bool GetClosestObject(const csl::math::Sphere& in_rSphere, const PathCollisionInput& in_rInput, PathCollisionOutput* out_pOutput) const = 0;
		virtual void Update(const fnd::SUpdateInfo& in_rUpdateInfo) = 0;
	};
}