#pragma once

namespace app::game
{
	class CPhysicsWorld : public fnd::GameService
	{
	public:
		inline static fnd::GameServiceClass* ms_pStaticClass = reinterpret_cast<fnd::GameServiceClass*>(ASLR(0x00FD4040));

		ut::RefPtr<PhysicsWorldImplBase> m_rpImpl{};
		INSERT_PADDING(4){}; // RefPtr<HandleManager<ColliShape>>
		ut::RefPtr<PhysicsDebugDraw> m_rpDebugDraw{};

		CPhysicsWorld() : GameService(0)
		{

		}

		void Collide(uint in_a1) const
		{
			m_rpImpl->Collide(in_a1);
		}

		void SetGroupFilter(int in_a1, int in_a2, bool in_a3) const
		{
			m_rpImpl->SetGroupFilter(in_a1, in_a2, in_a3);
		}

		void AddRaycastJob(PhysicsRaycastJob* in_pJob) const
		{
			m_rpImpl->AddRaycastJob(in_pJob);
		}

		bool RaycastAll(const Vector3& in_from, const Vector3& in_to, uint in_filter, MoveArray<PhysicsRaycastOutput>* out_pOutputs) const
		{
			return m_rpImpl->RaycastAll(in_from, in_to, in_filter, out_pOutputs);
		}

		bool Raycast(const Vector3& in_from, const Vector3& in_to, uint in_filter, PhysicsRaycastOutput* out_pOutput) const
		{
			return m_rpImpl->Raycast(in_from, in_to, in_filter, out_pOutput);
		}

		bool OverlapSphere(const Sphere& in_sphere, uint in_filter, MoveArray<PhysicsOverlapOutput>* out_pOutputs) const
		{
			return m_rpImpl->OverlapSphere(in_sphere, in_filter, out_pOutputs);
		}

		bool OverlapCapsule(const Capsule& in_capsule, uint in_filter, MoveArray<PhysicsOverlapOutput>* out_pOutputs) const
		{
			return m_rpImpl->OverlapCapsule(in_capsule, in_filter, out_pOutputs);
		}

		bool OverlapAabb(const Aabb& in_aabb, uint in_filter, MoveArray<PhysicsOverlapOutput>* out_pOutputs) const
		{
			return m_rpImpl->OverlapAabb(in_aabb, in_filter, out_pOutputs);
		}

		bool CheckSphere(const Sphere& in_sphere, uint in_filter) const
		{
			return m_rpImpl->CheckSphere(in_sphere, in_filter);
		}

		bool SweepSphere(const Sphere& in_sphere, const Vector3& in_bounds, uint in_filter, MoveArray<PhysicsSweepOutput>* out_pOutputs) const
		{
			return m_rpImpl->SweepSphere(in_sphere, in_bounds, in_filter, out_pOutputs);
		}

		bool SweepCapsule(const Capsule& in_capsule, const Vector3& in_bounds, uint in_filter, MoveArray<PhysicsSweepOutput>* out_pOutputs) const
		{
			return m_rpImpl->SweepCapsule(in_capsule, in_bounds, in_filter, out_pOutputs);
		}

		static fnd::GameServiceClass& staticClass()
		{
			return *ms_pStaticClass;
		}
	};
}