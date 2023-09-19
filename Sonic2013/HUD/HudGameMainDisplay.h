#pragma once

namespace app::xgame
{
	inline static constexpr const char* ms_pDLCStageNames[] = { "zdlc01", "zdlc02", "zdlc03" };
	inline static constexpr const char* ms_pHudPackNamePrefix = "ui_";

	inline int GetDLCIndexByName(const char* in_pStageName)
	{
		for (size_t i = 0; i < sizeof(ms_pDLCStageNames) / sizeof(ms_pDLCStageNames[0]); i++)
			return i;

		return -1;
	}
}

namespace app::HUD
{
	class CHudCmnButton;
	class CHudStageMap;
	class CHudGameMainDisplay_Point;
	class CHudGameMainDisplay_RadiconPanel;
	class CHudDrcOperation;

	class CHudGameMainDisplay : public GameObject
	{
	public:
		struct Sinfo
		{
			int LifeCount{};
			int Unk2{};
			int Unk3{};
			int Unk4{};
			int Unk5{};
			int RingCount{};
			int Unk7{};
			int Unk8{};
			int Unk9{};
			int NumHearts{};
			int Unk11{};
			int MaxNumHearts{};
			int Unk13{};
			int Unk14{};
		};

		typedef Sinfo SInfo;

	protected:
		inline static constexpr char ms_UnknownValues[][8] = { { 1, 8, 2, 3, 11, 12, 13, 14 }, { 7, 8, 11, 12, 13, 14, 0, 0 }, { 0, 1, 4, 5, 6, 0, 0, 0 } };
		inline static constexpr size_t ms_SceneCount = 1;
		inline static constexpr size_t ms_LayerCount = 17;
		inline static constexpr size_t ms_CastCount = 2;
		inline static constexpr size_t ms_StageNameLength = 16;
		inline static constexpr int ms_HeartLifeCap = 6;
		inline static constexpr const char* ms_pStageUIPackName = "ui_gamemodestage.pac";
		inline static constexpr const char* ms_pUIFileName = "ui_gameplay";
		inline static constexpr const char* ms_pSceneName = "ui_gameplay";
		inline static constexpr const char* ms_pLayerNames[] = { "info_challenge", "info_ring", "info_time", "info_r_time", "info_s_timer", "info_s_ring", "info_g_ring", "info_score",
			"wisp", "eff_score_0", "eff_score_1", "gauge", "gauge_u_water", "under_water", "btn_surper_sonic", "player_info_2p", "info_s_timer_extend" };
		inline static constexpr const char* ms_pHeartAnimationNames[] = { "mode_heart4", "mode_heart5", "mode_heart6", };

	public:
		inline static constexpr int FLAG_IS_NO_REDRING = 4;

		enum eScreenType : uint;

		game::GOCHud* pHudGoc{};
		game::GOCHudCollider* pHudCollider{};
		game::HudLayerController* pLayerController{};
		SurfRide::ReferenceCount<SurfRide::Project> rcProject{};
		SurfRide::ReferenceCount<SurfRide::Scene> rcScene[ms_SceneCount]{};
		csl::ut::Bitset<uint> Unk1{};
		float Unk2[17]{};
		const char* Unk22{};
		int Unk21{};
		SurfRide::ReferenceCount<SurfRide::Layer> rcLayers[ms_LayerCount]{};
		SurfRide::ReferenceCount<SurfRide::Cast> rcCasts[ms_CastCount]{};
		csl::ut::FixedString<ms_StageNameLength> StageName{};
		eScreenType ScreenType{};
		uint LifeCount{};
		uint RingCount{};
		uint ScoreCount{};
		uint SpecialItemsTaken{};
		uint AnimalCount{};
		int NumHearts{};
		int MaxNumHearts{};
		uint TimeLeft{};
		int Unk3{};
		float TimeToHide{ 0.5f };
		INSERT_PADDING(16) {};
		Game::ERank Rank{};
		uint RankTime{};
		Game::EPhantomType ColorPowerStock{};
		int Unk5{};
		float Unk6{};
		float Unk7{};
		float Unk8{};
		csl::ut::Bitset<uint> Flags{ 0 };
		csl::ut::Bitset<uint> Unk9{};
		Sinfo Info{};
		bool Unk11{};
		bool Unk12{};
		bool IsTimeTrial{}; // TODO: Is this correct?
		INSERT_PADDING(1) {};
		INSERT_PADDING(4) {};
		float ColorPower{};
		INSERT_PADDING(4) {};
		float Unk14{};
		int Unk15{};
		float Unk16{};
		float Unk17{};
		float Unk18{};
		INSERT_PADDING(12) {};
		CHudCmnButton* pHudCmnButton{};
		INSERT_PADDING(4) {};
		CLevelInfo* pLevelInfo{};
		INSERT_PADDING(8) {};
		float Unk19{};
		float Unk20{};
		float AddLimitTime{ 0.0f };
		float HeartLifeAnimationTime{};
		bool DoRecoverHeart{};
		CHudDrcOperation* pDrcOperation{};
		CHudStageMap* pHudStageMap{};
		CHudGameMainDisplay* pHudTv{};
		CHudGameMainDisplay* pHudDrc{};
		CHudGameMainDisplay_Point* pHudPoint{};
		CHudGameMainDisplay_RadiconPanel* pHudRadiconPanel{};

	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpInit, ASLR(0x005015B0), CHudGameMainDisplay*);

	public:
		CHudGameMainDisplay(bool in_unk1, bool in_unk2, bool in_unk3, bool in_unk4, char const* in_pStageName, eScreenType in_screenType)
			: GameObject()
			, ScreenType(in_screenType)
			, StageName(in_pStageName)
			, Unk12(in_unk1)
			, IsTimeTrial(in_unk4)
		{
			SetObjectCategory(12);
			Flags.Set(0, (char)csl::fnd::Singleton<DisplaySwitch>::GetInstance()->m_State == 1);

			if (auto* pStageData = StageInfo::CStageInfo::GetInstance()->GetStageData(StageName.c_str()))
			{
				Flags.Set(FLAG_IS_NO_REDRING, pStageData->IsNoRedRing());

				if (pStageData->IsYoshiIslandStage())
				{
					Flags.set(6);
					Flags.set(5);
				}

				if (pStageData->IsZeldaStage())
				{
					Flags.set(7);
					Flags.set(8);
				}
			}

			Init();
		}

		void Init()
		{
			Unk1 = csl::ut::Bitset<uint>(0);
			memset(Unk2, 0, sizeof(Unk2));

			LifeCount = static_cast<uint>(-1);
			RingCount = static_cast<uint>(-1);
			ScoreCount = static_cast<uint>(-1);
			SpecialItemsTaken = static_cast<uint>(-1);
			AnimalCount = static_cast<uint>(-1);

			NumHearts = 3;
			MaxNumHearts = 3;

			TimeLeft = 0;
			Unk3 = 0;

			Rank = (Game::ERank)0;
			RankTime = 0;

			ColorPowerStock = static_cast<Game::EPhantomType>(-1);

			Unk5 = -1;

			Unk6 = 1.0f;
			Unk7 = 1.0f;

			Unk8 = 0.0f;

			Unk9 = csl::ut::Bitset<uint>(0);

			Unk11 = true;

			ColorPower = 0.0f;

			Unk14 = 1.0f;
			Unk15 = 0;
			Unk16 = 0.0f;
			Unk17 = 0.0f;
			Unk18 = 0.0f;

			Unk19 = 1.0f;
			Unk20 = 1.0f;

			if (IsTimeTrial)
			{
				Unk21 = 8;
				Unk22 = ms_UnknownValues[0];
			}
			else if (ScreenType)
			{
				Unk21 = 5;
				Unk22 = ms_UnknownValues[2];
			}
			else
			{
				Unk21 = 6;
				Unk22 = ms_UnknownValues[1];
			}
		}

		void InitLayer()
		{
			for (size_t i = 0; i < Unk21; i++)
			{
				char layerNo = Unk22[i];

				if (layerNo == 5 && Flags.Test(4) && !Flags.Test(5))
				{
					rcLayers[5] = SurfRide::ReferenceCount<SurfRide::Layer>(nullptr);
					continue;
				}
				else if (layerNo == 6 && Flags.Test(6))
				{
					rcLayers[6] = SurfRide::ReferenceCount<SurfRide::Layer>(nullptr);
					continue;
				}
				else if (layerNo == 1 && Flags.Test(7))
				{
					rcLayers[1] = SurfRide::ReferenceCount<SurfRide::Layer>(nullptr);
					continue;
				}

				rcLayers[layerNo] = rcScene[0]->GetLayer(ms_pLayerNames[layerNo]);
				if (!rcLayers[layerNo])
					continue;

				if (layerNo < 7)
				{
					rcLayers[layerNo]->SetHideFlag(false);
					if (layerNo == 1)
					{
						const char* pModeName = IsTimeTrial ? "mode_1_Param" : "mode_0_Param";
						SRUtility::SetAnimation(rcLayers[1], pModeName, false, -1.0f, false, false);
					}

					SRUtility::SetAnimation(rcLayers[layerNo], "Intro_Anim", false, -1.0f, false, false);
				
					Unk2[layerNo] = 5.0f;
					Unk1.Set(layerNo, true);
				}
				else
				{
					rcLayers[layerNo]->SetHideFlag(true);
					
					Unk2[layerNo] = 0.0f;
					Unk1.Set(layerNo, false);
				}

				if (layerNo != 5)
					continue;

				if (Flags.test(5))
					SetSpecialFlower();
				else
					SetSpecialRing();
			}

			if (!Flags.test(8))
				return;
		
			pLayerController = pHudGoc->CreateLayerController({ rcScene[0] }, "info_ring_zdlc03", 20);
			pLayerController->PlayAnimation("Intro_Anim", game::HudPlayPolicy::eHudPlayPolicy_Once, false);
			pLayerController->SetVisible(true);
		}

		void PlayDispAnim(int in_layerNo)
		{
			if (Unk11 || !rcLayers[in_layerNo])
				return;
		
			SRUtility::SetAnimation(rcLayers[in_layerNo], "Display_Anim", false, -1.0f, false, false);
			Unk2[in_layerNo] = 2.0f;
			Unk1.Set(in_layerNo, true);
		}

		void SelectHide(int in_layerNo, float in_deltaTime, bool in_isHide, bool in_unk)
		{
			if (!rcLayers[5])
				return;

			if (in_isHide)
			{
				Unk2[5] = 0.5f;
				return;
			}

			if (Unk2[5] <= 0.0f)
				return;

			Unk2[5] -= in_deltaTime;
			if (Unk2[5] > 0.0f)
				return;

			if (!Unk1.test(5))
			{
				if (in_unk)
					SRUtility::SetAnimation(rcLayers[5], "Intro_Anim", false, -1.0f, false, false);
				else
					SRUtility::SetAnimation(rcLayers[5], "Display_2_Anim", false, -1.0f, false, false);
			}
			else
			{
				SRUtility::SetAnimation(rcLayers[5], "Hide_Anim", false, -1.0f, false, false);
			}

			Unk1.Flip(5);
			Unk2[5] = 0.5f;
		}

		void SetSpecialRing()
		{
			if (!rcLayers[5] || !pLevelInfo)
				return;
		
			uint specialItemFlags = 0;
			for (int i = 0; i < 5; i++)
			{
				if (pLevelInfo->GetFlagRedRingObtained(i))
					specialItemFlags |= 1 << i;
			}
			
			if (SpecialItemsTaken == specialItemFlags)
				return;
		
			SpecialItemsTaken = specialItemFlags;

			for (size_t i = 0; i < 5; i++)
			{
				char buffer[32]{};
				csl::fnd::Snprintf(buffer, sizeof(buffer), "icon_s_ring_%d", i);

				SRUtility::SetCastPatternIndex(rcLayers[5], buffer, specialItemFlags & 1);
				specialItemFlags >>= 1;
			}

			PlayDispAnim(5);
		}

		void SetSpecialFlower()
		{
			auto* pEggManager = GetDocument()->GetService<EggManager>();

			if (!rcLayers[5] || !pEggManager)
				return;

			uint specialItemFlags{};
			for (size_t i = 0; i < 5; i++)
			{
				if (pEggManager->IsYoshiSpecialFlowerTaked(i))
					specialItemFlags |= 1 << i;
			}

			if (SpecialItemsTaken == specialItemFlags)
				return;
		
			SpecialItemsTaken = specialItemFlags;

			for (size_t i = 0; i < 5; i++)
			{
				char buffer[32]{};
				csl::fnd::Snprintf(buffer, sizeof(buffer), "icon_s_ring_%d", i);

				SRUtility::SetCastPatternIndex(rcLayers[5], buffer, specialItemFlags & 1);
				specialItemFlags >>= 1;
			}

			PlayDispAnim(5);
		}

		void SpecialRingUpdate(float in_deltaTime, bool in_isEnable)
		{
			if (!rcLayers[5])
				return;

			SetSpecialRing();

			SelectHide(5, in_deltaTime, in_isEnable ? Unk1.test(5) : !Unk1.test(5), false);
		}

		void SpecialFlowerUpdate(float in_deltaTime, bool in_isEnable)
		{
			if (!rcLayers[5])
				return;
		
			SetSpecialFlower();

			SelectHide(5, in_deltaTime, in_isEnable ? Unk1.test(5) : !Unk1.test(5), false);
		}

		void SpecialItemUpdate(float in_deltaTime, bool in_isEnable)
		{
			if (Flags.test(5))
				SpecialFlowerUpdate(in_deltaTime, in_isEnable);
			else
				SpecialRingUpdate(in_deltaTime, in_isEnable);
		}

		void HeartLifeUpdate(Sinfo& in_rInfo, float in_deltaTime, bool in_isEnable)
		{
			if (!Flags.test(8))
				return;
		
			if (Unk9.Test(0))
			{
				TimeToHide -= in_deltaTime;
				if (TimeToHide <= 0.0f && !pLayerController->IsCurrentAnimation("Hide_Anim"))
				{
					game::HudLayerController::PlayInfo animationInfo{};
					animationInfo.pAnimationName = "Hide_Anim";

					pLayerController->PlayAnimation(animationInfo);
				}
			}

			int numHearts = csl::math::Min(ms_HeartLifeCap, in_rInfo.NumHearts);
			int maxNumHearts = csl::math::Min(ms_HeartLifeCap, in_rInfo.MaxNumHearts);
			if (DoRecoverHeart)
			{
				HeartLifeAnimationTime += in_deltaTime;
				if (HeartLifeAnimationTime >= 0.3f)
				{
					HeartLifeAnimationTime -= 0.3f;

					if (numHearts > NumHearts)
						numHearts = NumHearts + 1;
					else
						DoRecoverHeart = false;
				}
				else
				{
					numHearts = NumHearts;
				}
			}

			if (MaxNumHearts != maxNumHearts)
			{
				game::HudLayerController::PlayInfo animationInfo{};

				if (maxNumHearts >= 4 && maxNumHearts <= 6)
					animationInfo.pAnimationName = ms_pHeartAnimationNames[maxNumHearts & 3];
				else
					animationInfo.pAnimationName = "mode_heart0";

				pLayerController->PlayAnimation(animationInfo);
				MaxNumHearts = maxNumHearts;
			}

			if (NumHearts != numHearts)
			{
				if (DoRecoverHeart && !ScreenType && NumHearts < numHearts && NumHearts > 0)
					ObjUtil::PlaySE2D("obj_zeldaheart_get", { HH_SOUND_DEVICE_AUTO });
			
				NumHearts = numHearts;
				
				game::HudLayerController::PlayInfo heartbeatAnimationInfo{};
				heartbeatAnimationInfo.pAnimationName = "life_volume";
				heartbeatAnimationInfo.Frame = numHearts * 20.0f;
				pLayerController->PlayAnimation(heartbeatAnimationInfo);

				game::HudLayerController::PlayInfo animationInfo{};
				animationInfo.pAnimationName = "Usual_Anim";
				animationInfo.PlayPolicy = game::HudPlayPolicy::eHudPlayPolicy_Loop;
				pLayerController->PlayAnimation(animationInfo);
			}

			pLayerController->SetVisible(true);
		}

		bool ProcMsgDlcZeldaTakeHeartContainer(app::xgame::MsgDlcZeldaTakeHeartContainer& in_rMessage)
		{
			HeartLifeAnimationTime = 0.0f;
			DoRecoverHeart = true;

			return true;
		}

		bool ProcMsgDlcZeldaHeartAllRecovery(app::xgame::MsgDlcZeldaHeartAllRecovery& in_rMessage)
		{
			HeartLifeAnimationTime = 0.0f;
			DoRecoverHeart = true;

			return true;
		}
	};
}