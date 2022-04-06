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
	public:
		enum FadeScreenType;
		friend CGame;
		friend CGameSequence;
		inline static const fnd::GameServiceClass* ms_DefaultServices[] = { nullptr };

	public:
		CGame* m_pGame{};
		void* m_Unk1{};
		const char* m_pName{ "UnnamedMode" };
		GameDocument* m_pDocument{};
		app::ut::RefPtr<ReferencedObject> m_rpDisplaySwitchListener{};
	
	public:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpDefaultGameLoop, ASLR(0x004AC9B0), GameMode*, const fnd::SUpdateInfo&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpInitializeGameMode, ASLR(0x004ACAF0), GameMode*, CGame&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpDestroy, ASLR(0x004AC7C0), GameMode*, CGame&);
		inline static FUNCTION_PTR(void, __stdcall, ms_fpBlackout, ASLR(0x004AC560), float, FadeScreenType);
		inline static FUNCTION_PTR(void, __stdcall, ms_fpWhiteout, ASLR(0x004AC590), float, FadeScreenType);
		inline static FUNCTION_PTR(void, __stdcall, ms_fpFadeIn, ASLR(0x004AC5C0), float, FadeScreenType);

		GameMode()
		{
			
		}
		
		virtual void OnEnter(CGame& in_game);
		virtual void OnLeave(CGame& in_game);
		virtual void Update(CGame& in_game, const fnd::SUpdateInfo& in_updateInfo)
		{
			DefaultGameLoop(in_updateInfo);
		}

		virtual bool ProcessMessage(CGame& in_game, fnd::Message& in_msg)
		{
			return false;
		}

		virtual bool PreProcessMessage(CGame& in_game, fnd::Message& in_msg)
		{
			return false;
		}

		static bool IsLoadEnd();
		static void LoadFile(const char* in_pName, const fnd::FileLoaderParam& in_param);
		static void PreLoadFile(const char* in_pName, int in_priority);

		void SendToGroup(uint in_group, fnd::Message& in_msg) const;
		bool CreateService(const char* in_pName);
		void CreateService(const fnd::GameServiceClass** in_ppClasses);
		void DefaultGameLoop(const fnd::SUpdateInfo& in_updateInfo)
		{
			ms_fpDefaultGameLoop(this, in_updateInfo);
		}

		void InitializeGameMode(CGame& in_game)
		{
			ms_fpInitializeGameMode(this, in_game);
		}

		void ReleaseGameMode()
		{
			m_pGame = nullptr;
		}

		void Destroy(CGame& in_game)
		{
			ms_fpDestroy(this, in_game);
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
			return m_pDocument;
		}
		
		const char* GetName() const
		{
			return m_pName;
		}
		
		CGame* GetGame() const
		{
			return m_pGame;
		}

		void SetName(const char* in_pName)
		{
			m_pName = in_pName;
		}

		void* operator new (size_t size)
		{
			return ReferencedObject::operator new(size, game::GlobalAllocator::GetAllocator(2));
		}

		enum FadeScreenType
		{
			
		};
	};
}

#pragma pop_macro("CreateService")