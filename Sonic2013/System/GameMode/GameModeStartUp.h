#pragma once

namespace app
{
	class GameModeStartUp :
		public GameMode,
		public TTinyFsm<GameModeStartUp, GameModeUtil::Event<GameModeStartUp>, false>,
		TinyFsmSetOption<TiFSM_OPTION_USE_FP_TOP>
	{
	private:
		inline static FUNCTION_PTR(TiFsmState_t&, __thiscall, ms_fpStateFirstCpk, ASLR(0x0091BCB0), GameModeStartUp*, TiFsmState_t&, const TiFsmEvent_t&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpUpdate, ASLR(0x0091B940), GameModeStartUp*, CGame&, const fnd::SUpdateInfo&);

	public:
		INSERT_PADDING(8){};
		bool WarningEnd{};
		INSERT_PADDING(24){};

		GameModeStartUp()
		{
			FSM_INIT(&GameModeStartUp::StateFirstCpk);
		}

		void OnEnter(CGame& in_rGame) override
		{
			GameMode::OnEnter(in_rGame);
			Blackout(0, static_cast<FadeScreenType>(3));
			InitFSM();
		}

		void OnLeave(CGame& in_rGame) override
		{
			ShutdownFSM();
			GameMode::OnLeave(in_rGame);
		}

		void Update(CGame& in_rGame, const fnd::SUpdateInfo& in_rUpdateInfo) override
		{
			ms_fpUpdate(this, in_rGame, in_rUpdateInfo);
			/*
				GameMode::Update(in_game, in_updateInfo);
				app::xgame::DlcManager::GetInstance()->Update();
				DispatchFSM(TiFsmEvent_t::CreateUpdate(in_updateInfo.deltaTime));
			*/
		}

		bool PreProcessMessage(CGame& in_rGame, fnd::Message& in_rMessage) override
		{
			DispatchFSM(TiFsmEvent_t::CreateMessage(in_rMessage));
			return in_rMessage.Handled;
		}

		bool ProcessMessage(CGame& in_rGame, fnd::Message& in_rMessage) override
		{
			if (PreProcessMessage(in_rGame, in_rMessage))
				return true;

			if (in_rMessage.GetType() == 4099) // MsgWarningEnd
			{
				WarningEnd = true;
				return true;
			}

			return GameMode::ProcessMessage(in_rGame, in_rMessage);
		}

		TiFsmState_t StateFirstCpk(const TiFsmEvent_t& in_rEvent)
		{
			TiFsmState_t result{};
			ms_fpStateFirstCpk(this, result, in_rEvent);

			return result;
		}
	};
}