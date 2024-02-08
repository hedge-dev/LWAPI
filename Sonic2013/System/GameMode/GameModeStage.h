#pragma once
#pragma push_macro("CreateService")
#undef CreateService

namespace app
{
	struct SGameModeStageCinfo
	{
		struct Mission
		{
			int Unk1{};
			int Unk2{};
		};

		const char* pStageName{};
		int NumChallenges{ 5 };
		csl::ut::Bitset<char> Flags{};
		byte RcType{ static_cast<byte>(-1) };
		byte RcVariant{};
		char Unk5{};
		char Unk6{};
		char IsSuperSonicUnlocked{};
		char Unk8{};
		char Unk9{};
		char Unk10{};
		char Unk11{};
		int Unk12{ -1 };
		int Unk13{};
		Game::CRecordTime RecordTimes[10]{};
		int TotalScore{};
		int TotalAnimals{};
		csl::ut::InplaceMoveArray<Mission, 3> Missions{ nullptr };

		bool IsRadioControlExist()
		{
			return RcType != static_cast<byte>(-1);
		}
	};

	struct alignas(16) SGameWarpInfo
	{
		INSERT_PADDING(52) {};
		int Unk1{};
		INSERT_PADDING(8) {};
	};

	class GameModeStage :
		public GameMode,
		public TTinyFsm<GameModeStage, GameModeUtil::Event<GameModeStage>, false>,
		TinyFsmSetOption<TiFSM_OPTION_USE_FP_TOP>
	{
	private:
		inline static FUNCTION_PTR(TiFsmState_t&, __thiscall, ms_fpStateLoad, ASLR(0x00918C80), GameModeStage*, TiFsmState_t&, const TiFsmEvent_t&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetupGameStatus, ASLR(0x00915AF0), GameModeStage*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetupMission, ASLR(0x00915D20), GameModeStage*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpResetStage, ASLR(0x00916BC0), GameModeStage*);

	public:
		struct SSuspendInfo
		{
			float Unk1{};
			int Unk2{};

			void Reset()
			{
				Unk1 = 0.0f;
				Unk2 = 0;
			}
		};

		class CSuspendMgr
		{
			INSERT_PADDING(84) {};
		};

		class CRedRingState
		{
		public:
			csl::ut::Bitset<char> Flags{};

			void Miss(CLevelInfo& in_rLevelInfo)
			{
				for (size_t i = 0; i < 5; i++)
					in_rLevelInfo.SetFlagRedRingObtained(i, Flags.test(i));
			}

			void Init(CLevelInfo& in_rLevelInfo, csl::ut::Bitset<byte> in_flags)
			{
				Flags = in_flags;
				Miss(in_rLevelInfo);
			}
		};

		SGameModeStageCinfo CreateInfo{};
		csl::ut::FixedString<16> StageName{};
		GameObject* pUnk2{}; // boost::intrusive_ptr<GameObject>
		GameObject* pUnk3{}; // boost::intrusive_ptr<GameObject>
		int Unk4{};
		int Unk5{};
		int Unk6{};
		int Unk7{};
		INSERT_PADDING(8) {}; // GameObjectHandle<HUD::CHudCountdown>
		INSERT_PADDING(8) {}; // GameObjectHandle<HUD::CHudTimeAttack>
		INSERT_PADDING(8) {}; // GameObjectHandle<HUD::HudMissionBanner>
		csl::ut::Bitset<uint> Flags{};
		int Unk8{};
		Camera::CCameraController* pUnk9{}; // boost::intrusive_ptr<Camera::CCameraController>
		Camera::CCameraController* pUnk10{}; // boost::intrusive_ptr<Camera::CCameraController>
		TInplaceArray<uint, 3, std::dummy::allocator<uint>> Unk11{ 0 };
		StageInfo::SStageData* pStageData{};
		int Unk12{};
		xgame::CStageSoundDirector* pStageSoundDirector{}; // boost::intrusive_ptr<xgame::CStageSoundDirector>
		int Unk13{};
		float Unk14{};
		float Unk15{};
		CLevelInfo* pLevelInfo{};
		SSuspendInfo SuspendInfo{};
		CSuspendMgr SuspendMgr{};
		CRedRingState RedRingState{};
		int Unk17{ 3 };
		SGameWarpInfo WarpInfo{};
		bool Unk18{};
		bool Unk19{};
		int Unk20{};
		float Unk21{ 1.0f };
		int Unk22{};
		int Unk23{};
		ut::RefPtr<xgame::StageGameStatus> rpStageGameStatus{};
		ut::RefPtr<StageDataInitializer> rpStageDataInitailizer{};
		INSERT_PADDING(4) {}; // ut::RefPtr<MyStageDataListener>
		int Unk24{};
		int Unk25{};
		INSERT_PADDING(4) {}; // ut::RefPtr<MyTimeStatusListener>
		ut::RefPtr<SceneFxDirector> rpSceneFxDirector{};
		float Unk26{};
		float Unk27{}; // xgame::SoftResetChecker
		float Unk28{};
		GameObjectHandle<ObjColorParamChanger> ColorParamChanger{};
		int NumHearts{ 3 };
		int MaxNumHearts{ 3 }; // TODO: Is this actually meaning of the value?
		int Unk31{ 3 };

		GameModeStage(const SGameModeStageCinfo& in_rCreateInfo)
			: GameMode()
			, CreateInfo(in_rCreateInfo)
			, StageName(in_rCreateInfo.pStageName)
		{
			FSM_INIT(&GameModeStage::StateLoad);
			SetName("GameModeStage");
			// pStageGameStatus = new(m_pAllocator) StageGameStatus({ 10 });
		}

		TiFsmState_t StateLoad(const TiFsmEvent_t& in_rEvent)
		{
			TiFsmState_t result{};
			ms_fpStateLoad(this, result, in_rEvent);

			return result;
		}

		void ChangeState(TiFsmState_t in_state)
		{
			FSM_TRAN(in_state);
		}

		bool IsPlayer(uint in_actorId) const
		{
			return pLevelInfo->IsPlayer(in_actorId);
		}

		SPlayerInfo* GetPlayerInfo(uint in_playerNo)
		{
			return pLevelInfo->GetPlayerInfo(in_playerNo);
		}

		void InitServices()
		{
			CreateService(static_cast<const fnd::GameServiceClass**>((void*)ASLR(0x00E05B20)));
		}

		void SetupPlayer()
		{
			auto* pMarkerStatus = GetCheckPointStatus();

			Player::SCinfo playerCreateInfo{};
			playerCreateInfo.Position = pMarkerStatus->Position;
			playerCreateInfo.Rotation = pMarkerStatus->Rotation;
			playerCreateInfo.DeadLine = rpStageDataInitailizer->DeadLine;
			playerCreateInfo.Flags.set(0, pMarkerStatus->Unk1);
			playerCreateInfo.Flags.set(1, pStageData->PlayerFlags.test(3));
			playerCreateInfo.Flags.set(2, pStageData->PlayerFlags.test(2));
			playerCreateInfo.Flags.set(3, pStageData->PlayerFlags.test(4));
			playerCreateInfo.Flags.set(5, CreateInfo.IsRadioControlExist());
			playerCreateInfo.Flags.set(4, CreateInfo.IsSuperSonicUnlocked);
			playerCreateInfo.Flags.set(8, pStageData->IsBakuBakuStage());
			playerCreateInfo.Flags.set(9, pStageData->PlayerFlags.test(1));
			playerCreateInfo.Flags.set(10, pStageData->IsDrawReflect());
			playerCreateInfo.Flags.set(11, pStageData->IsLastBossStage());
			playerCreateInfo.Flags.set(12, pStageData->IsZeldaStage());
			playerCreateInfo.Flags.set(13, pStageData->IsYoshiIslandStage());

			if (!pStageData->IsYoshiIslandStage() && !pStageData->IsZeldaStage())
				playerCreateInfo.Flags.set(14, false);
			else
				playerCreateInfo.Flags.set(14, true);

			playerCreateInfo.pPhantoms = pStageData->GetPhantoms();
			playerCreateInfo.EagleAltitude = pStageData->EagleAltitude * 10.0f;

			auto* pPlayer = Player::CreatePlayer(pDocument, playerCreateInfo);

			if (pLevelInfo && pPlayer)
				pLevelInfo->Players[0].ActorId = pPlayer->ActorID;
		
			if (pStageSoundDirector)
				pStageSoundDirector->InitPlayerGuidePathControl();

			RcCreateInfo rcCreateInfo{};
			rcCreateInfo.Position = pMarkerStatus->Position;
			rcCreateInfo.Rotation = pMarkerStatus->Rotation;
			rcCreateInfo.Type = CreateInfo.RcType;
			rcCreateInfo.Variant = CreateInfo.RcVariant;
			rcCreateInfo.Unk1 = CreateInfo.Unk5;

			CreateRCObject(*pDocument, rcCreateInfo, *game::GlobalAllocator::GetAllocator(2));
		}

		void InitFirst()
		{
			Flags.set(0);

			InitServices();

			Unk11.push_back_unchecked(32759);

			Flags.set(25, pStageData->IsDLCStage());

			auto* pLevelInfoService = pDocument->GetService<CLevelInfo>();
			if (pLevelInfoService)
			{
				pLevelInfoService->Level = findFileName(pStageData->Directory.c_str());
				pLevelInfoService->ReflectStageInfo(*pStageData);
			
				pLevelInfoService->SetPlayMode((Game::EPlayMode)(CreateInfo.Unk8 != 0));

				if (Flags.test(25))
				{
					if (pStageData->IsYoshiIslandStage())
					{
						pLevelInfoService->SetDLCStage(2);
					}
					else if (pStageData->IsZeldaStage())
					{
						pLevelInfoService->SetDLCStage(3);
					}
					else
					{
						pLevelInfoService->SetDLCStage(1);
					}
				}

				pLevelInfo = pLevelInfoService;
			}

			auto* pGameScoreManager = pDocument->GetService<xgame::GameScoreManager>();
			pGameScoreManager->SetTotalScore(CreateInfo.TotalScore);

			SetupGameStatus();

			xgame::StagePhysicsSetup::SetupWorld(pDocument);

			for (size_t i = 0; i < 2; i++)
				GetPlayerInfo(i)->NumChallenges = CreateInfo.NumChallenges;
		
			/*xgame::CStageSoundDirector* pSoundDirector = xgame::CStageSoundDirector::Create(pStageData, pLevelInfo);
			if (pSoundDirector)
				pStageSoundDirector = pSoundDirector;
		
			pDocument->AddGameObject(pStageSoundDirector);

			SceneFxDirector* pSceneDirector = SceneFxDirector::Create(GetAllocator());
			if (pSceneDirector)
				rpSceneFxDirector = pSceneDirector;

			pDocument->AddGameObject(rpSceneFxDirector.get());

			auto* pEffectManager = pDocument->GetService<Effect::CEffectManager>();
			if (pEffectManager)
				pEffectManager->SetStageName(StageName);

			ColorParamChanger = ObjColorParamChanger::Create(GetAllocator());
			pDocument->AddGameObject(ColorParamChanger.Get());*/

			csl::fnd::Singleton<gfx::RenderManager>::GetInstance()->SetDRCRenderMode(3);
			ResetStage();
		}

		void SetupGameStatus()
		{
			ms_fpSetupGameStatus(this);
		}

		void SetupMission()
		{
			ms_fpSetupMission(this);
		}

		void ResetStage()
		{
			ms_fpResetStage(this);

			/*Flags.reset(1);
			SuspendInfo.Reset();

			csl::ut::Bitset<byte> flags{ CreateInfo.Flags };
			RedRingState.Init(*pLevelInfo, flags);

			pUnk9 = nullptr;
			pUnk10 = nullptr;

			rpStageGameStatus->ResetForRestart();

			Unk23 = 0;
			Unk30 = 3;
			Unk31 = 3;

			for (size_t i = 0; i < 2; i++)
				GetPlayerInfo(i)->NumChallenges = CreateInfo.NumChallenges;

			SetupMission();
			
			auto* pColorParamChanger = ColorParamChanger.Get();
			if (pColorParamChanger)
				pColorParamChanger->Restart();

			Unk30 = 3;

			auto* pLevelInfoService = pDocument->GetService<CLevelInfo>();
			pLevelInfoService->SetPlayingZeldaEvent(false);*/
		}

		const xgame::MarkerStatus* GetCheckPointStatus()
		{
			return rpStageGameStatus->GetStatus<xgame::StatusCheckPoint>()->GetMarker();
		}

		void RegisterObjInfos()
		{
			Player::ResourceInfo resourceInfo{};
			resourceInfo.pPhantoms = pStageData->GetPhantoms();
			resourceInfo.Flags.set(0, pStageData->PlayerFlags.test(2));
			resourceInfo.Flags.set(1, pStageData->PlayerFlags.test(4));
			resourceInfo.Flags.set(3, CreateInfo.IsSuperSonicUnlocked);
			resourceInfo.Flags.set(4, pStageData->IsZeldaStage());
			Player::RegisterResourceInfos(pDocument, resourceInfo, *game::GlobalAllocator::GetAllocator(2));

			RcInfo rcResourceInfo{};
			rcResourceInfo.Type = CreateInfo.RcType;
			rcResourceInfo.Variant = CreateInfo.RcVariant;
			RegisterResourceInfo(*pDocument, rcResourceInfo, *game::GlobalAllocator::GetAllocator(2));

			worldmap::CWorldMapDioramaStage::RegisterResourceInfo(*pDocument, StageName.c_str(), *game::GlobalAllocator::GetAllocator(2));
		}

		const char* findFileName(const char* in_pDirectoryName)
		{
			const char* fileName = strrchr(in_pDirectoryName, '/');
			if (fileName)
				return fileName + 1;
			
			return in_pDirectoryName;
		}
	};
}

#pragma pop_macro("CreateService")