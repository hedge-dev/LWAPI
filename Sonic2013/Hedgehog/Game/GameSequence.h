#pragma once

namespace app
{
	namespace StageInfo
	{
		class SStageData;
	}

	class CGame;
	enum RcType;
	class GameMode;

	struct WorldAreaMapCInfo
	{
	public:
		struct Event
		{
			enum class EEventType : int
			{
				eEventType_StageUnlocked,
				eEventType_WorldUnlocked,
				eEventType_BattleStageUnlocked,
				eEventType_MinigameOpened,
				eEventType_MinigameClosed,
				eEventType_SuperSonicUnlocked,
				eEventType_EmeraldUnlocked,
				eEventType_MissionUnlocked,
				eEventType_RadiconUnlocked,
				eEventType_AllMissionCompleted,
				eEventType_TrialStageCompleted,
				eEventType_DlcStageOpened,
				eEventType_DlcStageClosed,
				eEventType_DlcStageTakePrize
			};

			enum class EItemType : int
			{
				eItemType_None,
				eItemType_ItemBox,
				eItemType_Radicon,
			};

			enum class EItemBoxType : int
			{
				eItemBoxType_Ring,
				eItemBoxType_SpeedShoes,
				eItemBoxType_Barrier,
				eItemBoxType_Radar,
				eItemBoxType_OneUp,
				eItemBoxType_BlackBomb,
				eItemBoxType_ThunderBarrier,
				eItemBoxType_Invincibility,
				eItemBoxType_Warp
			};

			enum class ERadiconType : int
			{
				eRadiconType_Helicopter,
				eRadiconType_FighterJet,
				eRadiconType_StealthJet,
				eRadiconType_Hovercraft,
				eRadiconType_Balloon,
				eRadiconType_Ufo,
				eRadiconType_Omochao
			};

			EEventType EventType{};
			int Unk1{};
			int RewardType{};
			int Unk2{};
			int ItemRank{};
			int Unk3{};
		};

		bool Unk1{};
		csl::ut::MoveArray<Event> Events{};
		bool IsRequestingChangeItem{};
		bool IsTrialVersion{};

		WorldAreaMapCInfo(csl::fnd::IAllocator* in_pAllocator) : Events(15, in_pAllocator)
		{

		}

		void AddEvent(const Event& in_rEvent)
		{
			if (Events.size() < 15)
				Events.push_back_unchecked(in_rEvent);
		}
	};

	// Size is actually 272 bytes
	class CGameSequence : public fnd::ReferencedObject,
		public TTinyFsm<CGameSequence, TiFsmBasicEvent<CGameSequence>, true>,
		TinyFsmSetOption<TiFSM_OPTION_USE_FP_TOP>
	{
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSeqGotoStage, ASLR(0x009116B0), CGameSequence*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpStateProduct, ASLR(0x00910850), CGameSequence*, TiFsmState_t& ret, const TiFsmBasicEvent<CGameSequence>&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpStateBoot, ASLR(0x00910C30), CGameSequence*, TiFsmState_t& ret, const TiFsmBasicEvent<CGameSequence>&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpStateDevelop, ASLR(0x00910280), CGameSequence*, TiFsmState_t& ret, const TiFsmBasicEvent<CGameSequence>&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpStateSegalogo, ASLR(0x00910770), CGameSequence*, TiFsmState_t& ret, const TiFsmBasicEvent<CGameSequence>&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpStateSaveInit, ASLR(0x00910690), CGameSequence*, TiFsmState_t& ret, const TiFsmBasicEvent<CGameSequence>&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpStateTitle, ASLR(0x00910370), CGameSequence*, TiFsmState_t& ret, const TiFsmBasicEvent<CGameSequence>&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpStateStage, ASLR(0x00911000), CGameSequence*, TiFsmState_t& ret, const TiFsmBasicEvent<CGameSequence>&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpStateDevMenu, ASLR(0x0090FEF0), CGameSequence*, TiFsmState_t& ret, const TiFsmBasicEvent<CGameSequence>&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpStateEventMovie, ASLR(0x009119A0), CGameSequence*, TiFsmState_t& ret, const TiFsmBasicEvent<CGameSequence>&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpPushMovieEventQueue, ASLR(0x0090DBE0), CGameSequence*, short);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSaveRedRingInfo, ASLR(0x0090D5C0), CGameSequence*, uint, uint);

	public:
		struct DevData
		{
			csl::ut::FixedString<32> Unk1{};
			uint Unk2; // Language?
			RcType RcType;
			uint RcDesign;
			uint RcLevel;
			uint BattleMode;
			uint RingRaceSetNo;
			uint MinigameMode;
		};

		CGame* pGame;
		void* pUnk1;
		csl::ut::FixedString<16> StgId;
		TiFsmState_t NextState;
		INSERT_PADDING(8);
		GameMode* pGameMode;
		INSERT_PADDING(8);
		DevData* pDevData;
		INSERT_PADDING(100);
		WorldAreaMapCInfo WorldMapInfo{ m_pAllocator };
		INSERT_PADDING(28);

		CGameSequence()
		{
			ASSERT_OFFSETOF(CGameSequence, pGame, 56);
			ASSERT_OFFSETOF(CGameSequence, pGameMode, 104);
			ASSERT_OFFSETOF(CGameSequence, pDevData, 116);
		}

		DevData* GetDevData() const
		{
			return pDevData;
		}

		GameMode* GetGameMode() const
		{
			return pGameMode;
		}
		
		void SetDevData(DevData* in_pDevData)
		{
			pDevData = in_pDevData;
		}

		void ChangeState(TiFsmState_t in_state)
		{
			NextState = in_state;
		}

		template<TiFsmHookState_t ExternalState>
		void ChangeStateExternal()
		{
			ChangeState(FSM_HOOK<ExternalState>());
		}

		void SeqGotoStage()
		{
			ms_fpSeqGotoStage(this);
		}

		void SeqGotoDevMenu()
		{
			ChangeState(&CGameSequence::StateDevMenu);
		}

		void SeqGotoPlayMovie()
		{
			ChangeState(&CGameSequence::StateEventMovie);
		}

		void PushMovieEventQueue(short in_eventNo)
		{
			ms_fpPushMovieEventQueue(this, in_eventNo);
		}

		TiFsmState_t StateProduct(const TiFsmBasicEvent<CGameSequence>& in_rEvent)
		{
			TiFsmState_t result{};
			ms_fpStateProduct(this, result, in_rEvent);
			return result;
		}

		TiFsmState_t StateBoot(const TiFsmBasicEvent<CGameSequence>& in_rEvent)
		{
			TiFsmState_t result{};
			ms_fpStateBoot(this, result, in_rEvent);
			return result;
		}

		TiFsmState_t StateSegalogo(const TiFsmBasicEvent<CGameSequence>& in_rEvent)
		{
			TiFsmState_t result{};
			ms_fpStateSegalogo(this, result, in_rEvent);
			return result;
		}

		TiFsmState_t StateSaveInit(const TiFsmBasicEvent<CGameSequence>& in_rEvent)
		{
			TiFsmState_t result{};
			ms_fpStateSaveInit(this, result, in_rEvent);
			return result;
		}

		TiFsmState_t StateTitle(const TiFsmBasicEvent<CGameSequence>& in_rEvent)
		{
			TiFsmState_t result{};
			ms_fpStateTitle(this, result, in_rEvent);
			return result;
		}

		TiFsmState_t StateStage(const TiFsmBasicEvent<CGameSequence>& in_rEvent)
		{
			TiFsmState_t result{};
			ms_fpStateStage(this, result, in_rEvent);
			return result;
		}

		TiFsmState_t StateDevMenu(const TiFsmBasicEvent<CGameSequence>& in_rEvent)
		{
			TiFsmState_t result{};
			ms_fpStateDevMenu(this, result, in_rEvent);
			return result;
		}

		TiFsmState_t StateDevelop(const TiFsmBasicEvent<CGameSequence>& in_rEvent)
		{
			TiFsmState_t result{};
			ms_fpStateDevelop(this, result, in_rEvent);
			return result;
		}

		TiFsmState_t StateEventMovie(const TiFsmBasicEvent<CGameSequence>& in_rEvent)
		{
			TiFsmState_t result{};
			ms_fpStateEventMovie(this, result, in_rEvent);
			return result;
		}

		void InitGameMode(GameMode* in_pMode);
		void ShutdownGameMode();

		StageInfo::SStageData* GetStageDataByWorldStageID(int in_worldIndex, int in_stageIndex);

		void SaveRedRingInfo(uint in_worldIndex, uint in_stageIndex)
		{
			ms_fpSaveRedRingInfo(this, in_worldIndex, in_stageIndex);
		}

		void OnMinigameOpened(uint in_worldIndex, uint in_minigameIndex);
		void OnChaosEmeraldUnlocked(uint in_worldIndex);
		void OnSuperSonicUnlocked();
	};

	enum RcType
	{
		eRcType_None = -1,
		eRcType_Helicopter = 0,
		eRcType_Fighter = 1,
		eRcType_Stealth = 2,
		eRcType_Hovercraft = 3,
		eRcType_Balloon = 4,
		eRcType_Ufo = 5,
		eRcType_Omochao = 6,
	};

	namespace SaveData
	{
		class CGameData;
		class CFlagSet;
	}

	inline SaveData::CGameData* GetGameData(void* out_pValue);
	inline SaveData::CFlagSet* GetFlagSet(void* out_pValue);
}