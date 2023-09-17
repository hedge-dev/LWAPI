#pragma once

namespace app::Collision
{
	class CCollisionWorld;
}

namespace app::game
{
	class ColliWorldImplBase : public fnd::ReferencedObject
	{
	public:
		virtual void Init(Collision::CCollisionWorld& in_world) {}
		virtual void Destroy() {}
		virtual void Update(float in_delta) {}
		virtual bool OverlapFrustum(const csl::math::Frustum& in_frustum, uint in_filter, MoveArray<ColliOverlapOutput>* out_pOutputs) const = 0;
		virtual bool OverlapSphere(const Sphere& in_sphere, uint in_filter, MoveArray<ColliOverlapOutput>* out_pOutputs) const = 0;
	};
}