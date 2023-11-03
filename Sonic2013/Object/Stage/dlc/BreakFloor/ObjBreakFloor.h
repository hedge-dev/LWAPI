#pragma once

namespace app
{
	class ObjBreakFloor : public CSetObjectListener
	{
	private:
		inline static const char* ms_pSoundName = "obj_zeldabreakfloor";
		inline static const char* ms_pPuzzleSolutionSoundName = "obj_zeldapuzzle_solution";
		inline static const char* ms_pEffectName = "ef_dl3_floor_break";
		inline static const char* ms_pScoreName = "CRYSTAL_FLOOR";
		inline static const size_t ms_ShapeCount = 9;
		inline static const size_t ms_PhysicsShapeCount = 1;
		inline static const size_t ms_FloorLayout[] = { 1, 3, 3, 1 };
		inline static const csl::math::Vector3 ms_PositionOffset = { 0.0f, 0.0f, -45.0f };
		inline static const csl::math::Vector3 ms_CollisionSize = { 15.0f, 12.0f, 15.0f };
		inline static const csl::math::Vector3 ms_CollisionOffset = { 0.0f, -9.0f, 0.0f };
		inline static const csl::math::Vector3 ms_MeshCollisionOffset = { 0.0f, 0.0, -45.0f };

	public:
		csl::ut::InplaceObjectMoveArrayAligned16<fnd::HFrame, 8> Frames{};

		ObjBreakFloor() : CSetObjectListener()
		{

		}

	protected:
		void AddCallback(GameDocument* in_pDocument) override
		{
			fnd::GOComponent::Create<fnd::GOCVisualModel>(*this);
			fnd::GOComponent::Create<game::GOCCollider>(*this);
			fnd::GOComponent::Create<game::GOCSound>(*this);
			fnd::GOComponent::Create<game::GOCEffect>(*this);

			fnd::GOComponent::BeginSetup(*this);

			auto* pTransform = GetComponent<fnd::GOCTransform>();;
			pTransform->Unk2 = false;

			for (size_t i = 0; i < Frames.size(); i++)
				pTransform->Frame.AddChild(&Frames[i]);
			
			auto* pInfo = ObjUtil::GetObjectInfo<ObjBreakFloorInfo>(*in_pDocument);

			if (auto* pVisualModel = GetComponent<fnd::GOCVisualModel>())
			{
				fnd::GOCVisualModel::Description description{};
				description.Model = pInfo->Model;
				description.Skeleton = pInfo->Skeleton;
				description.field_08 = 1;

				pVisualModel->Setup(description);
				pVisualModel->SetLocalTranslation(ms_PositionOffset);
			}

			if (auto* pCollider = GetComponent<game::GOCCollider>())
			{
				pCollider->Setup({ ms_ShapeCount });

				game::ColliBoxShapeCInfo collisionInfo{};
				collisionInfo.ShapeType = game::CollisionShapeType::ShapeType::eShapeType_Box;
				collisionInfo.MotionType = game::PhysicsMotionType::MotionType::eMotionType_Value2;
				collisionInfo.Unk2 |= 1;
				collisionInfo.Size = ms_CollisionSize;
				ObjUtil::SetupCollisionFilter(ObjUtil::EFilter::eFilter_Unk5, collisionInfo);
				collisionInfo.SetLocalPosition(ms_CollisionOffset);

				for (size_t i = 0; i < ms_ShapeCount - 1; i++)
				{
					collisionInfo.ShapeID = i;
					collisionInfo.pParent = &Frames[i];
					pCollider->CreateShape(collisionInfo);
				}

				game::ColliMeshShapeCInfo meshCollisionInfo{};
				meshCollisionInfo.ShapeType = game::CollisionShapeType::ShapeType::eShapeType_Mesh;
				meshCollisionInfo.MotionType = game::PhysicsMotionType::MotionType::eMotionType_Value2;
				meshCollisionInfo.Flags = 1;
				meshCollisionInfo.Unk2 |= 0x100;
				meshCollisionInfo.ShapeID = ms_ShapeCount - 1;
				meshCollisionInfo.Mesh = pInfo->Collision;
				meshCollisionInfo.SetLocalPosition(ms_MeshCollisionOffset);
				pCollider->CreateShape(meshCollisionInfo);
			}

			game::GOCSound::SimpleSetup(this, 0, 0);
			
			if (GetComponent<game::GOCEffect>())
				game::GOCEffect::SimpleSetup(this);

			if (auto* pGravityManager = in_pDocument->GetService<game::GravityManager>())
			{
				ObjUtil::LayoutCylinder layout{};
				layout.Setup({ &pTransform->Frame, pGravityManager->GetObjectAtPoint(pTransform->Transform.Position) });

				csl::math::Vector3 right = { csl::math::Vector3::UnitX() * (30.0f - 4.0f) };
				csl::math::Vector3 forward = { -csl::math::Vector3::UnitZ() * 30.0f };

				size_t currentBlock{};
				for (size_t i = 0; i < 4; i++)
				{
					size_t blockCount = ms_FloorLayout[i];
					csl::math::Vector3 offset = { (forward * i) + (right * -0.5f * (blockCount - 1)) };

					if (!blockCount)
						continue;

					for (size_t j = 0; j < blockCount; j++)
					{
						auto* pTransform = layout.CalcTransform({ right * j + offset });
						Frames[currentBlock].SetLocalTranslation(pTransform->Position);
						Frames[currentBlock].SetLocalRotation(pTransform->Rotation);

						currentBlock++;
					}
				}
			}

			fnd::GOComponent::EndSetup(*this);
		}

		bool ProcessMessage(fnd::Message& in_rMessage) override
		{
			if (PreProcessMessage(in_rMessage))
				return true;

			switch (in_rMessage.GetType())
			{
			case xgame::MsgDamage::MessageID:				return ProcMsgDamage(static_cast<xgame::MsgDamage&>(in_rMessage));
			default:										return CSetObjectListener::ProcessMessage(in_rMessage);
			}
		}

		bool ProcMsgDamage(xgame::MsgDamage& in_rMessage)
		{
			if (!AttackType::IsDamaged(in_rMessage.AttackType, 9) && (in_rMessage.AttackType & 0x400080) != 0x400080 && (in_rMessage.DefensePower != 3 || in_rMessage.SenderType != 3))
			{
				in_rMessage.ReplyStatus.set(4);
				return true;
			}

			GetComponent<game::GOCSound>()->Play3D(ms_pSoundName, 0.0f);
			GetComponent<game::GOCSound>()->Play(ms_pPuzzleSolutionSoundName, 0.0f);
			GetComponent<game::GOCEffect>()->CreateEffect(ms_pEffectName);

			in_rMessage.SetReply(in_rMessage.Unk2, true);
			ObjUtil::AddScorePlayerAction(*this, ms_pScoreName, in_rMessage.PlayerNo);

			auto* pInfo = ObjUtil::GetObjectInfo<ObjBreakFloorInfo>(*GetDocument());
			if (pInfo)
			{
				for (size_t i = 0; i < ms_ShapeCount - 1; i++)
				{
					if (AttackType::And(in_rMessage.AttackType, 1))
						ObjCrystalFloorBaseUtil::CreateUpDebris(Frames[i].Unk3, in_rMessage.Unk2, pInfo->Debris, GetDocument());
					else
						ObjCrystalFloorBaseUtil::CreateDownDebris(Frames[i].Unk3, in_rMessage.Unk2, pInfo->Debris, GetDocument());
				}
			}

			SetStatusRetire();
			Kill();

			return true;
		}
	};
}