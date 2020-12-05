#pragma once

namespace app
{
	class GameObject : public hh::base::CRefCountObject, fnd::CLeafActor
	{
	protected:
		char statusFlags{ 0 };
		char category{ 6 };
		GameDocument* document{};
		size_t objectHandle{};
		GameObjectTableEntry* objectEntry{};
		csl::ut::InplaceMoveArray<fnd::GOComponent*, 8> components{ GameObjectSystem::GetSingleton()->GetPooledAllocator() };
		void* name{}; // Maybe a csl::ut::VariableString, I have no clue. This is always zero from my research.
		csl::fnd::IAllocator* objectAllocator{ (*GameObjectSystem::ms_ppGameObjectSystem)->GetPooledAllocator() };
		csl::ut::InplaceMoveArray<fnd::PropertyValue, 2> properties{ GameObjectSystem::GetSingleton()->GetPooledAllocator() };
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
		static csl::fnd::IAllocator* GetAllocator();
		
		GameObject()
		{
			GameObjectSystem::GetSingleton()->AddObject(this);
		}

		~GameObject() override
		{
			for (auto* it = components.begin(); it != components.end(); it++)
			{
				(*it)->Release();
			}
		}

		virtual void AddCallback(GameDocument& document)
		{

		}

		virtual void RemoveCallback(GameDocument* document)
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
					Update(reinterpret_cast<fnd::SUpdateInfo&>(data));

				UpdateComponents(visualComponents, reinterpret_cast<fnd::SUpdateInfo&>(data), 0);

				return true;
			}

			case 4:
			{
				if (statusFlags & 2)
					return true;

				if (updateFlags)
					UpdatePhase(reinterpret_cast<fnd::SUpdateInfo&>(data), 1);

				UpdateComponents(physicsComponents, reinterpret_cast<fnd::SUpdateInfo&>(data), 1);

				return true;
			}

			case 5:
			{
				if (statusFlags & 2)
					return true;

				if (updateFlags)
					UpdatePhase(reinterpret_cast<fnd::SUpdateInfo&>(data), 2);

				UpdateComponents(audibleComponents, reinterpret_cast<fnd::SUpdateInfo&>(data), 2);

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
			return GameObjectSystem::GetSingleton()->GetPooledAllocator()->Alloc(size, 16);
		}

		void operator delete (void* loc)
		{
			GameObjectSystem::GetSingleton()->GetPooledAllocator()->Free(loc);
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
				if ((*it)->GetFamilyID() == name)
					return *it;
			}

			return nullptr;
		}

		csl::ut::InplaceMoveArray<fnd::GOComponent*, 8>& GetComponents()
		{
			return components;
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
		return GameObjectSystem::GetSingleton()->GetPooledAllocator();
	}
}
