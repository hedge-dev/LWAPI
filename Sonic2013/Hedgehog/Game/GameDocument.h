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
	public:
		inline static GameDocument** ms_ppGameDocument = reinterpret_cast<GameDocument**>(ASLR(0xFEFEF4));
		inline static FUNCTION_PTR(void, __thiscall, ms_fpAddGameObject, ASLR(0x0090B3C0), GameDocument* This, GameObject* object);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpAddService, ASLR(0x0090B610), void* This, fnd::GameService* service);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpShutdownPendingObjects, ASLR(0x0090B6C0), void* This);
		inline static constexpr const char* ms_CategoryNames[OBJECT_CATEGORY_COUNT] = 
		{
			"SERVER", "DEBUG", "ENVIRONMENT", "PATH", "PLATFORM", "RADIO_CONTROL", "OBJECT",
			"ENEMY", "PLAYER", "ATTACHED", "CAMERA", "HUD", "HUD_NONSTOP", "SYSTEM", "NONSTOP"
		};

		GameMode* m_pGameMode{};
		size_t m_GameActorID{};
		std::unique_ptr<CWorld> m_pWorld{};
		float m_GlobalTime{};
		csl::ut::FixedArray<fnd::CBranchActor*, 32> m_Layers{};
		csl::ut::MoveArray<GameObject*> m_Objects{ GetAllocator() };
		csl::ut::MoveArray<fnd::GameService*> m_Services{ GetAllocator() };
		csl::ut::MoveArray<GameObject*> m_ShutdownObjects{ GetAllocator() };
		csl::ut::MoveArray<fnd::GameDocumentListener*> m_Listeners{ GetAllocator() };
		
	public:
		inline static FUNCTION_PTR(uint, __thiscall, ms_fpGetGroupActorID, ASLR(0x0090B2C0), void* This, uint group);

		HH_FORCE_INLINE static constexpr const char* GetCategoryName(size_t in_category)
		{
			if (in_category >= OBJECT_CATEGORY_COUNT)
				return nullptr;

			return ms_CategoryNames[in_category];
		}

		HH_FORCE_INLINE void UpdateGlobalTime(const fnd::SUpdateInfo& info)
		{
			m_GlobalTime += info.deltaTime;
		}

		HH_FORCE_INLINE GameMode* GetGameMode() const
		{
			return m_pGameMode;
		}
		
		HH_FORCE_INLINE float GetGlobalTime() const
		{
			return m_GlobalTime;
		}

		HH_FORCE_INLINE size_t GetGameActorID() const
		{
			return m_GameActorID;
		}
		
		HH_FORCE_INLINE uint GetGroupActorID(uint group) const
		{
			return m_Layers[group]->GetID();
		}

		HH_FORCE_INLINE fnd::CBranchActor* GetGroupActor(uint group) const
		{
			if (group > m_Layers.size())
				return nullptr;

			return m_Layers[group];
		}

		HH_FORCE_INLINE const csl::ut::Array<GameObject*>& GetObjects() const
		{
			return m_Objects;
		}

		HH_FORCE_INLINE const csl::ut::Array<fnd::GameService*>& GetServices() const
		{
			return m_Services;
		}
		
		inline void AddGameDocumentListener(fnd::GameDocumentListener* pListener)
		{
			m_Listeners.push_back(pListener);
		}

		void RemoveGameDocumentListener(fnd::GameDocumentListener* pListener)
		{
			auto idx = m_Listeners.find(pListener);
			if (idx == -1)
				return;

			m_Listeners.remove(idx);
		}
		
		void AddGameObject(GameObject* object)
		{
			ms_fpAddGameObject(this, object);
		}

		void AddService(fnd::GameService* service)
		{
			ms_fpAddService(this, service);
		}

		fnd::GameService* CreateService(const fnd::GameServiceClass& cls, csl::fnd::IAllocator* allocator = nullptr);

		template<typename T>
		T* CreateService(csl::fnd::IAllocator* allocator = nullptr)
		{
			return reinterpret_cast<T*>(CreateService(T::staticClass(), allocator));
		}
		
		fnd::GameService* GetServiceByClass(const fnd::GameServiceClass& cls) const;

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

inline app::fnd::GameService* app::GameDocument::CreateService(const fnd::GameServiceClass& cls, csl::fnd::IAllocator* allocator)
{
	if (!allocator)
		allocator = GetAllocator();
	
	auto* service = cls.Construct(allocator);
	AddService(service);

	return service;
}

inline app::fnd::GameService* app::GameDocument::GetServiceByClass(const app::fnd::GameServiceClass& cls) const
{
	auto** begin = m_Services.begin();
	auto** end = m_Services.end();

	if (begin == end)
		return { nullptr };

	for (begin; (*begin)->m_pClass != &cls;)
	{
		if (++begin == m_Services.end())
			return { nullptr };
	}

	return *begin;
}

#pragma pop_macro("CreateService")