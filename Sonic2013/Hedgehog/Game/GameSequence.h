#pragma once

namespace app
{
	class CGame;
	enum RcType;
	class GameMode;

	// Size is actually 272 bytes
	class CGameSequence : public fnd::ReferencedObject,
		public TTinyFsm<CGameSequence, TiFsmBasicEvent<CGameSequence>, true>,
		TinyFsmSetOption<TiFSM_OPTION_USE_FP_TOP>
	{
	public:
		struct DevData
		{
			csl::ut::FixedString<32> m_Unk1{};
			uint m_Unk2; // Language?
			RcType m_RcType;
			uint m_RcDesign;
			uint m_RcLevel;
			uint m_BattleMode;
			uint m_RingRaceSetNo;
			uint m_MinigameMode;
		};
		CGame* m_pGame;
		void* m_pUnk1;
		
	public:
		csl::ut::FixedString<16> m_StgId;
		TiFsmState_t m_NextState;
		INSERT_PADDING(8);
		GameMode* m_pGameMode;
		INSERT_PADDING(8);
		DevData* m_pDevData;
		
	public:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSeqGotoStage, ASLR(0x009116B0), CGameSequence*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpStateProduct, ASLR(0x00910850), CGameSequence*, TiFsmState_t& ret, const TiFsmBasicEvent<CGameSequence>&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpStateBoot, ASLR(0x00910C30), CGameSequence*, TiFsmState_t& ret, const TiFsmBasicEvent<CGameSequence>&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpStateDevelop, ASLR(0x00910280), CGameSequence*, TiFsmState_t& ret, const TiFsmBasicEvent<CGameSequence>&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpStateSegalogo, ASLR(0x00910770), CGameSequence*, TiFsmState_t& ret, const TiFsmBasicEvent<CGameSequence>&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpStateSaveInit, ASLR(0x00910690), CGameSequence*, TiFsmState_t& ret, const TiFsmBasicEvent<CGameSequence>&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpStateTitle, ASLR(0x00910370), CGameSequence*, TiFsmState_t& ret, const TiFsmBasicEvent<CGameSequence>&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpStateStage, ASLR(0x00911000), CGameSequence*, TiFsmState_t& ret, const TiFsmBasicEvent<CGameSequence>&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpStateDevMenu, ASLR(0x0090FEF0), CGameSequence*, TiFsmState_t& ret, const TiFsmBasicEvent<CGameSequence>&);

		CGameSequence()
		{
			ASSERT_OFFSETOF(CGameSequence, m_pGame, 56);
			ASSERT_OFFSETOF(CGameSequence, m_pGameMode, 104);
			ASSERT_OFFSETOF(CGameSequence, m_pDevData, 116);
		}

		DevData* GetDevData() const
		{
			return m_pDevData;
		}

		GameMode* GetGameMode() const
		{
			return m_pGameMode;
		}
		
		void SetDevData(DevData* in_pDevData)
		{
			m_pDevData = in_pDevData;
		}

		void ChangeState(TiFsmState_t in_state)
		{
			m_NextState = in_state;
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

		TiFsmState_t StateProduct(const TiFsmBasicEvent<CGameSequence>& in_event)
		{
			TiFsmState_t result{};
			ms_fpStateProduct(this, result, in_event);
			return result;
		}

		TiFsmState_t StateBoot(const TiFsmBasicEvent<CGameSequence>& in_event)
		{
			TiFsmState_t result{};
			ms_fpStateBoot(this, result, in_event);
			return result;
		}

		TiFsmState_t StateSegalogo(const TiFsmBasicEvent<CGameSequence>& in_event)
		{
			TiFsmState_t result{};
			ms_fpStateSegalogo(this, result, in_event);
			return result;
		}

		TiFsmState_t StateSaveInit(const TiFsmBasicEvent<CGameSequence>& in_event)
		{
			TiFsmState_t result{};
			ms_fpStateSaveInit(this, result, in_event);
			return result;
		}

		TiFsmState_t StateTitle(const TiFsmBasicEvent<CGameSequence>& in_event)
		{
			TiFsmState_t result{};
			ms_fpStateTitle(this, result, in_event);
			return result;
		}

		TiFsmState_t StateStage(const TiFsmBasicEvent<CGameSequence>& in_event)
		{
			TiFsmState_t result{};
			ms_fpStateStage(this, result, in_event);
			return result;
		}

		TiFsmState_t StateDevMenu(const TiFsmBasicEvent<CGameSequence>& in_event)
		{
			TiFsmState_t result{};
			ms_fpStateDevMenu(this, result, in_event);
			return result;
		}

		TiFsmState_t StateDevelop(const TiFsmBasicEvent<CGameSequence>& in_event)
		{
			TiFsmState_t result{};
			ms_fpStateDevelop(this, result, in_event);
			return result;
		}

		void InitGameMode(GameMode* in_pMode);
		void ShutdownGameMode();
	};

	enum RcType
	{
		NONE = -1,
		HELICOPTER = 0,
		FIGTHER = 1,
		STEALTH = 2,
		HOVERCRAFT = 3,
		BALLOON = 4,
		UFO = 5,
		OMOCHAO = 6,
	};
}