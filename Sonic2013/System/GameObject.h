#pragma once

namespace app
{
	class GameObject : public hh::base::CRefCountObject, public fnd::CLeafActor
	{
	public:
		static csl::fnd::IAllocator* GetAllocator();
		
	protected:
		char statusFlags{ 0 };
		char category{ 6 };
		GameDocument* ownerDocument{};
		size_t objectHandle{};
		GameObjectTableEntry* objectEntry{};
		csl::ut::InplaceMoveArray<fnd::GOComponent*, 8> components{ GetAllocator() };
		void* name{}; // Maybe a csl::ut::VariableString, I have no clue. This is always zero from my research.
		csl::fnd::IAllocator* objectAllocator{ GetAllocator() };
		csl::ut::InplaceMoveArray<fnd::Property, 2> properties{ GetAllocator() };
		unsigned int componentFlags{};
		csl::ut::LinkList<fnd::GOComponent> visualComponents{ offsetof(fnd::GOComponent, visualComponentNode) };
		csl::ut::LinkList<fnd::GOComponent> physicsComponents{ offsetof(fnd::GOComponent, physicsComponentNode) };
		csl::ut::LinkList<fnd::GOComponent> audibleComponents{ offsetof(fnd::GOComponent, audibleComponentNode) };


		static void UpdateComponents(csl::ut::LinkList<fnd::GOComponent>& comps, const fnd::SUpdateInfo& update_info, fnd::UpdatingPhase phase)
		{
			if (!comps.size())
				return;

			auto* it = comps.begin();

			for (auto i = 0; i < comps.size(); i++)
			{
				comps.get(it)->Update(phase, update_info);
				it = (*it)++;
			}
		}

	public:
		void Kill();
		
		GameObject()
		{
			csl::ut::Singleton<GameObjectSystem>::GetInstance()->AddObject(this);
		}

		~GameObject() override
		{
			csl::ut::Singleton<GameObjectSystem>::GetInstance()->RemoveObject(this);
			for (auto* it = components.begin(); it != components.end(); it++)
			{
				(*it)->Release();
			}
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
				if (!enabled)
					return false;

				auto* msg = static_cast<fnd::Message*>(data);

				if (allowedMessageMask & msg->mask)
				{
					for (auto** it = components.begin(); it != components.end(); it++)
					{
						(*it)->ProcessMessage(*msg);
					}
				}

				return CLeafActor::ActorProc(id, data);
			}

			case 3:
			{
				if (statusFlags & 2)
					return true;

				auto* component = visualComponents.get(visualComponents.begin());

				if (updateFlags)
					Update(*reinterpret_cast<fnd::SUpdateInfo*>(data));

				UpdateComponents(visualComponents, *reinterpret_cast<fnd::SUpdateInfo*>(data), 0);

				return true;
			}

			case 4:
			{
				if (statusFlags & 2)
					return true;

				if (updateFlags)
					UpdatePhase(*reinterpret_cast<fnd::SUpdateInfo*>(data), 1);

				UpdateComponents(physicsComponents, *reinterpret_cast<fnd::SUpdateInfo*>(data), 1);

				return true;
			}

			case 5:
			{
				if (statusFlags & 2)
					return true;

				if (updateFlags)
					UpdatePhase(*reinterpret_cast<fnd::SUpdateInfo*>(data), 2);

				UpdateComponents(audibleComponents, *reinterpret_cast<fnd::SUpdateInfo*>(data), 2);

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
			for (auto* it = components.begin(); it != components.end(); it++)
			{
				if ((*it)->GetFamilyID() == component->GetFamilyID())
					return false;
			}

			components.push_back(component);
			component->AddRef();
			component->SetGameObject(this);
			componentFlags |= component->componentStats;

			return true;
		}

		fnd::GOComponent* GetComponent(const char* name) const
		{
			for (auto* it = components.begin(); it != components.end(); it++)
			{
				auto* family = (*it)->GetFamilyID();
				if (family == name)
					return *it;
			}

			return nullptr;
		}

		template<typename T>
		T* GetComponent()
		{
			return (T*)GetComponent(T::staticClass()->familyID);
		}
		
		csl::ut::InplaceMoveArray<fnd::GOComponent*, 8>& GetComponents()
		{
			return components;
		}

		bool BroadcastMessageImmToGroup(uint group, fnd::Message& msg)
		{
			uint groupActor = ownerDocument->GetGroupActorID(group);
			if (!groupActor)
				return false;

			BroadcastMessageImm(groupActor, msg);
		}
	};

	inline void GameObject::Kill()
	{
		if (!(statusFlags & 1))
		{
			statusFlags |= 1;
			enabled = false;
		}
	}

	inline csl::fnd::IAllocator* GameObject::GetAllocator()
	{
		return csl::ut::Singleton<GameObjectSystem>::GetInstance()->GetPooledAllocator();
	}
}
