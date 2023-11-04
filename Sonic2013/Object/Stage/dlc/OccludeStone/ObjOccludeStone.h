#pragma once

namespace app
{
	class ObjOccludeStone : public CSetObjectListener
	{
	protected:
		inline static const size_t ms_ShapeCount = 2;
		inline static const csl::math::Vector3 ms_CollisionSize = { 30.0f, 45.0f, 25.0f };
		inline static const csl::math::Vector3 ms_CollisionOffset = { 0.0f, 45.0f * 0.5f, 0.0f };
		inline static const char* ms_pEffectName = "ef_dl3_wall_break";
		inline static const char* ms_pPuzzleClearSoundName = "obj_zeldapuzzle_solution";
		inline static const char* ms_pRockBreakSoundName = "obj_zeldarock_break";

	public:
		ObjOccludeStone() : CSetObjectListener()
		{

		}

	protected:
		void AddCallback(GameDocument* in_pDocument) override
		{
			fnd::GOComponent::Create<fnd::GOCVisualModel>(*this);
			fnd::GOComponent::Create<game::GOCShadowSimple>(*this);
			fnd::GOComponent::Create<game::GOCEffect>(*this);
			fnd::GOComponent::Create<game::GOCSound>(*this);
			fnd::GOComponent::Create<game::GOCCollider>(*this);
			
			fnd::GOComponent::BeginSetup(*this);

			auto* pInfo = ObjUtil::GetObjectInfo<ObjOccludeStoneInfo>(*in_pDocument);
			GetAdapter()->GetData<SOccludeStoneParam>();

			if (auto* pVisualModel = GetComponent<fnd::GOCVisualModel>())
			{
				fnd::GOCVisualModel::Description description{};
				description.Model = pInfo->Model;

				pVisualModel->Setup(description);
			}

			if (auto* pShadowSimple = GetComponent<game::GOCShadowSimple>())
			{
				game::ShadowModelShapeCInfo shadowInfo{ pInfo->ShadowModel };
				pShadowSimple->Setup({ &shadowInfo });
			}

			if (auto* pCollider = GetComponent<game::GOCCollider>())
			{
				pCollider->Setup({ ms_ShapeCount });

				game::ColliBoxShapeCInfo collisionInfo{};
				collisionInfo.ShapeType = game::CollisionShapeType::ShapeType::eShapeType_Box;
				collisionInfo.MotionType = game::PhysicsMotionType::MotionType::eMotionType_Value2;
				collisionInfo.Unk2 |= 1;
				collisionInfo.Size = ms_CollisionSize;
				ObjUtil::SetupCollisionFilter(ObjUtil::eFilter_Default, collisionInfo);
				collisionInfo.SetLocalPosition({ ms_CollisionOffset });
				collisionInfo.SetLocalRotation({ Eigen::AngleAxisf(MATHF_PI / 7.2f, csl::math::Vector3::UnitY()) });
				pCollider->CreateShape(collisionInfo);

				game::ColliMeshShapeCInfo meshCollisionInfo{};
				meshCollisionInfo.ShapeType = game::CollisionShapeType::ShapeType::eShapeType_Mesh;
				meshCollisionInfo.MotionType = game::PhysicsMotionType::MotionType::eMotionType_Value2;
				meshCollisionInfo.Flags = 8;
				meshCollisionInfo.Unk2 |= 0x100;
				meshCollisionInfo.Unk3 = 27;
				meshCollisionInfo.Mesh = pInfo->Collision;
				pCollider->CreateShape(meshCollisionInfo);
			}

			if (GetComponent<game::GOCEffect>())
				game::GOCEffect::SimpleSetup(this);

			game::GOCSound::SimpleSetup(this, 0, 0);

			fnd::GOComponent::EndSetup(*this);
		}

		bool ProcessMessage(fnd::Message& in_rMessage) override
		{
			if (PreProcessMessage(in_rMessage))
				return true;

			switch (in_rMessage.GetType())
			{
			case xgame::MsgDamage::MessageID:			return ProcMsgDamage(static_cast<xgame::MsgDamage&>(in_rMessage));
			default:									return CSetObjectListener::ProcessMessage(in_rMessage);
			}
		}

		bool ProcMsgDamage(xgame::MsgDamage& in_rMessage)
		{
			bool damageByObject{};
			if (in_rMessage.DefensePower == 3 && in_rMessage.SenderType == 3)
				damageByObject = true;

			auto* pPlayerInfo = ObjUtil::GetPlayerInformation(*GetDocument(), 0);

			if ((in_rMessage.Bonus.Unk1 != 3 || !pPlayerInfo || pPlayerInfo->PixieNo != Game::EPhantomType::ePhantom_Bomb) && !damageByObject)
				return true;

			auto* pInfo = ObjUtil::GetObjectInfo<ObjOccludeStoneInfo>(*GetDocument());
			auto& transform = GetComponent<fnd::GOCTransform>()->Frame.Unk3;
			csl::math::Vector3 direction = math::Vector3Rotate(transform.GetRotationQuaternion(), { csl::math::Vector3::UnitY() });

			debris::SRandomSpaceDebrisInfo debrisInfo{};
			debrisInfo.Transform.Position = { transform.GetTranslation() + (direction * 45.0f * 0.5f) };
			debrisInfo.Transform.SetFlag(1);
			debrisInfo.Transform.Rotation = transform.GetRotationQuaternion();
			debrisInfo.Transform.SetFlag(1);
			debrisInfo.Unk1 = 400.0f;
			debrisInfo.Unk2 = 2.0f;
			debrisInfo.Unk3 = 0.5f;
			debrisInfo.Unk4.set(0);
			debrisInfo.Unk5 = in_rMessage.Unk2;
			debrisInfo.Unk6 = direction;
			debrisInfo.Unk7 = 2.0f;
			debrisInfo.Unk8 = 1.0f;
			debrisInfo.Unk4.set(2);
			debrisInfo.Unk10 = 0.0f;
			debrisInfo.Unk11 = 10.0f;
			debrisInfo.Unk4.set(1);
			debrisInfo.Unk9 = 0.5f;
			debrisInfo.SetModelRes(pInfo->Debris, 24);
			debrisInfo.Unk14 = 3;
			debrisInfo.Unk15 = 22.5f;
			debrisInfo.Unk16 = 25.0f;
			debrisInfo.Unk17 = 15.0f;
			debrisUtil::CreateRandomSpaceDebris(*GetDocument(), debrisInfo);

			GetComponent<game::GOCEffect>()->CreateEffect(ms_pEffectName);
			GetComponent<game::GOCSound>()->Play(ms_pPuzzleClearSoundName, 0.0f);
			GetComponent<game::GOCSound>()->Play3D(ms_pRockBreakSoundName, 0.0f);
			SetStatusRetire();
			Kill();

			return true;
		}
	};
}