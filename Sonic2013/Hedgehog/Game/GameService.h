#pragma once
#pragma push_macro("SendMessage")
#undef SendMessage

namespace app::fnd
{
	class GameService;
	typedef GameService* __cdecl initializeService(csl::fnd::IAllocator* allocator);
	typedef uint ServiceType;

	class GameService : public ReferencedObject, public CLeafActor
	{
		friend GameServiceClass;

	public:
		GameDocument* m_pOwnerDocument{};
		const GameServiceClass* m_pClass{};
		void* m_Unk1{};
		void* m_Unk2{};
		unsigned int m_Flags{};

		GameService(ServiceType serviceType)
		{
			if (serviceType)
			{
				m_Flags = serviceType > 2 ? 0 : serviceType;
			}
			else
			{
				m_Flags = 0x2000;
			}
		}

	public:
		virtual void ResolveAccessibleService(GameDocument& document) {}
		virtual void Load() {}
		virtual void EndLoad() {}
		virtual void PrepareToStartGame(bool a1) {}
		virtual void StartGame(bool a1) {}
		virtual void InitByScript(app::game::LuaScript& script) {}
		virtual void OnAddedToGame() {}
		virtual void OnRemovedFromGame() {}
		virtual void UpdateFinal(const SUpdateInfo& updatdeInfo) {}

		bool ActorProc(int id, void* data) override
		{
			if (id != 5)
				return CLeafActor::ActorProc(id, data);

			UpdateFinal(*reinterpret_cast<const SUpdateInfo*>(data));
			return true;
		}

		void SendMessageToGame(fnd::Message& msg)
		{
			SendMessage(m_pOwnerDocument->GetGameActorID(), msg);
		}

		bool SendMessageImmToGame(fnd::Message& msg)
		{
			return SendMessageImm(m_pOwnerDocument->GetGameActorID(), msg);
		}
	};

	inline GameService* app::fnd::GameServiceClass::Construct(csl::fnd::IAllocator* allocator) const
	{
		GameService* service = m_pInitializer(allocator);
		service->m_pClass = this;

		return service;
	}
}

#pragma pop_macro("SendMessage")