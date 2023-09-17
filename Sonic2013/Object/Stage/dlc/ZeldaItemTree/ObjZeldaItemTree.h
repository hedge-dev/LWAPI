#pragma once

namespace app
{
	class ObjZeldaItemTree : public CSetObjectListener
	{
	private:
		inline static const char* ms_pAnimationName = "ACT";
		inline static size_t ms_AnimationCount = 1;
		inline static size_t ms_ShapeCount = 3;
		inline static const float ms_TreeTopCollisionRadius = 10.0f;
		inline static const float ms_CrownCollisionRadius = 40.0f;
		inline static const float ms_CrownCollisionHeight = 40.0f;
		inline static const float ms_TrunkCollisionRadius = 4.5f;
		inline static const float ms_TrunkCollisionHeight = 92.0f;
		inline static const csl::math::Vector3 ms_TreeTopCollisionOffset = { 0.0f, 100.0f, 0.0f };
		inline static const csl::math::Vector3 ms_CrownCollisionOffset = { 0.0f, 65.0f, 0.0f };
		inline static const csl::math::Vector3 ms_TrunkCollisionOffset = { 0.0f, ms_TrunkCollisionHeight / 2.0f, 0.0f };

	public:
		csl::math::Vector3 Position{};
		csl::math::Vector3 TreeTopPosition{};
		csl::math::Vector3 UpDirection{};

		ObjZeldaItemTree() : CSetObjectListener()
		{

		}

	protected:
		void AddCallback(GameDocument& in_rDocument) override
		{
			fnd::GOComponent::Create<fnd::GOCVisualModel>(*this);
			fnd::GOComponent::Create<game::GOCAnimationSimple>(*this);
			fnd::GOComponent::Create<game::GOCEffect>(*this);
			fnd::GOComponent::Create<game::GOCCollider>(*this);
			fnd::GOComponent::Create<game::GOCSound>(*this);

			fnd::GOComponent::BeginSetup(*this);

			auto* pInfo = ObjUtil::GetObjectInfo<ObjZeldaItemTreeInfo>(in_rDocument);

			if (auto* pVisualGoc = GetComponent<fnd::GOCVisualModel>())
			{
				fnd::GOCVisualModel::Description description{};
				description.m_Model = pInfo->Model;
				description.m_Skeleton = pInfo->Skeleton;
				description.m_LightQualityType = 1;
				description.field_0C |= 0x400000u;

				pVisualGoc->Setup(description);

				if (auto* pAnimationGoc = GetComponent<game::GOCAnimationSimple>())
				{
					pAnimationGoc->Setup({ ms_AnimationCount });
					pAnimationGoc->Add(ms_pAnimationName, pInfo->Animation, game::PlayPolicy::Once);

					pVisualGoc->AttachAnimation(pAnimationGoc);
				}
			}

			if (GetComponent<game::GOCEffect>())
				game::GOCEffect::SimpleSetup(this);

			game::GOCSound::SimpleSetup(this, 0, 0);

			if (auto* pColliderGoc = GetComponent<game::GOCCollider>())
			{
				pColliderGoc->Setup({ ms_ShapeCount });

				game::ColliSphereShapeCInfo treeTopCollisionInfo{};
				treeTopCollisionInfo.m_ShapeType = game::CollisionShapeType::ShapeType::ShapeType_Sphere;
				treeTopCollisionInfo.m_MotionType = game::PhysicsMotionType::MotionType::MotionType_VALUE0;
				treeTopCollisionInfo.m_Unk2 |= 1;
				treeTopCollisionInfo.m_Radius = ms_TreeTopCollisionRadius;
				treeTopCollisionInfo.m_ShapeID = 1;
				ObjUtil::SetupCollisionFilter(ObjUtil::EFilter::eFilter_Unk6, treeTopCollisionInfo);
				treeTopCollisionInfo.SetLocalPosition(ms_TreeTopCollisionOffset);
				pColliderGoc->CreateShape(treeTopCollisionInfo);

				game::ColliCylinderShapeCInfo crownCollisionInfo{};
				crownCollisionInfo.m_ShapeType = game::CollisionShapeType::ShapeType::ShapeType_Cylinder;
				crownCollisionInfo.m_MotionType = game::PhysicsMotionType::MotionType::MotionType_VALUE0;
				crownCollisionInfo.m_Unk2 |= 3;
				crownCollisionInfo.m_Radius = ms_CrownCollisionRadius;
				crownCollisionInfo.m_Height = ms_CrownCollisionHeight;
				crownCollisionInfo.m_ShapeID = 2;
				ObjUtil::SetupCollisionFilter(ObjUtil::EFilter::eFilter_Unk6, crownCollisionInfo);
				crownCollisionInfo.SetLocalPosition(ms_CrownCollisionOffset);
				pColliderGoc->CreateShape(crownCollisionInfo);

				game::ColliCapsuleShapeCInfo trunkCollisionInfo{};
				trunkCollisionInfo.m_ShapeType = game::CollisionShapeType::ShapeType::ShapeType_Capsule;
				trunkCollisionInfo.m_MotionType = game::PhysicsMotionType::MotionType::MotionType_VALUE0;
				trunkCollisionInfo.m_Unk2 |= 0x100;
				trunkCollisionInfo.m_Unk3 = 0x2010000;
				trunkCollisionInfo.m_Radius = ms_TrunkCollisionRadius;
				trunkCollisionInfo.m_Height = ms_TrunkCollisionHeight;
				trunkCollisionInfo.m_ShapeID = 0;
				trunkCollisionInfo.SetLocalPosition(ms_TrunkCollisionOffset);
				pColliderGoc->CreateShape(trunkCollisionInfo);
			}

			fnd::GOComponent::EndSetup(*this);
		}

		bool ProcessMessage(fnd::Message& in_rMessage) override
		{
			if (PreProcessMessage(in_rMessage))
				return true;

			switch (in_rMessage.GetType())
			{
			case xgame::MsgGetClimbObjectInfo::MessageID:		return ProcMsgGetClimbObjectInfo(static_cast<xgame::MsgGetClimbObjectInfo&>(in_rMessage));
			case xgame::MsgHitEventCollision::MessageID:		return ProcMsgHitEventCollision(static_cast<xgame::MsgHitEventCollision&>(in_rMessage));
			case xgame::MsgLeaveEventCollision::MessageID:		return ProcMsgLeaveEventCollision(static_cast<xgame::MsgLeaveEventCollision&>(in_rMessage));
			default:											return CSetObjectListener::ProcessMessage(in_rMessage);
			}
		}

		bool ProcMsgGetClimbObjectInfo(xgame::MsgGetClimbObjectInfo& in_rMessage)
		{
			auto& objectMtx = GetComponent<fnd::GOCTransform>()->m_Frame.m_Unk3.m_Mtx;

			Position = objectMtx.GetTransVector();
			TreeTopPosition = objectMtx * csl::math::Vector4(0.0f, ms_TrunkCollisionRadius + ms_TrunkCollisionHeight, 0.0f, 1.0f);
			UpDirection = objectMtx * csl::math::Vector3(csl::math::Vector3::UnitY());

			in_rMessage.pPosition = &Position;
			in_rMessage.Unk1 = 1;

			return true;
		}

		bool ProcMsgHitEventCollision(xgame::MsgHitEventCollision& in_rMessage)
		{
			switch (in_rMessage.m_pSelf->m_ID)
			{
			case 1:
			{
				auto& objectMtx = GetComponent<fnd::GOCTransform>()->m_Frame.m_Unk3.m_Mtx;

				xgame::MsgItemTreeWobblePoint msg{};
				msg.WobblePoint = objectMtx * csl::math::Vector4(0.0f, ms_TrunkCollisionRadius + ms_TrunkCollisionHeight, 0.0f, 1.0f);
				SendMessageImm(in_rMessage.m_Sender, msg);

				break;
			}
			case 2:
			{
				GetComponent<game::GOCAnimationSimple>()->SetAnimation("ACT");
				GetComponent<game::GOCSound>();

				break;
			}
			default:
				break;
			}

			return true;
		}

		bool ProcMsgLeaveEventCollision(xgame::MsgLeaveEventCollision& in_rMessage)
		{
			csl::math::Vector3 position{};
			xgame::MsgGetPosition msg{ position };
			if (SendMessageImm(in_rMessage.m_Sender, msg))
			{
				GetComponent<game::GOCEffect>();
				GetComponent<fnd::GOCTransform>()->m_Frame.m_Unk3.m_Mtx.SetColumn(3, position);
			}

			GetComponent<game::GOCSound>();


			return true;
		}
	};
}