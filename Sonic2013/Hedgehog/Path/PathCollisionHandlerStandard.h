#pragma once

namespace app::game
{
	class PathCollisionHandlerStandard : public PathCollisionHandler
	{
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpAddObject, ASLR(0x004DA6F0), PathCollisionHandlerStandard*, PathComponent*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpReturnObject, ASLR(0x004DA770), PathCollisionHandlerStandard*, PathComponent*);
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpCastRayOnWorld, ASLR(0x004DAB90), const PathCollisionHandlerStandard*, const PathRaycastInput&, PathRaycastOutput*);
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpCastRay, ASLR(0x004DAC70), const PathCollisionHandlerStandard*, const csl::math::Vector3&, const csl::math::Vector3&, PathComponent*, PathRaycastOutput*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpOverlapAabb, ASLR(0x004DACA0), const PathCollisionHandlerStandard*, const PathOverlapAabbInput& in_rAabb, csl::ut::MoveArray<PathComponent*>& in_rComponents);
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpGetClosestObject, ASLR(0x004DB0D0), const PathCollisionHandlerStandard*, const csl::math::Sphere& in_rSphere, const PathCollisionInput& in_rInput, PathCollisionOutput* out_pOutput);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpUpdate, ASLR(0x004DA7A0), PathCollisionHandlerStandard*, const fnd::SUpdateInfo&);
	
	public:
		ut::RefPtr<ut::AabbTree> rpAabbTree{};
		csl::fnd::PoolHeapBase Heap{};
		INSERT_PADDING(4);

		PathCollisionHandlerStandard()
		{
			rpAabbTree = ut::AabbTree::Create(GetAllocator(), 512, 6);
			void* pBuffer = GetAllocator()->Alloc(4096, 4);
			Heap.Initialize(pBuffer, 512, 8, 4);
		}

		void AddObject(PathComponent* in_pComponent) override
		{
			ms_fpAddObject(this, in_pComponent);
		}

		void RemoveObject(PathComponent* in_pComponent) override
		{
			ms_fpReturnObject(this, in_pComponent);
		}

		bool CastRayOnWorld(const PathRaycastInput& in_rInput, PathRaycastOutput* out_pOutput) const override
		{
			return ms_fpCastRayOnWorld(this, in_rInput, out_pOutput);
		}
		
		bool CastRay(const csl::math::Vector3& in_rFrom, const csl::math::Vector3& in_rTo, PathComponent* in_pComponent, PathRaycastOutput* out_pOutput) const override
		{
			return ms_fpCastRay(this, in_rFrom, in_rTo, in_pComponent, out_pOutput);
		}
		
		void OverlapAabb(const PathOverlapAabbInput& in_rAabb, csl::ut::MoveArray<PathComponent*>& in_rComponents) const override
		{
			ms_fpOverlapAabb(this, in_rAabb, in_rComponents);
		}

		void OverlapSphereOnWorld(const csl::math::Sphere& in_rSphere, PathComponentCollector& in_rCollector) const override
		{
			return;
		}

		void OverlapSphereSegments(const csl::math::Sphere& in_rSphere, PathComponent* in_pComponent, PathSegmentCollector& in_rCollector) const override
		{
			return;
		}

		bool GetClosestObject(const csl::math::Sphere& in_rSphere, const PathCollisionInput& in_rInput, PathCollisionOutput* out_pOutput) const override
		{
			return ms_fpGetClosestObject(this, in_rSphere, in_rInput, out_pOutput);
		}

		void Update(const fnd::SUpdateInfo& in_rUpdateInfo) override
		{
			ms_fpUpdate(this, in_rUpdateInfo);
		}
	};
}