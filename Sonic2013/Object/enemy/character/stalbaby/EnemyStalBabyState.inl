#pragma once
#include "EnemyStalBaby.h"

namespace app
{
	inline void EnemyStalBaby::State::Idle::OnEnter(EnemyStalBaby& in_rObj, int in_unk)
	{
		in_rObj.GetComponent<fnd::GOCVisualModel>()->SetVisible(false);
		in_rObj.GetComponent<game::GOCShadowSimple>()->SetVisible(false);
		in_rObj.GetComponent<game::GOCAnimationScript>()->ChangeAnimation(ms_pAnimationName);

		pEnemyTargetGoc = in_rObj.GetComponent<GOCEnemyTarget>();

		MoveStop(in_rObj);
	}

	inline void EnemyStalBaby::State::Idle::OnLeave(EnemyStalBaby& in_rObj, int in_unk)
	{
		in_rObj.GetComponent<fnd::GOCVisualModel>()->SetVisible(true);
		in_rObj.GetComponent<game::GOCShadowSimple>()->SetVisible(true);
	}

	inline bool EnemyStalBaby::State::Idle::Step(EnemyStalBaby& in_rObj, float in_deltaTime)
	{
		if (pEnemyTargetGoc->IsFindTarget())
		{
			pEnemyTargetGoc->LockTarget();
			ChangeState(in_rObj, 1);
		}

		return false;
	}

	inline void EnemyStalBaby::State::Find::OnEnter(EnemyStalBaby& in_rObj, int in_unk)
	{
		MoveStop(in_rObj);
		
		auto* pEnemyTargetGoc = in_rObj.GetComponent<GOCEnemyTarget>();
		if (pEnemyTargetGoc->IsFindTarget())
		{
			auto* pTransformGoc = in_rObj.GetComponent<fnd::GOCTransform>();
			csl::math::Matrix34 transformMtx{ pTransformGoc->Frame.Unk3.Mtx };
			csl::math::Vector3 upVector{ transformMtx.GetColumn(1) };

			csl::math::Vector3 centerPos{ *pEnemyTargetGoc->GetTargetCenterPosition(&centerPos) };
			csl::math::Vector3 offset{ centerPos - transformMtx.GetTransVector() };

			if (math::Vector3NormalizeIfNotZero(offset, &offset) && fabs(upVector.dot(offset)) < 0.999999f)
			{
				csl::math::Vector3 frontVector = upVector.cross(offset);

				csl::math::Matrix34 rotationMatrix{};
				rotationMatrix.SetColumn(0, frontVector);
				rotationMatrix.SetColumn(1, upVector);
				rotationMatrix.SetColumn(2, { frontVector.cross(upVector) });
				
				csl::math::Quaternion rotation{ rotationMatrix };
				rotation.Normalize();

				pTransformGoc->SetLocalRotation(rotation);
			}
		}

		pAnimationGoc = in_rObj.GetComponent<game::GOCAnimationScript>();
		pAnimationGoc->ChangeAnimation(ms_pAnimationName);
		in_rObj.GetComponent<game::GOCSound>()->Play3D(ms_pSoundName, 0.0f);
		in_rObj.GetComponent<game::GOCEffect>()->CreateEffectLoop(&EffectHandle, ms_pEffectName);
	}

	inline void EnemyStalBaby::State::Find::OnLeave(EnemyStalBaby& in_rObj, int in_unk)
	{
		in_rObj.SetEnableCollision(true, false);
	}

	inline bool EnemyStalBaby::State::Find::Step(EnemyStalBaby& in_rObj, float in_deltaTime)
	{
		ElapsedTime += in_deltaTime;
	
		float offsetY = csl::math::Min(ElapsedTime * 30.0f - 15.0f, 0.0f);
		in_rObj.GetComponent<game::GOCShadowSimple>()->SetLocalOffsetPosition({ 0.0f, offsetY, 0.0f });

		if (offsetY >= 0.0f && pAnimationGoc->IsFinished())
		{
			EffectHandle.Stop(false);
			ChangeState(in_rObj, 2);
			return true;
		}

		return false;
	}

	inline bool EnemyStalBaby::State::Find::ProcessMessage(GameObject& in_rObj, fnd::Message& in_rMessage)
	{
		switch (in_rMessage.GetType())
		{
		case xgame::MsgDlcZeldaNoticeStopEnemy::MessageID:		return ProcMsgDlcZeldaNoticeStopEnemy(in_rObj, static_cast<xgame::MsgDlcZeldaNoticeStopEnemy&>(in_rMessage));
		case xgame::MsgDlcZeldaNoticeActiveEnemy::MessageID:	return ProcMsgDlcZeldaNoticeActiveEnemy(in_rObj, static_cast<xgame::MsgDlcZeldaNoticeActiveEnemy&>(in_rMessage));
		}
		
		return EnemyState<EnemyStalBaby>::ProcessMessage(in_rObj, in_rMessage);
	}

	inline bool EnemyStalBaby::State::Find::ProcMsgDlcZeldaNoticeStopEnemy(GameObject& in_rObj, xgame::MsgDlcZeldaNoticeStopEnemy& in_rMessage)
	{
		EffectHandle.SetVisible(false);
		return true;
	}

	inline bool EnemyStalBaby::State::Find::ProcMsgDlcZeldaNoticeActiveEnemy(GameObject& in_rObj, xgame::MsgDlcZeldaNoticeActiveEnemy& in_rMessage)
	{
		EffectHandle.SetVisible(true);
		return true;
	}

	inline void EnemyStalBaby::State::Chase::OnEnter(EnemyStalBaby& in_rObj, int in_unk)
	{
		pEnemyTargetGoc = in_rObj.GetComponent<GOCEnemyTarget>();
		in_rObj.GetComponent<game::GOCAnimationScript>()->ChangeAnimation(ms_pAnimationName);
	}

	inline bool EnemyStalBaby::State::Chase::Step(EnemyStalBaby& in_rObj, float in_deltaTime)
	{
		csl::math::Vector3 centerPos{};
		
		if (in_rObj.Flags.test(0))
		{
			in_rObj.Flags.reset(0);
			ChangeState(in_rObj, 6);
			return false;
		}
		else if (pEnemyTargetGoc->IsFindTarget() && pEnemyTargetGoc->GetTargetCenterPosition(&centerPos) && IsInRangeAttack(in_rObj, centerPos))
		{
			ChangeState(in_rObj, 3);
			return true;
		}
		else
		{
			csl::math::Vector3 turnDirection{ in_rObj.GetTurnDirection(centerPos, in_deltaTime) };
			if (pEnemyTargetGoc && pEnemyTargetGoc->IsFindTarget() && (pEnemyTargetGoc->GetTargetCenterPosition(&centerPos), turnDirection.squaredNorm() > 0.000001f))
			{
				in_rObj.GetComponent<game::GOCMovementComplex>()->GetContextParam()->Velocity = { turnDirection * in_rObj.GetMoveSpeed() };
				return false;
			}
			else
			{
				ChangeState(in_rObj, 6);
				return true;
			}
		}

		return false;
	}

	inline void EnemyStalBaby::State::Attack::OnEnter(EnemyStalBaby& in_rObj, int in_unk)
	{
		pAnimationGoc = in_rObj.GetComponent<game::GOCAnimationScript>();
		pAnimationGoc->ChangeAnimation(ms_pAnimationName);
		MoveStop(in_rObj);
	}

	inline bool EnemyStalBaby::State::Attack::Step(EnemyStalBaby& in_rObj, float in_deltaTime)
	{
		if (!pAnimationGoc->IsFinished())
			return false;
		
		if (in_rObj.Flags.test(0))
		{
			in_rObj.Flags.reset(0);
			ChangeState(in_rObj, 6);
		}
		else
		{
			ChangeState(in_rObj, 4);
		}

		return false;
	}

	inline void EnemyStalBaby::State::Gap::OnEnter(EnemyStalBaby& in_rObj, int in_unk)
	{
		pEnemyTargetGoc = in_rObj.GetComponent<GOCEnemyTarget>();
		LifeSpan = 2.0f;

		in_rObj.GetComponent<game::GOCAnimationScript>()->ChangeAnimation(ms_pAnimationName);
		MoveStop(in_rObj);
	}

	inline bool EnemyStalBaby::State::Gap::Step(EnemyStalBaby& in_rObj, float in_deltaTime)
	{
		LifeSpan -= in_deltaTime;

		if (LifeSpan > 0.0f)
			return false;

		csl::math::Vector3 centerPos{};

		if (in_rObj.Flags.test(0))
		{
			in_rObj.Flags.reset(0);
			ChangeState(in_rObj, 6);
		}
		else if (pEnemyTargetGoc->IsFindTarget() && (pEnemyTargetGoc->GetTargetCenterPosition(&centerPos), IsInRangeAttack(in_rObj, centerPos)))
		{
			ChangeState(in_rObj, 3);
		}
		else
		{
			ChangeState(in_rObj, 2);
		}

		return false;
	}

	inline void EnemyStalBaby::State::Stagger::OnEnter(EnemyStalBaby& in_rObj, int in_unk)
	{
		pAnimationGoc = in_rObj.GetComponent<game::GOCAnimationScript>();
		pAnimationGoc->ChangeAnimation(ms_pAnimationName);

		LifeSpan = 4.0f;
		AnimationLoopFinished = false;

		MoveStop(in_rObj);
	}

	inline bool EnemyStalBaby::State::Stagger::Step(EnemyStalBaby& in_rObj, float in_deltaTime)
	{
		LifeSpan -= in_deltaTime;
		if (LifeSpan > 0.0f)
			return false;

		if (!AnimationLoopFinished)
		{
			pAnimationGoc->ExitLoop();
			AnimationLoopFinished = true;

			return false;
		}

		if (!pAnimationGoc->IsFinished())
			return false;

		if (in_rObj.Flags.test(0))
		{
			in_rObj.Flags.reset(0);
			ChangeState(in_rObj, 6);
			
			return false;
		}

		if (in_rObj.GetComponent<GOCEnemyTarget>()->IsFindTarget())
		{
			ChangeState(in_rObj, 2);
		
			return false;
		}

		ChangeState(in_rObj, 0);

		return false;
	}

	inline void EnemyStalBaby::State::Hide::OnEnter(EnemyStalBaby& in_rObj, int in_unk)
	{
		ElapsedTime = 0.0f;
		
		in_rObj.GetComponent<game::GOCAnimationScript>()->ChangeAnimation(ms_pAnimationName);

		in_rObj.SetEnableCollision(false, false);

		in_rObj.GetComponent<game::GOCEffect>()->CreateEffectLoop(&EffectHandle, ms_pEffectName);

		MoveStop(in_rObj);
	}

	inline bool EnemyStalBaby::State::Hide::Step(EnemyStalBaby& in_rObj, float in_deltaTime)
	{
		ElapsedTime += in_deltaTime;

		float offsetY = -(ElapsedTime * 30.0f);
		csl::math::Vector3 offset{ 0.0f, offsetY, 0.0f };
		
		in_rObj.GetComponent<fnd::GOCVisualModel>()->SetLocalTranslation(offset);
		in_rObj.GetComponent<game::GOCShadowSimple>()->SetLocalOffsetPosition(offset);

		if (offsetY <= -15.0f)
		{
			EffectHandle.Stop(false);
			in_rObj.OnDead();
		}

		return false;
	}

	inline bool EnemyStalBaby::State::Hide::ProcessMessage(GameObject& in_rObj, fnd::Message& in_rMessage)
	{
		switch (in_rMessage.GetType())
		{
		case xgame::MsgDlcZeldaNoticeStopEnemy::MessageID:		return ProcMsgDlcZeldaNoticeStopEnemy(in_rObj, static_cast<xgame::MsgDlcZeldaNoticeStopEnemy&>(in_rMessage));
		case xgame::MsgDlcZeldaNoticeActiveEnemy::MessageID:	return ProcMsgDlcZeldaNoticeActiveEnemy(in_rObj, static_cast<xgame::MsgDlcZeldaNoticeActiveEnemy&>(in_rMessage));
		}

		return EnemyState<EnemyStalBaby>::ProcessMessage(in_rObj, in_rMessage);
	}

	inline bool EnemyStalBaby::State::Hide::ProcMsgDlcZeldaNoticeStopEnemy(GameObject& in_rObj, xgame::MsgDlcZeldaNoticeStopEnemy& in_rMessage)
	{
		EffectHandle.SetVisible(false);
		return true;
	}

	inline bool EnemyStalBaby::State::Hide::ProcMsgDlcZeldaNoticeActiveEnemy(GameObject& in_rObj, xgame::MsgDlcZeldaNoticeActiveEnemy& in_rMessage)
	{
		EffectHandle.SetVisible(true);
		return true;
	}

	inline void EnemyStalBaby::State::Dead::OnEnter(EnemyStalBaby& in_rObj, int in_unk)
	{
		pAnimationGoc = in_rObj.GetComponent<game::GOCAnimationScript>();
		ElapsedTime = 0.0f;
		IsDeadNoHead = in_rObj.Flags.test(1);
		
		pAnimationGoc->ChangeAnimation(IsDeadNoHead ? ms_pDeadNoHeadAnimationName : ms_pDeadAnimationName);
		
		in_rObj.GetComponent<game::GOCEffect>()->CreateEffect(ms_pEffectName);

		in_rObj.SetEnableCollision(false, false);

		MoveStop(in_rObj);
	}

	inline bool EnemyStalBaby::State::Dead::Step(EnemyStalBaby& in_rObj, float in_deltaTime)
	{
		if (!IsDeadNoHead)
		{
			if (pAnimationGoc->IsFinished())
				in_rObj.OnDead();
		
			return false;
		}

		math::Transform transform{};
		if (!in_rObj.GetComponent<fnd::GOCVisualModel>()->GetNodeTransform(0, ms_pHeadNodeName, &transform))
			return false;

		auto* pInfo = ObjUtil::GetObjectInfo<EnemyStalBabyInfo>(*in_rObj.GetDocument());

		EnemyBlowOffObjectCInfo createInfo{};
		createInfo.Model = pInfo->HeadModel;
		createInfo.TrsMatrix = transform.GetTransformMatrix();
		createInfo.Unk6 = in_rObj.KickPosition;
		createInfo.CollisionRadius = 4.0f;
		createInfo.PlayerNo = 0;
		createInfo.Size = 5;
		in_rObj.CreateEnemyBlowOffObject(createInfo);

		IsDeadNoHead = false;

		return false;
	}

	inline bool EnemyStalBaby::State::IsInRangeAttack(EnemyStalBaby& in_rObj, const csl::math::Vector3& in_rTargetPosition)
	{
		auto* pTransformGoc = in_rObj.GetComponent<fnd::GOCTransform>();
		csl::math::Matrix34 transformMtx{ pTransformGoc->Frame.Unk3.Mtx };
		csl::math::Vector3 position{ transformMtx.GetTransVector() };

		csl::math::Vector3 offset{ in_rTargetPosition - position };
		if (offset.squaredNorm() >= in_rObj.MinimumTargetDistance)
			return false;

		math::Vector3NormalizeZero(offset, &offset);

		if (!ms_IsInRangeValue1Initialized)
		{
			ms_IsInRangeValue1Initialized = true;
			ms_IsInRangeValue1 = MATHF_PI / 36.0f;
		}

		if (!ms_IsInRangeValue2Initialized)
		{
			ms_IsInRangeValue2Initialized = true;
			ms_IsInRangeValue2 = MATHF_PI / 4.5f;
		}

		if (transformMtx.GetColumn(0).dot(offset) <= 0.0f)
		{
			if (cosf(ms_IsInRangeValue2) > transformMtx.GetColumn(2).dot(offset))
				return false;
		}
		else
		{
			if (cosf(ms_IsInRangeValue1) > transformMtx.GetColumn(2).dot(offset))
				return false;
		}

		return true;
	}

	inline void EnemyStalBaby::State::MoveStop(EnemyStalBaby& in_rObj)
	{
		if (auto* pMovementGoc = in_rObj.GetComponent<game::GOCMovementComplex>())
			pMovementGoc->GetContextParam()->Velocity = *csl::math::Vector3::Zero;
	}
}