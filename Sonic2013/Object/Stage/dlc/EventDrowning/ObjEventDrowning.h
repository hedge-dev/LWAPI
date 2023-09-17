#pragma once

namespace app
{
	class ObjEventDrowning : public CSetObjectListener
	{
	protected:
		inline static const char* ms_pEffectName = "ef_dl3_water_splash";
		inline static const char* ms_pSoundName = "sn_land_waterdeep";
		inline static const size_t ms_ShapeCount = 2;

	public:
		ObjEventDrowning() : CSetObjectListener()
		{
			SetUpdateFlag(0, false);
		}

		void AddCallback(GameDocument& in_rDocument) override
		{
			fnd::GOComponent::Create<game::GOCCollider>(*this);
			fnd::GOComponent::Create<game::GOCEffect>(*this);
			fnd::GOComponent::Create<game::GOCSound>(*this);
			
			fnd::GOComponent::BeginSetup(*this);

			auto* pParam = GetAdapter()->GetData<SEventDrowningParam>();

			if (auto* pCollider = GetComponent<game::GOCCollider>())
			{
				pCollider->Setup({ ms_ShapeCount });

				game::ColliBoxShapeCInfo effectCollisionInfo{};
				effectCollisionInfo.m_ShapeType = game::CollisionShapeType::ShapeType::ShapeType_Box;
				effectCollisionInfo.m_MotionType = game::PhysicsMotionType::MotionType::MotionType_VALUE2;
				effectCollisionInfo.m_Unk2 |= 1;
				effectCollisionInfo.m_Size = { pParam->CollisionWidth, pParam->CollisionDepth, pParam->CollisionHeight };
				effectCollisionInfo.SetLocalPosition({ csl::math::Vector3::UnitY() * pParam->EffectOffset });
				effectCollisionInfo.m_ShapeID = 1;
				ObjUtil::SetupCollisionFilter(ObjUtil::eFilter_Unk7, effectCollisionInfo);
				pCollider->CreateShape(effectCollisionInfo);

				game::ColliBoxShapeCInfo collisionInfo{};
				collisionInfo.m_ShapeType = game::CollisionShapeType::ShapeType::ShapeType_Box;
				collisionInfo.m_MotionType = game::PhysicsMotionType::MotionType::MotionType_VALUE2;
				collisionInfo.m_Unk2 |= 1;
				collisionInfo.m_Size = { pParam->CollisionWidth, pParam->CollisionDepth, pParam->CollisionHeight };
				collisionInfo.m_ShapeID = 0;
				ObjUtil::SetupCollisionFilter(ObjUtil::eFilter_Unk7, collisionInfo);
				pCollider->CreateShape(collisionInfo);
			}

			if (GetComponent<game::GOCSound>())
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
			case xgame::MsgHitEventCollision::MessageID:			return ProcMsgHitEventCollision(static_cast<xgame::MsgHitEventCollision&>(in_rMessage));
			default:												return CSetObjectListener::ProcessMessage(in_rMessage);
			}
		}

		bool ProcMsgHitEventCollision(xgame::MsgHitEventCollision& in_rMessage)
		{
			if (!ObjUtil::CheckShapeUserID(in_rMessage.m_pSelf, 1))
			{
				xgame::MsgDead msg{ 10 };
				SendMessageImm(in_rMessage.m_Sender, msg);
			
				return true;
			}

			auto* pParam = GetAdapter()->GetData<SEventDrowningParam>();

			csl::math::Matrix34 transformMtx = GetComponent<fnd::GOCTransform>()->m_Frame.m_Unk3.m_Mtx;
			csl::math::Vector3 upVector{ transformMtx.GetColumn(1) };
			csl::math::Vector3 position = transformMtx.GetTransVector();

			csl::math::Vector3 contactDistance{ * in_rMessage.GetContactPointPosition() - position };
			csl::math::Vector3 contactPosition{ position + contactDistance - csl::math::Vector3(upVector * contactDistance.dot(upVector)) };
			
			transformMtx.SetTransVector({ contactPosition + upVector * pParam->EffectOffset });
			GetComponent<game::GOCEffect>()->CreateEffectWorld(ms_pEffectName, transformMtx, 1.0f);
			GetComponent<game::GOCSound>()->Play3D(ms_pSoundName, contactPosition, 0.0f);

			return true;
		}
	};
}