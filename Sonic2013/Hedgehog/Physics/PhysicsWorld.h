#pragma once

namespace app
{
	class CPhysicsWorld : public fnd::GameService
	{
	private:
		inline static fnd::GameServiceClass* ms_pStaticClass = reinterpret_cast<fnd::GameServiceClass*>(ASLR(0x00FD4040));

	public:
		ut::RefPtr<game::PhysicsWorldImplBase> rpImpl{};
		INSERT_PADDING(4){}; // RefPtr<HandleManager<ColliShape>>
		ut::RefPtr<game::PhysicsDebugDraw> rpDebugDraw{};

		CPhysicsWorld() : GameService(0)
		{

		}

		void Collide(uint in_a1) const
		{
			rpImpl->Collide(in_a1);
		}

		void SetGroupFilter(int in_a1, int in_a2, bool in_a3) const
		{
			rpImpl->SetGroupFilter(in_a1, in_a2, in_a3);
		}

		void AddRaycastJob(game::PhysicsRaycastJob* in_pJob) const
		{
			rpImpl->AddRaycastJob(in_pJob);
		}

		bool RaycastAll(const csl::math::Vector3& in_rFrom, const csl::math::Vector3& in_rTo, uint in_filter, csl::ut::MoveArray<game::PhysicsRaycastOutput>* out_pOutputs) const
		{
			return rpImpl->RaycastAll(in_rFrom, in_rTo, in_filter, out_pOutputs);
		}

		bool Raycast(const csl::math::Vector3& in_rFrom, const csl::math::Vector3& in_rTo, uint in_filter, game::PhysicsRaycastOutput* out_pOutput) const
		{
			return rpImpl->Raycast(in_rFrom, in_rTo, in_filter, out_pOutput);
		}

		bool OverlapSphere(const csl::math::Sphere& in_rSphere, uint in_filter, csl::ut::MoveArray<game::PhysicsOverlapOutput>* out_pOutputs) const
		{
			return rpImpl->OverlapSphere(in_rSphere, in_filter, out_pOutputs);
		}

		bool OverlapCapsule(const csl::math::Capsule& in_rCapsule, uint in_filter, csl::ut::MoveArray<game::PhysicsOverlapOutput>* out_pOutputs) const
		{
			return rpImpl->OverlapCapsule(in_rCapsule, in_filter, out_pOutputs);
		}

		bool OverlapAabb(const csl::math::Aabb& in_rBounds, uint in_filter, csl::ut::MoveArray<game::PhysicsOverlapOutput>* out_pOutputs) const
		{
			return rpImpl->OverlapAabb(in_rBounds, in_filter, out_pOutputs);
		}

		bool CheckSphere(const csl::math::Sphere& in_rSphere, uint in_filter) const
		{
			return rpImpl->CheckSphere(in_rSphere, in_filter);
		}

		bool SweepSphere(const csl::math::Sphere& in_rSphere, const csl::math::Vector3& in_rBounds, uint in_filter, csl::ut::MoveArray<game::PhysicsSweepOutput>* out_pOutputs) const
		{
			return rpImpl->SweepSphere(in_rSphere, in_rBounds, in_filter, out_pOutputs);
		}

		bool SweepCapsule(const csl::math::Capsule& in_rCapsule, const csl::math::Vector3& in_rBounds, uint in_filter, csl::ut::MoveArray<game::PhysicsSweepOutput>* out_pOutputs) const
		{
			return rpImpl->SweepCapsule(in_rCapsule, in_rBounds, in_filter, out_pOutputs);
		}

		static fnd::GameServiceClass& staticClass()
		{
			return *ms_pStaticClass;
		}
	};
}