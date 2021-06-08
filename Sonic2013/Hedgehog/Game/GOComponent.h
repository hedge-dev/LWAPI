#pragma once

namespace app
{
	namespace fnd
	{
		class GOComponent;
		typedef GOComponent* initializeComponent(csl::fnd::IAllocator* allocator);
		
		class GOComponentClass
		{
		public:
			const char* name;
			unsigned int unk1;
			const char* familyID;
			size_t size;
			initializeComponent* initializer;
			unsigned short unk2;
			size_t unk3;
		};

		class GOComponent : public RefByHandleObject
		{
			friend GameObject;
			
		protected:
			GameObject* activeObject{};
			unsigned short unk1{};
			csl::ut::Bitset<char> m_Flags{};
			char componentType{};
			unsigned int componentStats{};
			unsigned int unk2{};
			csl::ut::LinkListNode visualComponentNode;
			csl::ut::LinkListNode physicsComponentNode;
			csl::ut::LinkListNode audibleComponentNode;

			GOComponent(bool skip) : RefByHandleObject()
			{
				
			}
			
		public:
			GOComponent() : RefByHandleObject()
			{
				csl::fnd::Singleton<GameObjectSystem>::GetInstance()->handleManager->AddObject(*this);
			}

			~GOComponent()
			{
				csl::fnd::Singleton<GameObjectSystem>::GetInstance()->handleManager->RemoveObject(*this);
			}
			
			virtual const char* GetFamilyID() = 0;
			virtual void Update(UpdatingPhase phase, const SUpdateInfo& updateInfo)
			{
				
			}
			
			virtual void OnGOCEvent(int event, GameObject& object, void* data)
			{
				
			}
			
			virtual bool ProcessMessage(const Message& message)
			{
				return false;
			}

			void SetGameObject(GameObject* object)
			{
				activeObject = object;
			}

			GameObject* GetGameObject() const
			{
				return activeObject;
			}
			
			template <typename  T>
			static T* Create(GameObject& obj);
			template <typename  T>
			static T* CreateSingle(GameObject& obj);
			
			static void BeginSetup(GameObject& obj);
			static void EndSetup(GameObject& obj);
		};
	}
}

#include "GameObject.h"
template <typename T>
inline T* app::fnd::GOComponent::Create(GameObject& obj)
{
	static_assert(std::is_base_of<app::fnd::GOComponent, T>(), "Type must be base of app::fnd::GOComponent");
	GOComponent* component = T::staticClass()->initializer(GameObject::GetAllocator());

	if (!component)
		return nullptr;
	
	obj.AddComponent(component);
	return reinterpret_cast<T*>(component);
}

template <typename T>
inline T* app::fnd::GOComponent::CreateSingle(GameObject& obj)
{
	static_assert(std::is_base_of<app::fnd::GOComponent, T>(), "Type must be base of app::fnd::GOComponent");
	GOComponent* component = T::staticClass()->initializer(GameObject::GetAllocator());

	if (!component)
		return nullptr;

	component->SetGameObject(&obj);
	if (component->unk1 & 1)
		component->OnGOCEvent(0, obj, nullptr);
	
	return reinterpret_cast<T*>(component);
}

inline void app::fnd::GOComponent::BeginSetup(GameObject& obj)
{
	auto& components = obj.GetComponents();
	for (auto* it = components.begin(); it != components.end(); it++)
	{
		(*it)->OnGOCEvent(0, obj, nullptr);
	}
}

inline void app::fnd::GOComponent::EndSetup(GameObject& obj)
{
	auto& components = obj.GetComponents();
	for (auto* it = components.begin(); it != components.end(); it++)
	{
		(*it)->OnGOCEvent(1, obj, nullptr);
	}
}