#pragma once

namespace app
{
	class CGame;
	enum RcType;

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

	protected:
		CGame* m_pGame;
		void* m_pUnk1;
		
	public:
		csl::ut::FixedString<16> m_StgId;
		TiFsmState_t m_NextState;
		INSERT_PADDING(20);
		DevData* m_pDevData;
		
	public:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSeqGotoStage, ASLR(0x009116B0), CGameSequence*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpStateProduct, ASLR(0x00910850), CGameSequence*, TiFsmState_t& ret, const TiFsmBasicEvent<CGameSequence>&);

		CGameSequence()
		{
			ASSERT_OFFSETOF(CGameSequence, m_pGame, 56);
			ASSERT_OFFSETOF(CGameSequence, m_pDevData, 116);
		}

		DevData* GetDevData() const
		{
			return m_pDevData;
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

		//template<TiFsmHookState_t ExternalState>
		//void ChangeStateExternal(TiFsmHookState_t)
		//{
		//	ChangeState(FSM_HOOK<ExternalState>());
		//}

		void SeqGotoStage()
		{
			ms_fpSeqGotoStage(this);
		}

		TiFsmState_t StateProduct(const TiFsmBasicEvent<CGameSequence>& in_event)
		{
			TiFsmState_t result{};
			ms_fpStateProduct(this, result, in_event);
			return result;
		}
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