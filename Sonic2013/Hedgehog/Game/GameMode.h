#pragma once
#pragma push_macro("CreateService")
#undef CreateService

namespace app
{
	namespace fnd
	{
		struct FileLoaderParam;
	}

	class GameMode : public fnd::ReferencedObject
	{
		enum FadeScreenType;
		friend CGame;
		friend CGameSequence;
		inline static const fnd::GameServiceClass* ms_DefaultServices[] = { nullptr };

	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpDefaultGameLoop, ASLR(0x004AC9B0), GameMode*, const fnd::SUpdateInfo&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpInitializeGameMode, ASLR(0x004ACAF0), GameMode*, CGame&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpDestroy, ASLR(0x004AC7C0), GameMode*, CGame&);
		inline static FUNCTION_PTR(void, __stdcall, ms_fpBlackout, ASLR(0x004AC560), float, FadeScreenType);
		inline static FUNCTION_PTR(void, __stdcall, ms_fpWhiteout, ASLR(0x004AC590), float, FadeScreenType);
		inline static FUNCTION_PTR(void, __stdcall, ms_fpFadeIn, ASLR(0x004AC5C0), float, FadeScreenType);

	public:
		CGame* pGame{};
		void* pUnk1{};
		const char* pName{ "UnnamedMode" };
		GameDocument* pDocument{};
		app::ut::RefPtr<ReferencedObject> rpDisplaySwitchListener{};

		GameMode()
		{
			
		}
		
		virtual void OnEnter(CGame& in_rGame);
		virtual void OnLeave(CGame& in_rGame);
		virtual void Update(CGame& in_rGame, const fnd::SUpdateInfo& in_rUpdateInfo)
		{
			DefaultGameLoop(in_rUpdateInfo);
		}

		virtual bool ProcessMessage(CGame& in_rGame, fnd::Message& in_rMessage)
		{
			return false;
		}

		virtual bool PreProcessMessage(CGame& in_rGame, fnd::Message& in_rMessage)
		{
			return false;
		}

		static bool IsLoadEnd();
		static void LoadFile(const char* in_pName, const fnd::FileLoaderParam& in_rParam);
		static void PreLoadFile(const char* in_pName, int in_priority);

		void SendToGroup(uint in_group, fnd::Message& in_rMessage) const;
		bool CreateService(const char* in_pName);
		void CreateService(const fnd::GameServiceClass** in_ppClasses);
		void DefaultGameLoop(const fnd::SUpdateInfo& in_rUpdateInfo)
		{
			ms_fpDefaultGameLoop(this, in_rUpdateInfo);
		}

		void InitializeGameMode(CGame& in_rGame)
		{
			ms_fpInitializeGameMode(this, in_rGame);
		}

		void ReleaseGameMode()
		{
			pGame = nullptr;
		}

		void Destroy(CGame& in_rGame)
		{
			ms_fpDestroy(this, in_rGame);
		}

		inline static void Blackout(float in_time, FadeScreenType in_type)
		{
			ms_fpBlackout(in_time, in_type);
		}

		inline static void Whiteout(float in_time, FadeScreenType in_type)
		{
			ms_fpWhiteout(in_time, in_type);
		}

		inline static void FadeIn(float in_time, FadeScreenType in_type)
		{
			ms_fpFadeIn(in_time, in_type);
		}

		GameDocument* GetGameDocument() const
		{
			return pDocument;
		}
		
		const char* GetName() const
		{
			return pName;
		}
		
		CGame* GetGame() const
		{
			return pGame;
		}

		void SetName(const char* in_pName)
		{
			pName = in_pName;
		}

		void* operator new (size_t in_size)
		{
			return ReferencedObject::operator new(in_size, game::GlobalAllocator::GetAllocator(2));
		}

		enum FadeScreenType
		{
			
		};
	};
}

#pragma pop_macro("CreateService")