#pragma once

namespace app::game
{
	class PathManager : public fnd::GameService
	{
	private:
		inline static fnd::GameServiceClass* ms_pStaticClass = reinterpret_cast<fnd::GameServiceClass*>(ASLR(0x00FD9C54));
		inline static FUNCTION_PTR(PathComponent*, __thiscall, ms_fpGetPathObject, ASLR(0x004D9A30), const PathManager*, uint);

	public:
		csl::ut::PointerMap<size_t, PathComponent*> Components{ GetAllocator() };
		INSERT_PADDING(4);
		csl::ut::StringMap<PathComponent*> ComponentNames{ GetAllocator() };
		ut::RefPtr<PathCollisionHandler> rpCollisionHandler{};
		ut::RefPtr<PathDebugDraw> rpDebugDraw{};

		PathManager() : GameService(0)
		{
			rpCollisionHandler = new(GetAllocator()) PathCollisionHandlerStandard();
		}

		void AddObject(PathComponent* in_pComponent)
		{
			if (auto componentUID = in_pComponent->GetUID())
				Components.insert(componentUID, in_pComponent);

			const char* pName = in_pComponent->GetName();
			ComponentNames.insert(pName, in_pComponent);

			in_pComponent->pManager = this;
			
			if (rpCollisionHandler)
				rpCollisionHandler->AddObject(in_pComponent);
		}

		void RemoveObject(PathComponent* in_pComponent)
		{
			const char* pName = in_pComponent->GetName();
			ComponentNames.erase(pName);
			
			if (auto componentUID = in_pComponent->GetUID())
				Components.erase(componentUID);

			in_pComponent->pManager = nullptr;

			if (rpCollisionHandler)
				rpCollisionHandler->RemoveObject(in_pComponent);
		}
		
		bool CastRay(const PathRaycastInput& in_rInput, PathRaycastOutput* out_pOutput) const
		{
			if (rpCollisionHandler)
				return rpCollisionHandler->CastRayOnWorld(in_rInput, out_pOutput);

			return false;
		}

		bool GetClosestObject(const csl::math::Sphere& in_rSphere, const PathCollisionInput& in_rColliInput, PathCollisionOutput* out_pColliOutput) const
		{
			if (rpCollisionHandler)
				return rpCollisionHandler->GetClosestObject(in_rSphere, in_rColliInput, out_pColliOutput);
		
			return false;
		}

		PathComponent* GetPathObject(const char* in_pName)
		{
			return ComponentNames.find(in_pName);
		}

		PathComponent* GetPathObject(uint in_uid) const
		{
			return ms_fpGetPathObject(this, in_uid);
			//return Components.find(in_uid);
		}

		void OverlapSphere(const csl::math::Sphere& in_rSphere, PathComponentCollector& in_rCollector) const
		{
			if (rpCollisionHandler)
				rpCollisionHandler->OverlapSphereOnWorld(in_rSphere, in_rCollector);
		}

		bool ProcessMessage(fnd::Message& in_rMessage) override
		{
			if (in_rMessage.GetType() != 0x2007)
				return false;

			return GameService::ProcessMessage(in_rMessage);
		}

		void Update(const fnd::SUpdateInfo& in_rUpdateInfo) override
		{
			if (rpCollisionHandler)
				rpCollisionHandler->Update(in_rUpdateInfo);
		}

		static fnd::GameServiceClass& staticClass()
		{
			return *ms_pStaticClass;
		}
	};
}