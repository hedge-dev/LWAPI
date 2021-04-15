#pragma once
#pragma push_macro("CreateService")
#undef CreateService

namespace app
{
	namespace fnd 
	{
		class GameServiceClass;
		class GameService;
	}

	class GameObject;
	
	class GameDocument : public fnd::ReferencedObject
	{
	public:
		inline static GameDocument** ms_ppGameDocument = reinterpret_cast<GameDocument**>(ASLR(0xFEFEF4));
		inline static FUNCTION_PTR(void, __thiscall, ms_fpAddGameObject, ASLR(0x0090B3C0), GameDocument* This, GameObject* object);
		inline static FUNCTION_PTR(fnd::GameService*, __thiscall, ms_fpGetServiceByClass, ASLR(0x0090B2E0), const GameDocument* This, const fnd::GameServiceClass& cls);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpAddService, ASLR(0x0090B610), void* This, fnd::GameService* service);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpShutdownPendingObjects, ASLR(0x0090B6C0), void* This);


	private:
		void* gameMode{};
		unsigned int unk1{};
		void* unk2{};
		float time{};

	public:

		inline static FUNCTION_PTR(uint, __thiscall, ms_fpGetGroupActorID, ASLR(0x0090B2C0), void* This, uint group);

		uint GetGroupActorID(uint group)
		{
			return ms_fpGetGroupActorID(this, group);
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