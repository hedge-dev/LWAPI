#pragma once

namespace app::game
{
	class ColliWorldImplHavok : public ColliWorldImplBase
	{
	private:
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpOverlapFrustum, ASLR(0x004B2AB0), const ColliWorldImplHavok*, const csl::math::Frustum&, uint, MoveArray<ColliOverlapOutput>*);
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpOverlapSphere, ASLR(0x004B2D10), const ColliWorldImplHavok*, const csl::math::Sphere&, uint, MoveArray<ColliOverlapOutput>*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpAttachToPhysicsWorld, ASLR(0x004B27D0), ColliWorldImplHavok*, Collision::CCollisionWorld&);

		INSERT_PADDING(4); // hkRefPtr<hkpWorld>

	public:
		void Init(Collision::CCollisionWorld& in_world) override {}
		void Destroy() override {}
		void Update(float in_delta) override {}

		bool OverlapFrustum(const csl::math::Frustum& in_frustum, uint in_filter, MoveArray<ColliOverlapOutput>* out_pOutputs) const override
		{
			return ms_fpOverlapFrustum(this, in_frustum, in_filter, out_pOutputs);
		}

		bool OverlapSphere(const Sphere& in_sphere, uint in_filter, MoveArray<ColliOverlapOutput>* out_pOutputs) const override
		{
			return ms_fpOverlapSphere(this, in_sphere, in_filter, out_pOutputs);
		}

		void AttachToPhysicsWorld(Collision::CCollisionWorld& in_rCollisionWorld)
		{
			ms_fpAttachToPhysicsWorld(this, in_rCollisionWorld);
		}
	};
}