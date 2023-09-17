#pragma once

namespace app::Player
{
	inline static const char* VoiceNames[] = {
		"sonicaction_v00", "sonicaction_v01", "sonicaction_v02", "sonicaction_v03", "sonicaction_v04", "sonicaction_v05",
		"sonicaction_v06", "sonicaction_v07", "sonicaction_v08", "sonicaction_v09", "sonicaction_v10", "sonicaction_v11",
		"sonicaction_v12", "sonicaction_v13", "sonicaction_v14", "sonicaction_v15", "sonicaction_v16", "sonicaction_v17",
		"sonicaction_v18", "sonicaction_v19", "sonicaction_v20", "sonicaction_v21", "sonicaction_v22", "sonicaction_v09",
		"sonicaction_v06"
	};

	typedef int VoiceID;
}

namespace app::Player::StateUtil
{
	inline static int PhantomMissionTypes[] = { 15, 11, 16, 21, 26, 29, -1, 31, -1 };

	inline static FUNCTION_PTR(void, __cdecl, ms_fpResetPosition, ASLR(0x008D9C60), CStateGOC&, const csl::math::Vector3&);
	inline static FUNCTION_PTR(void, __cdecl, ms_fpResetPositionAll, ASLR(0x008D85F0), CStateGOC&, const csl::math::Vector3&, const csl::math::Quaternion&);
	inline static FUNCTION_PTR(void, __cdecl, ms_fpResetLocater, ASLR(0x008DF670), CStateGOC&, const csl::math::Matrix34&);
	inline static FUNCTION_PTR(void, __cdecl, ms_fpAbortPhantom, ASLR(0x008D6930), CStateGOC&);
	inline static FUNCTION_PTR(void, __cdecl, ms_fpAddRingNum, ASLR(0x008D7BA0), CStateGOC&, int);
	inline static FUNCTION_PTR(void, __cdecl, ms_fpSetDraw, ASLR(0x008D7BA0), CStateGOC&, bool, bool);
	inline static FUNCTION_PTR(void, __cdecl, ms_fpSendNextStateToNotVisible, ASLR(0x008D9400), CStateGOC&);
	inline static FUNCTION_PTR(void, __cdecl, ms_fpEnable2ndDefCollision, ASLR(0x00861E30), CStateGOC&);
	inline static FUNCTION_PTR(void, __cdecl, ms_fpForcedStopFootPlacement, ASLR(0x008DF740), CStateGOC&);

	static CSnowBall* GetSnowBall(CStateGOC& in_rStateGoc)
	{
		CPlayerVehicle* pVehicle{};

		if (!in_rStateGoc.pPlayer->HaveVehicle() || (pVehicle = in_rStateGoc.pPlayer->GetPlayerVehicle(), pVehicle->VehicleType != 1))
		{
			return { nullptr };
		}

		return (CSnowBall*)pVehicle;
	}

	static void ResetPosition(CStateGOC& rStateGoc, const csl::math::Vector3& rPos)
	{
		ms_fpResetPosition(rStateGoc, rPos);
	}

	static void ResetPosition(CStateGOC& rStateGoc, const csl::math::Vector3& rPos, const csl::math::Quaternion& rRot)
	{
		ms_fpResetPositionAll(rStateGoc, rPos, rRot);
	}

	static void ResetPosition(CPlayer& rPlayer, const csl::math::Vector3& rPos)
	{
		auto* pStateGoc = rPlayer.GetStateGOC();

		if (pStateGoc)
			ResetPosition(*pStateGoc, rPos);
	}

	static void ResetPosition(CPlayer& rPlayer, const csl::math::Vector3& rPos, const csl::math::Quaternion& rRot)
	{
		auto* pStateGoc = rPlayer.GetStateGOC();

		if (pStateGoc)
			ResetPosition(*pStateGoc, rPos, rRot);
	}

	static void ClearAirOnceAction(CStateGOC& in_rStateGoc)
	{
		in_rStateGoc.GetBlackBoard()->SetStatus(1, true);
	}

	static void OnGround(CStateGOC& in_rStateGoc)
	{
		ClearAirOnceAction(in_rStateGoc);
	}

	static void ResetOnGround(CStateGOC& in_rStateGoc)
	{
		in_rStateGoc.GetPhysics()->ResetGroundState();
	}

	static void ForceOnGround(CStateGOC& in_rStateGoc)
	{
		in_rStateGoc.GetPhysics()->SetOnGround(true);
		return OnGround(in_rStateGoc);
	}

	static void SetVelocity(CStateGOC& in_rStateGoc, const csl::math::Vector3& in_rVelocity)
	{
		in_rStateGoc.GetPhysics()->SetVelocity(in_rVelocity);
	}

	static void ResetVelocity(CStateGOC& in_rStateGoc)
	{
		in_rStateGoc.GetPhysics()->SetVelocity(*csl::math::Vector3::Zero);
	}

	static void SetUpDirection(CStateGOC& in_rStateGoc, const csl::math::Vector3& in_rUpDirection)
	{
		in_rStateGoc.GetPhysics()->m_Up = in_rUpDirection;
	}

	static game::GravityType GetGravityType(CStateGOC& in_rStateGoc)
	{
		return in_rStateGoc.GetPhysics()->GetGravityController()->GetType();
	}

	void UpdateGravityForLaunch(CStateGOC& in_rStateGoc, const csl::math::Vector3& in_rOrigin)
	{
		auto* pPhysics = in_rStateGoc.GetPhysics();
		pPhysics->UpdateGravityForced(in_rOrigin);
		pPhysics->m_Unk7.set(6, true);
	}

	static void ResetLocater(CStateGOC& in_rStateGoc, const csl::math::Matrix34& in_rMatrix)
	{
		ms_fpResetLocater(in_rStateGoc, in_rMatrix);
	}

	static void RotateCollision(CStateGOC& in_rStateGoc, const csl::math::Quaternion& in_rRotation, bool in_unk)
	{
		in_rStateGoc.GetCollision()->Collision.SetRotation(in_rRotation, in_unk);
	}

	static bool SetPosition(CStateGOC& in_rStateGoc, const csl::math::Vector3& in_rPosition, bool in_unk)
	{
		if (in_unk)
		{
			csl::math::Vector3 position{};

			auto& collision = in_rStateGoc.GetCollision()->Collision;
			bool result = collision.SweepCapsule(position, in_rStateGoc.GetPosition(), in_rPosition, collision.GetRotation(), collision.CollisionFilter, false, false);

			in_rStateGoc.GetPhysics()->SetPosition(position);
			return !result;
		}
		else
		{
			in_rStateGoc.GetPhysics()->SetPosition(in_rPosition);
			return true;
		}
	}

	static void SetRotation(CStateGOC& in_rStateGoc, const csl::math::Vector3& in_rUnk1, const csl::math::Vector3& in_rGravityUpDir, bool in_unk3, bool in_unk4)
	{
		if (!PlayerUtil::SetDirection(in_rStateGoc.GetPhysics(), in_rUnk1, in_rGravityUpDir) || in_unk3)
			return;

		StateUtil::RotateCollision(in_rStateGoc, in_rStateGoc.GetRotation(), in_unk4);
	}

	static void AddRingNum(CStateGOC& in_rStateGoc, int ringNum)
	{
		ms_fpAddRingNum(in_rStateGoc, ringNum);
	}

	static void SubRingNum(CStateGOC& in_rStateGoc, int in_ringNum)
	{
		in_rStateGoc.GetBlackBoard()->GetRingParameter()->AddNum(-in_ringNum);
	}

	static int GetRingNum(CStateGOC& in_rStateGoc)
	{
		return in_rStateGoc.GetRingNum();
	}

	static void SetRingNum(CStateGOC& in_rStateGoc, int in_ringNum, bool in_unk = true)
	{
		in_rStateGoc.GetBlackBoard()->GetRingParameter()->SetNum(in_ringNum);
	}

	static int LostRing(CStateGOC& in_rStateGoc, int in_count)
	{
		int newCount = csl::math::Clamp(in_rStateGoc.GetRingNum(), 0, in_count);
		SetRingNum(in_rStateGoc, newCount, true);

		return newCount;
	}

	static CParameterPixie* GetPixieParameter(CStateGOC& in_rStateGoc)
	{
		return in_rStateGoc.GetBlackBoard()->GetPixieParameter();
	}

	static Game::EPhantomType GetNowPhantomType(CStateGOC& in_rStateGoc)
	{
		return GetPixieParameter(in_rStateGoc)->PixieNo;
	}

	static float GetPhantomEnergy(CStateGOC& in_rStateGoc)
	{
		return GetPixieParameter(in_rStateGoc)->Energy;
	}

	static bool IsNowAutoRun(CStateGOC& in_rStateGoc)
	{
		return in_rStateGoc.GetBlackBoard()->m_Unk1[3].test(17);
	}

	static bool IsNowStomping(CStateGOC& in_rStateGoc)
	{
		return in_rStateGoc.GetBlackBoard()->m_Unk1[3].test(8);
	}

	static bool IsNowPhantom(CStateGOC& in_rStateGoc)
	{
		return GetPixieParameter(in_rStateGoc)->PixieNo != -1;
	}

	static void AbortPhantom(CStateGOC& in_rStateGoc)
	{
		ms_fpAbortPhantom(in_rStateGoc);
	}

	static Game::EPhantomType GetStockPixieType(CStateGOC& in_rStateGoc)
	{
		return GetPixieParameter(in_rStateGoc)->Type;
	}

	static int GetGroundAttribute(CStateGOC& in_rStateGoc)
	{
		return in_rStateGoc.GetPhysics()->m_Unk9.GetAttribute();
	}

	static bool IsLandOnMovableGround(CStateGOC& in_rStateGoc)
	{
		return (GetGroundAttribute(in_rStateGoc) >> 14) & 1;
	}

	static void SendMission(CStateGOC& in_rStateGoc, xgame::MissionEventID::Type in_type)
	{
		xgame::MsgMissionEvent msg{};
		msg.Type = in_type;

		in_rStateGoc.SendMessageImmToGame(msg);
	}

	static void SendMissionGetRing(CStateGOC& in_rStateGoc, int in_ringCount)
	{
		xgame::MsgMissionEvent msg{};
		msg.Unk1 = in_ringCount;

		in_rStateGoc.SendMessageToGame(msg);

		auto phantomType = GetNowPhantomType(in_rStateGoc);
		if (phantomType < Game::EPhantomType::PHANTOM_MAX)
		{
			int missionType = PhantomMissionTypes[phantomType];
			if (missionType >= 0)
			{
				xgame::MsgMissionEvent phantomMsg{};
				phantomMsg.Type = missionType;
				phantomMsg.Unk1 = in_ringCount;

				in_rStateGoc.SendMessageToGame(msg);
			}
		}
	}

	static void SendDeadMessage(CStateGOC& in_rStateGoc)
	{
		in_rStateGoc.GetToHudPlayerNumber();
		xgame::MsgPLNotifyDead msg{};
		in_rStateGoc.SendMessageToGame(msg);
		StateUtil::SendMission(in_rStateGoc, 52);
	}

	static void SetDraw(CStateGOC& in_rStateGoc, bool in_unk, bool in_unk2)
	{
		ms_fpSetDraw(in_rStateGoc, in_unk, in_unk2);
	}

	static bool IsDead(CStateGOC& in_rStateGoc)
	{
		return in_rStateGoc.GetBlackBoard()->m_Unk1[3].test(0);
	}

	static bool IsDisableTime(CStateGOC& in_rStateGoc, EDisableTimer in_timer)
	{
		return in_rStateGoc.IsTimerDisable(in_timer);
	}

	static bool IsDisableTime(CStateGOC& in_rStateGoc, EDisableTimer in_timer, uint in_unk)
	{
		return in_rStateGoc.IsTimerDisable(in_timer, in_unk);
	}

	static void SetDisableTime(CStateGOC& in_rStateGoc, EDisableTimer in_timer, float in_time)
	{
		return in_rStateGoc.SetDisableTime(in_timer, in_time, 0);
	}

	static void SetDisableTime(CStateGOC& in_rStateGoc, EDisableTimer in_timer, uint in_sender, float in_time)
	{
		return in_rStateGoc.SetDisableTime(in_timer, in_time, in_sender);
	}

	static bool IsDamaged(CStateGOC& in_rStateGoc)
	{
		return StateUtil::IsDisableTime(in_rStateGoc, 3);
	}

	static bool IsBarrier(CStateGOC& in_rStateGoc);

	static bool IsInvincible(CStateGOC& in_rStateGoc)
	{
		auto* pAttackStatus = in_rStateGoc.GetAttackStatus();
		if (!pAttackStatus->Unk5.test(0) && !pAttackStatus->Unk5.test(1))
			return false;

		return true;
	}

	static bool IsInWater(CStateGOC& in_rStateGoc)
	{
		return in_rStateGoc.GetBlackBoard()->m_Unk1[3].test(6);
	}

	static bool IsHeartLife(CStateGOC& in_rStateGoc);

	static bool ReduceHeartLife(CStateGOC& in_rStateGoc);

	static SGroundInfo* GetGroundInfo(CStateGOC& in_rStateGoc)
	{
		return &in_rStateGoc.GetPhysics()->m_Unk9;
	}

	static void SetInputEnable(CStateGOC& in_rStateGoc, bool in_enable)
	{
		auto* pInput = in_rStateGoc.pPlayer->GetComponent<game::GOCCharacterInput>();
		if (pInput)
			pInput->SetEnable(in_enable);
	}

	static void SendNextStateToNotVisible(CStateGOC& in_rStateGoc)
	{
		ms_fpSendNextStateToNotVisible(in_rStateGoc);
	}

	static void EndDamageBlink(CStateGOC& in_rStateGoc)
	{
		in_rStateGoc.GetVisualGoc()->EndBlink();
	}

	static void StartDamageBlink(CStateGOC& in_rStateGoc, float in_time)
	{
		in_rStateGoc.GetVisualGoc()->StartBlink(in_time);
	}

	static bool ReduceBarrier(CStateGOC& in_rStateGoc);

	static void CreateScatterRing(CStateGOC& in_rStateGoc, bool in_unk, int in_count);

	static void ScatterRingForDamage(CStateGOC& in_rStateGoc, bool in_unk)
	{
		if (in_rStateGoc.IsNowSuperSonic())
			return;

		if (!IsBarrier(in_rStateGoc))
		{
			if (ReduceHeartLife(in_rStateGoc))
			{
				int scatterCount = LostRing(in_rStateGoc, 20);
				if (scatterCount > 0)
					CreateScatterRing(in_rStateGoc, in_unk, scatterCount);
			}
		}
		else
		{
			ReduceBarrier(in_rStateGoc);
		}
	}

	static void ScatterRingForDamage(CStateGOC& in_rStateGoc, bool in_unk, int in_count)
	{
		if (in_rStateGoc.IsNowSuperSonic())
			return;

		if (!IsBarrier(in_rStateGoc))
		{
			if (ReduceHeartLife(in_rStateGoc))
			{
				int scatterCount = csl::math::Min(GetRingNum(in_rStateGoc), in_count);
				if (scatterCount > 0)
				{
					SubRingNum(in_rStateGoc, scatterCount);
					CreateScatterRing(in_rStateGoc, in_unk, scatterCount);
				}
			}
		}
		else
		{
			ReduceBarrier(in_rStateGoc);
		}
	}

	static void SetStealth(CStateGOC& in_rStateGoc, bool in_enable)
	{
		in_rStateGoc.GetBlackBoard()->SetStatus(21, in_enable);
		auto* pVisual = in_rStateGoc.GetVisualGoc();
		if (in_enable)
			pVisual->StartStealth();
		else
			pVisual->EndStealth();
	}

	static bool IsBattleMode(CStateGOC& in_rStateGoc)
	{
		return in_rStateGoc.GetBlackBoard()->m_Unk1[3].test(20);
	}

	static fnd::SoundHandle PlaySE(CStateGOC& in_rStateGoc, const char* in_pName)
	{
		return in_rStateGoc.PlaySE(in_pName, false);
	}

	static const char* GetVoiceName(VoiceID in_index)
	{
		return VoiceNames[in_index];
	}

	static fnd::SoundHandle PlayVoice(CStateGOC& in_rStateGoc, const char* in_pName, bool in_unk)
	{
		if (!in_rStateGoc.IsNowSuperSonic() && !StateUtil::IsBattleMode(in_rStateGoc))
			return in_rStateGoc.PlaySE(in_pName, in_unk);
	
		fnd::SoundHandle soundHandle{};
		return soundHandle;
	}

	static fnd::SoundHandle PlayVoice(CStateGOC& in_rStateGoc, VoiceID in_index)
	{
		const char* pName = GetVoiceName(in_index);
		if (pName)
			PlayVoice(in_rStateGoc, pName, false);
	
		fnd::SoundHandle soundHandle{};
		return soundHandle;
	}

	static void SyncSnowBallPosition(CStateGOC& in_rStateGoc)
	{
		auto* pPlayer = in_rStateGoc.pPlayer;
		if (!pPlayer->HaveVehicle())
			return;
	
		auto* pVehicle = pPlayer->GetPlayerVehicle();
		if (pVehicle->VehicleType == 1)
		{
			auto* pSnowball = static_cast<CSnowBall*>(pVehicle);
			auto* pPhysics = in_rStateGoc.GetPhysics();
			
			pSnowball->SetPosition({ pPhysics->m_Position + pPhysics->GetUp() * pSnowball->Radius });
			pSnowball->SetDirection(pPhysics->GetFront(), pPhysics->GetUp());
		}
	}

	static void Enable2ndDefCollision(CStateGOC& in_rStateGoc)
	{
		ms_fpEnable2ndDefCollision(in_rStateGoc);
	}

	static void SetRCLockHoverAbility(CStateGOC& in_rStateGoc, bool in_lockAbility);

	bool IsDisableRCHoverAbility(CStateGOC& in_rStateGoc);

	static void SetDisableChangePhantom(CStateGOC& in_rStateGoc, bool in_disable);

	static void SetDisableTransformSuperSonic(CStateGOC& in_rStateGoc, bool in_disable);
	
	static void SetSuperSonicTransImmediate(CStateGOC& in_rStateGoc, bool in_enable);

	static void PauseSuperSonicReturnTimer(CStateGOC& in_rStateGoc, bool in_pause);

	static void SetDisableReturnToSonic(CStateGOC& in_rStateGoc, bool in_disable);

	static void SetItemDisableWarp(CStateGOC& in_rStateGoc, bool in_disable);

	static void TerminateSpeedUpByItem(CStateGOC& in_rStateGoc);

	static void TerminateInvincibleUpByItem(CStateGOC& in_rStateGoc);

	static void TerminateBarrierUpByItem(CStateGOC& in_rStateGoc);

	static void SetItemDisableBarrierSpeedInvincible(CStateGOC& in_rStateGoc, bool in_unk1, bool in_unk2);

	static void SetDisableItemAndTransformForPauseAct(CStateGOC& in_rStateGoc, bool in_unk1, bool in_unk2)
	{
		StateUtil::SetDisableTransformSuperSonic(in_rStateGoc, in_unk1);
		StateUtil::SetSuperSonicTransImmediate(in_rStateGoc, in_unk1);
		StateUtil::SetDisableChangePhantom(in_rStateGoc, in_unk1);
		StateUtil::SetItemDisableWarp(in_rStateGoc, in_unk1);
		StateUtil::SetItemDisableBarrierSpeedInvincible(in_rStateGoc, in_unk1, in_unk2);
	}

	bool AllRecoveryHeartLife(CStateGOC& in_rStateGoc);

	bool RecoveryHeartLife(CStateGOC& in_rStateGoc);

	void IncrementMaxHeartLife(CStateGOC& in_rStateGoc);

	static bool TestActionFlag(CStateGOC& in_rStateGoc, EActionFlag in_flag)
	{
		return in_rStateGoc.GetBlackBoard()->m_Unk1[1].test(in_flag);
	}

	static void ForcedStopFootPlacement(CStateGOC& in_rStateGoc)
	{
		ms_fpForcedStopFootPlacement(in_rStateGoc);
	}

	static void ChangeToChangePathMode(CStateGOC& in_rStateGoc, float in_unk1, bool in_unk2)
	{
		auto* pBlackboard = in_rStateGoc.GetBlackBoard();
		
		in_rStateGoc.ChangeTo3DMode(in_unk2);
		pBlackboard->m_Unk1[2].set(2, true);
		in_rStateGoc.SetDisableTime(5, 0.05f);
		pBlackboard->m_Unk1[2].set(3, in_unk2);
	}

	void SetTerrainCollisionDisable(CStateGOC& in_rStateGoc, bool in_isDisable);

	void DoSpringJump(CStateGOC& in_rStateGoc, const csl::math::Vector3* in_pOrigin, const csl::math::Vector3* in_pDirection, float in_outOfControl, float in_speedDropoffTime, const csl::ut::Bitset<uint>& in_rFlags, bool in_unk1, bool in_unk2, bool in_unk3, float in_unk4, const csl::math::Vector3* in_pYawDirection, float in_outOfParkour)
	{
		auto* pPhysics = in_rStateGoc.GetPhysics();

		if (in_pOrigin)
		{
			in_rStateGoc.GetPosition();
			StateUtil::SetPosition(in_rStateGoc, *in_pOrigin, false);
			in_rStateGoc.pPlayer->UpdateTransform();
			StateUtil::UpdateGravityForLaunch(in_rStateGoc, *in_pOrigin);
		}

		pPhysics->ResetGroundState();
		
		csl::math::Vector3 direction{ *in_pDirection };
		if (!in_rFlags.test(2))
			direction = { in_rStateGoc.GetVelocity() + direction };
	
		SpringJumpParameter springParam{};

		float speedDropoff = csl::math::Max(in_speedDropoffTime, 0.0f);
		if (in_rFlags.test(0))
			springParam.SpeedDropoffTime = 0.0;
		else
			springParam.SpeedDropoffTime = csl::math::Max(speedDropoff, in_outOfControl);

		springParam.OutOfParkour = in_outOfParkour;
		springParam.Direction = direction;

		springParam.Flags.set(0, in_rFlags.test(1));
		springParam.Flags.set(2, in_unk1);
		springParam.Flags.set(3, in_unk2);
		springParam.Flags.set(4, in_rFlags.test(11));
		springParam.Flags.set(5, in_rFlags.test(12));
		springParam.Flags.set(6, in_unk3);
		springParam.Flags.set(9, in_rFlags.test(16));
		springParam.Flags.set(10, in_rFlags.test(17));
		springParam.Flags.set(11, in_rFlags.test(18));

		if (in_rFlags.test(11))
			in_rStateGoc.SetMoveCylinderTimer(in_unk4);

		csl::math::Vector3 normalizedDir{};
		if (in_pYawDirection && math::Vector3NormalizeIfNotZero(direction, &normalizedDir))
		{
			PlayerUtil::SetDirection(pPhysics, *in_pYawDirection, normalizedDir);
			springParam.Flags.set(7, false);
		}

		in_rStateGoc.AddStateContextParameter(springParam);
		in_rStateGoc.ChangeStateAlways(24);

		if (speedDropoff > 0.0f)
			pPhysics->DisableExternalForce(speedDropoff);
	
		if (pPhysics->ConvertAirVertVector(pPhysics->GetVertVelocity()).x() > in_rStateGoc.GetParameter(21))
			StateUtil::ClearAirOnceAction(in_rStateGoc);
	}
}