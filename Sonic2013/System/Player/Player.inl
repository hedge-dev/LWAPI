#include "Player.h"
#pragma once

namespace app::Player
{
	inline void CPlayer::UpdatePlayerInformation()
	{
		size_t playerNo = GetPlayerNo();
		auto* pPlayerInfo = GetService<xgame::Blackboard>()->GetPlayerInformation(playerNo);
		if (!pPlayerInfo)
			return;

		auto* pPhysics = rpPhysics.get();
		pPlayerInfo->Position = pPhysics->Position;
		pPlayerInfo->Rotation = pPhysics->Rotation;
		pPlayerInfo->Velocity = pPhysics->Velocity;
		pPlayerInfo->Unk4 = pPhysics->Unk3;
		pPlayerInfo->Unk5 = pPhysics->Unk13;
		pPlayerInfo->MtxFront = pPhysics->GetFront();
		pPlayerInfo->MtxUp = pPhysics->GetUp();
		pPlayerInfo->MtxRight = pPhysics->GetRight();

		if (rpBlackboard->Unk1[2].test(4))
		{
			pPlayerInfo->GravityDirection = { -pPhysics->Up };
		}
		else
		{
			pPlayerInfo->GravityDirection = pPhysics->GetGravityDirection();
		}

		pPlayerInfo->UpVector = pPhysics->Up;

		pPlayerInfo->Unk10 = pPhysics->GetHistoryPosition(1);

		pPlayerInfo->Unk15 = { pPhysics->Position + pPhysics->GetUp() * 10.0f * 0.5f };

		auto* pVisualGoc = GetPlayerGOC<CVisualGOC>();
		auto* pStateGoc = GetPlayerGOC<CStateGOC>();

		auto& locaterMatrix = pVisualGoc->GetLocaterMatrix();

		if (rpBlackboard->Unk1[3].test(10))
		{
			pPlayerInfo->Unk12 = pPhysics->GetFront();
			pPlayerInfo->Unk13 = pPhysics->GetUp();
			pPlayerInfo->Unk14 = pPhysics->GetRight();
		}
		else
		{
			pPlayerInfo->Unk12 = locaterMatrix.GetColumn(2).Normalize();
			pPlayerInfo->Unk13 = locaterMatrix.GetColumn(1).Normalize();
			pPlayerInfo->Unk14 = csl::math::Vector3(-(locaterMatrix.GetColumn(0))).Normalize();
		}

		math::Vector3NormalizeZero(pPhysics->Unk5, &pPlayerInfo->Unk11);
		pPlayerInfo->Unk19 = pPhysics->Unk9.Unk4;
		pPlayerInfo->Unk20 = pPhysics->Unk9.Unk7;

		if (pStateGoc->GetCurrentState() != 105 || !StateUtil::GetSnowBall(*pStateGoc))
		{
			pPlayerInfo->IsOnGround = pPhysics->Unk9.IsOnGround;
			if (pPhysics->Unk9.IsOnGround)
			{
				pPlayerInfo->IsLandOnMovableGround = StateUtil::IsLandOnMovableGround(*pStateGoc);
			}
			else
			{
				pPlayerInfo->IsLandOnMovableGround = false;
			}
		}
		else
		{
			pPlayerInfo->IsOnGround = StateUtil::GetSnowBall(*pStateGoc)->IsOnGround;
		}

		pPlayerInfo->Unk23 = nullptr;
		pPlayerInfo->Unk24 = { 0.0f, 0.0f, 0.0f };
		if (auto* pTarget = spHomingService->GetFirstTarget())
		{
			pPlayerInfo->Unk23 = pTarget->GetShape()->GetGameObject()->pMessageManager;
			pPlayerInfo->Unk24 = pTarget->Unk7;
		}

		auto* pBlackboard = rpBlackboard.get();
		auto attackStatus = pBlackboard->GetAttackStatus();
		pPlayerInfo->PixieNo = pBlackboard->GetPixieParameter()->PixieNo;
		pPlayerInfo->Unk26 = pBlackboard->Unk2 == 1;
		pPlayerInfo->Unk27 = pBlackboard->Unk1[1].test(3);
		pPlayerInfo->Unk28 = pBlackboard->Unk1[1].test(0);
		pPlayerInfo->Unk29 = pBlackboard->Unk1[3].test(11);
		pPlayerInfo->Unk30 = pBlackboard->Unk1[3].test(12);
		pPlayerInfo->Unk31 = pBlackboard->Unk1[3].test(13);
		pPlayerInfo->Unk50 = (attackStatus->GetAttackTypeFlag() & 0x20) != false;
		pPlayerInfo->Unk32 = pBlackboard->Unk1[1].test(5);
		pPlayerInfo->Unk33 = pBlackboard->Unk1[1].test(6);
		pPlayerInfo->Unk34 = pStateGoc->GetCurrentState() == 7;
		pPlayerInfo->Unk35 = pBlackboard->Unk1[1].test(7);
		pPlayerInfo->Unk36 = pBlackboard->Unk1[3].test(15);
		pPlayerInfo->Unk37 = pBlackboard->Unk1[1].test(1);
		pPlayerInfo->Unk38 = pBlackboard->Unk1[3].test(0);
		pPlayerInfo->IsTimerDisabled = pStateGoc->IsTimerDisable(3);
		pPlayerInfo->IsAttack = attackStatus->IsAttack();
		pPlayerInfo->Unk41 = pBlackboard->Unk1[3].test(21);
		pPlayerInfo->Unk42 = pBlackboard->Unk1[3].test(4);
		pPlayerInfo->Unk43 = pBlackboard->Unk1[1].test(11);
		pPlayerInfo->Unk44 = pBlackboard->Unk1[1].test(12);
		pPlayerInfo->Unk46 = pBlackboard->Unk1[3].test(23);
		pPlayerInfo->Unk47 = pBlackboard->Unk1[1].test(13);

		auto* pPathEvaluator = spPathService->GetPathEvaluator(0);
		if (pPathEvaluator)
		{
			pPlayerInfo->Unk49[0] = pPathEvaluator->Distance;
			pPlayerInfo->PathComponents[0] = pPathEvaluator->Component;
		}
		else
		{
			pPlayerInfo->Unk49[0] = 0.0f;
			pPlayerInfo->PathComponents[0] = {};
		}

		pPathEvaluator = spPathService->GetPathEvaluator(1);
		if (pPathEvaluator)
		{
			pPlayerInfo->Unk49[1] = pPathEvaluator->Distance;
			pPlayerInfo->PathComponents[1] = pPathEvaluator->Component;
		}
		else
		{
			pPlayerInfo->Unk49[1] = 0.0f;
			pPlayerInfo->PathComponents[1] = {};
		}

		auto* pGravityController = pPhysics->GetGravityController();
		pPlayerInfo->SetGravityField(pGravityController->GetGravityField());
		pPlayerInfo->CameraId = CameraId;

		if (pGravityController->Path.Component.IsValid())
		{
			pPlayerInfo->PathComponent = pGravityController->Path.Component;
			pPlayerInfo->PathDistance = pGravityController->Path.Distance;
		}
		else
		{
			pPlayerInfo->PathComponent = {};
			pPlayerInfo->PathDistance = 0.0f;
		}

		pPathEvaluator = &pGravityController->Path;
		if (!pPathEvaluator->Component.IsValid())
		{
			if (rpBlackboard.get()->Unk2 == 1)
			{
				if (spPathService->GetPathEvaluator(0))
				{
					pPathEvaluator = spPathService->GetPathEvaluator(0);
				}
			}
		}
		if (pPathEvaluator->Component.IsValid())
		{
			csl::math::Vector3 normal{};
			csl::math::Vector3 tangent{};

			pPathEvaluator->GetPNT(pPathEvaluator->Distance, nullptr, &normal, &tangent);
			auto velocity = rpPhysics->GetVelocity();
			csl::math::Vector3 vec{ tangent* velocity.dot(tangent) };
			float length = vec.norm();

			if (length >= GetParameter(140) * GetParameter(140))
			{
				pPlayerInfo->Unk16 = vec;
			}

			return;
		}

		pPlayerInfo->Unk16 = { 0.0f, 0.0f, 0.0f };
	}
}