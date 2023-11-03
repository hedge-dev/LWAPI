#pragma once
#pragma push_macro("SendMessage")
#undef SendMessage

namespace app
{
	class GameObjectHandleBase;
	
	class GameObject : public hh::base::CRefCountObject, public fnd::CLeafActor
	{
		friend GameObjectHandleBase;
		
	public:
		static csl::fnd::IAllocator* GetAllocator();
		
	protected:
		csl::ut::Bitset<char> m_StatusFlags{ };
		char m_Category{ 6 };
		GameDocument* m_pOwnerDocument{};
		size_t m_ObjectHandle{};
		GameObjectTableEntry* m_pObjectEntry{};
		csl::ut::InplaceMoveArray<fnd::GOComponent*, 8> m_Components{ GetAllocator() };
		csl::ut::VariableString m_Name{ GetAllocator() };
		csl::ut::InplaceMoveArray<fnd::Property, 2> m_Properties{ GetAllocator() };
		unsigned int m_ComponentFlags{};
		csl::ut::LinkList<fnd::GOComponent> m_VisualComponents{ &fnd::GOComponent::visualComponentNode };
		csl::ut::LinkList<fnd::GOComponent> m_PhysicsComponents{ &fnd::GOComponent::physicsComponentNode };
		csl::ut::LinkList<fnd::GOComponent> m_AudibleComponents{ &fnd::GOComponent::audibleComponentNode };

		static void UpdateComponents(csl::ut::LinkList<fnd::GOComponent>& in_rComponents, const fnd::SUpdateInfo& in_rUpdateInfo, fnd::UpdatingPhase in_phase)
		{
			if (!in_rComponents.size())
				return;

			for (auto& component : in_rComponents)
			{
				component.Update(in_phase, in_rUpdateInfo);
			}
		}

		GameObject(bool in_skip)
		{
			
		}

	public:
		void Kill();
		bool IsKilled() const
		{
			return m_StatusFlags.test(0);
		}

		void Sleep()
		{
			m_StatusFlags.set(1);
		}

		void Resume()
		{
			m_StatusFlags.reset(1);
		}
		
		GameObject()
		{
			csl::fnd::Singleton<GameObjectSystem>::GetInstance()->AddObject(this);
		}

		~GameObject() override
		{
			csl::fnd::Singleton<GameObjectSystem>::GetInstance()->RemoveObject(this);
			for (auto& component : m_Components)
			{
				component->Release();
			}
		}

		void SetObjectCategory(size_t in_category)
		{
			m_Category = in_category;
		}

		size_t GetObjectCategory() const
		{
			return m_Category;
		}
		
		virtual void AddCallback(GameDocument* in_pDocument)
		{

		}

		virtual void RemoveCallback(GameDocument* in_pDocument)
		{

		}

		virtual void UpdatePhase(const fnd::SUpdateInfo& in_rUpdateInfo, fnd::UpdatingPhase in_phase)
		{

		}

		bool ActorProc(int in_id, void* in_pData) override
		{
			switch (in_id)
			{
			case 0:
			case 1:
			{
				if (!Enabled)
					return false;

				auto* pMessage = static_cast<fnd::Message*>(in_pData);

				if (m_AllowedMessageFlags & pMessage->Mask)
				{
					for (auto** it = m_Components.begin(); it != m_Components.end(); it++)
					{
						(*it)->ProcessMessage(*pMessage);
					}
				}

				return CLeafActor::ActorProc(in_id, in_pData);
			}

			case 3:
			{
				if (m_StatusFlags.test(1))
					return true;

				if (UpdateFlags)
					Update(*reinterpret_cast<fnd::SUpdateInfo*>(in_pData));

				UpdateComponents(m_VisualComponents, *reinterpret_cast<fnd::SUpdateInfo*>(in_pData), 0);

				return true;
			}

			case 4:
			{
				if (m_StatusFlags.test(1))
					return true;

				if (UpdateFlags)
					UpdatePhase(*reinterpret_cast<fnd::SUpdateInfo*>(in_pData), 1);

				UpdateComponents(m_PhysicsComponents, *reinterpret_cast<fnd::SUpdateInfo*>(in_pData), 1);

				return true;
			}

			case 5:
			{
				if (m_StatusFlags.test(1))
					return true;

				if (UpdateFlags)
					UpdatePhase(*reinterpret_cast<fnd::SUpdateInfo*>(in_pData), 2);

				UpdateComponents(m_AudibleComponents, *reinterpret_cast<fnd::SUpdateInfo*>(in_pData), 2);

				return true;
			}

			default:
				return CLeafActor::ActorProc(in_id, in_pData);
			}
		}

		bool ProcessMessage(fnd::Message& in_rMessage) override
		{
			if (PreProcessMessage(in_rMessage))
				return true;
			
			if (in_rMessage.IsOfType<xgame::MsgKill>())
			{
				Kill();
				return true;
			}
			
			return CLeafActor::ProcessMessage(in_rMessage);
		}

		void* operator new (size_t in_size)
		{
			return GetAllocator()->Alloc(in_size, 16);
		}

		void operator delete (void* in_pLoc)
		{
			GetAllocator()->Free(in_pLoc);
		}

		bool AddComponent(fnd::GOComponent* in_pComponent)
		{
			for (auto* it = m_Components.begin(); it != m_Components.end(); it++)
			{
				if ((*it)->GetFamilyID() == in_pComponent->GetFamilyID())
					return false;
			}

			m_Components.push_back(in_pComponent);
			in_pComponent->AddRef();
			in_pComponent->SetGameObject(this);
			m_ComponentFlags |= in_pComponent->componentStats;

			return true;
		}

		fnd::GOComponent* GetComponent(const char* in_pName) const
		{
			for (auto* it = m_Components.begin(); it != m_Components.end(); it++)
			{
				auto* pFamily = (*it)->GetFamilyID();
				if (pFamily == in_pName)
					return *it;
			}

			return nullptr;
		}

		template<typename T>
		T* GetComponent() const
		{
			return (T*)GetComponent(T::staticClass()->familyID);
		}
		
		const csl::ut::InplaceMoveArray<fnd::GOComponent*, 8>& GetComponents() const
		{
			return m_Components;
		}

		GameDocument* GetDocument() const
		{
			return m_pOwnerDocument;
		}

		fnd::GameService* GetServiceByClass(const fnd::GameServiceClass& in_rClass)
		{
			return GetDocument()->GetServiceByClass(in_rClass);
		}

		template <typename T>
		T* GetService()
		{
			return reinterpret_cast<T*>(GetServiceByClass(T::staticClass()));
		}
		
		bool BroadcastMessageImmToGroup(uint in_group, fnd::Message& in_rMessage)
		{
			uint groupActor = m_pOwnerDocument->GetGroupActorID(in_group);
			if (!groupActor)
				return false;

			BroadcastMessageImm(groupActor, in_rMessage);
		}

		void SendMessageToGame(fnd::Message& in_rMessage)
		{
			SendMessage(m_pOwnerDocument->GetGameActorID(), in_rMessage);
		}
		
		bool SendMessageImmToGame(fnd::Message& in_rMessage)
		{
			return SendMessageImm(m_pOwnerDocument->GetGameActorID(), in_rMessage);
		}

		bool SendMessageImmToGameObject(GameObject* in_pObject, fnd::Message& in_rMessage)
		{
			return SendMessageImm(in_pObject->m_ActorID, in_rMessage);
		}
		
		bool HasProperty(uint in_key) const
		{
			for (auto& prop : m_Properties)
			{
				if (prop.GetKey() == in_key)
					return true;
			}

			return false;
		}
		
		void AddProperty(uint in_key, fnd::PropertyValue in_value)
		{
			m_Properties.push_back(fnd::Property(in_key, in_value));
		}

		void SetProperty(uint in_key, fnd::PropertyValue in_value)
		{
			for (auto& prop : m_Properties)
			{
				if (prop.GetKey() == in_key)
				{
					prop.SetValue(in_value);
					return;
				}
			}
			
			AddProperty(kin_keyey, in_value);
		}

		fnd::PropertyValue GetProperty(uint in_key) const
		{
			for (auto& prop : m_Properties)
			{
				if (prop.GetKey() == in_key)
					return prop.GetValue();
			}
			
			return fnd::PropertyValue{};
		}

		const csl::ut::Array<fnd::Property>& GetProperties() const
		{
			return m_Properties;
		}
	};

	inline void GameObject::Kill()
	{
		if (!IsKilled())
		{
			m_StatusFlags.set(0);
			Enabled = false;
		}
	}

	inline csl::fnd::IAllocator* GameObject::GetAllocator()
	{
		return csl::fnd::Singleton<GameObjectSystem>::GetInstance()->GetPooledAllocator();
	}
}

#pragma pop_macro("SendMessage")