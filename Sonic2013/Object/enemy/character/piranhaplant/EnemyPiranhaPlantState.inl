#include "EnemyPiranhaPlant.h"
#pragma once

namespace app
{
	inline void EnemyPiranhaPlant::State::UpdateHeadPosture(EnemyPiranhaPlant& in_rObj, bool in_changeAnimation)
	{
		if (in_rObj.HeadRotation >= 0.0f)
		{
			if (in_rObj.Flags.test(1))
			{
				in_rObj.Flags.flip(1);
				if (in_changeAnimation)
				{
					auto* pAnimationScript = in_rObj.GetComponent<game::GOCAnimationScript>();
					if (in_rObj.Flags.test(0))
						pAnimationScript->ChangeAnimation("ATTACK_R");
					else
						pAnimationScript->ChangeAnimation("ATTACK_L");
				}
			}

			in_rObj.GetCenterPositionFrame()->SetLocalRotation({ });
		}
		else
		{
			if (!in_rObj.Flags.test(1))
			{
				in_rObj.Flags.flip(1);
				if (in_changeAnimation)
				{
					auto* pAnimationScript = in_rObj.GetComponent<game::GOCAnimationScript>();
					if (in_rObj.Flags.test(0))
						pAnimationScript->ChangeAnimation("ATTACK_L");
					else
						pAnimationScript->ChangeAnimation("ATTACK_R");
				}
			}

			in_rObj.GetCenterPositionFrame()->SetLocalRotation({ Eigen::AngleAxisf(MATHF_PI, csl::math::Vector3::UnitY()) });
		}
	}

	inline void EnemyPiranhaPlant::State::Idle::OnEnter(EnemyPiranhaPlant& in_rObj, int in_unk)
	{
		pEnemyTargetGoc = in_rObj.GetComponent<GOCEnemyTarget>();
		in_rObj.SetEnableDamageCollision(false);
		in_rObj.SetScale(0.4f);

		auto* pAnimationScript = in_rObj.GetComponent<game::GOCAnimationScript>();
		if (in_rObj.Flags.test(0))
			pAnimationScript->ChangeAnimation("IDLE_R");
		else
			pAnimationScript->ChangeAnimation("IDLE_L");
	}

	inline bool EnemyPiranhaPlant::State::Idle::Step(EnemyPiranhaPlant& in_rObj, float in_deltaTime)
	{
		float angle = MATHF_PI * 70.0f / 180.0f;

		in_rObj.HeadRotation = csl::math::Lerp(in_rObj.HeadRotation, csl::math::Select(in_rObj.HeadRotation, angle, csl::math::Nabs(angle)), in_deltaTime * 5.0f);
		UpdateHeadPosture(in_rObj, false);

		if (pEnemyTargetGoc && pEnemyTargetGoc->IsFindTarget())
			ChangeState(in_rObj, 1);
		
		return true;
	}

	inline bool EnemyPiranhaPlant::State::Idle::ProcessMessage(GameObject& in_rObj, fnd::Message& in_rMessage)
	{
		switch (in_rMessage.GetType())
		{
		case xgame::MsgDamage::MessageID:		return ProcMsgDamage(static_cast<EnemyPiranhaPlant&>(in_rObj), static_cast<xgame::MsgDamage&>(in_rMessage));
		default:								return EnemyState<EnemyPiranhaPlant>::ProcessMessage(in_rObj, in_rMessage);
		}
	}

	inline bool EnemyPiranhaPlant::State::Idle::ProcMsgDamage(EnemyPiranhaPlant& in_rObj, xgame::MsgDamage& in_rMessage)
	{
		in_rObj.PlayerNo = in_rMessage.PlayerNo;
		in_rMessage.SetReply(in_rObj.GetCenterPositionFrame()->Unk3.GetTranslation(), true);
		ChangeState(in_rObj, 4);

		return true;
	}

	inline void EnemyPiranhaPlant::State::ShiftAttack::OnEnter(EnemyPiranhaPlant& in_rObj, int in_unk)
	{
		in_rObj.SetEnableDamageCollision(false);
		ElapsedTime = 0.0f;
	}

	inline bool EnemyPiranhaPlant::State::ShiftAttack::Step(EnemyPiranhaPlant& in_rObj, float in_deltaTime)
	{
		UpdateHeadPosture(in_rObj, false);
		
		ElapsedTime += in_deltaTime;
		if (ElapsedTime < 0.1f)
			in_rObj.SetScale(0.6f * sinf(MATHF_PI / 2.0f * ElapsedTime / 0.1f) + 0.4f);
		else
			ChangeState(in_rObj, 2);

		return true;
	}

	inline bool EnemyPiranhaPlant::State::ShiftAttack::ProcessMessage(GameObject& in_rObj, fnd::Message& in_rMessage)
	{
		switch (in_rMessage.GetType())
		{
		case xgame::MsgDamage::MessageID:		return ProcMsgDamage(static_cast<EnemyPiranhaPlant&>(in_rObj), static_cast<xgame::MsgDamage&>(in_rMessage));
		default:								return EnemyState<EnemyPiranhaPlant>::ProcessMessage(in_rObj, in_rMessage);
		}
	}

	inline bool EnemyPiranhaPlant::State::ShiftAttack::ProcMsgDamage(EnemyPiranhaPlant& in_rObj, xgame::MsgDamage& in_rMessage)
	{
		in_rObj.PlayerNo = in_rMessage.PlayerNo;
		in_rMessage.SetReply(in_rObj.GetCenterPositionFrame()->Unk3.GetTranslation(), true);
		ChangeState(in_rObj, 4);

		return true;
	}

	inline void EnemyPiranhaPlant::State::Attack::OnEnter(EnemyPiranhaPlant& in_rObj, int in_unk)
	{
		pEnemyTargetGoc = in_rObj.GetComponent<GOCEnemyTarget>();

		in_rObj.SetEnableDamageCollision(true);
		in_rObj.SetScale(1.0f);

		auto* pAnimationScript = in_rObj.GetComponent<game::GOCAnimationScript>();
		if (in_rObj.Flags.test(0))
			pAnimationScript->ChangeAnimation("ATTACK_R");
		else
			pAnimationScript->ChangeAnimation("ATTACK_L");
	}

	inline bool EnemyPiranhaPlant::State::Attack::Step(EnemyPiranhaPlant& in_rObj, float in_deltaTime)
	{
		if (!pEnemyTargetGoc)
			return true;
	
		if (!pEnemyTargetGoc->IsFindTarget())
		{
			ChangeState(in_rObj, 3);
			return true;
		}

		csl::math::Vector3 targetCenter{};
		targetCenter = *pEnemyTargetGoc->GetTargetCenterPosition(&targetCenter);

		auto* pTransform = in_rObj.GetComponent<fnd::GOCTransform>();
		
		auto up = pTransform->Frame.Unk3.Mtx.GetColumn(1);
		auto front = pTransform->Frame.Unk3.Mtx.GetColumn(2);

		auto position = in_rObj.GetCenterPositionFrame()->Unk3.GetTranslation();
		csl::math::Vector3 offset{ targetCenter - position };
		math::Vector3NormalizeZero(offset, &offset);

		float angle = csl::math::Min(acosf(csl::math::Clamp(up.dot(offset), -1.0f, 1.0f)), MATHF_PI * 70.0f / 180.0f);
		angle = csl::math::Select(front.dot(offset), fabs(angle), csl::math::Nabs(angle));

		in_rObj.HeadRotation = csl::math::Lerp(in_rObj.HeadRotation, angle, in_deltaTime * 5.0f);
		UpdateHeadPosture(in_rObj, true);

		return true;
	}

	inline bool EnemyPiranhaPlant::State::Attack::ProcessMessage(GameObject& in_rObj, fnd::Message& in_rMessage)
	{
		switch (in_rMessage.GetType())
		{
		case xgame::MsgDamage::MessageID:		return ProcMsgDamage(static_cast<EnemyPiranhaPlant&>(in_rObj), static_cast<xgame::MsgDamage&>(in_rMessage));
		default:								return EnemyState<EnemyPiranhaPlant>::ProcessMessage(in_rObj, in_rMessage);
		}
	}

	inline bool EnemyPiranhaPlant::State::Attack::ProcMsgDamage(EnemyPiranhaPlant& in_rObj, xgame::MsgDamage& in_rMessage)
	{
		in_rObj.PlayerNo = in_rMessage.PlayerNo;
		in_rMessage.SetReply(in_rObj.GetCenterPositionFrame()->Unk3.GetTranslation(), true);
		ChangeState(in_rObj, 4);

		return true;
	}

	inline void EnemyPiranhaPlant::State::ShiftIdle::OnEnter(EnemyPiranhaPlant& in_rObj, int in_unk)
	{
		in_rObj.SetEnableDamageCollision(true);
		ElapsedTime = 0.0f;

		auto* pAnimationScript = in_rObj.GetComponent<game::GOCAnimationScript>();
		if (in_rObj.Flags.test(0))
			pAnimationScript->ChangeAnimation("IDLE_R");
		else
			pAnimationScript->ChangeAnimation("IDLE_L");
	}

	inline bool EnemyPiranhaPlant::State::ShiftIdle::Step(EnemyPiranhaPlant& in_rObj, float in_deltaTime)
	{
		float angle = MATHF_PI * 70.0f / 180.0f;

		in_rObj.HeadRotation = csl::math::Lerp(in_rObj.HeadRotation, csl::math::Select(in_rObj.HeadRotation, angle, csl::math::Nabs(angle)), in_deltaTime * 5.0f);
		UpdateHeadPosture(in_rObj, false);
		
		ElapsedTime += in_deltaTime;
		if (ElapsedTime < 0.1f)
			in_rObj.SetScale(-(0.6f * sinf(MATHF_PI / 2.0f * ElapsedTime / 0.1f) - 1.0f));
		else
			ChangeState(in_rObj, 0);

		return true;
	}

	inline bool EnemyPiranhaPlant::State::ShiftIdle::ProcessMessage(GameObject& in_rObj, fnd::Message& in_rMessage)
	{
		switch (in_rMessage.GetType())
		{
		case xgame::MsgDamage::MessageID:		return ProcMsgDamage(static_cast<EnemyPiranhaPlant&>(in_rObj), static_cast<xgame::MsgDamage&>(in_rMessage));
		default:								return EnemyState<EnemyPiranhaPlant>::ProcessMessage(in_rObj, in_rMessage);
		}
	}

	inline bool EnemyPiranhaPlant::State::ShiftIdle::ProcMsgDamage(EnemyPiranhaPlant& in_rObj, xgame::MsgDamage& in_rMessage)
	{
		in_rObj.PlayerNo = in_rMessage.PlayerNo;
		in_rMessage.SetReply(in_rObj.GetCenterPositionFrame()->Unk3.GetTranslation(), true);
		ChangeState(in_rObj, 4);

		return true;
	}

	inline void EnemyPiranhaPlant::State::Dead::ChangeSubState(SubState in_subState)
	{
		State = in_subState;
		ElapsedTime = 0.0f;
	}

	inline void EnemyPiranhaPlant::State::Dead::OnEnter(EnemyPiranhaPlant& in_rObj, int in_unk)
	{
		HeadRotation = fabs(in_rObj.HeadRotation);
		Scale = in_rObj.Scale;

		in_rObj.SetEnableCollision(false);

		ChangeSubState(SubState::eSubState_Freeze);

		auto* pAnimationScript = in_rObj.GetComponent<game::GOCAnimationScript>();
		if (in_rObj.Flags.test(0))
			pAnimationScript->ChangeAnimation("DAMAGE_R");
		else
			pAnimationScript->ChangeAnimation("DAMAGE_L");

		in_rObj.Flags.set(2);
	}

	inline bool EnemyPiranhaPlant::State::Dead::Step(EnemyPiranhaPlant& in_rObj, float in_deltaTime)
	{
		ElapsedTime += in_deltaTime;
		
		switch ((SubState)State)
		{
		case SubState::eSubState_Freeze:
		{
			float angle = sinf(csl::math::Clamp(ElapsedTime / 0.2f, 0.0f, 1.0f) * (MATHF_PI / 2.0f));

			in_rObj.HeadRotation = (-(MATHF_PI / 9.0f) - HeadRotation) * csl::math::Clamp(angle, 0.0f, 1.0f) + HeadRotation;
			if (angle >= 1.0f)
				ChangeSubState(SubState::eSubState_Hit);

			break;
		}
		case SubState::eSubState_Hit:
		{
			if (ElapsedTime < 0.4f)
				break;

			if (auto* pVisualModel = in_rObj.GetComponent<fnd::GOCVisualModel>())
				pVisualModel->GetTexSrtControl()->SetSpeed(1.0f);
			
			if (auto* pSound = in_rObj.GetComponent<game::GOCSound>())
				pSound->Play3D(ms_pSoundName, 0.0f);

			ChangeSubState(SubState::eSubState_Shrink);

			break;
		}
		case SubState::eSubState_Shrink:
		{
			float modifier = csl::math::Clamp(ElapsedTime / 0.6f, 0.0f, 1.0f);

			in_rObj.SetScale((0.2f - Scale) * modifier + Scale);
			if (modifier >= 1.0f)
				ChangeSubState(eSubState_Dead);

			break;
		}
		case SubState::eSubState_Dead:
		{
			auto trsMatrix = in_rObj.GetCenterPositionFrame()->Unk3.Mtx;
			auto position = trsMatrix.GetTransVector();
			ObjUtil::AddScore(in_rObj, "PIRANHAPLANT", (int)in_rObj.PlayerNo, position);

			enemy::DeadEffectCInfo createEffectInfo{};
			createEffectInfo.Owner = &in_rObj;
			createEffectInfo.PlayerNo = in_rObj.PlayerNo;
			createEffectInfo.SetYoshiIsland();

			math::Transform transform{};
			auto* pVisualModel = in_rObj.GetComponent<fnd::GOCVisualModel>();
			if (pVisualModel && pVisualModel->GetNodeTransform(1, "Mouth", &transform))
			{
				transform.Position *= 0.2f;
				transform.SetFlag(1);

				auto mouthMatrix = transform.GetTransformMatrix();
				createEffectInfo.SetTransform({ trsMatrix * mouthMatrix });
			}

			in_rObj.CreateDeadEffect(createEffectInfo);
			in_rObj.ProcMission();
			in_rObj.SetStatusRetire();
			in_rObj.Kill();

			break;
		}
		default:
		{
			break;
		}
		}

		return true;
	}
}