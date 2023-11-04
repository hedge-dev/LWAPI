#pragma once
#pragma push_macro("CreateService")
#undef CreateService

#define OBJECT_CATEGORY_SERVER 0
#define OBJECT_CATEGORY_DEBUG 1
#define OBJECT_CATEGORY_ENVIRONMENT 2
#define OBJECT_CATEGORY_PATH 3
#define OBJECT_CATEGORY_PLATFORM 4
#define OBJECT_CATEGORY_RADIO_CONTROL 5
#define OBJECT_CATEGORY_OBJECT 6
#define OBJECT_CATEGORY_ENEMY 7
#define OBJECT_CATEGORY_PLAYER 8
#define OBJECT_CATEGORY_ATTACHED 9
#define OBJECT_CATEGORY_CAMERA 10
#define OBJECT_CATEGORY_HUD 11
#define OBJECT_CATEGORY_HUD_NONSTOP 12
#define OBJECT_CATEGORY_SYSTEM 13
#define OBJECT_CATEGORY_NONSTOP 14
#define OBJECT_CATEGORY_COUNT 15

namespace app
{
	namespace Render
	{
		class CameraParam;
	}

	class GameDocument;
	class GameMode;
	namespace fnd 
	{
		class GameServiceClass;
		class GameService;
		class GameDocumentListener
		{
		public:
			virtual ~GameDocumentListener() = default;
			virtual void PreShutdownObjectCallback(GameDocument* in_pDocument) { }
			virtual void PostShutdownObjectCallback(GameDocument* in_pDocument) { }
		};
	}
	class GameObject;

	class CWorld
	{
	private:
		inline static FUNCTION_PTR(Render::CameraParam*, __thiscall, ms_fpGetCamera, ASLR(0x004DF5E0), CWorld*, size_t);

	public:
		Render::CameraParam* GetCamera(size_t in_unk)
		{
			return ms_fpGetCamera(this, in_unk);
		}
	};
	
	class GameDocument : public fnd::ReferencedObject
	{
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpAddGameObject, ASLR(0x0090B3C0), GameDocument*, GameObject*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpAddService, ASLR(0x0090B610), GameDocument*, fnd::GameService*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpShutdownPendingObjects, ASLR(0x0090B6C0), GameDocument*);
		inline static FUNCTION_PTR(uint, __thiscall, ms_fpGetGroupActorID, ASLR(0x0090B2C0), GameDocument*, uint);
		inline static GameDocument** ms_ppGameDocument = reinterpret_cast<GameDocument**>(ASLR(0x00FEFEF4));
		inline static constexpr const char* ms_CategoryNames[OBJECT_CATEGORY_COUNT] = 
		{
			"SERVER", "DEBUG", "ENVIRONMENT", "PATH", "PLATFORM", "RADIO_CONTROL", "OBJECT",
			"ENEMY", "PLAYER", "ATTACHED", "CAMERA", "HUD", "HUD_NONSTOP", "SYSTEM", "NONSTOP"
		};

	public:
		GameMode* pGameMode{};
		size_t GameActorID{};
		std::unique_ptr<CWorld> pWorld{};
		float GlobalTime{};
		csl::ut::FixedArray<fnd::CBranchActor*, 32> Layers{};
		csl::ut::MoveArray<GameObject*> Objects{ GetAllocator() };
		csl::ut::MoveArray<fnd::GameService*> Services{ GetAllocator() };
		csl::ut::MoveArray<GameObject*> ShutdownObjects{ GetAllocator() };
		csl::ut::MoveArray<fnd::GameDocumentListener*> Listeners{ GetAllocator() };
		
		HH_FORCE_INLINE static constexpr const char* GetCategoryName(size_t in_category)
		{
			if (in_category >= OBJECT_CATEGORY_COUNT)
				return nullptr;

			return ms_CategoryNames[in_category];
		}

		HH_FORCE_INLINE void UpdateGlobalTime(const fnd::SUpdateInfo& in_rUpdateInfo)
		{
			GlobalTime += in_rUpdateInfo.DeltaTime;
		}

		HH_FORCE_INLINE GameMode* GetGameMode() const
		{
			return pGameMode;
		}
		
		HH_FORCE_INLINE float GetGlobalTime() const
		{
			return GlobalTime;
		}

		HH_FORCE_INLINE size_t GetGameActorID() const
		{
			return GameActorID;
		}
		
		HH_FORCE_INLINE uint GetGroupActorID(uint in_group) const
		{
			return Layers[in_group]->GetID();
		}

		HH_FORCE_INLINE fnd::CBranchActor* GetGroupActor(uint in_group) const
		{
			if (in_group > Layers.size())
				return nullptr;

			return Layers[in_group];
		}

		HH_FORCE_INLINE const csl::ut::Array<GameObject*>& GetObjects() const
		{
			return Objects;
		}

		HH_FORCE_INLINE const csl::ut::Array<fnd::GameService*>& GetServices() const
		{
			return Services;
		}
		
		inline void AddGameDocumentListener(fnd::GameDocumentListener* in_pListener)
		{
			Listeners.push_back(in_pListener);
		}

		void RemoveGameDocumentListener(fnd::GameDocumentListener* in_pListener)
		{
			auto idx = Listeners.find(in_pListener);
			if (idx == -1)
				return;

			Listeners.remove(idx);
		}
		
		void AddGameObject(GameObject* in_pObject)
		{
			ms_fpAddGameObject(this, in_pObject);
		}

		void AddService(fnd::GameService* in_pService)
		{
			ms_fpAddService(this, in_pService);
		}

		fnd::GameService* CreateService(const fnd::GameServiceClass& in_rClass, csl::fnd::IAllocator* in_pAllocator = nullptr);

		template<typename T>
		T* CreateService(csl::fnd::IAllocator* in_pAllocator = nullptr)
		{
			return reinterpret_cast<T*>(CreateService(T::staticClass(), in_pAllocator));
		}
		
		fnd::GameService* GetServiceByClass(const fnd::GameServiceClass& in_rClass) const;

		template <typename T>
		T* GetService() const
		{
			return reinterpret_cast<T*>(GetServiceByClass(T::staticClass()));
		}

		void ShutdownPendingObjects()
		{
			ms_fpShutdownPendingObjects(this);
		}
		
		inline static GameDocument* GetSingleton()
		{
			return *ms_ppGameDocument;
		}
	};
}

#include "GameService.h"
#include "GameServiceClass.h"

inline app::fnd::GameService* app::GameDocument::CreateService(const fnd::GameServiceClass& in_rClass, csl::fnd::IAllocator* in_pAllocator)
{
	if (!in_pAllocator)
		in_pAllocator = GetAllocator();
	
	auto* pService = in_rClass.Construct(in_pAllocator);
	AddService(pService);

	return pService;
}

inline app::fnd::GameService* app::GameDocument::GetServiceByClass(const app::fnd::GameServiceClass& in_rClass) const
{
	auto** ppBegin = Services.begin();
	auto** ppEnd = Services.end();

	if (ppBegin == ppEnd)
		return { nullptr };

	for (ppBegin; (*ppBegin)->pClass != &in_rClass;)
	{
		if (++ppBegin == Services.end())
			return { nullptr };
	}

	return *ppBegin;
}

#pragma pop_macro("CreateService")