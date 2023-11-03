#include "EnemyDekunuts.h"
#pragma once

namespace app
{
	inline void EnemyDekunuts::State::Hide::OnEnter(EnemyDekunuts& in_rObj, int in_unk)
	{
		in_rObj.SetBodyCollisionEnable(false);

		in_rObj.SetAnimation(1);
	}

	inline bool EnemyDekunuts::State::Hide::Step(EnemyDekunuts& in_rObj, float in_deltaTime)
	{
		if (in_rObj.Flags.test(FLAG_IS_READY_TO_ATTACK))
			ChangeState(in_rObj, 1);

		return true;
	}

	inline void EnemyDekunuts::State::Appear::OnEnter(EnemyDekunuts& in_rObj, int in_unk)
	{
		in_rObj.SetBodyCollisionEnable(false);
		ElapsedTime = 0.0f;
		
		in_rObj.SetAnimation(2);

		in_rObj.GetComponent<game::GOCSound>()->Play3D(ms_pAppearSoundName, 0.0f);
	}

	inline bool EnemyDekunuts::State::Appear::Step(EnemyDekunuts& in_rObj, float in_deltaTime)
	{
		ElapsedTime += in_deltaTime;
		in_rObj.RotateTarget(-1.0f, csl::math::Clamp(ElapsedTime * 2.0f, 0.0f, 1.0f));
		
		if (ElapsedTime > 0.5f)
			ChangeState(in_rObj, 3);

		return true;
	}

	inline void EnemyDekunuts::State::Retreat::OnEnter(EnemyDekunuts& in_rObj, int in_unk)
	{
		in_rObj.SetBodyCollisionEnable(false);
		ElapsedTime = 0.0f;

		in_rObj.SetAnimation(3);

		in_rObj.GetComponent<game::GOCSound>()->Play3D(ms_pRetreatSoundName, 0.0f);
	}

	inline bool EnemyDekunuts::State::Retreat::Step(EnemyDekunuts& in_rObj, float in_deltaTime)
	{
		ElapsedTime += in_deltaTime;
		
		if (ElapsedTime > 0.416f)
			ChangeState(in_rObj, 0);

		return true;
	}

	inline void EnemyDekunuts::State::Attack::OnEnter(EnemyDekunuts& in_rObj, int in_unk)
	{
		in_rObj.SetBodyCollisionEnable(true);
		RemainingTime = 0.0f;
	}

	inline bool EnemyDekunuts::State::Attack::Step(EnemyDekunuts& in_rObj, float in_deltaTime)
	{
		if (in_rObj.Flags.test(FLAG_IS_DAMAGE_RECEIVED))
		{
			ChangeState(in_rObj, 4);
			return false;
		}
		else if (in_rObj.Flags.test(FLAG_IS_READY_TO_ATTACK))
		{
			in_rObj.RotateTarget(MATHF_PI / 1.125 * in_deltaTime, -1.0f);

			auto* pEnemyTargetGoc = in_rObj.GetComponent<GOCEnemyTarget>();
			if (pEnemyTargetGoc->IsFindTarget() && !in_rObj.IsCurrentAnimation(5))
			{
				RemainingTime -= in_deltaTime;
				if (RemainingTime < 0.0f)
				{
					in_rObj.SetAnimation(5);
					RemainingTime = 2.0f;
				}
			}

			return true;
		}
		else
		{
			ChangeState(in_rObj, 2);
			return true;
		}

		return true;
	}

	inline void EnemyDekunuts::State::Disappear::OnEnter(EnemyDekunuts& in_rObj, int in_unk)
	{
		in_rObj.SetAnimation(4);
		in_rObj.KillShots(true);

		in_rObj.GetComponent<game::GOCSound>()->Play3D(ms_pDisappearSoundName, 0.0f);
	}

	inline bool EnemyDekunuts::State::Disappear::Step(EnemyDekunuts& in_rObj, float in_deltaTime)
	{
		if (!in_rObj.IsEndAnimation(4))
			return true;

		in_rObj.GetComponent<fnd::GOCVisualContainer>()->Visuals[1]->SetVisible(false);
		in_rObj.GetComponent<GOCEnemyHsm>()->SetEnableUpdate(false);

		enemy::DeadEffectCInfo effectCreateInfo{};
		effectCreateInfo.Owner = &in_rObj;
		effectCreateInfo.SetMsgDamage({ 2, 8, 2, *csl::math::Vector3::Zero, *csl::math::Vector3::Zero });
		effectCreateInfo.SetTransform(in_rObj.Frame.Unk3.Mtx);
		effectCreateInfo.SetZeldaDekunuts();

		in_rObj.CreateDeadEffect(effectCreateInfo);
		in_rObj.ProcMission();
		in_rObj.SetStatusRetire();

		return true;
	}
}