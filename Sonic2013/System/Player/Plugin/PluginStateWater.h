#pragma once

namespace app::Player
{
	class CPluginStateWater : public CStatePlugin
	{
	public:
		inline static const char* ms_pName = (const char*)ASLR(0x00E007DC);
		
		float LimitTimer{};
		csl::ut::Bitset<uint> Flags{};
		int Unk2{};

		CPluginStateWater() : CStatePlugin(ms_pName)
		{

		}

		bool CheckInside()
		{
			return false;
		}

		bool CheckOutside()
		{
			return false;
		}

		float GetRestTime(CStateGOC& in_rStateGoc)
		{
			return csl::math::Max(30.0f - LimitTimer, 0.0f);
		}

		void ExtendTimerForLack(CStateGOC& in_rStateGoc)
		{
			if (!Flags.test(0))
				return;

			Flags.set(0, false);
			LimitTimer = 17.0f;

			xgame::MsgHudUnderWater msg{ true, GetRestTime(in_rStateGoc) };
			in_rStateGoc.SendMessageToHud(msg);
		}

		void ResetLimitTimer(CStateGOC& in_rStateGoc)
		{
			LimitTimer = 0.0f;
			Flags.set(0, false);

			xgame::MsgHudUnderWater msg{ true, GetRestTime(in_rStateGoc) };
			in_rStateGoc.SendMessageToHud(msg);
		}

		void SetIgnoreTimer(bool in_isIgnore)
		{
			Flags.set(2, in_isIgnore);
		}

		void UpdateDeadTimer(CStateGOC& in_rStateGoc, float in_deltaTime)
		{
			if (StateUtil::IsDead(in_rStateGoc) || StateUtil::IsNowPhantom(in_rStateGoc) || Flags.test(2))
				return;
		
			LimitTimer += in_deltaTime;
			if (LimitTimer <= 30.0f)
			{
				if (GetRestTime(in_rStateGoc) > 13.0f || Flags.test(0))
					return;
			
				Flags.set(0, true);
			}
			else if (in_rStateGoc.IsOnGround())
			{
				in_rStateGoc.ChangeState(58);
			}
			else
			{
				in_rStateGoc.ChangeState(59);
			}
		}

		void SetGravityChange(CStateGOC& in_rStateGoc)
		{
			in_rStateGoc.GetPhysics()->SetGravityScale(0.45f);
		}

		void GoOutWater(CStateGOC& in_rStateGoc)
		{
			Unk2 = 0;

			in_rStateGoc.GetBlackBoard()->SetStatus(6, false);

			Flags.reset();
			LimitTimer = 0.0f;

			auto* pLockOnPlugin = in_rStateGoc.GetStatePlugin<CPluginStateLockOn>();
			if (pLockOnPlugin)
				pLockOnPlugin->SetDisable(false);
		
			Param::Type::EType__ paramType = in_rStateGoc.Is2DMode() ? 4 : 5;
			
			auto* pParameterGoc = in_rStateGoc.pPlayer->GetPlayerGOC<CParameterGOC>();
			pParameterGoc->ResetParam(paramType);

			in_rStateGoc.GetPhysics()->SetGravityScale(1.0f);
			
			xgame::MsgPLChangeEnvironment msg{ 0 };
			in_rStateGoc.SendMessageToGame(msg);
		
			xgame::MsgHudUnderWater msgHud{ 0, 0.0f };
			in_rStateGoc.SendMessageToHud(msgHud);
		}

		void GoUnderWater(CStateGOC& in_rStateGoc)
		{
			Unk2 = 1;

			in_rStateGoc.GetBlackBoard()->SetStatus(6, true);

			Flags.reset();

			auto* pLockOnPlugin = in_rStateGoc.GetStatePlugin<CPluginStateLockOn>();
			if (pLockOnPlugin)
				pLockOnPlugin->SetDisable(true);

			SetGravityChange(in_rStateGoc);

			xgame::MsgPLChangeEnvironment msg{ 1 };
			in_rStateGoc.SendMessageToGame(msg);

			ResetLimitTimer(in_rStateGoc);

			Param::Type::EType__ paramType = in_rStateGoc.Is2DMode() ? 4 : 5;

			auto* pParameterGoc = in_rStateGoc.pPlayer->GetPlayerGOC<CParameterGOC>();
			pParameterGoc->ChangeParam(paramType);
		}

		bool ProcMsgGetBubble(CStateGOC& in_rStateGoc, xgame::MsgGetBubble& in_rMessage)
		{
			ResetLimitTimer(in_rStateGoc);
			MsgPLChangeStateGetBubble msg{};
			in_rStateGoc.ProcessMessageToCurrentState(msg);

			return true;
		}

		bool ProcMsgPLFlipInWater(CStateGOC& in_rStateGoc, xgame::MsgPLFlipInWater& in_rMessage)
		{
			return true;
		}

		bool ProcMsgPLGetWaterLimitTime(CStateGOC& in_rStateGoc, xgame::MsgPLGetWaterLimitTime& in_rMessage)
		{
			in_rMessage.WaterLimitTime = LimitTimer;
			return true;
		}

		bool ProcessMessage(CStateGOC& in_rStateGoc, fnd::Message& in_rMessage) override
		{
			switch (in_rMessage.GetType())
			{
			case xgame::MsgGetBubble::MessageID:				return ProcMsgGetBubble(in_rStateGoc, static_cast<xgame::MsgGetBubble&>(in_rMessage));
			case xgame::MsgPLFlipInWater::MessageID:			return ProcMsgPLFlipInWater(in_rStateGoc, static_cast<xgame::MsgPLFlipInWater&>(in_rMessage));
			case xgame::MsgPLGetWaterLimitTime::MessageID:		return ProcMsgPLGetWaterLimitTime(in_rStateGoc, static_cast<xgame::MsgPLGetWaterLimitTime&>(in_rMessage));
			default:											return CStatePlugin::ProcessMessage(in_rStateGoc, in_rMessage);
			}
		}

		void UpdateCheckWater(CStateGOC& in_rStateGoc, float in_deltaTime)
		{
			if (CheckInside())
				GoUnderWater(in_rStateGoc);
		}

		void UpdateInWater(CStateGOC& in_rStateGoc, float in_deltaTime)
		{
			if (StateUtil::IsInWater(in_rStateGoc) && !CheckOutside())
				UpdateDeadTimer(in_rStateGoc, in_deltaTime);
			else
				GoOutWater(in_rStateGoc);
		}

		bool Update(CStateGOC& in_rStateGoc, float in_deltaTime) override
		{
			switch (Unk2)
			{
			case 0:
			{
				UpdateCheckWater(in_rStateGoc, in_deltaTime);
				break;
			}
			case 1:
			{
				UpdateInWater(in_rStateGoc, in_deltaTime);
				break;
			}
			default:
				break;
			}

			return true;
		}
	};
}