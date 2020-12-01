#pragma once

namespace app::fnd
{
	class GameService;
	typedef GameService* initializeService(csl::fnd::IAllocator& allocator);
	typedef void RflClass;
	
	class GameServiceClass
	{
		const char* name;
		initializeService* serviceInitializer;
		RflClass* rflClass;

	public:
		GameServiceClass(const char* nam, initializeService* initializer, RflClass* cls = nullptr) : name(nam), serviceInitializer(initializer), rflClass(cls)
		{
			
		}
	};

	class GameService : public ReferencedObject, public CLeafActor
	{
	protected:
		GameDocument* document{};
		const char* serviceName{};
		void* unk1{};
		void* unk2{};
		
	public:
		virtual void ResolveAccessibleService(GameDocument& document) {}
		virtual void Load() {}
		virtual void EndLoad() {}
		virtual void PrepareToStartGame() {}
		virtual void StartGame() {}
		virtual void InitByScript(void* script) {}
		virtual void OnAddedToGame() {}
		virtual void OnRemovedFromGame() {}
		virtual void UpdateFinal(SUpdateInfo& updatdeInfo) {}

		bool ActorProc(int id, void* data) override
		{
			if (id != 5)
				return CLeafActor::ActorProc(id, data);

			UpdateFinal(reinterpret_cast<SUpdateInfo&>(data));
			return true;
		}
	};
}