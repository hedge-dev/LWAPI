#include "StateUtil.h"
#pragma once

namespace app::Player::StateUtil
{
	inline bool ReduceBarrier(CStateGOC& in_rStateGoc)
	{
		auto* pPlugin = in_rStateGoc.GetStatePlugin<PluginStateBarrier>();
		if (!pPlugin)
			return true;

		pPlugin->ReduceBarrier(in_rStateGoc);
	}

	inline void CreateScatterRing(CStateGOC& in_rStateGoc, bool in_unk, int in_count)
	{
		SDroppedRingInfo droppedRingInfo{};
		droppedRingInfo.Position = { in_rStateGoc.GetPosition() + in_rStateGoc.GetUpDirection() * 0.5f * 10.0f };
		droppedRingInfo.RingCount = in_count;
		
		if (in_rStateGoc.IsControlMode2D() && in_rStateGoc.GetPath(0))
			droppedRingInfo.Is2D = true;
	
		droppedRingInfo.DroppedByPlayer = true;
		
		if (in_unk)
		{
			droppedRingInfo.Unk6 = 2.0f;
			droppedRingInfo.LifeSpan = 0.25f;
		}

		if (in_rStateGoc.GetBlackBoard()->m_Unk1[3].test(24))
			droppedRingInfo.Unk5 = 1;
	
		dropped_ring::Create(*in_rStateGoc.GetDocument(), droppedRingInfo);
	}

	inline bool IsBarrier(CStateGOC& in_rStateGoc)
	{
		auto* pPlugin = in_rStateGoc.GetStatePlugin<PluginStateBarrier>();
		if (!pPlugin)
			return false;
		
		return !pPlugin->IsPause();
	}

	inline bool IsHeartLife(CStateGOC& in_rStateGoc)
	{
		auto* pPlugin = in_rStateGoc.GetStatePlugin<PluginStateHeartLife>();
		if (!pPlugin)
			return false;

		return pPlugin->GetNumHearts() > 1;
	}

	inline bool ReduceHeartLife(CStateGOC& in_rStateGoc)
	{
		auto* pPlugin = in_rStateGoc.GetStatePlugin<PluginStateHeartLife>();
		if (!pPlugin || StateUtil::IsNowPhantom(in_rStateGoc) && pPlugin->GetNumHearts() <= 1)
			return true;

		return pPlugin->Damaged();
	}

	inline void SetRCLockHoverAbility(CStateGOC& in_rStateGoc, bool in_lockAbility)
	{
		auto* pItemCheckerPlugin = in_rStateGoc.GetStatePlugin<PluginStateCheckEnableItem>();
		if (!pItemCheckerPlugin)
			return;

		if (in_lockAbility)
		{
			if (!pItemCheckerPlugin->IsItemDisable(7))
			{
				xgame::MsgRcLockAbility msg{};
				msg.Type = 2;

				in_rStateGoc.pPlayer->SendMessageImmToRC(msg);
			}

			pItemCheckerPlugin->SetItemDisable(7, true);
		}
		else
		{
			bool isItemDisabled = pItemCheckerPlugin->IsItemDisable(7);
			pItemCheckerPlugin->SetItemDisable(7, false);
			if (!isItemDisabled)
				return;
		
			if (pItemCheckerPlugin->IsItemDisable(7))
				return;

			xgame::MsgRcUnlockAbility msg{};
			msg.Type = 2;

			in_rStateGoc.pPlayer->SendMessageImmToRC(msg);
		}
	}

	inline bool IsDisableRCHoverAbility(CStateGOC& in_rStateGoc, bool in_lockAbility)
	{
		auto* pItemCheckerPlugin = in_rStateGoc.GetStatePlugin<PluginStateCheckEnableItem>();
		if (!pItemCheckerPlugin)
			return true;

		return pItemCheckerPlugin->IsItemDisable(7);
	}

	inline void SetDisableChangePhantom(CStateGOC& in_rStateGoc, bool in_disable)
	{
		auto* pPlugin = in_rStateGoc.GetStatePlugin<CPluginStateCheckChangePhantom>();
		if (!pPlugin)
			return;

		if (in_disable)
		{
			pPlugin->Unk3++;
		}
		else if (pPlugin->Unk3)
		{
			pPlugin->Unk3--;
		}
	}

	inline void SetDisableTransformSuperSonic(CStateGOC& in_rStateGoc, bool in_disable)
	{
		auto* pPlugin = in_rStateGoc.GetStatePlugin<PluginStateCheckSuperSonic>();
		if (!pPlugin)
			return;
	
		if (in_disable)
			pPlugin->AddDisableFlag();
		else
			pPlugin->DecDisableFlag();
	}

	inline void SetSuperSonicTransImmediate(CStateGOC& in_rStateGoc, bool in_enable)
	{
		auto* pPlugin = in_rStateGoc.GetStatePlugin<PluginStateCheckSuperSonic>();
		if (!pPlugin)
			return;

		pPlugin->SetTransImmediate(in_enable);
	}

	inline void PauseSuperSonicReturnTimer(CStateGOC& in_rStateGoc, bool in_pause)
	{
		auto* pPlugin = in_rStateGoc.GetStatePlugin<PluginStateCheckSuperSonic>();
		if (!pPlugin)
			return;

		pPlugin->PauseTimer(in_rStateGoc, in_pause);
	}

	inline void SetDisableReturnToSonic(CStateGOC& in_rStateGoc, bool in_disable)
	{
		auto* pPlugin = in_rStateGoc.GetStatePlugin<PluginStateCheckSuperSonic>();
		if (!pPlugin)
			return;

		pPlugin->SetDisableReturn(in_disable);
	}

	inline void SetItemDisableWarp(CStateGOC& in_rStateGoc, bool in_disable)
	{
		auto* pPlugin = in_rStateGoc.GetStatePlugin<PluginStateCheckEnableItem>();
		if (!pPlugin)
			return;

		pPlugin->SetItemDisable(4, in_disable);
	}

	inline void TerminateSpeedUpByItem(CStateGOC& in_rStateGoc)
	{
		auto* pPlugin = in_rStateGoc.GetStatePlugin<PluginStateSpeedUp>();
		if (!pPlugin)
			return;

		pPlugin->Terminate(in_rStateGoc);
	}

	inline void TerminateInvincibleUpByItem(CStateGOC& in_rStateGoc)
	{
		bool isInvincible = StateUtil::IsInvincible(in_rStateGoc);
		in_rStateGoc.GetAttackStatus()->SetInvincible(false, true);

		auto* pPlugin = in_rStateGoc.GetStatePlugin<PluginStateInvincible>();
		if (pPlugin)
			pPlugin->Terminate(in_rStateGoc);

		if (!isInvincible)
			return;

		if (StateUtil::IsInvincible(in_rStateGoc))
			return;
		
		StateUtil::Enable2ndDefCollision(in_rStateGoc);
	}

	inline void TerminateBarrierUpByItem(CStateGOC& in_rStateGoc)
	{
		auto* pPlugin = in_rStateGoc.GetStatePlugin<PluginStateBarrier>();
		if (!pPlugin)
			return;

		pPlugin->Terminate(in_rStateGoc);
	}

	inline void SetItemDisableBarrierSpeedInvincible(CStateGOC& in_rStateGoc, bool in_unk1, bool in_unk2)
	{
		auto* pPlugin = in_rStateGoc.GetStatePlugin<PluginStateCheckEnableItem>();
		if (!pPlugin)
			return;

		pPlugin->SetItemDisable(0, in_unk1);
		pPlugin->SetItemDisable(1, in_unk1);
		pPlugin->SetItemDisable(2, in_unk1);

		if (in_unk1 && !in_unk2)
		{
			StateUtil::TerminateSpeedUpByItem(in_rStateGoc);
			StateUtil::TerminateInvincibleUpByItem(in_rStateGoc);
			StateUtil::TerminateBarrierUpByItem(in_rStateGoc);
		}
	}

	inline bool AllRecoveryHeartLife(CStateGOC& in_rStateGoc)
	{
		auto* pPlugin = in_rStateGoc.GetStatePlugin<PluginStateHeartLife>();
		if (!pPlugin)
			return true;

		return pPlugin->AllRecovery();
	}

	inline bool RecoveryHeartLife(CStateGOC& in_rStateGoc)
	{
		auto* pPlugin = in_rStateGoc.GetStatePlugin<PluginStateHeartLife>();
		if (!pPlugin)
			return true;

		return pPlugin->Recovery();
	}

	inline void IncrementMaxHeartLife(CStateGOC& in_rStateGoc)
	{
		auto* pPlugin = in_rStateGoc.GetStatePlugin<PluginStateHeartLife>();
		if (!pPlugin)
			return;

		pPlugin->IncrementMaxHearts();
	}

	inline void SetTerrainCollisionDisable(CStateGOC& in_rStateGoc, bool in_isDisable)
	{
		in_rStateGoc.GetBlackBoard()->m_Unk1[2].set(0, in_isDisable);
	}
}