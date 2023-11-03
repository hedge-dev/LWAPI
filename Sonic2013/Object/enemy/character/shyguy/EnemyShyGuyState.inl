#include "EnemyShyGuy.h"
#pragma once

namespace app
{
	inline void EnemyShyGuy::State::Move::OnEnter(EnemyShyGuy& in_rObj, int in_unk)
	{
		auto* pAnimationScript = in_rObj.GetComponent<game::GOCAnimationScript>();
		if (!pAnimationScript)
			return;

		if (in_rObj.Flags.test(2))
			pAnimationScript->ChangeAnimation("WALK_L");
		else
			pAnimationScript->ChangeAnimation("WALK_R");
	}

	inline bool EnemyShyGuy::State::Move::Step(EnemyShyGuy& in_rObj, float in_deltaTime)
	{
		if (in_rObj.Flags.test(1))
			ChangeState(in_rObj, 1);

		return true;
	}

	inline void EnemyShyGuy::State::Turnaround::ChangeSubState(SubState in_subState)
	{
		State = in_subState;
		ElapsedTime = 0.0f;
	}

	inline void EnemyShyGuy::State::Turnaround::OnEnter(EnemyShyGuy& in_rObj, int in_unk)
	{
		ChangeSubState(SubState::eSubState_Enter);

		LookCount = 0;
		IsLooking = false;

		in_rObj.Flags.reset(1);

		auto* pTransform = in_rObj.GetComponent<fnd::GOCTransform>();
		if (!pTransform)
			return;

		Rotation = pTransform->Transform.Rotation;

		auto* pAnimationScript = in_rObj.GetComponent<game::GOCAnimationScript>();
		if (!pAnimationScript)
			return;

		if (in_rObj.Flags.test(2))
			pAnimationScript->ChangeAnimation("IDLE_L");
		else
			pAnimationScript->ChangeAnimation("IDLE_R");
	}

	inline void EnemyShyGuy::State::Turnaround::OnLeave(EnemyShyGuy& in_rObj, int in_unk)
	{
		auto* pParam = in_rObj.GetAdapter()->GetData<SShyGuyParam>();

		auto* pMovement = in_rObj.GetComponent<game::GOCMovementComplex>();
		if (!pMovement)
			return;

		auto* pTransform = in_rObj.GetComponent<fnd::GOCTransform>();
		if (!pTransform)
			return;

		csl::math::Matrix34 trsMatrix{ pTransform->Transform.GetTransformMatrix() };
		pMovement->GetContextParam()->Velocity = { trsMatrix.GetColumn(2) * pParam->Speed };
		pMovement->EnableMovementFlag(0);
		in_rObj.Flags.flip(2);
	}

	inline bool EnemyShyGuy::State::Turnaround::Step(EnemyShyGuy& in_rObj, float in_deltaTime)
	{
		ElapsedTime += in_deltaTime;
		switch (State)
		{
		case SubState::eSubState_Enter:
		{
			if (0.3f > ElapsedTime)
				return true;

			in_rObj.GetComponent<game::GOCAnimationScript>();

			IsLooking = false;
			ChangeSubState(SubState::eSubState_Turn);

			break;
		}
		case SubState::eSubState_Turn:
		{
			if (!IsLooking)
			{
				IsLooking = true;

				auto* pAnimationScript = in_rObj.GetComponent<game::GOCAnimationScript>();
				if (!pAnimationScript)
					return false;

				if (in_rObj.Flags.test(2) == ((LookCount & 1) == 0))
					pAnimationScript->ChangeAnimation("LOOKAROUND_R");
				else
					pAnimationScript->ChangeAnimation("LOOKAROUND_L");
			}

			auto* pTransform = in_rObj.GetComponent<fnd::GOCTransform>();
			if (!pTransform)
				return false;

			if (ElapsedTime > 0.1f)
			{
				pTransform->Transform.GetTransformMatrix();

				csl::math::Quaternion rotation{ csl::math::QuaternionMultiply(Rotation, { Eigen::AngleAxisf(MATHF_PI, csl::math::Vector3::UnitY()) }) };
				rotation.Normalize();

				Rotation = rotation;
				pTransform->SetLocalRotation(rotation);
				ChangeSubState(eSubState_Leave);

				return true;
			}
			else
			{
				pTransform->Transform.GetTransformMatrix();

				float angle = MATHF_PI * csl::math::Clamp(ElapsedTime / 0.1f, 0.0f, 1.0f);
				if (in_rObj.Flags.test(2) != (LookCount & 1) == 0)
					angle *= -1.0f;
				else
					angle *= 1.0f;

				csl::math::Quaternion rotation{ csl::math::QuaternionMultiply(Rotation, { Eigen::AngleAxisf(angle, csl::math::Vector3::UnitY()) }) };
				rotation.Normalize();
				pTransform->SetLocalRotation(rotation);

				return true;
			}

			break;
		}
		case SubState::eSubState_Leave:
		{
			if (0.3f > ElapsedTime)
				return true;

			LookCount++;
			if (LookCount >= 3)
			{
				auto* pAnimationScript = in_rObj.GetComponent<game::GOCAnimationScript>();
				if (!pAnimationScript)
					return false;

				if (in_rObj.Flags.test(2))
					pAnimationScript->ChangeAnimation("LOOKAROUND_R");
				else
					pAnimationScript->ChangeAnimation("LOOKAROUND_L");

				if (auto* pEnemyHsm = in_rObj.GetComponent<GOCEnemyHsm>())
					pEnemyHsm->ChangeState(0);

				return true;
			}

			IsLooking = false;
			ChangeSubState(SubState::eSubState_Turn);

			break;
		}
		default:
		{
			break;
		}
		}

		return true;
	}
	inline void EnemyShyGuy::State::Stop::OnEnter(EnemyShyGuy& in_rObj, int in_unk)
	{
		auto* pAnimationScript = in_rObj.GetComponent<game::GOCAnimationScript>();
		if (!pAnimationScript)
			return;

		if (in_rObj.Flags.test(2))
			pAnimationScript->ChangeAnimation("IDLE_L");
		else
			pAnimationScript->ChangeAnimation("IDLE_R");

		auto* pMovement = in_rObj.GetComponent<game::GOCMovementComplex>();
		if (!pMovement)
			return;

		pMovement->DisableMovementFlag(0);
	}

	inline void EnemyShyGuy::State::Stop::OnLeave(EnemyShyGuy& in_rObj, int in_unk)
	{
		auto* pMovement = in_rObj.GetComponent<game::GOCMovementComplex>();
		if (!pMovement)
			return;

		pMovement->EnableMovementFlag(0);
	}

	inline bool EnemyShyGuy::State::Stop::Step(EnemyShyGuy& in_rObj, float in_deltaTime)
	{
		return true;
	}

	inline bool EnemyShyGuy::State::Stop::ProcessMessage(GameObject& in_rObj, fnd::Message& in_rMessage)
	{
		switch (in_rMessage.GetType())
		{
		case xgame::MsgNotifyObjectEvent::MessageID:
			return ProcMsgNotifyObjectEvent(in_rObj, static_cast<xgame::MsgNotifyObjectEvent&>(in_rMessage));
		default:
			return StateBase<GameObject>::ProcessMessage(in_rObj, in_rMessage);
		}
	}

	inline bool EnemyShyGuy::State::Stop::ProcMsgNotifyObjectEvent(GameObject& in_rObj, xgame::MsgNotifyObjectEvent& in_rMessage)
	{
		if (in_rMessage.GetEventType() == 1)
			ChangeState(in_rObj, 0);

		return true;
	}
}