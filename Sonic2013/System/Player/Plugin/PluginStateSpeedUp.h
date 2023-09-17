#pragma once

namespace app::Player
{
	class PluginStateSpeedUp : public CStatePlugin
	{
	public:
		inline static float ms_SpeedUpLengths[] = { 10.0f, 15.0f, 20.0f, 30.0f };
		inline static const char* ms_pName = (const char*)ASLR(0x00E00988);

		enum Mode
		{
			eMode_WaitStart,
			eMode_SpeedUp,
			eMode_SlowDown
		};

	protected:
		csl::ut::Enum<Mode, char> Unk1{};
		csl::ut::Enum<Mode, char> Unk2{};
		int ItemLevel{};
		float RemainingTime{};

	public:
		PluginStateSpeedUp() : CStatePlugin(ms_pName)
		{

		}

		void RequestSlowDown(CStateGOC& in_rStateGoc)
		{
			ItemLevel = 0;
			Unk2 = Mode::eMode_SlowDown;
		}

		void RequestSpeedUp(CStateGOC& in_rStateGoc, int in_itemLevel)
		{
			if (in_itemLevel >= 4)
				return;

			ItemLevel = in_itemLevel;
			Unk2 = Mode::eMode_SpeedUp;
		}

		void ExtendSpeedUp(CStateGOC& in_rStateGoc, int in_itemLevel)
		{
			if (in_itemLevel >= 4)
				return;

			if (Unk1 != Mode::eMode_SpeedUp)
				return;
		
			ItemLevel = in_itemLevel;
			RemainingTime = ms_SpeedUpLengths[in_itemLevel];
		}

		bool IsWaitStart()
		{
			return Unk2 != Mode::eMode_WaitStart;
		}

		void Start(CStateGOC& in_rStateGoc)
		{
			End(in_rStateGoc);

			in_rStateGoc.GetPhysics()->GetSpeedParameter()->SetSpeedUp(true);
			RemainingTime = ms_SpeedUpLengths[ItemLevel];

			xgame::MsgStartSpeedup msg{};
			msg.PlayerNo = in_rStateGoc.GetPlayerNo();

			in_rStateGoc.SendMessageImmToGame(msg);
			in_rStateGoc.PlaySE("obj_item_high_speed", false);
			Unk1 = Mode::eMode_SpeedUp;
		}

		void StartSlowDown(CStateGOC& in_rStateGoc)
		{
			End(in_rStateGoc);

			in_rStateGoc.GetPhysics()->GetSpeedParameter()->SetSlowDown(true);
			RemainingTime = 10.0f;

			xgame::MsgStartSpeeddown msg{};
			msg.PlayerNo = in_rStateGoc.GetPlayerNo();

			in_rStateGoc.SendMessageImmToGame(msg);
			Unk1 = Mode::eMode_SlowDown;
		}

		void End(CStateGOC& in_rStateGoc)
		{
			switch ((Mode)Unk1)
			{
			case Mode::eMode_SpeedUp:
			{
				in_rStateGoc.GetPhysics()->GetSpeedParameter()->SetSpeedUp(false);
				
				xgame::MsgEndSpeedup msg{};
				msg.PlayerNo = in_rStateGoc.GetPlayerNo();

				in_rStateGoc.SendMessageImmToGame(msg);
			}
			case Mode::eMode_SlowDown:
			{
				in_rStateGoc.GetPhysics()->GetSpeedParameter()->SetSlowDown(false);

				xgame::MsgEndSpeeddown msg{};
				msg.PlayerNo = in_rStateGoc.GetPlayerNo();

				in_rStateGoc.SendMessageImmToGame(msg);
			}
			default:
				Unk1 = Mode::eMode_WaitStart;
				break;
			}
		}

		void Terminate(CStateGOC& in_rStateGoc)
		{
			End(in_rStateGoc);
			SetStatusEnd();
		}

		void OnLeave(CStateGOC& in_rStateGoc) override
		{
			End(in_rStateGoc);
		}

		bool Update(CStateGOC& in_rStateGoc, float in_deltaTime) override
		{
			if (Unk2 != Mode::eMode_WaitStart)
			{
				switch ((Mode)Unk2)
				{
				case Mode::eMode_SpeedUp:
				{
					Start(in_rStateGoc);
					Unk2 = Mode::eMode_WaitStart;

					return true;
				}
				case Mode::eMode_SlowDown:
				{
					StartSlowDown(in_rStateGoc);
					Unk2 = Mode::eMode_WaitStart;

					return true;
				}
				default:
				{
					Unk2 = Mode::eMode_WaitStart;

					return true;
				}
				}
			}
			else
			{
				RemainingTime -= in_deltaTime;
				if (RemainingTime < 0.0f)
				{
					End(in_rStateGoc);
					SetStatusEnd();
				}

				return true;
			}
		}
	};
}