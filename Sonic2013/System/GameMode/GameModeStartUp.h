#pragma once

namespace app
{
	class GameModeStartUp :
		public GameMode,
		public TTinyFsm<GameModeStartUp, GameModeUtil::Event<GameModeStartUp>, false>,
		TinyFsmSetOption<TiFSM_OPTION_USE_FP_TOP>
	{
	public:
		INSERT_PADDING(8){};
		bool m_WarningEnd{};
		INSERT_PADDING(24){};

		inline static FUNCTION_PTR(TiFsmState_t&, __thiscall, ms_fpStateFirstCpk, ASLR(0x0091BCB0), GameModeStartUp*, TiFsmState_t&, const TiFsmEvent_t&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpUpdate, ASLR(0x0091B940), GameModeStartUp*, CGame&, const fnd::SUpdateInfo&);

		GameModeStartUp()
		{
			FSM_INIT(&GameModeStartUp::StateFirstCpk);
		}

		void OnEnter(CGame& in_game) override
		{
			GameMode::OnEnter(in_game);
			Blackout(0, static_cast<FadeScreenType>(3));
			InitFSM();
		}

		void OnLeave(CGame& in_game) override
		{
			ShutdownFSM();
			GameMode::OnLeave(in_game);
		}

		void Update(CGame& in_game, const fnd::SUpdateInfo& in_updateInfo) override
		{
			ms_fpUpdate(this, in_game, in_updateInfo);
			/*
				GameMode::Update(in_game, in_updateInfo);
				app::xgame::DlcManager::GetInstance()->Update();
				DispatchFSM(TiFsmEvent_t::CreateUpdate(in_updateInfo.deltaTime));
			*/
		}

		bool PreProcessMessage(CGame& in_game, fnd::Message& in_msg) override
		{
			DispatchFSM(TiFsmEvent_t::CreateMessage(in_msg));
			return in_msg.m_Handled;
		}

		bool ProcessMessage(CGame& in_game, fnd::Message& in_msg) override
		{
			if (PreProcessMessage(in_game, in_msg))
				return true;

			if (in_msg.GetType() == 4099) // MsgWarningEnd
			{
				m_WarningEnd = true;
				return true;
			}

			return GameMode::ProcessMessage(in_game, in_msg);
		}

		TiFsmState_t StateFirstCpk(const TiFsmEvent_t& in_event)
		{
			TiFsmState_t result{};
			ms_fpStateFirstCpk(this, result, in_event);

			return result;
		}
	};
}