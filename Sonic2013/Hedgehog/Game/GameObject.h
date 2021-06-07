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
		csl::ut::VariableString* m_pName{};
		csl::fnd::IAllocator* m_pObjectAllocator{ GetAllocator() };
		csl::ut::InplaceMoveArray<fnd::Property, 2> m_Properties{ GetAllocator() };
		unsigned int m_ComponentFlags{};
		csl::ut::LinkList<fnd::GOComponent> m_VisualComponents{ &fnd::GOComponent::visualComponentNode };
		csl::ut::LinkList<fnd::GOComponent> m_PhysicsComponents{ &fnd::GOComponent::physicsComponentNode };
		csl::ut::LinkList<fnd::GOComponent> m_AudibleComponents{ &fnd::GOComponent::audibleComponentNode };

		static void UpdateComponents(csl::ut::LinkList<fnd::GOComponent>& comps, const fnd::SUpdateInfo& update_info, fnd::UpdatingPhase phase)
		{
			if (!comps.size())
				return;

			for (auto& component : comps)
			{
				component.Update(phase, update_info);
			}
		}

	public:
		void Kill();
		bool IsKilled() const
		{
			return m_StatusFlags.test(0);
		}
		
		GameObject()
		{
			csl::fnd::Singleton<GameObjectSystem>::GetInstance()->AddObject(this);
		}

		~GameObject() override
		{
			csl::fnd::Singleton<GameObjectSystem>::GetInstance()->RemoveObject(this);
			for (auto* it = m_Components.begin(); it != m_Components.end(); it++)
			{
				(*it)->Release();
			}
		}

		void SetObjectCategory(size_t category)
		{
			m_Category = category;
		}

		size_t GetObjectCategory() const
		{
			return m_Category;
		}
		
		virtual void AddCallback(GameDocument& document)
		{

		}

		virtual void RemoveCallback(GameDocument& document)
		{

		}

		virtual void UpdatePhase(const fnd::SUpdateInfo& update_info, fnd::UpdatingPhase phase)
		{

		}

		bool ActorProc(int id, void* data) override
		{
			switch (id)
			{
			case 0:
			case 1:
			{
				if (!m_Enabled)
					return false;

				auto* msg = static_cast<fnd::Message*>(data);

				if (m_AllowedMessageFlags & msg->mask)
				{
					for (auto** it = m_Components.begin(); it != m_Components.end(); it++)
					{
						(*it)->ProcessMessage(*msg);
					}
				}

				return CLeafActor::ActorProc(id, data);
			}

			case 3:
			{
				if (m_StatusFlags.test(1))
					return true;

				if (m_updateFlags)
					Update(*reinterpret_cast<fnd::SUpdateInfo*>(data));

				UpdateComponents(m_VisualComponents, *reinterpret_cast<fnd::SUpdateInfo*>(data), 0);

				return true;
			}

			case 4:
			{
				if (m_StatusFlags.test(1))
					return true;

				if (m_updateFlags)
					UpdatePhase(*reinterpret_cast<fnd::SUpdateInfo*>(data), 1);

				UpdateComponents(m_PhysicsComponents, *reinterpret_cast<fnd::SUpdateInfo*>(data), 1);

				return true;
			}

			case 5:
			{
				if (m_StatusFlags.test(1))
					return true;

				if (m_updateFlags)
					UpdatePhase(*reinterpret_cast<fnd::SUpdateInfo*>(data), 2);

				UpdateComponents(m_AudibleComponents, *reinterpret_cast<fnd::SUpdateInfo*>(data), 2);

				return true;
			}

			default:
				return CLeafActor::ActorProc(id, data);
			}
		}

		bool ProcessMessage(fnd::Message& msg) override
		{
			if (PreProcessMessage(msg))
				return true;
			
			if (msg.IsOfType<xgame::MsgKill>())
			{
				Kill();
				return true;
			}
			
			return CLeafActor::ProcessMessage(msg);
		}
		
		void* operator new (size_t size)
		{
			return GetAllocator()->Alloc(size, 16);
		}

		void operator delete (void* loc)
		{
			GetAllocator()->Free(loc);
		}

		bool AddComponent(fnd::GOComponent* component)
		{
			for (auto* it = m_Components.begin(); it != m_Components.end(); it++)
			{
				if ((*it)->GetFamilyID() == component->GetFamilyID())
					return false;
			}

			m_Components.push_back(component);
			component->AddRef();
			component->SetGameObject(this);
			m_ComponentFlags |= component->componentStats;

			return true;
		}

		fnd::GOComponent* GetComponent(const char* name) const
		{
			for (auto* it = m_Components.begin(); it != m_Components.end(); it++)
			{
				auto* family = (*it)->GetFamilyID();
				if (family == name)
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
		
		bool BroadcastMessageImmToGroup(uint group, fnd::Message& msg)
		{
			uint groupActor = m_pOwnerDocument->GetGroupActorID(group);
			if (!groupActor)
				return false;

			BroadcastMessageImm(groupActor, msg);
		}

		void SendMessageToGame(fnd::Message& msg)
		{
			SendMessage(m_pOwnerDocument->GetGameActorID(), msg);
		}
		
		bool SendMessageImmToGame(fnd::Message& msg)
		{
			return SendMessageImm(m_pOwnerDocument->GetGameActorID(), msg);
		}
		
		bool HasProperty(uint key) const
		{
			for (auto& prop : m_Properties)
			{
				if (prop.GetKey() == key)
					return true;
			}

			return false;
		}
		
		void AddProperty(uint key, fnd::PropertyValue value)
		{
			m_Properties.push_back(fnd::Property(key, value));
		}

		void SetProperty(uint key, fnd::PropertyValue value)
		{
			for (auto& prop : m_Properties)
			{
				if (prop.GetKey() == key)
				{
					prop.SetValue(value);
					return;
				}
			}
			
			AddProperty(key, value);
		}

		fnd::PropertyValue GetProperty(uint key) const
		{
			for (auto& prop : m_Properties)
			{
				if (prop.GetKey() == key)
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
			m_Enabled = false;
		}
	}

	inline csl::fnd::IAllocator* GameObject::GetAllocator()
	{
		return csl::fnd::Singleton<GameObjectSystem>::GetInstance()->GetPooledAllocator();
	}
}

#pragma pop_macro("SendMessage")