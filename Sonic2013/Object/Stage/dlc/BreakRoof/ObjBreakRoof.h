#pragma once

namespace app
{
	class ObjBreakRoof : public CSetObjectListener
	{
	private:
		inline static const char* ms_pSoundName = "obj_zeldabreakfloor";
		inline static const char* ms_pEffectName = "ef_dl3_lid_break";
		inline static const size_t ms_ShapeCount = 1;
		inline static const size_t ms_PhysicsShapeCount = 1;
		inline static const csl::math::Vector3 ms_CollisionSize = { 30.0f * 0.5f, 20.0f * 0.5f + 1.0f, 30.0f };
		inline static const csl::math::Vector3 ms_CollisionOffset = { 0.0f, -(20.0f * 0.5f - 1.0f), 0.0f };

	public:
		ObjBreakRoof() : CSetObjectListener()
		{
			
		}

	protected:
		void AddCallback(GameDocument* in_pDocument) override
		{
			auto* pInfo = ObjUtil::GetObjectInfo<ObjBreakRoofInfo>(*in_pDocument);

			fnd::GOComponent::Create<fnd::GOCVisualModel>(*this);
			fnd::GOComponent::Create<game::GOCCollider>(*this);
			fnd::GOComponent::Create<game::GOCPhysics>(*this);
			fnd::GOComponent::Create<game::GOCSound>(*this);
			fnd::GOComponent::Create<game::GOCEffect>(*this);

			fnd::GOComponent::BeginSetup(*this);

			if (auto* pVisualModel = GetComponent<fnd::GOCVisualModel>())
			{
				fnd::GOCVisualModel::Description description{};
				description.Model = pInfo->Model;
				description.Skeleton = pInfo->Skeleton;
				description.Unk1 = 1;

				pVisualModel->Setup(description);
			}

			if (auto* pCollider = GetComponent<game::GOCCollider>())
			{
				pCollider->Setup({ ms_ShapeCount });

				game::ColliBoxShapeCInfo collisionInfo{};
				collisionInfo.ShapeType = game::CollisionShapeType::ShapeType::eShapeType_Box;
				collisionInfo.MotionType = game::PhysicsMotionType::MotionType::eMotionType_Value2;
				collisionInfo.Unk2 |= 1;
				collisionInfo.Size = ms_CollisionSize;
				ObjUtil::SetupCollisionFilter(ObjUtil::EFilter::eFilter_Default, collisionInfo);
				collisionInfo.SetLocalPosition(ms_CollisionOffset);
				pCollider->CreateShape(collisionInfo);
			}

			if (auto* pPhysics = GetComponent<game::GOCPhysics>())
			{
				pPhysics->Setup({ ms_PhysicsShapeCount });

				game::ColliMeshShapeCInfo collisionInfo{};
				collisionInfo.ShapeType = game::CollisionShapeType::ShapeType::eShapeType_Mesh;
				collisionInfo.MotionType = game::PhysicsMotionType::MotionType::eMotionType_Value2;
				collisionInfo.Flags = 1;
				collisionInfo.Mesh = pInfo->Collision;
				pPhysics->CreateShape(collisionInfo);
			}

			game::GOCSound::SimpleSetup(this, 0, 0);
			
			if (GetComponent<game::GOCEffect>())
				game::GOCEffect::SimpleSetup(this);

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
			if (!AttackType::IsDamaged(in_rMessage.AttackType, 9))
				return false;
		
			auto* pTransform = GetComponent<fnd::GOCTransform>();
			auto* pVisualModel = GetComponent<fnd::GOCVisualModel>();

			auto& upVector = pTransform->Frame.Unk3.Mtx.GetColumn(1);
			for (size_t i = 0; i < 9; i++)
			{
				math::Transform transform{};
				pVisualModel->GetNodeTransform(0, i, &transform);

				debris::SRandomSpaceDebrisInfo debrisInfo{};
				debrisInfo.Transform.Position = { transform.Position };
				debrisInfo.Transform.SetFlag(1);
				debrisInfo.Transform.Rotation = pTransform->Frame.Unk3.GetRotationQuaternion();
				debrisInfo.Transform.SetFlag(1);
				debrisInfo.Unk1 = 400.0f;
				debrisInfo.Unk2 = 2.0f;
				debrisInfo.Unk3 = 0.5f;
				debrisInfo.Unk4.set(0);
				debrisInfo.Unk5 = in_rMessage.Unk2;
				debrisInfo.Unk6 = upVector;
				debrisInfo.Unk7 = 5.0f;
				debrisInfo.Unk8 = 1.0f;
				debrisInfo.Unk4.set(2);
				debrisInfo.Unk10 = 0.0f;
				debrisInfo.Unk11 = 5.0f;
				debrisInfo.Unk4.set(1);
				debrisInfo.Unk9 = 1.0f;
				debrisInfo.SetModelRes(ObjUtil::GetObjectInfo<ObjBreakRoofInfo>(*GetDocument())->Debris, 24);
				debrisInfo.Unk14 = 3;
				debrisInfo.Unk15 = 30.0f * 0.5f;
				debrisInfo.Unk16 = 20.0f * 0.5f;
				debrisInfo.Unk17 = debrisInfo.Unk15;
				debrisUtil::CreateRandomSpaceDebris(*GetDocument(), debrisInfo);
			}

			GetComponent<game::GOCSound>()->Play3D(ms_pSoundName, 0.0f);
			GetComponent<game::GOCEffect>()->CreateEffect(ms_pEffectName);

			int playerNo = ObjUtil::GetPlayerNo(*GetDocument(), in_rMessage.Sender);
			if (playerNo >= 0)
			{
				xgame::MsgShakeCamera msg{};
				msg.Unk1 = 3.0f;
				msg.Unk2 = 0.2f;

				ObjUtil::SendMessageImmToCamera(*this, playerNo, msg);
			}

			in_rMessage.SetReply(GetComponent<fnd::GOCTransform>()->Transform.Position, true);
			SetStatusRetire();
			Kill();
		}
	};
}