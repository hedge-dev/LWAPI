#pragma once
#pragma push_macro("CreateService")
#undef CreateService

namespace app
{
	namespace fnd 
	{
		class GameServiceClass;
		class GameService;
		class GameDocumentListener;
	}
	class GameObject;

	class CWorld
	{
		
	};
	
	class GameDocument : public fnd::ReferencedObject
	{
	public:
		inline static GameDocument** ms_ppGameDocument = reinterpret_cast<GameDocument**>(ASLR(0xFEFEF4));
		inline static FUNCTION_PTR(void, __thiscall, ms_fpAddGameObject, ASLR(0x0090B3C0), GameDocument* This, GameObject* object);
		inline static FUNCTION_PTR(fnd::GameService*, __thiscall, ms_fpGetServiceByClass, ASLR(0x0090B2E0), const GameDocument* This, const fnd::GameServiceClass& cls);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpAddService, ASLR(0x0090B610), void* This, fnd::GameService* service);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpShutdownPendingObjects, ASLR(0x0090B6C0), void* This);


	protected:
		void* m_pGameMode{};
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

		HH_FORCE_INLINE const csl::ut::Array<GameObject*>& GetObjects() const
		{
			return m_Objects;
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
		
		fnd::GameService* GetServiceByClass(const fnd::GameServiceClass& cls) const
		{
			return ms_fpGetServiceByClass(this, cls);
		}

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

#pragma pop_macro("CreateService")