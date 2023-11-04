#pragma once

namespace app::game
{
	class GOCHud : public fnd::GOComponent
	{
	public:
		struct Description
		{
			const char* pRenderableName{};
			int PriorityOpa{};
			int PriorityXlu{};
			char Unk1{};
			uint Option{};
			int Size{};
			int Unk2{};

			Description(const char* in_pRenderableName, int in_priorityOpa, int in_priorityXlu, char in_unk1, uint in_option, int in_size, int in_unk2)
			{
				pRenderableName = in_pRenderableName;
				PriorityOpa = in_priorityOpa;
				PriorityXlu = in_priorityXlu;
				Unk1 = in_unk1;
				Option = in_option;
				Size = in_size;
				Unk2 = in_unk2;
			}
		};
		
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpCtor, ASLR(0x004B1D30), GOCHud*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpDtor, ASLR(0x004C0220), GOCHud*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetup, ASLR(0x004BFF90), GOCHud*, const Description&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetupProject, ASLR(0x004BFA20), GOCHud*, SurfRide::ReferenceCount<SurfRide::Project>* out_refCount, const char*, hh::ut::PackFile);
		inline static FUNCTION_PTR(HudLayerController*, __thiscall, f_CreateLayerController, ASLR(0x004BFD70), GOCHud*, int*, const char*, int);
		inline static FUNCTION_PTR(HudLayerController*, __thiscall, ms_fpCreateLayerController, ASLR(0x004BFEB0), GOCHud*, SurfRide::ReferenceCount<SurfRide::Project>, const char*, const char*, byte);
		inline static FUNCTION_PTR(HudLayerController*, __thiscall, ms_fpGetLayerController, ASLR(0x004BF8E0), GOCHud*, byte);
		inline static fnd::GOComponentClass* ms_pStaticClass = reinterpret_cast<fnd::GOComponentClass*>(ASLR(0x00FD7710));
		inline static const char* ms_pGOCHudFamilyID = (const char*)ASLR(0x00D64334);

	public:
		int Unk1{};
		csl::ut::ObjectMoveArray<SurfRide::ReferenceCount<SurfRide::Project>> rcProjects{};
		csl::ut::MoveArray<game::HudLayerController*> LayerControllers{};
		ut::RefPtr<gfx::Renderable> pRenderable{}; // boost::intrusive_ptr<gfx::Renderable>
		csl::ut::Bitset<char> Unk2{};
		int Unk3{};

		GOCHud() : fnd::GOComponent()
		{
		
		}

		const char* GetFamilyID() const override
		{
			return ms_pGOCHudFamilyID;
		}

		static fnd::GOComponentClass* staticClass()
		{
			return ms_pStaticClass;
		}

		inline static GOComponent* Initialize(csl::fnd::IAllocator* in_pAllocator)
		{
			return new(in_pAllocator) GOCHud();
		}

		void Setup(const Description& in_description)
		{
			ms_fpSetup(this, in_description);
		}

		void SetupProject(SurfRide::ReferenceCount<SurfRide::Project>* out_pRefCount, const char* in_pProjectName, hh::ut::PackFile in_packFile)
		{
			ms_fpSetupProject(this, out_pRefCount, in_pProjectName, in_packFile);
		}

		HudLayerController* CreateLayerController(int* in_prcScene, const char* in_layerName, int in_a3)
		{
			return f_CreateLayerController(this, in_prcScene, in_layerName, in_a3);
		}

		HudLayerController* GetLayerController(byte in_controllerNo)
		{
			return ms_fpGetLayerController(this, in_controllerNo);
		}

		HudLayerController* CreateLayerController(SurfRide::ReferenceCount<SurfRide::Layer> in_rcLayer, byte in_controllerNo)
		{
			FUNCTION_PTR(HudLayerController*, __thiscall, fpCreateLayerController, ASLR(0x004BFB10), GOCHud*, SurfRide::ReferenceCount<SurfRide::Layer>, byte);
			return fpCreateLayerController(this, in_rcLayer, in_controllerNo);
		}

		HudLayerController* CreateLayerController(SurfRide::ReferenceCount<SurfRide::Scene> in_rcScene, const char* in_pLayerName, byte in_controllerNo)
		{
			return CreateLayerController(in_rcScene->GetLayer(in_pLayerName), in_controllerNo);
		}

		HudLayerController* CreateLayerController(SurfRide::ReferenceCount<SurfRide::Project> in_refCount, const char* in_pSceneName, const char* in_pLayerName, byte in_unk)
		{
			return ms_fpCreateLayerController(this, in_refCount, in_pSceneName, in_pLayerName, in_unk);
		}
	};
}