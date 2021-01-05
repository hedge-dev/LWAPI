#pragma once

namespace app::fnd
{
	class GameService;
	typedef GameService* initializeService(csl::fnd::IAllocator* allocator);
	typedef void RflClass;
	typedef uint ServiceType;
	
	class GameServiceClass
	{
		const char* name;
		initializeService* serviceInitializer;
		RflClass* rflClass;

	public:
		GameServiceClass(const char* nam, initializeService* initializer, RflClass* cls = nullptr) : name(nam), serviceInitializer(initializer), rflClass(cls)
		{
			
		}

		[[nodiscard]] const char* GetName() const
		{
			return name;
		}

		[[nodiscard]] GameService* Construct(csl::fnd::IAllocator* allocator) const;
	};

	class GameService : public ReferencedObject, public CLeafActor
	{
		friend GameServiceClass;

	protected:
		GameDocument* document{};
		const GameServiceClass* serviceClass{};
		void* unk1{};
		void* unk2{};
		unsigned int flags{};

		GameService(ServiceType serviceType)
		{
			if (serviceType)
			{
				flags = serviceType > 2 ? 0 : serviceType;
			}
			else
			{
				flags = 0x2000;
			}
		}

	public:
		virtual void ResolveAccessibleService(GameDocument& document) {}
		virtual void Load() {}
		virtual void EndLoad() {}
		virtual void PrepareToStartGame(bool a1) {}
		virtual void StartGame(bool a1) {}
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

	inline GameService* app::fnd::GameServiceClass::Construct(csl::fnd::IAllocator* allocator) const
	{
		GameService* service = serviceInitializer(allocator);
		service->serviceClass = this;

		return service;
	}
}