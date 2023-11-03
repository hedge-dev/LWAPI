#pragma once

namespace app::Collision
{
	class CCollisionWorld : public fnd::GameService
	{
	private:
		inline static fnd::GameServiceClass* ms_pStaticClass = reinterpret_cast<fnd::GameServiceClass*>(ASLR(0x00FD4030));

	public:
		ut::RefPtr<game::ColliWorldImplBase> rpImpl{};
		INSERT_PADDING(4){}; // RefPtr<HandleManager<ColliShape>>
		ut::RefPtr<game::CollideDebugDraw> rpDebugDraw{};

		CCollisionWorld() : GameService(0), rpImpl(new(GetAllocator()) game::ColliWorldImplHavok())
		{
			rpImpl->Init(static_cast<CCollisionWorld&>(*this));
		}

		bool OverlapFrustum(const csl::math::Frustum& in_rCapsule, uint in_filter, csl::ut::MoveArray<game::ColliOverlapOutput>* out_pOutputs) const
		{
			return rpImpl->OverlapFrustum(in_rCapsule, in_filter, out_pOutputs);
		}

		bool OverlapSphere(const csl::math::Sphere& in_rSphere, uint in_filter, csl::ut::MoveArray<game::ColliOverlapOutput>* out_pOutputs) const
		{
			return rpImpl->OverlapSphere(in_rSphere, in_filter, out_pOutputs);
		}

		void Update(const fnd::SUpdateInfo& in_rUpdateInfo) override
		{
			rpImpl->Update(in_rUpdateInfo.DeltaTime);
		}

		static fnd::GameServiceClass& staticClass()
		{
			return *ms_pStaticClass;
		}
	};
}