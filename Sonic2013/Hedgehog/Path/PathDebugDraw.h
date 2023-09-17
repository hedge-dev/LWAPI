#pragma once

namespace app::game
{
	class PathManager;
	class PathComponent;

	class PathDebugDraw : public fnd::ReferencedObject
	{
	public:
		csl::ut::PointerMap<PathComponent*, size_t> Components{ GetAllocator() };
		PathManager* pManager{};
		PathComponent* pComponent{};
		int Unk2{};
		float Unk3{ 1000.0f };

		PathDebugDraw(csl::fnd::IAllocator* in_pAllocator, PathManager* in_pManager, int in_capacity)
		{
			Components = csl::ut::PointerMap<PathComponent*, size_t>(in_pAllocator);
			Components.reserve(in_capacity);

			pManager = in_pManager;
		}

	private:
		void AddObject(PathComponent* in_pComponent)
		{
			// TODO	
		}

	public:
		void BlinkPathObject(PathComponent* in_pComponent)
		{
			pComponent = in_pComponent;
			Unk2 = 60;
		}

	private:
		void GetPathObjectVisisble(PathComponent* in_pComponent)
		{
			// TODO	
		}

		void RemoveObject(PathComponent* in_pComponent)
		{
			// TODO
		}

		void SetPathObjectVisisble(PathComponent* in_pComponent, bool in_visible)
		{
			// TODO
		}
		
		void Update(const fnd::SUpdateInfo& in_rUpdateInfo)
		{
			// TODO
		}
	};
}