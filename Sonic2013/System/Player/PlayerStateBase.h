#pragma once

namespace app::Player
{
	class CStateBase : public CState
	{
	public:
		inline static int ms_ReleaseBoxRingCount[] = { 10, 20, 30, 50 };
		inline static int ms_ReleaseBoxLivesCount[] = { 1, 2, 3, 5 };
		inline static PluginStateBarrier::EType ms_BarrierTypes[] = { 
			(PluginStateBarrier::EType)0, (PluginStateBarrier::EType)0, (PluginStateBarrier::EType)0, (PluginStateBarrier::EType)0,
			(PluginStateBarrier::EType)0, (PluginStateBarrier::EType)65, (PluginStateBarrier::EType)48, (PluginStateBarrier::EType)0, (PluginStateBarrier::EType)0,
			PluginStateBarrier::EType::eType_Barrier, PluginStateBarrier::EType::eType_WaterBarrier, PluginStateBarrier::EType::eType_ThunderBarrier, (PluginStateBarrier::EType)0
		};

		bool ProcessMessage(CStateGOC& in_rStateGoc, fnd::Message& in_rMessage) override
		{
			switch (in_rMessage.GetType())
			{
			case xgame::MsgGetCenterPosition::MessageID:				return ProcMsgGetCenterPosition(in_rStateGoc, static_cast<xgame::MsgGetCenterPosition&>(in_rMessage));
			case xgame::MsgPLGetRingNum::MessageID:						return ProcMsgPLGetRingNum(in_rStateGoc, static_cast<xgame::MsgPLGetRingNum&>(in_rMessage));
			case xgame::MsgPLStartSleepMode::MessageID:					return ProcMsgPLStartSleepMode(in_rStateGoc, static_cast<xgame::MsgPLStartSleepMode&>(in_rMessage));
			case xgame::MsgPLIsDead::MessageID:							return ProcMsgPLIsDead(in_rStateGoc, static_cast<xgame::MsgPLIsDead&>(in_rMessage));
			case xgame::MsgPLGetUserNo::MessageID:						return ProcMsgPLGetUserNo(in_rStateGoc, static_cast<xgame::MsgPLGetUserNo&>(in_rMessage));
			case xgame::MsgPLIsDisableChangePhantomArea::MessageID:		return ProcMsgPLIsDisableChangePhantomArea(in_rStateGoc, static_cast<xgame::MsgPLIsDisableChangePhantomArea&>(in_rMessage));
			case xgame::MsgPLGetPhantomRestTime::MessageID:				return ProcMsgPLGetPhantomRestTime(in_rStateGoc, static_cast<xgame::MsgPLGetPhantomRestTime&>(in_rMessage));
			case xgame::MsgPLGetHistoryPosition::MessageID:				return ProcMsgPLGetHistoryPosition(in_rStateGoc, static_cast<xgame::MsgPLGetHistoryPosition&>(in_rMessage));
			case xgame::MsgCylinderSpeedDown::MessageID:				return ProcMsgCylinderSpeedDown(in_rStateGoc, static_cast<xgame::MsgCylinderSpeedDown&>(in_rMessage));
			case xgame::MsgPLBeginAutorun::MessageID:					return ProcMsgPLBeginAutorun(in_rStateGoc, static_cast<xgame::MsgPLBeginAutorun&>(in_rMessage));
			case xgame::MsgPLFinishAutorun::MessageID:					return ProcMsgPLFinishAutorun(in_rStateGoc, static_cast<xgame::MsgPLFinishAutorun&>(in_rMessage));
			case xgame::MsgNotifyBossStart::MessageID:					return ProcMsgNotifyBossStart(in_rStateGoc, static_cast<xgame::MsgNotifyBossStart&>(in_rMessage));
			case xgame::MsgPLHoldOn::MessageID:							return ProcMsgPLHoldOn(in_rStateGoc, static_cast<xgame::MsgPLHoldOn&>(in_rMessage));
			case xgame::MsgPLReleaseHold::MessageID:					return ProcMsgPLReleaseHold(in_rStateGoc, static_cast<xgame::MsgPLReleaseHold&>(in_rMessage));
			case xgame::MsgPlayerReachGoal::MessageID:					return ProcMsgPlayerReachGoal(in_rStateGoc, static_cast<xgame::MsgPlayerReachGoal&>(in_rMessage));
			case xgame::MsgPLEnableSearchAllDirections::MessageID:		return ProcMsgPLEnableSearchAllDirections(in_rStateGoc, static_cast<xgame::MsgPLEnableSearchAllDirections&>(in_rMessage));
			case xgame::MsgPLStealth::MessageID:						return ProcMsgPLStealth(in_rStateGoc, static_cast<xgame::MsgPLStealth&>(in_rMessage));
			case xgame::MsgRestrictWarp::MessageID:						return ProcMsgRestrictWarp(in_rStateGoc, static_cast<xgame::MsgRestrictWarp&>(in_rMessage));
			case xgame::MsgRestrictWarpCancel::MessageID:				return ProcMsgRestrictWarpCancel(in_rStateGoc, static_cast<xgame::MsgRestrictWarpCancel&>(in_rMessage));
			case xgame::MsgPLVisibleItemEffect::MessageID:				return ProcMsgPLVisibleItemEffect(in_rStateGoc, static_cast<xgame::MsgPLVisibleItemEffect&>(in_rMessage));
			case xgame::MsgTakeObject::MessageID:						return ProcMsgTakeObject(in_rStateGoc, static_cast<xgame::MsgTakeObject&>(in_rMessage));
			case xgame::MsgPlayerPassPointMarker::MessageID:			return ProcMsgPlayerPassPointMarker(in_rStateGoc, static_cast<xgame::MsgPlayerPassPointMarker&>(in_rMessage));
			case xgame::MsgTakePixie::MessageID:						return ProcMsgTakePixie(in_rStateGoc, static_cast<xgame::MsgTakePixie&>(in_rMessage));
			case xgame::MsgBeginGPathMode::MessageID:					return ProcMsgBeginGPathMode(in_rStateGoc, static_cast<xgame::MsgBeginGPathMode&>(in_rMessage));
			case xgame::MsgEndGPathMode::MessageID:						return ProcMsgEndGPathMode(in_rStateGoc, static_cast<xgame::MsgEndGPathMode&>(in_rMessage));
			case xgame::MsgWarpNewArea::MessageID:						return ProcMsgWarpNewArea(in_rStateGoc, static_cast<xgame::MsgWarpNewArea&>(in_rMessage));
			case xgame::MsgExitLoop::MessageID:							return ProcMsgExitLoop(in_rStateGoc, static_cast<xgame::MsgExitLoop&>(in_rMessage));
			case xgame::MsgGetDeathTornadoInfo::MessageID:				return ProcMsgGetDeathTornadoInfo(in_rStateGoc, static_cast<xgame::MsgGetDeathTornadoInfo&>(in_rMessage));
			case xgame::MsgLossRing::MessageID:							return ProcMsgLossRing(in_rStateGoc, static_cast<xgame::MsgLossRing&>(in_rMessage));
			case xgame::MsgNotifySilhouetteState::MessageID:			return ProcMsgNotifySilhouetteState(in_rStateGoc, static_cast<xgame::MsgNotifySilhouetteState&>(in_rMessage));
			case xgame::MsgDlcZeldaHeartAllRecovery::MessageID:			return ProcMsgDlcZeldaHeartAllRecovery(in_rStateGoc, static_cast<xgame::MsgDlcZeldaHeartAllRecovery&>(in_rMessage));
			case xgame::MsgHitEventCollision::MessageID:				return ProcMsgHitEventCollision(in_rStateGoc, static_cast<xgame::MsgHitEventCollision&>(in_rMessage));
			case xgame::MsgStayTrigger::MessageID:						return ProcMsgStayTrigger(in_rStateGoc, static_cast<xgame::MsgStayTrigger&>(in_rMessage));
			case xgame::MsgEndSign::MessageID:							return ProcMsgEndSign(in_rStateGoc, static_cast<xgame::MsgEndSign&>(in_rMessage));
			case xgame::MsgStartPhantomSign::MessageID:					return ProcMsgStartPhantomSign(in_rStateGoc, static_cast<xgame::MsgStartPhantomSign&>(in_rMessage));
			case xgame::MsgHudStartStomping::MessageID:					return ProcMsgHudStartStomping(in_rStateGoc, static_cast<xgame::MsgHudStartStomping&>(in_rMessage));
			case xgame::MsgHudStartHoming::MessageID:					return ProcMsgHudStartHoming(in_rStateGoc, static_cast<xgame::MsgHudStartHoming&>(in_rMessage));
			case xgame::MsgHudStartFallDead::MessageID:					return ProcMsgHudStartFallDead(in_rStateGoc, static_cast<xgame::MsgHudStartFallDead&>(in_rMessage));
			//case xgame::MsgFlipBoostAnytimeBoost::MessageID:			return ProcMsgFlipBoostAnytimeBoost(in_rStateGoc, static_cast<xgame::MsgFlipBoostAnytimeBoost&>(in_rMessage));
			//case xgame::MsgNotifyFinishAutoRun::MessageID:			return ProcMsgNotifyFinishAutoRun(in_rStateGoc, static_cast<xgame::MsgNotifyFinishAutoRun&>(in_rMessage));
			default:													return CState::ProcessMessage(in_rStateGoc, in_rMessage);
			}
		}

		bool ProcMsgGetCenterPosition(CStateGOC& in_rStateGoc, xgame::MsgGetCenterPosition& in_rMessage)
		{
			*in_rMessage.CenterPosition = { in_rStateGoc.GetPosition() + in_rStateGoc.GetMatrix() * csl::math::Vector3(0.0f, 5.0f, 0.0f) };
			return true;
		}

		bool ProcMsgPLGetRingNum(CStateGOC& in_rStateGoc, xgame::MsgPLGetRingNum& in_rMessage)
		{
			in_rMessage.RingCount = in_rStateGoc.GetBlackBoard()->GetRingParameter()->GetRingCount();
			return true;
		}

		bool ProcMsgPLStartSleepMode(CStateGOC& in_rStateGoc, xgame::MsgPLStartSleepMode& in_rMessage)
		{
			in_rStateGoc.ChangeState(0);
			if (in_rMessage.Flags.test(0))
			{
				in_rStateGoc.SetAnimation("STAND");
			}
			else
			{
				StateUtil::SetDraw(in_rStateGoc, false, true);
			}

			if (in_rMessage.Flags.test(1))
				StateUtil::ResetPosition(in_rStateGoc, *in_rMessage.Position, *in_rMessage.Rotation);

			return true;
		}

		bool ProcMsgPLIsDead(CStateGOC& in_rStateGoc, xgame::MsgPLIsDead& in_rMessage)
		{
			in_rMessage.IsDead = StateUtil::IsDead(in_rStateGoc);
			return true;
		}

		bool ProcMsgPLGetUserNo(CStateGOC& in_rStateGoc, xgame::MsgPLGetUserNo& in_rMessage)
		{
			in_rMessage.PlayerNo = in_rStateGoc.GetPlayerNo();
			return true;
		}

		bool ProcMsgPLIsDisableChangePhantomArea(CStateGOC& in_rStateGoc, xgame::MsgPLIsDisableChangePhantomArea& in_rMessage)
		{
			auto pixieType = StateUtil::GetStockPixieType(in_rStateGoc);
			if (pixieType == -1)
				return true;

			if (StateUtil::IsDead(in_rStateGoc))
			{
				in_rMessage.IsDisable = true;
				return true;
			}

			auto* pPlugin = in_rStateGoc.GetStatePlugin<CPluginStateCheckChangePhantom>();
			if (pPlugin)
			{
				if (pPlugin->Unk3)
					in_rMessage.IsDisable = true;

				if (!pPlugin->CheckArea(in_rStateGoc, (Game::EPhantomType)pixieType))
					in_rMessage.IsDisable = true;
			}

			return true;
		}

		bool ProcMsgPLGetPhantomRestTime(CStateGOC& in_rStateGoc, xgame::MsgPLGetPhantomRestTime& in_rMessage)
		{
			auto phantomType = StateUtil::GetNowPhantomType(in_rStateGoc);
			in_rMessage.Type = phantomType;

			if (phantomType != -1)
				in_rMessage.RestTime = StateUtil::GetPhantomEnergy(in_rStateGoc);

			return true;
		}

		bool ProcMsgPLGetHistoryPosition(CStateGOC& in_rStateGoc, xgame::MsgPLGetHistoryPosition& in_rMessage)
		{
			if (in_rMessage.PositionIndex == 255)
				return false;

			in_rMessage.HistoryPosition = in_rStateGoc.GetPhysics()->GetHistoryPosition(in_rMessage.PositionIndex + 1);
			return true;
		}

		bool ProcMsgCylinderSpeedDown(CStateGOC& in_rStateGoc, xgame::MsgCylinderSpeedDown& in_rMessage)
		{
			in_rStateGoc.GetPhysics()->SetHorzVelocity({ in_rStateGoc.GetHorzVelocity() * 0.1f });
			return true;
		}

		bool ProcMsgPLBeginAutorun(CStateGOC& in_rStateGoc, xgame::MsgPLBeginAutorun& in_rMessage)
		{
			if (in_rStateGoc.GetStatePlugin<PluginStateAutoRun>())
				in_rStateGoc.RemoveStatePlugin(8);
		
			in_rStateGoc.AddStatePlugin(8);

			auto* pPlugin = in_rStateGoc.GetStatePlugin<PluginStateAutoRun>();
			if (pPlugin && !pPlugin->Setup(in_rStateGoc, in_rMessage.Unk2, in_rMessage.Unk3))
			{
				in_rStateGoc.RemoveStatePlugin(8);
				return true;
			}

			if (in_rMessage.Unk1 != 1)
				return true;

			LaunchAutoRunCannonParameter autoRunParam{};
			autoRunParam.Unk1 = 1;
			autoRunParam.Unk3 = { in_rMessage.Unk4 * in_rMessage.Unk3 };
			autoRunParam.Unk2 = in_rMessage.Unk5;
			in_rStateGoc.AddStateContextParameter(autoRunParam);
			in_rStateGoc.ChangeState(116);

			return true;
		}

		bool ProcMsgPLFinishAutorun(CStateGOC& in_rStateGoc, xgame::MsgPLFinishAutorun& in_rMessage)
		{
			in_rStateGoc.RemoveStatePlugin(8);
			return true;
		}

		bool ProcMsgNotifyBossStart(CStateGOC& in_rStateGoc, xgame::MsgNotifyBossStart& in_rMessage)
		{
			in_rStateGoc.GetBlackBoard()->SetStatus(18, true);
			return true;
		}

		bool ProcMsgPLHoldOn(CStateGOC& in_rStateGoc, xgame::MsgPLHoldOn& in_rMessage)
		{
			SetPLHoldOn(in_rStateGoc, in_rMessage);
			return true;
		}

		bool ProcMsgPLReleaseHold(CStateGOC& in_rStateGoc, xgame::MsgPLReleaseHold& in_rMessage)
		{
			StateUtil::SetInputEnable(in_rStateGoc, true);
			return true;
		}

		bool ProcMsgPlayerReachGoal(CStateGOC& in_rStateGoc, xgame::MsgPlayerReachGoal& in_rMessage)
		{
			xgame::MsgGoal msg{};
			msg.PanCamera = !in_rStateGoc.Is2DMode();

			if (in_rMessage.Unk1 == 2)
			{
				msg.FinishType = xgame::MsgGoal::EFinishType::eFinishType_FadeToWhite;
				in_rStateGoc.SendMessageToGame(msg);

				return true;
			}

			if (in_rMessage.Unk1 == 1)
			{
				auto* pParameter = in_rStateGoc.CreateStateContextParameter<GoalParameter>();
				pParameter->Unk2 = 1;
				pParameter->Unk3= in_rMessage.Unk3;
			}

			if (in_rStateGoc.GetLevelInfo()->GetDLCStageIndex() == 3)
				msg.PanCamera = false;

			in_rStateGoc.SendMessageToGame(msg);
			in_rStateGoc.ChangeState(47);

			return true;
		}

		bool ProcMsgPLEnableSearchAllDirections(CStateGOC& in_rStateGoc, xgame::MsgPLEnableSearchAllDirections& in_rMessage)
		{
			auto* pHomingService = in_rStateGoc.pPlayer->spHomingService.get();
			if (pHomingService)
				pHomingService->Unk2.set(3, in_rMessage.IsEnabled);
		
			return true;
		}

		bool ProcMsgPLStealth(CStateGOC& in_rStateGoc, xgame::MsgPLStealth& in_rMessage)
		{
			if (!in_rMessage.IsStealth || !StateUtil::IsDead(in_rStateGoc))
				StateUtil::SetStealth(in_rStateGoc, in_rMessage.IsStealth);

			return true;
		}

		bool ProcMsgRestrictWarp(CStateGOC& in_rStateGoc, xgame::MsgRestrictWarp& in_rMessage)
		{
			in_rStateGoc.GetBlackBoard()->SetStatus(28, true);
			return true;
		}

		bool ProcMsgRestrictWarpCancel(CStateGOC& in_rStateGoc, xgame::MsgRestrictWarpCancel& in_rMessage)
		{
			in_rStateGoc.GetBlackBoard()->SetStatus(28, false);
			return true;
		}

		bool ProcMsgPLVisibleItemEffect(CStateGOC& in_rStateGoc, xgame::MsgPLVisibleItemEffect& in_rMessage)
		{
			StateUtil::SetPauseItemEffect(in_rStateGoc, !in_rMessage.IsVisible);
			return true;
		}

		bool ProcMsgTakeObject(CStateGOC& in_rStateGoc, xgame::MsgTakeObject& in_rMessage)
		{
			if (StateUtil::IsDead(in_rStateGoc) || in_rStateGoc.GetBlackBoard()->Unk1[3].test(26))
				return true;
			
			bool isVariantValid = in_rMessage.ItemLevel != -1;
			auto* pPlugin = in_rStateGoc.GetStatePlugin<PluginStateCheckEnableItem>();

			switch (in_rMessage.Type)
			{
			case xgame::MsgTakeObject::EType::eType_Ring:
			case xgame::MsgTakeObject::EType::eType_DroppedRing:
			{
				if (in_rMessage.IsValidUserID() && in_rMessage.UserID != 6)
					break;
			
				if (isVariantValid && pPlugin && pPlugin->IsItemDisable(8))
				{
					CallErrSE(in_rStateGoc, isVariantValid);
					break;
				}

				if (in_rMessage.ItemLevel == -1)
				{
					StateUtil::AddRingNum(in_rStateGoc, 1);
					if (in_rMessage.Type == xgame::MsgTakeObject::EType::eType_DroppedRing)
						StateUtil::SendMissionGetRing(in_rStateGoc, 1);

					in_rMessage.Taken = true;
					break;
				}

				in_rStateGoc.PlaySE("obj_release_ring", false);
				StateUtil::AddRingNum(in_rStateGoc, ms_ReleaseBoxRingCount[in_rMessage.ItemLevel]);
					
				int numHearts{};
				int maxNumHearts{};
				auto* pHeartPlugin = in_rStateGoc.GetStatePlugin<PluginStateHeartLife>();
				if (pHeartPlugin)
				{
					numHearts = pHeartPlugin->GetNumHearts();
					maxNumHearts = pHeartPlugin->GetMaxNumHearts();
				}

				xgame::MsgPLSendGameInfo msg{ (Game::EUser)in_rStateGoc.GetPlayerNo(), in_rStateGoc.GetPhysics()->GetHorzVelocityLength(), StateUtil::GetRingNum(in_rStateGoc), numHearts, maxNumHearts };
				in_rStateGoc.SendMessageImmToGame(msg);

				in_rMessage.Taken = true;
				break;
			}
			case xgame::MsgTakeObject::EType::eType_SuperRing:
			{
				if (in_rMessage.IsValidUserID() && in_rMessage.UserID != 6)
					break;

				StateUtil::AddRingNum(in_rStateGoc, 10);
				StateUtil::SendMissionGetRing(in_rStateGoc, 10);
				
				in_rMessage.Taken = true;
				break;
			}
			case xgame::MsgTakeObject::EType::eType_OneUp:
			{
				xgame::MsgExtendPlayer msg{ (Game::EUser)in_rStateGoc.GetToHudPlayerNumber(), 1 };
				if (in_rMessage.ItemLevel == -1)
				{
					StateUtil::SendMission(in_rStateGoc, 2);
					StateUtil::PlayVoice(in_rStateGoc, 13);
					
					msg.LifeCount = 1;
					in_rStateGoc.SendMessageImmToGame(msg);

					in_rMessage.Taken = true;
					break;
				}

				in_rStateGoc.PlaySE("obj_extended", false);

				msg.LifeCount = ms_ReleaseBoxLivesCount[in_rMessage.ItemLevel];
				in_rStateGoc.SendMessageImmToGame(msg);
				
				in_rMessage.Taken = true;
				break;
			}
			case xgame::MsgTakeObject::EType::eType_RedRing:
			{
				StateUtil::PlayVoice(in_rStateGoc, 13);
				StateUtil::SendMission(in_rStateGoc, 1);
				
				in_rMessage.Taken = true;
				break;
			}
			case xgame::MsgTakeObject::EType::eType_SpeedUp:
			{
				if (pPlugin && pPlugin->IsItemDisable(0))
				{
					CallErrSE(in_rStateGoc, isVariantValid);
					break;
				}
				
				int itemLevel = in_rMessage.ItemLevel == -1 ? 0 : in_rMessage.ItemLevel;

				auto* pSpeedUpPlugin = in_rStateGoc.GetStatePlugin<PluginStateSpeedUp>();
				if (!pSpeedUpPlugin)
				{
					in_rStateGoc.AddStatePlugin(9);
					pSpeedUpPlugin = in_rStateGoc.GetStatePlugin<PluginStateSpeedUp>();
					if (pSpeedUpPlugin)
						pSpeedUpPlugin->RequestSpeedUp(in_rStateGoc, itemLevel);
				}
				else
				{
					if (pSpeedUpPlugin->IsWaitStart())
					{
						CallErrSE(in_rStateGoc, isVariantValid);
						break;
					}

					if (StateUtil::IsBattleMode(in_rStateGoc))
						pSpeedUpPlugin->RequestSpeedUp(in_rStateGoc, itemLevel);
					else
						pSpeedUpPlugin->ExtendSpeedUp(in_rStateGoc, itemLevel);
				}

				if (isVariantValid)
					in_rStateGoc.PlaySE("obj_itembox", false);

				in_rMessage.Taken = true;
				break;
			}
			case xgame::MsgTakeObject::EType::eType_SlowDown:
			{
				if (pPlugin && pPlugin->IsItemDisable(0))
				{
					CallErrSE(in_rStateGoc, isVariantValid);
					break;
				}

				in_rStateGoc.RemoveStatePlugin(9);
				in_rStateGoc.AddStatePlugin(9);
				auto* pSpeedUpPlugin = in_rStateGoc.GetStatePlugin<PluginStateSpeedUp>();
				if (pSpeedUpPlugin)
					pSpeedUpPlugin->RequestSlowDown(in_rStateGoc);

				in_rMessage.Taken = true;
				break;
			}
			case xgame::MsgTakeObject::EType::eType_Invincibility:
			{
				if (pPlugin && pPlugin->IsItemDisable(1))
				{
					CallErrSE(in_rStateGoc, isVariantValid);
					break;
				}

				int itemLevel = in_rMessage.ItemLevel == -1 ? 0 : in_rMessage.ItemLevel;

				auto* pInvinciblePlugin = in_rStateGoc.GetStatePlugin<PluginStateInvincible>();
				if (!pInvinciblePlugin)
				{
					in_rStateGoc.AddStatePlugin(10);
					pInvinciblePlugin = in_rStateGoc.GetStatePlugin<PluginStateInvincible>();
					if (pInvinciblePlugin)
						pInvinciblePlugin->RequestStart(in_rStateGoc, itemLevel);
				}
				else
				{
					if (pInvinciblePlugin->IsWaitStart())
					{
						CallErrSE(in_rStateGoc, isVariantValid);
						break;
					}

					pInvinciblePlugin->Extend(in_rStateGoc, itemLevel);
				}

				if (isVariantValid)
					in_rStateGoc.PlaySE("obj_itembox", false);

				in_rMessage.Taken = true;
				break;
			}
			case xgame::MsgTakeObject::EType::eType_Warp:
			{
				if (in_rStateGoc.GetBlackBoard()->Unk1[3].test(28) || pPlugin && pPlugin->IsItemDisable(4))
				{
					CallErrSE(in_rStateGoc, isVariantValid);
					break;
				}

				if (StateUtil::IsBattleMode(in_rStateGoc))
				{
					xgame::MsgWarpNewAreaByItem msg{};
					msg.PlayerNo = in_rStateGoc.GetPlayerNo();
					msg.Position = in_rStateGoc.GetPosition();
					msg.ItemLevel = in_rMessage.ItemLevel == -1 ? 0 : in_rMessage.ItemLevel;
					
					in_rStateGoc.SendMessageImmToGame(msg);
					if (!msg.Unk1)
						break;
				
					in_rStateGoc.PlaySE("obj_item_warp", false);
					if (in_rStateGoc.GetCurrentState() == 105)
						StateUtil::SyncSnowBallPosition(in_rStateGoc);
					else
						in_rStateGoc.ChangeState(121);

					in_rMessage.Taken = true;
					break;
				}

				pPlugin = in_rStateGoc.GetStatePlugin<PluginStateCheckEnableItem>();
				if (!pPlugin)
					break;

				if (pPlugin->IsWaitWarp())
				{
					CallErrSE(in_rStateGoc, isVariantValid);
					break;
				}
				
				xgame::MsgCheckWarpNewAreaByItem msg{};
				msg.PlayerNo = in_rStateGoc.GetPlayerNo();
				msg.Position = in_rStateGoc.GetPosition();
				msg.ItemLevel = in_rMessage.ItemLevel == -1 ? 0 : in_rMessage.ItemLevel;

				in_rStateGoc.SendMessageImmToGame(msg);
				if (!msg.Unk1)
				{
					CallErrSE(in_rStateGoc, isVariantValid);
					break;
				}

				pPlugin->RequestWarp(in_rStateGoc, msg.ItemLevel);

				if (isVariantValid)
					in_rStateGoc.PlaySE("obj_itembox", false);

				in_rMessage.Taken = true;
				break;
			}
			case xgame::MsgTakeObject::EType::eType_Barrier:
			case xgame::MsgTakeObject::EType::eType_WaterBarrier:
			case xgame::MsgTakeObject::EType::eType_ThunderBarrier:
			{
				if (pPlugin && pPlugin->IsItemDisable(2))
				{
					CallErrSE(in_rStateGoc, isVariantValid);
					break;
				}

				int itemLevel = in_rMessage.ItemLevel == -1 ? 0 : in_rMessage.ItemLevel;

				PluginStateBarrier::EType barrierType{};
				if (in_rMessage.Type >= xgame::MsgTakeObject::EType::eType_Barrier && in_rMessage.Type <= xgame::MsgTakeObject::EType::eType_ThunderBarrier)
					barrierType = ms_BarrierTypes[in_rMessage.Type];
			
				auto* pBarrierPlugin = in_rStateGoc.GetStatePlugin<PluginStateBarrier>();
				if (!pBarrierPlugin)
				{
					in_rStateGoc.AddStatePlugin(11);
					pBarrierPlugin = in_rStateGoc.GetStatePlugin<PluginStateBarrier>();
					if (pBarrierPlugin)
						pBarrierPlugin->StartRequest(in_rStateGoc, barrierType, itemLevel);
				}
				else
				{
					if (pBarrierPlugin->IsWaitStart())
					{
						CallErrSE(in_rStateGoc, isVariantValid);
						break;
					}

					pBarrierPlugin->StartRequest(in_rStateGoc, barrierType, itemLevel);
				}

				if (isVariantValid)
					in_rStateGoc.PlaySE("obj_itembox", false);
			
				in_rMessage.Taken = true;
				break;
			}
			case xgame::MsgTakeObject::EType::eType_RedRingRadar:
			{
				int itemLevel = csl::math::Clamp(in_rMessage.ItemLevel, 0u, 3u);

				auto* pRadarPlugin = in_rStateGoc.GetStatePlugin<PluginStateRedRingRadar>();
				if (!pRadarPlugin)
				{
					in_rStateGoc.AddStatePlugin(14);
					pRadarPlugin = in_rStateGoc.GetStatePlugin<PluginStateRedRingRadar>();
					if (pRadarPlugin)
						pRadarPlugin->StartRadar(in_rStateGoc, itemLevel);
				}
				else
				{
					if (pRadarPlugin->IsWaitStart())
					{
						CallErrSE(in_rStateGoc, isVariantValid);
						break;
					}

					pRadarPlugin->StartRadar(in_rStateGoc, itemLevel);
				}

				if (isVariantValid)
					in_rStateGoc.PlaySE("obj_itembox", false);

				in_rMessage.Taken = true;
				break;
			}
			case xgame::MsgTakeObject::EType::eType_StealRing:
			{
				auto* pLevelInfo = in_rStateGoc.pPlayer->GetLevelInfo();
				if (!pLevelInfo)
				{
					in_rMessage.Taken = true;
					break;
				}
			
				size_t rivalPlayerNo = in_rStateGoc.pPlayer->GetRivalPlayerNo();
				int rivalRingCount = pLevelInfo->GetPlayerInfo(rivalPlayerNo)->RivalRingCount;
				int ringCount = StateUtil::GetRingNum(in_rStateGoc);

				int stealAmount = csl::math::Min((int)(SonicUSA::System::Random::GetInstance()->genrand_float32() * 11.0f) + 10, rivalRingCount);
				StateUtil::SetRingNum(in_rStateGoc, ringCount + stealAmount);

				xgame::MsgPLSetNumRing msgSetNumRing{};
				msgSetNumRing.RingCount = rivalRingCount - stealAmount;
				in_rStateGoc.SendMessageToRival(msgSetNumRing);

				xgame::MsgNotifyChangeRing msgChangeRing{};
				msgChangeRing.UserNo = (Game::EUser)in_rStateGoc.GetPlayerNo();
				msgChangeRing.Type = 7;
				msgChangeRing.Unk2 = stealAmount;
				msgChangeRing.Unk3 = -stealAmount;
				in_rStateGoc.SendMessageImmToGame(msgChangeRing);

				in_rMessage.Taken = true;
				break;
			}
			case xgame::MsgTakeObject::EType::eType_ChangeRing:
			{
				auto* pLevelInfo = in_rStateGoc.pPlayer->GetLevelInfo();
				if (!pLevelInfo)
				{
					in_rMessage.Taken = true;
					break;
				}

				size_t rivalPlayerNo = in_rStateGoc.pPlayer->GetRivalPlayerNo();
				int rivalRingCount = pLevelInfo->GetPlayerInfo(rivalPlayerNo)->RivalRingCount;
				int ringCount = StateUtil::GetRingNum(in_rStateGoc);

				StateUtil::SetRingNum(in_rStateGoc, rivalRingCount);

				xgame::MsgPLSetNumRing msgSetNumRing{};
				msgSetNumRing.RingCount = ringCount;
				in_rStateGoc.SendMessageToRival(msgSetNumRing);

				xgame::MsgNotifyChangeRing msgChangeRing{};
				msgChangeRing.UserNo = (Game::EUser)in_rStateGoc.GetPlayerNo();
				msgChangeRing.Type = 9;
				msgChangeRing.Unk2 = rivalRingCount - ringCount;
				msgChangeRing.Unk3 = ringCount - rivalRingCount;
				in_rStateGoc.SendMessageImmToGame(msgChangeRing);

				in_rMessage.Taken = true;
				break;
			}
			case xgame::MsgTakeObject::EType::eType_PhantomBomb:
			{
				if (StateUtil::GetNowPhantomType(in_rStateGoc) == Game::EPhantomType::PHANTOM_BOMB)
				{
					xgame::MsgTakePixie msg{ Game::EPhantomType::PHANTOM_BOMB, 1.0f };
					in_rStateGoc.ProcessMessageToCurrentState(msg);
					in_rMessage.Taken = msg.Taken;

					if (isVariantValid)
						in_rStateGoc.PlaySE("obj_itembox", false);
				
					break;
				}

				if (StateUtil::GetNowPhantomType(in_rStateGoc) != static_cast<Game::EPhantomType>(-1))
				{
					CallErrSE(in_rStateGoc, isVariantValid);
					break;
				}

				auto* pChangePhantomPlugin = in_rStateGoc.GetStatePlugin<CPluginStateCheckChangePhantom>();
				if (!pChangePhantomPlugin)
					break;
			
				if (!pChangePhantomPlugin->ChangePhantomByItem(in_rStateGoc, Game::EPhantomType::PHANTOM_BOMB, csl::math::Clamp(in_rMessage.ItemLevel, 0u, 3u)))
				{
					CallErrSE(in_rStateGoc, isVariantValid);
					break;
				}

				if (isVariantValid)
					in_rStateGoc.PlaySE("obj_itembox", false);

				in_rMessage.Taken = true;
				break;
			}
			case xgame::MsgTakeObject::EType::eType_YoshiOneUp:
			{
				xgame::MsgExtendPlayer msg{ (Game::EUser)in_rStateGoc.GetToHudPlayerNumber(), 1 };
				if (in_rMessage.ItemLevel == -1)
				{
					StateUtil::SendMission(in_rStateGoc, 2);
					msg.LifeCount = 1;
				}
				else
				{
					msg.LifeCount = ms_ReleaseBoxLivesCount[msg.LifeCount];
				}
				
				in_rStateGoc.SendMessageImmToGame(msg);
				in_rMessage.Taken = true;
				break;
			}
			case xgame::MsgTakeObject::EType::eType_YoshiCoin:
			{
				if (!in_rMessage.IsValidUserID() || in_rMessage.UserID == 6)
				{
					StateUtil::AddRingNum(in_rStateGoc, 1);
					in_rMessage.Taken = true;
				}

				break;
			}
			case xgame::MsgTakeObject::EType::eType_ZeldaOneUp:
			{
				xgame::MsgExtendPlayer msg{ (Game::EUser)in_rStateGoc.GetToHudPlayerNumber(), 1 };
				msg.LifeCount = 10;

				for (size_t i = 0; i < 10; i++)
					StateUtil::SendMission(in_rStateGoc, 2);

				in_rStateGoc.SendMessageImmToGame(msg);

				in_rMessage.Taken = true;
				break;
			}
			default:
			{
				in_rMessage.Taken = true;
				break;
			}
			}

			return true;
		}

		bool ProcMsgPlayerPassPointMarker(CStateGOC& in_rStateGoc, xgame::MsgPlayerPassPointMarker& in_rMessage)
		{
			StateUtil::PlayVoice(in_rStateGoc, 12);
			return true;
		}

		bool ProcMsgTakePixie(CStateGOC& in_rStateGoc, xgame::MsgTakePixie& in_rMessage)
		{
			if (StateUtil::GetNowPhantomType(in_rStateGoc) == Game::EPhantomType::PHANTOM_BOMB)
				return true;
			
			TakePixie(in_rStateGoc, in_rMessage.Type, in_rMessage.ItemLevel);
			in_rMessage.Taken = true;
			
			return true;
		}

		bool ProcMsgBeginGPathMode(CStateGOC& in_rStateGoc, xgame::MsgBeginGPathMode& in_rMessage)
		{
			if (!in_rMessage.Path.IsValid())
				return true;

			if (in_rStateGoc.IsOutOfControl())
				in_rStateGoc.GetBlackBoard()->SetStatus(9, true);
			else
				in_rStateGoc.GetPhysics()->UpdateGravityForced(in_rStateGoc.GetPosition());

			return true;
		}

		bool ProcMsgEndGPathMode(CStateGOC& in_rStateGoc, xgame::MsgEndGPathMode& in_rMessage)
		{
			if (in_rStateGoc.IsOutOfControl())
				in_rStateGoc.GetBlackBoard()->SetStatus(9, true);
			else
				in_rStateGoc.GetPhysics()->UpdateGravityForced(in_rStateGoc.GetPosition());

			return true;
		}

		bool ProcMsgWarpNewArea(CStateGOC& in_rStateGoc, xgame::MsgWarpNewArea& in_rMessage)
		{
			auto* pPlugin = in_rStateGoc.GetStatePlugin<PluginStateCheckEnableItem>();
			if (!pPlugin)
				return true;
	
			pPlugin->StateWarpByCollision(in_rStateGoc, in_rMessage.Unk3);
			return true;
		}

		bool ProcMsgExitLoop(CStateGOC& in_rStateGoc, xgame::MsgExitLoop& in_rMessage)
		{
			in_rStateGoc.GetPathService()->ReleasePath(3);

			in_rStateGoc.GetCollision()->Collision.SetFilterEnale(512, false);
			in_rStateGoc.GetCollision()->Collision.SetFilterEnale(1024, false);

			return true;
		}

		bool ProcMsgGetDeathTornadoInfo(CStateGOC& in_rStateGoc, xgame::MsgGetDeathTornadoInfo& in_rMessage)
		{
			if (!in_rStateGoc.GetStatePlugin<CPluginStateCheckNDC>())
				in_rStateGoc.AddStatePlugin(6);

			return true;
		}

		bool ProcMsgLossRing(CStateGOC& in_rStateGoc, xgame::MsgLossRing& in_rMessage)
		{
			if (StateUtil::IsDead(in_rStateGoc))
				return true;

			if (in_rMessage.Unk2)
			{
				int ringCount = in_rStateGoc.GetRingNum();
				StateUtil::SubRingNum(in_rStateGoc, ringCount);
				in_rMessage.RingCount = ringCount;
			}
			else
			{
				StateUtil::SubRingNum(in_rStateGoc, in_rMessage.Unk1);
				in_rMessage.RingCount = csl::math::Min(in_rMessage.Unk1, in_rStateGoc.GetRingNum());
			}

			return true;
		}

		bool ProcMsgDlcZeldaHeartAllRecovery(CStateGOC& in_rStateGoc, xgame::MsgDlcZeldaHeartAllRecovery& in_rMessage)
		{
			StateUtil::AllRecoveryHeartLife(in_rStateGoc);
			return true;
		}

		bool ProcMsgNotifySilhouetteState(CStateGOC& in_rStateGoc, xgame::MsgNotifySilhouetteState& in_rMessage)
		{
			auto* pPlugin = in_rStateGoc.GetStatePlugin<CPluginStateLockOn>();
			if (!pPlugin)
				return true;

			pPlugin->SetDisable(in_rMessage.DisableLockOn);
			return true;
		}

		bool ProcMsgHitEventCollision(CStateGOC& in_rStateGoc, xgame::MsgHitEventCollision& in_rMessage)
		{
			CheckHitEventCollision(in_rStateGoc, in_rMessage);
			return true;
		}

		bool ProcMsgStayTrigger(CStateGOC& in_rStateGoc, xgame::MsgStayTrigger& in_rMessage)
		{
			if (!CheckHitPressDeadCollision(in_rStateGoc, reinterpret_cast<xgame::MsgHitTriggerBase&>(in_rMessage)) &&
				!CheckHitTargetSearchCollision(in_rStateGoc, reinterpret_cast<xgame::MsgHitTriggerBase&>(in_rMessage)))
			{
				return false;
			}

			return true;
		}

		bool ProcMsgEndSign(CStateGOC& in_rStateGoc, xgame::MsgEndSign& in_rMessage)
		{
			xgame::MsgEndSign msg{ in_rMessage.Type, in_rMessage.Unk1 };
			in_rStateGoc.SendMessageToHud(msg);
			in_rMessage.Unk1 = true;

			return true;
		}

		bool ProcMsgStartPhantomSign(CStateGOC& in_rStateGoc, xgame::MsgStartPhantomSign& in_rMessage)
		{
			return true;
		}

		bool ProcMsgHudStartStomping(CStateGOC& in_rStateGoc, xgame::MsgHudStartStomping& in_rMessage)
		{
			return true;
		}

		bool ProcMsgHudStartHoming(CStateGOC& in_rStateGoc, xgame::MsgHudStartHoming& in_rMessage)
		{
			return true;
		}

		bool ProcMsgHudStartFallDead(CStateGOC& in_rStateGoc, xgame::MsgHudStartFallDead& in_rMessage)
		{
			in_rStateGoc.SendMessageToHud(in_rMessage);
			in_rMessage.Unk3 = true;

			return true;
		}

		bool ProcMsgFlipBoostAnytimeBoost(CStateGOC& in_rStateGoc, xgame::MsgFlipBoostAnytimeBoost& in_rMessage)
		{
			return true;
		}

		bool ProcMsgNotifyFinishAutoRun(CStateGOC& in_rStateGoc, xgame::MsgNotifyFinishAutoRun& in_rMessage)
		{
			return true;
		}

		void SetPLHoldOn(CStateGOC& in_rStateGoc, xgame::MsgPLHoldOn& in_rMessage)
		{
			if (in_rMessage.Unk1)
			{
				if (in_rMessage.Unk1 == 1)
				{
					StateUtil::SetInputEnable(in_rStateGoc, false);
				}
				else if (in_rMessage.Unk1 == 2 && !StateUtil::IsDead(in_rStateGoc))
				{
					StateUtil::SendNextStateToNotVisible(in_rStateGoc);
					in_rStateGoc.ChangeState(117);
				}
			}
			else if (!StateUtil::IsDead(in_rStateGoc))
			{
				in_rStateGoc.ChangeState(117);
			}
		}

		void CallErrSE(CStateGOC& in_rStateGoc, bool in_playSound)
		{
			if (!in_playSound)
				return;

			in_rStateGoc.PlaySE("sys_menu_error", false);
		}

		void TakePixie(CStateGOC& in_rStateGoc, Game::EPhantomType in_type, int in_itemLevel)
		{
			if (in_type == static_cast<Game::EPhantomType>(-1))
				return;
		
			if (!in_rStateGoc.GetBlackBoard()->GetPixieParameter()->TakePixie(in_type, in_itemLevel))
				return;
		
			if (in_type == Game::EPhantomType::PHANTOM_BOMB)
				return;
		
			xgame::MsgPLStockPhantom msg{ (Game::EUser)in_rStateGoc.GetToHudPlayerNumber(), in_type };
			in_rStateGoc.SendMessageToGame(msg);
		}

		bool CheckHitDeadCollision(CStateGOC& in_rStateGoc, xgame::MsgHitEventCollision& in_rMessage)
		{
			if (StateUtil::IsDead(in_rStateGoc))
				return true;
		
			if (in_rStateGoc.GetCurrentState() == 38 || HIBYTE(in_rMessage.pOther->Unk3) != 23)
				return false;
			
			in_rStateGoc.ChangeState(19);
			return true;
		}

		bool CheckHitHighJumpCollision(CStateGOC& in_rStateGoc, xgame::MsgHitEventCollision& in_rMessage)
		{
			if (in_rMessage.pSelf->GetID() != 8)
				return false;
		
			MsgGoHighJumpState msg{ in_rMessage };
			if (in_rStateGoc.ProcessMessageToCurrentState(msg))
				return msg.Unk1;

			return false;
		}

		bool CheckHitInletCollision(CStateGOC& in_rStateGoc, xgame::MsgHitEventCollision& in_rMessage)
		{
			size_t selfId = in_rMessage.pSelf->GetID();
			if (selfId != 10 && selfId != 11)
				return false;
		
			xgame::MsgRingGetSuckedInto msg{};
			msg.PlayerNo = in_rStateGoc.GetPlayerNo();

			in_rStateGoc.SendMessageImm(in_rMessage.Sender, msg);
			return true;
		}

		bool CheckHitPressDeadCollision(CStateGOC& in_rStateGoc, xgame::MsgHitTriggerBase& in_rMessage)
		{
			if (in_rMessage.pSelf->GetID() != 12)
				return false;

			auto* pPlugin = in_rStateGoc.GetStatePlugin<PluginStateCheckDead>();
			if (!pPlugin)
				return true;

			pPlugin->HitCheckPressCollision(in_rStateGoc, in_rMessage);
			return true;
		}

		bool CheckHitTargetSearchCollision(CStateGOC& in_rStateGoc, xgame::MsgHitTriggerBase& in_rMessage)
		{
			if (in_rMessage.pSelf->GetID() != 13 && in_rMessage.pSelf->GetID() != 14)
				return false;
		
			auto* pPlugin = in_rStateGoc.GetStatePlugin<CPluginStateLockOn>();
			if (!pPlugin)
				return true;

			pPlugin->HitCheckTargetCollision(in_rStateGoc, in_rMessage);
			return true;
		}

		bool CheckEnableAttackByHitCollision(CStateGOC& in_rStateGoc, xgame::MsgHitEventCollision& in_rMessage) const
		{
			if (!in_rStateGoc.GetAttackStatus()->IsAttack())
				return false;
		
			auto* pShapeData = in_rStateGoc.GetCollision()->GetShapeData(in_rMessage.pSelf);
			if (!pShapeData)
				return false;
			
			if (pShapeData->ForAttack())
				return true;

			return false;
		}

		bool CheckHitCollisionAttackStatus(CStateGOC& in_rStateGoc, xgame::MsgHitEventCollision& in_rMessage)
		{
			if (in_rStateGoc.IsDamagedShape(in_rMessage.pOther))
				return false;
		
			if (StateUtil::TestActionFlag(in_rStateGoc, 11))
			{
				xgame::MsgStartKick msg{ in_rMessage.pOther, in_rMessage.pSelf, *in_rMessage.GetContactPointPosition(), *in_rMessage.GetContactPointNormal() };
				in_rStateGoc.ProcessMessageToCurrentState(msg);
				if (msg.Unk1)
					return true;
			}

			auto* pPhysics = in_rStateGoc.GetPhysics();
			auto* pAttackStatus = in_rStateGoc.GetAttackStatus();

			xgame::MsgDamage msgDamage{ 1, pAttackStatus->GetAttackTypeFlag(), pAttackStatus->GetAttackPower(), in_rMessage, pPhysics->GetVelocity() };
			msgDamage.Bonus.Unk1 = 0;
			msgDamage.Bonus.Bonus = 1;

			xgame::MsgSetupDamageAndBonus msgBonusSetup{ in_rMessage.pOther->GetGameObject(), msgDamage };
			in_rStateGoc.ProcessMessageToCurrentState(msgBonusSetup);

			msgDamage.PlayerNo = in_rStateGoc.GetPlayerNo();
	
			in_rStateGoc.SendMessageImm(in_rMessage.pOther->GetGameObject(), msgDamage);

			if (msgDamage.IsComingReply())
				ChangeStateForMsgDamageReply(in_rStateGoc, msgDamage);
		
			return true;
		}

		bool CheckHitDamage(CStateGOC& in_rStateGoc, bool* out_pDamaged) const
		{
			if (StateUtil::IsDead(in_rStateGoc) || StateUtil::IsDisableTime(in_rStateGoc, 3) || StateUtil::IsInvincible(in_rStateGoc))
				return false;
	
			auto* pBlackboard = in_rStateGoc.GetBlackBoard();
			if (pBlackboard->Unk1[3].test(21))
			{
				in_rStateGoc.ChangeState(125);
				return false;
			}
			else
			{
				if (StateUtil::IsBarrier(in_rStateGoc) | StateUtil::IsHeartLife(in_rStateGoc) || in_rStateGoc.GetRingNum() > 0 || StateUtil::IsNowPhantom(in_rStateGoc))
				{
					*out_pDamaged = false;
					return true;
				}
				else
				{
					StateUtil::ReduceHeartLife(in_rStateGoc);
					*out_pDamaged = true;
					return true;
				}
			}
		}

		void ChangeStateForMsgDamageReply(CStateGOC& in_rStateGoc, xgame::MsgDamage& in_rMessage)
		{
			if (in_rMessage.ReplyStatus.test(1))
			{
				if (StateUtil::IsInvincible(in_rStateGoc))
				{
					in_rStateGoc.ChangeState(125);
					return;
				}
				else
				{
					bool isDamaged{};
					if (!CheckHitDamage(in_rStateGoc, &isDamaged))
						return;

					if (isDamaged)
					{
						MsgChangeDeadState msg{ { 0.0f, 0.0f, 0.0f } };
						in_rStateGoc.ProcessMessageToCurrentState(msg);
					}
					else
					{
						StateUtil::SetDisableTime(in_rStateGoc, 3, in_rStateGoc.GetParameter(1));
						StateUtil::StartDamageBlink(in_rStateGoc, in_rStateGoc.GetParameter(1));
						in_rStateGoc.GetBlackBoard()->SetStatus(1, true);

						MsgChangeDamageState msg{ in_rMessage.Unk2 };
						in_rStateGoc.ProcessMessageToCurrentState(msg);
					}
				}
			}
			else
			{
				MsgHitDamage msg{ in_rMessage };
				msg.pObject = in_rMessage.SenderShape->GetGameObject();
				in_rStateGoc.ProcessMessageToCurrentState(msg);
			}
		}

		bool CheckHitEventCollision(CStateGOC& in_rStateGoc, xgame::MsgHitEventCollision& in_rMessage)
		{
			if (!CheckHitDeadCollision(in_rStateGoc, in_rMessage) && !CheckHitHighJumpCollision(in_rStateGoc, in_rMessage) &&
				!CheckHitInletCollision(in_rStateGoc, in_rMessage) && CheckEnableAttackByHitCollision(in_rStateGoc, in_rMessage))
			{
				CheckHitCollisionAttackStatus(in_rStateGoc, in_rMessage);
			}

			return true;
		}

		bool CheckMsgStayTrigger(CStateGOC& in_rStateGoc, xgame::MsgStayTrigger& in_rMessage)
		{
			if (!CheckHitPressDeadCollision(in_rStateGoc, reinterpret_cast<xgame::MsgHitTriggerBase&>(in_rMessage)) ||
				CheckHitTargetSearchCollision(in_rStateGoc, reinterpret_cast<xgame::MsgHitTriggerBase&>(in_rMessage)))
			{
				return true;
			}

			return false;
		}

		float GetDamageTime(CStateGOC& in_rStateGoc, xgame::MsgDamage& in_rMessage)
		{
			if (AttackType::And(in_rMessage.AttackType, 0x80000) || !AttackType::And(in_rMessage.AttackType, 0x40000))
				return in_rStateGoc.GetParameter(1);
			else
				return 2.5f;
		}

		void StartDiving(CStateGOC& in_rStateGoc, xgame::MsgPLStartDiving& in_rMessage)
		{
			if (in_rStateGoc.GetBlackBoard()->Unk1[1].test(14) || in_rStateGoc.IsOnGround())
				return;
			
			auto* pDivingParam = in_rStateGoc.CreateStateContextParameter<DivingParameter>();
			pDivingParam->Unk2 = 1;
			pDivingParam->Unk3 = in_rMessage.Unk1;
			pDivingParam->Unk4 = in_rMessage.Unk2;
			pDivingParam->Unk5 = 0.0f;
			pDivingParam->Unk6 = in_rMessage.Unk4;
			pDivingParam->Unk7 = in_rMessage.Unk3;

			in_rStateGoc.ChangeState(60);
		}

		void ChangeAreaTopView(CStateGOC& in_rStateGoc, xgame::MsgPLChangeAreaTopView& in_rMessage)
		{
			in_rStateGoc.pPlayer->ChangeToTopView(in_rMessage.IsTopView);
		}

		void Change2DMode(CStateGOC& in_rStateGoc, xgame::MsgChange2DMode& in_rMessage)
		{
			in_rStateGoc.GetBlackBoard();
			if (in_rMessage.Flags.test(1))
			{
				in_rStateGoc.ChangeTo2DMode({ in_rMessage.Unk2 - in_rStateGoc.GetPosition() }, in_rMessage.Flags.test(0));
			}
			else
			{
				auto* pPhysics = in_rStateGoc.GetPhysics();
				csl::math::Vector3 gravityDir { pPhysics->GetGravityController()->GetGravityDirectionAtPointWorld(in_rStateGoc.GetPosition()) * 20.0f };
				
				if (!in_rStateGoc.ChangeTo2DMode({ gravityDir * 10.0f }, in_rMessage.Flags.test(0)))
					in_rStateGoc.ChangeTo2DMode({ gravityDir * -20.0f * 10.0f }, in_rMessage.Flags.test(0));
			}
		}

		void WarpOtherSide(CStateGOC& in_rStateGoc, xgame::MsgWarpOtherSide in_rMessage)
		{
			auto* pPhysics = in_rStateGoc.GetPhysics();

			auto& targetPosition = in_rMessage.TargetPosition;
			auto playerPosition = in_rStateGoc.GetPosition();
			targetPosition.y() = playerPosition.y();

			csl::math::Vector3 offset{ targetPosition - playerPosition };
		
			if (fabs(offset.squaredNorm()) <= 0.000001f)
				return;
		
			offset.Normalize();
			targetPosition - offset * 10.0f;

			StateUtil::ResetPosition(in_rStateGoc, targetPosition, in_rStateGoc.GetRotation());
			
			auto& collision = in_rStateGoc.GetCollision()->Collision;
			
			StateUtil::ResetLocater(in_rStateGoc, in_rStateGoc.GetMatrix());

			if (in_rStateGoc.IsOnGround())
			{
				SGroundInfo groundInfo{};
				groundInfo.Reset();

				if (collision.CheckOnGroundByHitInfo(&groundInfo, in_rStateGoc.GetUpDirection(), true, MATHF_PI / 4.0f))
					pPhysics->SetGroundInfo(groundInfo);
			}

			StateUtil::RetireHomingEffect(in_rStateGoc);
			MsgAfterWarpOtherSide msg{};
			in_rStateGoc.ProcessMessageToCurrentState(msg);
		}
	};
	
	class CStateActionBase : public CStateBase
	{
	public:
		bool ProcessMessage(CStateGOC& in_rStateGoc, fnd::Message& in_rMessage) override
		{
			switch (in_rMessage.GetType())
			{
			case xgame::MsgDamage::MessageID:							return ProcMsgDamage(in_rStateGoc, static_cast<xgame::MsgDamage&>(in_rMessage));
			case xgame::MsgDead::MessageID:								return ProcMsgDead(in_rStateGoc, static_cast<xgame::MsgDead&>(in_rMessage));
			case xgame::MsgPLStartDiving::MessageID:					return ProcMsgPLStartDiving(in_rStateGoc, static_cast<xgame::MsgPLStartDiving&>(in_rMessage));
			case xgame::MsgPLEnterDivingVolume::MessageID:				return ProcMsgPLEnterDivingVolume(in_rStateGoc, static_cast<xgame::MsgPLEnterDivingVolume&>(in_rMessage));
			case xgame::MsgPLSetNumRing::MessageID:						return ProcMsgPLSetNumRing(in_rStateGoc, static_cast<xgame::MsgPLSetNumRing&>(in_rMessage));
			case xgame::MsgPLChangeAreaTopView::MessageID:				return ProcMsgPLChangeAreaTopView(in_rStateGoc, static_cast<xgame::MsgPLChangeAreaTopView&>(in_rMessage));
			case MsgChangeDamageState::MessageID:						return ProcMsgChangeDamageState(in_rStateGoc, static_cast<MsgChangeDamageState&>(in_rMessage));
			case MsgChangeDeadState::MessageID:							return ProcMsgChangeDeadState(in_rStateGoc, static_cast<MsgChangeDeadState&>(in_rMessage));
			case xgame::MsgGravitySwitched::MessageID:					return ProcMsgGravitySwitched(in_rStateGoc, static_cast<xgame::MsgGravitySwitched&>(in_rMessage));
			case xgame::MsgChange2DMode::MessageID:						return ProcMsgChange2DMode(in_rStateGoc, static_cast<xgame::MsgChange2DMode&>(in_rMessage));
			case xgame::MsgChange3DMode::MessageID:						return ProcMsgChange3DMode(in_rStateGoc, static_cast<xgame::MsgChange3DMode&>(in_rMessage));
			case xgame::MsgCatchPlayer::MessageID:						return ProcMsgCatchPlayer(in_rStateGoc, static_cast<xgame::MsgCatchPlayer&>(in_rMessage));
			case xgame::MsgStopForGoal::MessageID:						return ProcMsgStopForGoal(in_rStateGoc, static_cast<xgame::MsgStopForGoal&>(in_rMessage));
			case xgame::MsgWarp::MessageID:								return ProcMsgWarp(in_rStateGoc, static_cast<xgame::MsgWarp&>(in_rMessage));
			case xgame::MsgEnterLoop::MessageID:						return ProcMsgEnterLoop(in_rStateGoc, static_cast<xgame::MsgEnterLoop&>(in_rMessage));
			case xgame::MsgGetPLLoopInfo::MessageID:					return ProcMsgGetPLLoopInfo(in_rStateGoc, static_cast<xgame::MsgGetPLLoopInfo&>(in_rMessage));
			case xgame::MsgSetLoopFilter::MessageID:					return ProcMsgSetLoopFilter(in_rStateGoc, static_cast<xgame::MsgSetLoopFilter&>(in_rMessage));
			case xgame::MsgAppeareKnockback::MessageID:					return ProcMsgAppeareKnockback(in_rStateGoc, static_cast<xgame::MsgAppeareKnockback&>(in_rMessage));
			default:													return CStateBase::ProcessMessage(in_rStateGoc, in_rMessage);
			}
		}

		bool ProcMsgDamage(CStateGOC& in_rStateGoc, xgame::MsgDamage& in_rMessage)
		{
			auto* pSenderData = in_rStateGoc.GetCollision()->GetShapeData(in_rMessage.SenderShape.Get());
			if (pSenderData && !pSenderData->ForDefence())
				return true;

			if (!StateUtil::IsInvincible(in_rStateGoc) && !in_rStateGoc.IsNowSuperSonic()
				&& !StateUtil::IsDisableTime(in_rStateGoc, 3) || !((in_rMessage.AttackType >> 30) & 1))
			{
				if (in_rStateGoc.GetAttackStatus()->GetDefensePower() >= in_rMessage.DefensePower)
					return true;

				float damageTime = GetDamageTime(in_rStateGoc, in_rMessage);

				bool isDamaged{};
				if (!CheckHitDamage(in_rStateGoc, &isDamaged))
					return true;

				if (!StateUtil::IsBarrier(in_rStateGoc))
					StateUtil::SendMission(in_rStateGoc, 51);

				if (isDamaged)
				{
					in_rMessage.SetReply(in_rStateGoc.GetPosition(), true);
					Player::MsgChangeDamageState msg{ *csl::math::Vector3::Zero };
					in_rStateGoc.ProcessMessageToCurrentState(msg);
					return true;
				}

				in_rMessage.SetReply(in_rStateGoc.GetPosition(), false);
				Player::MsgChangeDamageState msg{ in_rMessage.Unk3 };
				msg.pDamageMsg = &in_rMessage;
				in_rStateGoc.ProcessMessageToCurrentState(msg);

				StateUtil::SetDisableTime(in_rStateGoc, 3, damageTime);
				StateUtil::StartDamageBlink(in_rStateGoc, damageTime);
				in_rStateGoc.GetBlackBoard()->SetStatus(1, true);

				return true;
			}

			auto phantomType = StateUtil::GetNowPhantomType(in_rStateGoc);
			if (phantomType != Game::EPhantomType::ePhantom_Bomb)
			{
				if (phantomType == static_cast<Game::EPhantomType>(-1) && in_rStateGoc.GetCurrentState() != 125)
				{
					in_rMessage.SetReply(in_rStateGoc.GetPosition(), false);

					KnockedBackParameter parameter{};
					parameter.Velocity = in_rMessage.Unk3;
					in_rStateGoc.AddStateContextParameter(parameter);
					in_rStateGoc.ChangeState(125);
				}

				return true;
			}

			StateUtil::SetVelocity(in_rStateGoc, in_rMessage.Unk3);

			return true;
		}

		bool ProcMsgDead(CStateGOC& in_rStateGoc, xgame::MsgDead& in_rMessage)
		{
			if (StateUtil::IsDead(in_rStateGoc))
				return true;

			xgame::MsgPLNotifyDying msg{};
			in_rStateGoc.SendMessageToGame(msg);

			switch (in_rMessage.DeadType)
			{
			case 0:
			{
				in_rStateGoc.ChangeState(19);
				break;
			}
			case 1:
			{
				StateUtil::ResetOnGround(in_rStateGoc);
				in_rStateGoc.ChangeState(19);
				break;
			}
			case 2:
			{
				in_rStateGoc.ChangeState(23);
				break;
			}
			case 3:
			{
				StateUtil::SendDeadMessage(in_rStateGoc);
				in_rStateGoc.ChangeState(0);
				break;
			}
			case 4:
			{
				in_rStateGoc.PlaySE("sn_press_dead", false);
				if (in_rStateGoc.Is2DMode())
					in_rStateGoc.ChangeState(37);

				in_rStateGoc.ChangeState(34);
				break;
			}
			case 5:
			{
				in_rStateGoc.GetBlackBoard()->SetStatus(0, false);
				StateUtil::SendDeadMessage(in_rStateGoc);
				break;
			}
			case 6:
			{
				in_rStateGoc.ChangeState(37);
				break;
			}
			case 7:
			{
				in_rStateGoc.ChangeState(33);
				break;
			}
			case 8:
			{
				in_rStateGoc.ChangeState(22);
				break;
			}
			case 9:
			{
				in_rStateGoc.ChangeState(21);
				break;
			}
			case 10:
			{
				in_rStateGoc.GetBlackBoard()->SetStatus(30, true);
				in_rStateGoc.ChangeState(19);
				break;
			}
			default:
			{
				Player::MsgChangeDeadState msg{ *csl::math::Vector3::Zero };
				in_rStateGoc.ProcessMessageToCurrentState(msg);
				break;
			}
			}

			return true;
		}

		bool ProcMsgPLStartDiving(CStateGOC& in_rStateGoc, xgame::MsgPLStartDiving& in_rMessage)
		{
			StartDiving(in_rStateGoc, in_rMessage);
			return true;
		}

		bool ProcMsgPLEnterDivingVolume(CStateGOC& in_rStateGoc, xgame::MsgPLEnterDivingVolume& in_rMessage)
		{
			EnterDivingVolume(in_rStateGoc, in_rMessage);
			return true;
		}

		bool ProcMsgPLSetNumRing(CStateGOC& in_rStateGoc, xgame::MsgPLSetNumRing& in_rMessage)
		{
			StateUtil::SetRingNum(in_rStateGoc, in_rMessage.RingCount, true);
			return true;
		}

		bool ProcMsgPLChangeAreaTopView(CStateGOC& in_rStateGoc, xgame::MsgPLChangeAreaTopView& in_rMessage)
		{
			ChangeAreaTopView(in_rStateGoc, in_rMessage);
			return true;
		}

		bool ProcMsgChangeDamageState(CStateGOC& in_rStateGoc, MsgChangeDamageState& in_rMessage)
		{
			DamageParameter damageParam{};
			damageParam.Unk3 = in_rMessage.Unk1;
			in_rStateGoc.AddStateContextParameter(damageParam);

			if (!in_rMessage.pDamageMsg)
			{
				ChangeToDamageState(in_rStateGoc);
				return true;
			}

			if (AttackType::And(in_rMessage.pDamageMsg->AttackType, 0x80000))
			{
				in_rStateGoc.ChangeState(30);
			}
			else if (AttackType::And(in_rMessage.pDamageMsg->AttackType, 0x40000))
			{
				in_rStateGoc.ChangeState(31);
			}
			else if (AttackType::And(in_rMessage.pDamageMsg->AttackType, 0x200000))
			{
				StateUtil::PlayVoice(in_rStateGoc, 9);
				StateUtil::ScatterRingForDamage(in_rStateGoc, false, 10);
			}
			else
			{
				ChangeToDamageState(in_rStateGoc);
			}

			return true;
		}

		bool ProcMsgChangeDeadState(CStateGOC& in_rStateGoc, MsgChangeDeadState& in_rMessage)
		{
			in_rStateGoc.ChangeState(33);
			return true;
		}

		bool ProcMsgGravitySwitched(CStateGOC& in_rStateGoc, xgame::MsgGravitySwitched& in_rMessage)
		{
			auto* pPhysics = in_rStateGoc.GetPhysics();
			pPhysics->UpdateGravityForced(in_rStateGoc.GetPosition());

			pPhysics->Up = { -pPhysics->GetGravityController()->GetGravityDirectionAtPointWorld(in_rStateGoc.GetPosition()) };

			return true;
		}

		bool ProcMsgChange2DMode(CStateGOC& in_rStateGoc, xgame::MsgChange2DMode& in_rMessage)
		{
			Change2DMode(in_rStateGoc, in_rMessage);
			return true;
		}

		bool ProcMsgChange3DMode(CStateGOC& in_rStateGoc, xgame::MsgChange3DMode& in_rMessage)
		{
			StateUtil::IsDead(in_rStateGoc);
			in_rStateGoc.ChangeTo3DMode(in_rMessage.Unk2);
			return true;
		}

		bool ProcMsgCatchPlayer(CStateGOC& in_rStateGoc, xgame::MsgCatchPlayer& in_rMessage)
		{
			SetCatchPlayer(in_rStateGoc, in_rMessage);
			return true;
		}

		bool ProcMsgStopForGoal(CStateGOC& in_rStateGoc, xgame::MsgStopForGoal& in_rMessage)
		{
			in_rStateGoc.ChangeState(47);
			return true;
		}

		bool ProcMsgWarp(CStateGOC& in_rStateGoc, xgame::MsgWarp& in_rMessage)
		{
			if (auto* pPlugin = in_rStateGoc.GetStatePlugin<PluginStateCheckEnableItem>())
				pPlugin->DoneWarp(in_rStateGoc);

			if (in_rStateGoc.GetCurrentState() == 105)
			{
				auto* pSnowball = StateUtil::GetSnowBall(in_rStateGoc);
				csl::math::Matrix34 rotationMatrix{ in_rMessage.TargetRotation };

				pSnowball->SetPosition({ in_rMessage.TargetPosition + rotationMatrix.GetColumn(1) * pSnowball->Radius });
				StateUtil::ResetPosition(in_rStateGoc, { in_rMessage.TargetPosition + rotationMatrix.GetColumn(1) * pSnowball->Radius * 2.0f });
				StateUtil::ResetVelocity(in_rStateGoc);
				xgame::MsgCameraReset msg{};
				in_rStateGoc.SendMessageImmToCamera(msg);
			}
			else
			{
				game::PathComponent* pComponent{};
				float unk{};

				in_rStateGoc.RemoveStatePlugin(6);
				in_rStateGoc.RemoveStatePlugin(8);
				StateUtil::ResetPosition(in_rStateGoc, in_rMessage.TargetPosition, in_rMessage.TargetRotation);
				StateUtil::ResetVelocity(in_rStateGoc);
				StateUtil::ResetLocater(in_rStateGoc, in_rStateGoc.GetMatrix());

				bool is2D = in_rMessage.Unk1;
				if (is2D)
				{
					auto* pPathService = in_rStateGoc.GetPathService();

					csl::math::Vector3 from{ in_rMessage.TargetPosition + csl::math::Vector3::UnitY() * 1.0f };
					csl::math::Vector3 to{ in_rMessage.TargetPosition - csl::math::Vector3::UnitY() * 5000.0f };
					pComponent = pPathService->Search2DPath(from, to, &unk);
					if (!pComponent)
					{
						from = { in_rMessage.TargetPosition + math::Vector3Rotate(in_rMessage.TargetRotation, { csl::math::Vector3::UnitY() }) * 1.0f };
						to = { in_rMessage.TargetPosition - math::Vector3Rotate(in_rMessage.TargetRotation, { csl::math::Vector3::UnitY() }) * 5000.0f };
						pComponent = pPathService->Search2DPath(from, to, &unk);
						if (!pComponent)
							is2D = false;
					}
				}

				in_rStateGoc.pPlayer->ChangeDimension(is2D, true, pComponent, unk);
				StateUtil::RetireHomingEffect(in_rStateGoc);
				in_rStateGoc.GetPhysics()->Up = in_rStateGoc.GetPhysics()->GetUp();
				in_rStateGoc.ChangeState(122);
			}

			return true;
		}

		bool ProcMsgEnterLoop(CStateGOC& in_rStateGoc, xgame::MsgEnterLoop& in_rMessage)
		{
			EnterLoop(in_rStateGoc, in_rMessage);
			return true;
		}

		bool ProcMsgGetPLLoopInfo(CStateGOC& in_rStateGoc, xgame::MsgGetPLLoopInfo& in_rMessage)
		{
			if (auto* pPathEvaluator = in_rStateGoc.GetPath(3))
			{
				in_rStateGoc.IsOnGround();

				in_rMessage.Unk1 = true;
				in_rMessage.Unk2 = pPathEvaluator->Distance;
				in_rMessage.Unk3 = in_rStateGoc.GetUpDirection();
				in_rMessage.Unk4 = in_rStateGoc.IsOnGround();
			}

			return true;
		}

		bool ProcMsgSetLoopFilter(CStateGOC& in_rStateGoc, xgame::MsgSetLoopFilter& in_rMessage)
		{
			auto* pCollision = in_rStateGoc.GetCollision();
			pCollision->Collision.SetFilterEnale(512, in_rMessage.Unk1);
			pCollision->Collision.SetFilterEnale(1024, in_rMessage.Unk2);

			return true;
		}

		bool ProcMsgAppeareKnockback(CStateGOC& in_rStateGoc, xgame::MsgAppeareKnockback& in_rMessage)
		{
			if (StateUtil::GetNowPhantomType(in_rStateGoc) == static_cast<Game::EPhantomType>(-1) && (in_rStateGoc.IsOnGround() || !in_rMessage.Unk1))
			{
				KnockedBackParameter parameter{};
				parameter.Velocity = in_rMessage.Velocity;

				in_rStateGoc.AddStateContextParameter(parameter);
				in_rStateGoc.ChangeState(125);
			}

			return true;
		}

		void EnterDivingVolume(CStateGOC& in_rStateGoc, xgame::MsgPLEnterDivingVolume& in_rMessage)
		{
			if (in_rStateGoc.GetBlackBoard()->Unk1[1].test(14) || in_rStateGoc.IsOnGround() && in_rMessage.Unk6)
				return;

			auto* pDivingParam = in_rStateGoc.CreateStateContextParameter<DivingParameter>();
			pDivingParam->Unk2 = 2;
			pDivingParam->Unk8 = in_rMessage.Unk3;
			pDivingParam->Unk9 = in_rMessage.Unk4;
			pDivingParam->Unk10 = in_rMessage.Unk5;

			in_rStateGoc.ChangeState(60);
		}

		void ChangeToDamageState(CStateGOC& in_rStateGoc)
		{
			if (StateUtil::IsNowAutoRun(in_rStateGoc))
			{
				in_rStateGoc.ChangeState(28);
				return;
			}

			in_rStateGoc.ChangeState(in_rStateGoc.IsOnGround() ? 26 : 27);
		}

		void SetCatchPlayer(CStateGOC& in_rStateGoc, xgame::MsgCatchPlayer& in_rMessage)
		{
			if (StateUtil::GetNowPhantomType(in_rStateGoc) != static_cast<Game::EPhantomType>(-1))
			{
				if (!in_rMessage.Unk1.test(3))
					return;

				StateUtil::AbortPhantom(in_rStateGoc);
			}

			if (in_rStateGoc.GetBlackBoard()->Unk1[3].test(4))
				return;

			StateHangOnParameter hangParam{};
			switch (in_rMessage.Unk3)
			{
			case 0:
			{
				hangParam.HangType = 3;
				break;
			}
			case 2:
			{
				hangParam.HangType = 10;
				break;
			}
			case 3:
			case 11:
			{
				hangParam.HangType = 1;
				break;
			}
			case 4:
			case 7:
			{
				hangParam.HangType = 4;
				break;
			}
			case 5:
			{
				hangParam.HangType = 5;
				break;
			}
			case 8:
			{
				hangParam.HangType = 6;
				break;
			}
			case 9:
			{
				auto* pPinballParam = in_rStateGoc.CreateStateContextParameter<PinBallParameter>();
				pPinballParam->Unk2 = in_rMessage.Sender;
				pPinballParam->Unk3 = 4;
				in_rMessage.Unk4 = true;
				in_rStateGoc.ChangeState(82);

				return;
			}
			case 10:
			{
				hangParam.HangType = 12;
				break;
			}
			case 12:
			{
				hangParam.HangType = 8;
				break;
			}
			case 13:
			{
				hangParam.HangType = 9;
				break;
			}
			case 14:
			{
				hangParam.HangType = 13;
				if (in_rStateGoc.IsOnGround())
					break;

				return;
			}
			case 15:
			{
				hangParam.HangType = 7;
				break;
			}
			case 16:
			{
				hangParam.HangType = 0;
				hangParam.Unk1 = 1;
				hangParam.Unk2 = in_rMessage.Sender;

				in_rStateGoc.AddStateContextParameter(hangParam);

				in_rMessage.Unk4 = true;
				in_rStateGoc.ChangeStateAlways(89);

				return;
			}
			case 17:
			{
				hangParam.HangType = 11;
				break;
			}
			case 19:
			{
				hangParam.HangType = 14;
				StateUtil::EndDamageBlink(in_rStateGoc);
				break;
			}
			case 20:
			{
				hangParam.HangType = 15;
				break;
			}
			default:
			{
				hangParam.HangType = 0;
				break;
			}
			}

			hangParam.Unk1 = 1;
			hangParam.Unk2 = in_rMessage.Sender;
			hangParam.Unk3.set(0, in_rMessage.Unk1.test(0));
			hangParam.Unk3.set(1, in_rMessage.Unk1.test(1));
			hangParam.Unk3.set(2, in_rMessage.Unk1.test(2));
			hangParam.Unk3.set(3, in_rMessage.Unk1.test(4));
			hangParam.Unk3.set(4, in_rMessage.Unk1.test(5));

			in_rStateGoc.AddStateContextParameter(hangParam);
			in_rStateGoc.ChangeStateAlways(88);
			in_rMessage.Unk4 = true;
		}

		void EnterLoop(CStateGOC& in_rStateGoc, xgame::MsgEnterLoop& in_rMessage)
		{
			in_rStateGoc.GetPathService()->SetPath(3, in_rMessage.PathComponent.Get(), in_rMessage.Distance);
			auto* pPathEvaluator = in_rStateGoc.GetPath(3);
			if (!pPathEvaluator)
				return;

			csl::math::Vector3 point{}, normal{}, tangent{};
			pPathEvaluator->GetPNT(in_rMessage.Distance, &point, &normal, &tangent);

			csl::math::Matrix34 matrix = math::Matrix34OrthonormalDirection(tangent, normal);
			csl::math::Matrix34 inverseMtx{};
			csl::math::Matrix34Inverse(matrix, &inverseMtx);

			csl::math::Vector3 splinePoint{ inverseMtx* csl::math::Vector3(in_rStateGoc.GetPosition() - point) };
			splinePoint.y() = 0.0f;
			splinePoint = { point + matrix * splinePoint };

			float distance{};
			if (fabs(in_rMessage.Distance) > 0.000001f)
				pPathEvaluator->GetClosestPositionAlongSpline(splinePoint, pPathEvaluator->GetLength() * 0.5f, pPathEvaluator->GetLength(), &distance);
			else
				pPathEvaluator->GetClosestPositionAlongSpline(splinePoint, 0.0f, pPathEvaluator->GetLength() * 0.5f, &distance);

			pPathEvaluator->SetDistance(distance);
		}
	};

	class CStateSonicBase : public CStateActionBase
	{
	public:
		bool ProcessMessage(CStateGOC& in_rStateGoc, fnd::Message& in_rMessage) override
		{
			switch (in_rMessage.GetType())
			{
			case xgame::MsgPLStartAlongPathMode::MessageID:				return ProcMsgPLStartAlongPathMode(in_rStateGoc, static_cast<xgame::MsgPLStartAlongPathMode&>(in_rMessage));
			case xgame::MsgPLJumpToTargetPosition::MessageID:			return ProcMsgPLJumpToTargetPosition(in_rStateGoc, static_cast<xgame::MsgPLJumpToTargetPosition&>(in_rMessage));
			case xgame::MsgPLStagger::MessageID:						return ProcMsgPLStagger(in_rStateGoc, static_cast<xgame::MsgPLStagger&>(in_rMessage));
			case xgame::MsgPLQuake::MessageID:							return ProcMsgPLQuake(in_rStateGoc, static_cast<xgame::MsgPLQuake&>(in_rMessage));
			case MsgPLChangeStateGetBubble::MessageID:					return ProcMsgPLChangeStateGetBubble(in_rStateGoc, static_cast<MsgPLChangeStateGetBubble&>(in_rMessage));
			case MsgPLCheckPhantomStart::MessageID:						return ProcMsgPLCheckPhantomStart(in_rStateGoc, static_cast<MsgPLCheckPhantomStart&>(in_rMessage));
			case xgame::MsgSpringImpulse::MessageID:					return ProcMsgSpringImpulse(in_rStateGoc, static_cast<xgame::MsgSpringImpulse&>(in_rMessage));
			case xgame::MsgOnGroundImpulse::MessageID:					return ProcMsgOnGroundImpulse(in_rStateGoc, static_cast<xgame::MsgOnGroundImpulse&>(in_rMessage));
			case xgame::MsgBumperImpulse::MessageID:					return ProcMsgBumperImpulse(in_rStateGoc, static_cast<xgame::MsgBumperImpulse&>(in_rMessage)); 
			case xgame::MsgFlipperImpulse::MessageID:					return ProcMsgFlipperImpulse(in_rStateGoc, static_cast<xgame::MsgFlipperImpulse&>(in_rMessage));
			case xgame::MsgSheepBumperImpulse::MessageID:				return ProcMsgSheepBumperImpulse(in_rStateGoc, static_cast<xgame::MsgSheepBumperImpulse&>(in_rMessage));
			case xgame::MsgSheepRollingImpulse::MessageID:				return ProcMsgSheepRollingImpulse(in_rStateGoc, static_cast<xgame::MsgSheepRollingImpulse&>(in_rMessage));
			case xgame::MsgItemTreeWobblePoint::MessageID:				return ProcMsgItemTreeWobblePoint(in_rStateGoc, static_cast<xgame::MsgItemTreeWobblePoint&>(in_rMessage));
			case xgame::MsgSheepTargetImpulse::MessageID:				return ProcMsgSheepTargetImpulse(in_rStateGoc, static_cast<xgame::MsgSheepTargetImpulse&>(in_rMessage));
			case xgame::MsgWarpOtherSide::MessageID:					return ProcMsgWarpOtherSide(in_rStateGoc, static_cast<xgame::MsgWarpOtherSide&>(in_rMessage));
			case xgame::MsgDroppingSand::MessageID:						return ProcMsgDroppingSand(in_rStateGoc, static_cast<xgame::MsgDroppingSand&>(in_rMessage));
			case xgame::MsgQuicksandImpulse::MessageID:					return ProcMsgQuicksandImpulse(in_rStateGoc, static_cast<xgame::MsgQuicksandImpulse&>(in_rMessage));
			case xgame::MsgSandHoleDrawIn::MessageID:					return ProcMsgSandHoleDrawIn(in_rStateGoc, static_cast<xgame::MsgSandHoleDrawIn&>(in_rMessage));
			case xgame::MsgLaunchPathSpring::MessageID:					return ProcMsgLaunchPathSpring(in_rStateGoc, static_cast<xgame::MsgLaunchPathSpring&>(in_rMessage)); 
			case xgame::MsgOnRunningSand::MessageID:					return ProcMsgOnRunningSand(in_rStateGoc, static_cast<xgame::MsgOnRunningSand&>(in_rMessage)); 
			case xgame::MsgSeaMineStream::MessageID:					return ProcMsgSeaMineStream(in_rStateGoc, static_cast<xgame::MsgSeaMineStream&>(in_rMessage));
			case xgame::MsgWaterWorks::MessageID:						return ProcMsgWaterWorks(in_rStateGoc, static_cast<xgame::MsgWaterWorks&>(in_rMessage));
			case xgame::MsgPinBallStarter::MessageID:					return ProcMsgPinBallStarter(in_rStateGoc, static_cast<xgame::MsgPinBallStarter&>(in_rMessage));
			case xgame::MsgSandDriveStarter::MessageID:					return ProcMsgSandDriveStarter(in_rStateGoc, static_cast<xgame::MsgSandDriveStarter&>(in_rMessage));
			case xgame::MsgKekkoBlow::MessageID:						return ProcMsgKekkoBlow(in_rStateGoc, static_cast<xgame::MsgKekkoBlow&>(in_rMessage));
			case xgame::MsgGetSuckedIntoPipe::MessageID:				return ProcMsgGetSuckedIntoPipe(in_rStateGoc, static_cast<xgame::MsgGetSuckedIntoPipe&>(in_rMessage));
			case xgame::MsgHitUpdraftCollision::MessageID:				return ProcMsgHitUpdraftCollision(in_rStateGoc, static_cast<xgame::MsgHitUpdraftCollision&>(in_rMessage));
			case xgame::MsgBakubakuJump::MessageID:						return ProcMsgBakubakuJump(in_rStateGoc, static_cast<xgame::MsgBakubakuJump&>(in_rMessage));
			case xgame::MsgNotifyMidBossDMEvent::MessageID:				return ProcMsgNotifyMidBossDMEvent(in_rStateGoc, static_cast<xgame::MsgNotifyMidBossDMEvent&>(in_rMessage));
			case xgame::MsgHoverImpulse::MessageID:						return ProcMsgHoverImpulse(in_rStateGoc, static_cast<xgame::MsgHoverImpulse&>(in_rMessage));
			case xgame::MsgDlcZeldaTakeHeart::MessageID:				return ProcMsgDlcZeldaTakeHeart(in_rStateGoc, static_cast<xgame::MsgDlcZeldaTakeHeart&>(in_rMessage));
			case xgame::MsgDlcZeldaTakeHeartContainer::MessageID:		return ProcMsgDlcZeldaTakeHeartContainer(in_rStateGoc, static_cast<xgame::MsgDlcZeldaTakeHeartContainer&>(in_rMessage));
			case xgame::MsgStartPhantomSign::MessageID:					return ProcMsgStartPhantomSign(in_rStateGoc, static_cast<xgame::MsgStartPhantomSign&>(in_rMessage));
			case xgame::MsgHudStartStomping::MessageID:					return ProcMsgHudStartStomping(in_rStateGoc, static_cast<xgame::MsgHudStartStomping&>(in_rMessage));
			case xgame::MsgHudStartHoming::MessageID:					return ProcMsgHudStartHoming(in_rStateGoc, static_cast<xgame::MsgHudStartHoming&>(in_rMessage));
			default:													return CStateActionBase::ProcessMessage(in_rStateGoc, in_rMessage);
			}
		}

		virtual bool ProcMsgStartPhantomSign(CStateGOC& in_rStateGoc, xgame::MsgStartPhantomSign& in_rMessage)
		{
			if (in_rStateGoc.GetBlackBoard()->GetPixieParameter()->HasPixie())
			{
				in_rStateGoc.SendMessageToHud(in_rMessage);
				in_rMessage.Unk3 = 1;
			}

			return true;
		}

		virtual bool ProcMsgHudStartHoming(CStateGOC& in_rStateGoc, xgame::MsgHudStartHoming& in_rMessage)
		{
			in_rStateGoc.SendMessageToHud(in_rMessage);
			in_rMessage.Unk3 = 1;

			return true;
		}

		virtual bool ProcMsgHudStartStomping(CStateGOC& in_rStateGoc, xgame::MsgHudStartStomping& in_rMessage)
		{
			in_rStateGoc.SendMessageToHud(in_rMessage);
			in_rMessage.Unk3 = 1;

			return true;
		}

		virtual bool ProcMsgOnGroundImpulse(CStateGOC& in_rStateGoc, xgame::MsgOnGroundImpulse& in_rMessage)
		{
			if (StateUtil::IsDisableTime(in_rStateGoc, 1, in_rMessage.Sender))
				return true;

			csl::math::Vector3 vector { in_rMessage.Unk2 };
			if (!math::Vector3NormalizeIfNotZero(vector, &vector))
				return true;

			StateUtil::SetUpDirection(in_rStateGoc, in_rMessage.UpDirection);
			StateUtil::SetRotation(in_rStateGoc, vector, in_rMessage.UpDirection, true, false);

			if (in_rStateGoc.Is2DMode())
			{
				if (auto* pPathEvaluator = in_rStateGoc.GetPath(0))
				{
					float distance = csl::math::Vector3(in_rMessage.Unk1 - in_rStateGoc.GetPosition()).norm();
					pPathEvaluator->GetClosestPositionAlongSpline(in_rMessage.Unk1, pPathEvaluator->Distance - distance, pPathEvaluator->Distance + distance, &distance);
					pPathEvaluator->SetDistance(distance);
				}
			}

			in_rStateGoc.VisualLocaterStartInterpolation(0.1f, 0);
			StateUtil::SetPosition(in_rStateGoc, in_rMessage.Unk1, false);
			StateUtil::ForceOnGround(in_rStateGoc);
			
			auto* pPhysics = in_rStateGoc.GetPhysics();
			pPhysics->UpdateGravityForced(in_rMessage.Unk1);
			if (in_rStateGoc.GetCurrentState() != 68)
				in_rStateGoc.ChangeState(3);

			MsgSetupGroundImpulse setupImpulseMsg{};
			setupImpulseMsg.Unk1 = in_rMessage.Unk6;
			in_rStateGoc.ProcessMessageToCurrentState(setupImpulseMsg);

			StateUtil::SetVelocity(in_rStateGoc, vector);
			StateUtil::ForcedStopFootPlacement(in_rStateGoc);
			if (in_rMessage.Unk3 > 0.0f)
				in_rStateGoc.StartOutOfControl(in_rMessage.Unk3, false);

			if (in_rMessage.PanelType != 1)
				StateUtil::CreateSpringFollowEffect(in_rStateGoc);

			xgame::MsgPLStartGroundImpulse startImpulseMsg{};
			startImpulseMsg.Unk1 = in_rStateGoc.GetMatrix();
			startImpulseMsg.Unk2 = vector;
			startImpulseMsg.Unk3 = in_rMessage.Unk3;

			in_rMessage.Unk7 = true;

			return true;
		}

		virtual bool ProcMsgSpringImpulse(CStateGOC& in_rStateGoc, xgame::MsgSpringImpulse& in_rMessage)
		{
			if (StateUtil::IsDisableTime(in_rStateGoc, 0, in_rMessage.Sender) || (in_rMessage.Flags.test(15) && in_rStateGoc.IsOutOfControl()))
				return true;

			csl::math::Vector3 origin{};
			if (in_rMessage.Flags.test(5))
				origin = in_rMessage.Origin;
			
			csl::math::Vector3 yawDirection{};
			if (in_rMessage.Flags.test(8))
				yawDirection = in_rMessage.YawDirection;

			StateUtil::DoSpringJump(in_rStateGoc, &origin, &in_rMessage.Direction, in_rMessage.OutOfControl, in_rMessage.SpeedDropoffTime, in_rMessage.Flags, true, true, false, in_rMessage.Unk1, &yawDirection, in_rMessage.OutOfParkour);
			StateUtil::SetDisableTime(in_rStateGoc, 0, in_rMessage.Sender, 0.1f);
			StateUtil::ForcedStopFootPlacement(in_rStateGoc);

			if (in_rMessage.Flags.test(0))
			{
				StateUtil::ChangeToChangePathMode(in_rStateGoc, 0.5f, in_rMessage.Flags.test(3));
			}
			else
			{
				if (in_rStateGoc.Is2DMode() && in_rMessage.Flags.test(4))
					in_rStateGoc.ChangeTo3DMode(in_rMessage.Flags.test(3));
			}

			StateUtil::CreateSpringFollowEffect(in_rStateGoc);

			in_rMessage.Handled = true;

			return true;
		}

		virtual bool ProcMsgPLCheckPhantomStart(CStateGOC& in_rStateGoc, MsgPLCheckPhantomStart& in_rMessage)
		{
			if (in_rStateGoc.IsOutOfControl())
				CheckPhantomStart(in_rStateGoc, in_rMessage);

			return true;
		}

		bool ProcMsgPLChangeStateGetBubble(CStateGOC& in_rStateGoc, MsgPLChangeStateGetBubble& in_rMessage)
		{
			in_rStateGoc.ChangeState(in_rStateGoc.IsOnGround() ? 56 : 57);
			return true;
		}

		bool ProcMsgPLStartAlongPathMode(CStateGOC& in_rStateGoc, xgame::MsgPLStartAlongPathMode& in_rMessage)
		{
			LaunchToPathParameter parameter{};
			parameter.Sender = in_rMessage.Sender;
			parameter.PathComponent = in_rMessage.PathComponent;
			parameter.Unk2 = in_rMessage.Unk1;
			parameter.Unk3 = in_rMessage.Unk2;

			in_rStateGoc.AddStateContextParameter(parameter);
			in_rStateGoc.ChangeState(81);

			if (in_rStateGoc.Is2DMode() && in_rMessage.Flags.test(1))
				in_rStateGoc.ChangeTo3DMode(false);

			if (in_rMessage.Flags.test(0))
				StateUtil::ChangeToChangePathMode(in_rStateGoc, 0.5f, false);

			in_rMessage.Unk3 = true;

			return true;
		}

		bool ProcMsgPLJumpToTargetPosition(CStateGOC& in_rStateGoc, xgame::MsgPLJumpToTargetPosition& in_rMessage)
		{
			GoTargetParameter parameter{};
			parameter.Target = math::Matrix34AffineTransformation(in_rMessage.TargetPosition, in_rMessage.TargetRotation);
			parameter.Unk2 = in_rMessage.Unk1;
			parameter.Unk3 = in_rMessage.Unk2;
			parameter.Unk4 = in_rMessage.Unk3;

			in_rStateGoc.AddStateContextParameter(parameter);

			in_rStateGoc.ChangeState(120);
			return true;
		}

		bool ProcMsgPLStagger(CStateGOC& in_rStateGoc, xgame::MsgPLStagger& in_rMessage)
		{
			if (StateUtil::IsDead(in_rStateGoc) || StateUtil::IsDamaged(in_rStateGoc) || !in_rStateGoc.IsOnGround() || in_rStateGoc.IsNowSuperSonic())
				return true;

			in_rStateGoc.ChangeState(126);
			return true;
		}

		bool ProcMsgPLQuake(CStateGOC& in_rStateGoc, xgame::MsgPLQuake& in_rMessage)
		{
			if (StateUtil::IsDead(in_rStateGoc) || StateUtil::IsDamaged(in_rStateGoc) || !in_rStateGoc.IsOnGround())
				return true;

			in_rStateGoc.CreateStateContextParameter<DamageQuakeParameter>()->Unk2 = 3.0f;

			in_rStateGoc.ChangeState(32);
			return true;
		}

		bool ProcMsgBumperImpulse(CStateGOC& in_rStateGoc, xgame::MsgBumperImpulse& in_rMessage)
		{
			auto* pPhysics = in_rStateGoc.GetPhysics();
			pPhysics->SetVelocity(in_rMessage.Velocity);

			in_rMessage.Unk6 = true;

			auto* pPinballParam = in_rStateGoc.CreateStateContextParameter<PinBallParameter>();
			pPinballParam->Unk2 = in_rMessage.Unk4;
			pPinballParam->Unk3 = !in_rMessage.Unk5;
			pPinballParam->Unk9 = in_rMessage.Unk2;

			if (in_rStateGoc.Is2DMode())
				pPinballParam->IsMode2D = true;

			in_rStateGoc.ChangeState(82);
			return true;
		}

		bool ProcMsgFlipperImpulse(CStateGOC& in_rStateGoc, xgame::MsgFlipperImpulse& in_rMessage)
		{
			auto* pPhysics = in_rStateGoc.GetPhysics();
			pPhysics->SetVelocity(in_rMessage.Velocity);
			
			in_rMessage.Unk4 = true;

			auto* pPinballParam = in_rStateGoc.CreateStateContextParameter<PinBallParameter>();
			pPinballParam->Unk9 = in_rMessage.Unk2;
			if (in_rStateGoc.Is2DMode())
				pPinballParam->IsMode2D = true;

			in_rStateGoc.ChangeState(82);
			return true;
		}

		bool ProcMsgSheepBumperImpulse(CStateGOC& in_rStateGoc, xgame::MsgSheepBumperImpulse& in_rMessage)
		{
			if (StateUtil::IsDisableTime(in_rStateGoc, 0, in_rMessage.Sender))
				return false;

			csl::math::Vector3 vector{ in_rMessage.Unk2 };
			if (!math::Vector3NormalizeIfNotZero(vector, &vector))
				return false;
			
			auto* pPhysics = in_rStateGoc.GetPhysics();
			pPhysics->SetVelocity({ vector * in_rMessage.Unk3 });
			PlayerUtil::SetDirection(pPhysics, vector, pPhysics->GetGravityUpDirection());
			StateUtil::SetDisableTime(in_rStateGoc, 0, in_rMessage.Sender, 1.0f);

			auto* pPinballParam = in_rStateGoc.CreateStateContextParameter<PinBallParameter>();
			pPinballParam->Unk9 = in_rMessage.Unk4;
			if (in_rMessage.Unk5 == 1)
			{
				pPinballParam->Unk5 = 3;
				pPinballParam->Unk6 = in_rMessage.Unk1;
			}
			else
			{
				pPinballParam->Unk5 = 2;
			}

			in_rStateGoc.ChangeState(82);
			return true;
		}

		bool ProcMsgSheepRollingImpulse(CStateGOC& in_rStateGoc, xgame::MsgSheepRollingImpulse& in_rMessage)
		{
			if (StateUtil::IsDisableTime(in_rStateGoc, 0, in_rMessage.Sender))
				return false;

			auto* pPhysics = in_rStateGoc.GetPhysics();

			if (!pPhysics->IsGravityTypeRunPath())
				return false;

			StateUtil::SetDisableTime(in_rStateGoc, 0, in_rMessage.Sender, 1.0f);

			auto* pRollingParam = in_rStateGoc.CreateStateContextParameter<RollingParameter>();
			pRollingParam->Unk2 = in_rMessage.Unk2;
			pRollingParam->Unk3 = in_rMessage.Unk1;

			in_rStateGoc.ChangeState(65);
			return true;
		}

		bool ProcMsgItemTreeWobblePoint(CStateGOC& in_rStateGoc, xgame::MsgItemTreeWobblePoint& in_rMessage)
		{
			if (in_rStateGoc.GetCurrentState() == 73)
				return false;

			auto* pPhysics = in_rStateGoc.GetPhysics();

			if (in_rStateGoc.IsOnGround())
				return false;

			pPhysics->GetGravityUpDirection();

			if (pPhysics->GetVelocity().dot(csl::math::Vector3(in_rMessage.WobblePoint - in_rStateGoc.GetPosition())) > 0.0f)
				return false;

			auto* pWallrunParam = in_rStateGoc.CreateStateContextParameter<WallRunParameter>();
			pWallrunParam->Unk6 = 1;
			pWallrunParam->Unk7 = in_rMessage.WobblePoint;

			in_rStateGoc.ChangeState(73);
			return true;
		}

		bool ProcMsgSheepTargetImpulse(CStateGOC& in_rStateGoc, xgame::MsgSheepTargetImpulse& in_rMessage)
		{
			if (StateUtil::IsDisableTime(in_rStateGoc, 0, in_rMessage.Sender))
				return false;

			csl::math::Vector3 vector = in_rMessage.Unk2;
			if (!math::Vector3NormalizeIfNotZero(vector, &vector))
				return false;

			StateUtil::SetDisableTime(in_rStateGoc, 0, in_rMessage.Sender, 1.0f);
			in_rMessage.Unk6 = true;

			auto* pPinballParam = in_rStateGoc.CreateStateContextParameter<PinBallParameter>();
			pPinballParam->Unk5 = 1;
			pPinballParam->Unk6 = in_rMessage.Unk1;
			pPinballParam->Unk7 = { vector * in_rMessage.Unk4 };
			pPinballParam->Unk8 = in_rMessage.Unk4;
			pPinballParam->Unk9 = in_rMessage.Unk5;

			in_rStateGoc.ChangeState(82);
			return true;
		}

		bool ProcMsgWarpOtherSide(CStateGOC& in_rStateGoc, xgame::MsgWarpOtherSide& in_rMessage)
		{
			WarpOtherSide(in_rStateGoc, in_rMessage);
			return true;
		}

		bool ProcMsgDroppingSand(CStateGOC& in_rStateGoc, xgame::MsgDroppingSand& in_rMessage)
		{
			in_rStateGoc.CreateStateContextParameter<StopBySandParameter>()->Unk2 = in_rMessage.Unk1;

			in_rStateGoc.ChangeState(99);
			return true;
		}

		bool ProcMsgQuicksandImpulse(CStateGOC& in_rStateGoc, xgame::MsgQuicksandImpulse& in_rMessage)
		{
			auto* pSweptParam = in_rStateGoc.CreateStateContextParameter<SweptBySandParameter>();
			pSweptParam->Unk2 = in_rMessage.Unk1;
			pSweptParam->Unk3 = in_rMessage.Unk2;
			pSweptParam->Sender = in_rMessage.Sender;

			in_rStateGoc.ChangeState(98);
			return true;
		}

		bool ProcMsgLaunchPathSpring(CStateGOC& in_rStateGoc, xgame::MsgLaunchPathSpring& in_rMessage)
		{
			if (StateUtil::IsDisableTime(in_rStateGoc, 0, in_rMessage.Sender))
				return true;
			
			csl::ut::Bitset<uint> flags{};
			flags.set(2, true);
			
			csl::math::Vector3 direction{};
			bool isStomping = StateUtil::IsNowStomping(in_rStateGoc);
			if (!isStomping)
				direction = { in_rMessage.Direction * in_rMessage.Unk1 };
			else
				direction = { in_rMessage.Direction * in_rMessage.Unk2 };

			StateUtil::DoSpringJump(in_rStateGoc, &in_rMessage.Origin, &direction, 0.05f, 0.0f, flags, false, true, isStomping, 0.0f, nullptr, 0.0f);

			StateUtil::SetDisableTime(in_rStateGoc, 0, in_rMessage.Sender, 0.1f);
			StateUtil::ForcedStopFootPlacement(in_rStateGoc);
			StateUtil::CreateSpringFollowEffect(in_rStateGoc);

			in_rMessage.Unk3 = true;

			return true;
		}

		bool ProcMsgSandHoleDrawIn(CStateGOC& in_rStateGoc, xgame::MsgSandHoleDrawIn& in_rMessage)
		{
			if (!in_rStateGoc.GetStatePlugin<CPluginStateCheckSandHole>())
			{
				in_rStateGoc.AddStatePlugin(5);
				if (auto* pPlugin = in_rStateGoc.GetStatePlugin<CPluginStateCheckSandHole>())
					pPlugin->SetHoleInfo(in_rStateGoc, in_rMessage.Sender, in_rMessage.Unk1, in_rMessage.Unk2);
			}

			return true;
		}

		bool ProcMsgOnRunningSand(CStateGOC& in_rStateGoc, xgame::MsgOnRunningSand& in_rMessage)
		{
			auto* pSweptParam = in_rStateGoc.CreateStateContextParameter<SweptBySandParameter>();
			pSweptParam->Unk2 = in_rMessage.Unk1;
			pSweptParam->Unk3 = in_rMessage.Unk2;
			pSweptParam->Sender = in_rMessage.Sender;
			pSweptParam->Unk4 = true;
			pSweptParam->Unk5 = in_rMessage.Unk3;

			in_rStateGoc.ChangeState(98);
			return true;
		}

		bool ProcMsgSeaMineStream(CStateGOC& in_rStateGoc, xgame::MsgSeaMineStream& in_rMessage)
		{
			auto* pPhysics = in_rStateGoc.GetPhysics();
			auto velocity = pPhysics->GetVelocity();

			pPhysics->SetVelocity({ csl::math::Vector3(velocity - (in_rMessage.Unk1 * velocity.dot(in_rMessage.Unk1))) + in_rMessage.Unk1 * 200.0f });

			in_rStateGoc.ChangeState(101);
			return true;
		}

		bool ProcMsgWaterWorks(CStateGOC& in_rStateGoc, xgame::MsgWaterWorks& in_rMessage)
		{
			auto* pWaterParam = in_rStateGoc.CreateStateContextParameter<WaterFlowParameter>();
			pWaterParam->Unk2 = in_rMessage.Unk1;
			pWaterParam->Unk3 = in_rMessage.Unk2;

			in_rStateGoc.ChangeState(102);
			return true;
		}

		bool ProcMsgPinBallStarter(CStateGOC& in_rStateGoc, xgame::MsgPinBallStarter& in_rMessage)
		{
			in_rStateGoc.CreateStateContextParameter<PinBallParameter>()->IsMode2D = true;

			in_rStateGoc.ChangeState(82);
			return true;
		}

		bool ProcMsgSandDriveStarter(CStateGOC& in_rStateGoc, xgame::MsgSandDriveStarter& in_rMessage)
		{
			in_rStateGoc.ChangeState(119);
			return true;
		}

		bool ProcMsgKekkoBlow(CStateGOC& in_rStateGoc, xgame::MsgKekkoBlow& in_rMessage)
		{
			if (in_rStateGoc.GetCurrentState() == 47 || in_rStateGoc.GetCurrentState() == 105)
				return false;

			in_rStateGoc.GetPhysics()->SetVelocity(*csl::math::Vector3::Zero);
			in_rStateGoc.ChangeState(113);
			return true;
		}

		bool ProcMsgGetSuckedIntoPipe(CStateGOC& in_rStateGoc, xgame::MsgGetSuckedIntoPipe& in_rMessage)
		{
			auto* pPipeParam = in_rStateGoc.CreateStateContextParameter<PipeMoveParameter>();
			pPipeParam->Unk2 = in_rMessage.Unk1;
			pPipeParam->Unk3 = in_rMessage.Unk2;
			pPipeParam->Unk4 = in_rMessage.Unk3;

			in_rStateGoc.ChangeState(115);
			return true;
		}

		bool ProcMsgHitUpdraftCollision(CStateGOC& in_rStateGoc, xgame::MsgHitUpdraftCollision& in_rMessage)
		{
			in_rStateGoc.CreateStateContextParameter<GlideParameter>()->Unk2 = in_rMessage.Unk1;

			in_rStateGoc.ChangeState(118);
			return true;
		}

		bool ProcMsgBakubakuJump(CStateGOC& in_rStateGoc, xgame::MsgBakubakuJump& in_rMessage)
		{
			auto* pPhysics = in_rStateGoc.GetPhysics();
			pPhysics->SetPosition(in_rMessage.Position);
			pPhysics->SetVelocity(in_rMessage.Velocity);

			in_rStateGoc.ChangeState(124);
			return true;
		}

		bool ProcMsgNotifyMidBossDMEvent(CStateGOC& in_rStateGoc, xgame::MsgNotifyMidBossDMEvent& in_rMessage)
		{
			in_rStateGoc.GetPhysics()->SetVelocity(in_rMessage.Unk2);

			in_rStateGoc.ChangeState(127);
			return true;
		}

		bool ProcMsgHoverImpulse(CStateGOC& in_rStateGoc, xgame::MsgHoverImpulse& in_rMessage)
		{
			if (StateUtil::IsDisableTime(in_rStateGoc, 0, in_rMessage.Sender) || StateUtil::IsDisableRCHoverAbility(in_rStateGoc))
				return true;

			csl::ut::Bitset<uint> flags{};
			flags.set(2, true);
			flags.set(12, true);
			flags.set(17, true);

			StateUtil::DoSpringJump(in_rStateGoc, nullptr, &in_rMessage.Direction, in_rMessage.OutOfControl, in_rMessage.SpeedDropoffTime, flags, false, false, false, 0.0f, nullptr, 0.0f);

			StateUtil::SetDisableTime(in_rStateGoc, 0, in_rMessage.Sender, 0.1f);
			StateUtil::ForcedStopFootPlacement(in_rStateGoc);
			in_rMessage.Unk3 = true;

			return true;
		}

		bool ProcMsgDlcZeldaTakeHeart(CStateGOC& in_rStateGoc, xgame::MsgDlcZeldaTakeHeart& in_rMessage)
		{
			StateUtil::RecoveryHeartLife(in_rStateGoc);
			return true;
		}

		bool ProcMsgDlcZeldaTakeHeartContainer(CStateGOC& in_rStateGoc, xgame::MsgDlcZeldaTakeHeartContainer& in_rMessage)
		{
			StateUtil::IncrementMaxHeartLife(in_rStateGoc);
			return true;
		}

		void CheckSpinPhantomStart(CStateGOC& in_rStateGoc, MsgPLCheckPhantomStart& in_rMessage)
		{
			auto* pPhysics = in_rStateGoc.GetPhysics();

			if (!in_rStateGoc.IsOnGround() || !in_rStateGoc.Is2DMode() && StateUtil::GetGravityType(in_rStateGoc) != game::GravityType::eGravityType_OutsideCylinderSpline)
			{
				in_rMessage.Unk1 = 0;
				return;
			}

			csl::math::Vector3 from{ in_rStateGoc.GetPosition() + pPhysics->Unk9.Unk4 * 5.0f };
			csl::math::Vector3 to{ in_rStateGoc.GetPosition() - pPhysics->Unk9.Unk4 * 5.0f };

			game::PhysicsRaycastOutput output{};
			if (!PlayerUtil::RaycastPhantom(output, in_rStateGoc.pPlayer, from, to, 0xC996))
			{
				in_rMessage.Unk1 = 0;
				return;
			}

			if (!PlayerUtil::IsEnablePhantomDig(output.Attribute))
			{
				in_rMessage.Unk1 = 0;
				return;
			}

			in_rMessage.Unk2 = 1;
			if (in_rStateGoc.Is2DMode())
			{
				in_rMessage.Unk2 = 51;
				in_rMessage.Unk3 = { -output.Normal };
			}
			else
			{
				in_rMessage.Unk2 = 52;
				in_rMessage.Unk3 = pPhysics->GetFront();
			}
		}

		void CheckPhantomStart(CStateGOC& in_rStateGoc, MsgPLCheckPhantomStart& in_rMessage)
		{
			switch (in_rMessage.Type)
			{
			case Game::EPhantomType::ePhantom_Drill:
			{
				CheckSpinPhantomStart(in_rStateGoc, in_rMessage);
				break;
			}
			case Game::EPhantomType::ePhantom_Laser:
			{
				in_rMessage.Unk1 = 1;
				in_rMessage.Unk1 = 55;
				break;
			}
			case Game::EPhantomType::ePhantom_Rocket:
			{
				in_rMessage.Unk1 = 1;
				in_rMessage.Unk1 = 91;
				break;
			}
			case Game::EPhantomType::ePhantom_Asteroid:
			{
				if (in_rStateGoc.Is2DMode() || !in_rStateGoc.GetPath(0))
				{
					in_rMessage.Unk1 = 0;
					return;
				}

				in_rMessage.Unk1 = 1;
				in_rMessage.Unk1 = 90;
				break;
			}
			case Game::EPhantomType::ePhantom_Eagle:
			{
				in_rMessage.Unk1 = 1;
				in_rMessage.Unk1 = 92;
				break;
			}
			case Game::EPhantomType::ePhantom_Rhythm:
			{
				if (in_rStateGoc.Is2DMode() || !in_rStateGoc.GetPath(0))
				{
					in_rMessage.Unk1 = 0;
					return;
				}

				in_rMessage.Unk1 = 1;
				in_rMessage.Unk1 = 93;
				break;
			}
			case Game::EPhantomType::ePhantom_Hover:
			{
				in_rMessage.Unk1 = 1;
				in_rMessage.Unk1 = 95;
				break;
			}
			case Game::EPhantomType::ePhantom_Bomb:
			{
				if (!in_rStateGoc.IsOnGround())
				{
					in_rMessage.Unk1 = 0;
					return;
				}

				in_rMessage.Unk1 = 1;
				in_rMessage.Unk1 = 94;
				break;
			}
			case Game::EPhantomType::ePhantom_Quake:
			{
				in_rMessage.Unk1 = 1;
				in_rMessage.Unk1 = 96;
				break;
			}
			default:
				in_rMessage.Unk1 = 0;
				break;
			}
		}
	};
}