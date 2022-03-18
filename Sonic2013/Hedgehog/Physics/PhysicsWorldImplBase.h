#pragma once

namespace app
{
	class CPhysicsWorld;
}

namespace app::game
{
	using namespace csl::math;
	using namespace csl::ut;

	class PhysicsWorldImplBase : public fnd::ReferencedObject
	{
	public:
		virtual void Init(CPhysicsWorld& in_world) {}
		virtual void Destroy() {}
		virtual void Update(float in_delta) {}
		virtual void Collide(uint in_a1) {}
		virtual void SetGroupFilter(int in_a1, int in_a2, bool in_a3) = 0;
		virtual void AddRaycastJob(PhysicsRaycastJob* in_pJob) = 0;
		virtual bool Raycast(const Vector3& in_from, const Vector3& in_to, uint in_filter, PhysicsRaycastOutput* out_pOutput) const = 0;
		virtual bool RaycastAll(const Vector3& in_from, const Vector3& in_to, uint in_filter, MoveArray<PhysicsRaycastOutput>* out_pOutputs) const = 0;
		virtual bool OverlapSphere(const Sphere& in_sphere, uint in_filter, MoveArray<PhysicsOverlapOutput>* out_pOutputs) const = 0;
		virtual bool OverlapCapsule(const Capsule& in_capsule, uint in_filter, MoveArray<PhysicsOverlapOutput>* out_pOutputs) const = 0;
		virtual bool OverlapAabb(const Aabb& in_bounds, uint in_filter, MoveArray<PhysicsOverlapOutput>* out_pOutputs) const = 0;
		virtual bool CheckSphere(const Sphere& in_sphere, uint in_filter) const = 0;
		virtual bool SweepSphere(const Sphere& in_sphere, const Vector3& in_bounds, uint in_filter, MoveArray<PhysicsSweepOutput>* out_pOutputs) const = 0;
		virtual bool SweepCapsule(const Capsule& in_capsule, const Vector3& in_bounds, uint in_filter, MoveArray<PhysicsSweepOutput>* out_pOutputs) const = 0;
		virtual void ShapeAddedCallback(ColliShape* in_pShape) {}
		virtual void ShapeRemovedCallback(ColliShape* in_pShape) {}
	};
}