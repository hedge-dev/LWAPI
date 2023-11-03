#pragma once
#include "GOComponent.h"

namespace app
{
	namespace fnd
	{
		class GOComponent;
		typedef GOComponent* initializeComponent(csl::fnd::IAllocator* allocator);
		
		class GOComponentClass
		{
		public:
			const char* pName;
			unsigned int Unk1;
			const char* pFamilyID;
			size_t Size;
			initializeComponent* pInitializer;
			unsigned short Unk2;
			size_t Unk3;
		};

		class GOComponent : public RefByHandleObject
		{
			friend GameObject;
			
		public:
			GameObject* pActiveObject{};
			unsigned short Unk1{};
			csl::ut::Bitset<char> Flags{};
			char ComponentType{};
			unsigned int ComponentStats{};
			unsigned int Unk2{};
			csl::ut::LinkListNode VisualComponentNode;
			csl::ut::LinkListNode PhysicsComponentNode;
			csl::ut::LinkListNode AudibleComponentNode;

			GOComponent(bool in_skip) : RefByHandleObject()
			{

			}
			
		public:
			GOComponent() : RefByHandleObject()
			{
				csl::fnd::Singleton<GameObjectSystem>::GetInstance()->rpHandleManager->AddObject(*this);
			}

			~GOComponent()
			{
				csl::fnd::Singleton<GameObjectSystem>::GetInstance()->rpHandleManager->RemoveObject(*this);
			}
			
			virtual const char* GetFamilyID() const = 0;
			virtual void Update(UpdatingPhase in_phase, const SUpdateInfo& in_rUpdateInfo)
			{
				
			}
			
			virtual void OnGOCEvent(int in_event, GameObject& in_rObject, void* in_pData)
			{
				
			}
			
			virtual bool ProcessMessage(const Message& in_rMessage)
			{
				return false;
			}

			void SetGameObject(GameObject* in_pObject)
			{
				pActiveObject = in_pObject;
			}

			GameObject* GetGameObject() const
			{
				return pActiveObject;
			}
			
			bool SendMessageImm(uint in_to, fnd::Message& in_rMessage) const;

			template <typename  T>
			static T* Create(GameObject& in_rObject);
			template <typename  T>
			static T* CreateSingle(GameObject& in_rObject);
			
			static void BeginSetup(GameObject& in_rObject);
			static void EndSetup(GameObject& in_rObject);
		};
	}
}

#include "GameObject.h"
template <typename T>
inline T* app::fnd::GOComponent::Create(GameObject& in_rObject)
{
	static_assert(std::is_base_of<app::fnd::GOComponent, T>(), "Type must be base of app::fnd::GOComponent");
	GOComponent* pComponent = T::staticClass()->initializer(GameObject::GetAllocator());

	if (!pComponent)
		return nullptr;
	
	in_rObject.AddComponent(pComponent);
	return reinterpret_cast<T*>(pComponent);
}

template <typename T>
inline T* app::fnd::GOComponent::CreateSingle(GameObject& in_rObject)
{
	static_assert(std::is_base_of<app::fnd::GOComponent, T>(), "Type must be base of app::fnd::GOComponent");
	GOComponent* pComponent = T::staticClass()->initializer(GameObject::GetAllocator());

	if (!pComponent)
		return nullptr;

	pComponent->SetGameObject(&in_rObject);
	if (pComponent->Unk1 & 1)
		pComponent->OnGOCEvent(0, in_rObject, nullptr);
	
	return reinterpret_cast<T*>(pComponent);
}

inline void app::fnd::GOComponent::BeginSetup(GameObject& in_rObject)
{
	auto& components = in_rObject.GetComponents();
	for (auto* it = components.begin(); it != components.end(); it++)
	{
		(*it)->OnGOCEvent(0, in_rObject, nullptr);
	}
}

inline void app::fnd::GOComponent::EndSetup(GameObject& in_rObject)
{
	auto& components = in_rObject.GetComponents();
	for (auto* it = components.begin(); it != components.end(); it++)
	{
		(*it)->OnGOCEvent(1, in_rObject, nullptr);
	}
}

inline bool app::fnd::GOComponent::SendMessageImm(uint in_to, fnd::Message& in_rMessage) const
{
	return GetGameObject()->SendMessageImm(in_to, in_rMessage);
}