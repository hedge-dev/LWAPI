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
			char componentType{};
			char componentFlags{};
			unsigned int componentStats{};
			unsigned int unk2{};
			csl::ut::LinkListNode visualComponentNode;
			csl::ut::LinkListNode physicsComponentNode;
			csl::ut::LinkListNode audibleComponentNode;
			
		public:
			GOComponent()
			{
				
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

			template <typename  T>
			static GOComponent* Create(GameObject* obj);
			static void BeginSetup(GameObject& obj);
			static void EndSetup(GameObject& obj);
		};
	}
}

#include "GameObject.h"
template <typename T>
inline app::fnd::GOComponent* app::fnd::GOComponent::Create(GameObject* obj)
{
	static_assert(std::is_base_of<app::fnd::GOComponent, T>(), "Type must be base of app::fnd::GOComponent");
	GOComponent* component = T::staticClass()->initializer(GameObject::GetAllocator());
	obj->AddComponent(component);
	return component;
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