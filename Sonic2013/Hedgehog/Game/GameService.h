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
		GameDocument* pOwnerDocument{};
		const GameServiceClass* pClass{};
		void* Unk1{};
		void* Unk2{};
		unsigned int Flags{};

		GameService(ServiceType in_serviceType)
		{
			if (in_serviceType)
			{
				Flags = in_serviceType > 2 ? 0 : in_serviceType;
			}
			else
			{
				Flags = 0x2000;
			}
		}

		virtual void ResolveAccessibleService(GameDocument& in_rDocument) {}
		virtual void Load() {}
		virtual void EndLoad() {}
		virtual void PrepareToStartGame(bool in_a1) {}
		virtual void StartGame(bool in_a1) {}
		virtual void InitByScript(app::game::LuaScript& in_rScript) {}
		virtual void OnAddedToGame() {}
		virtual void OnRemovedFromGame() {}
		virtual void UpdateFinal(const SUpdateInfo& in_rUpdatdeInfo) {}

		bool ActorProc(int in_id, void* in_pData) override
		{
			if (in_id != 5)
				return CLeafActor::ActorProc(in_id, in_pData);

			UpdateFinal(*reinterpret_cast<const SUpdateInfo*>(in_pData));
			return true;
		}

		void SendMessageToGame(fnd::Message& in_rMessage)
		{
			SendMessage(pOwnerDocument->GetGameActorID(), in_rMessage);
		}

		bool SendMessageImmToGame(fnd::Message& in_rMessage)
		{
			return SendMessageImm(pOwnerDocument->GetGameActorID(), in_rMessage);
		}
	};
}

#pragma pop_macro("SendMessage")