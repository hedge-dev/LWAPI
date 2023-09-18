#pragma once

namespace app
{
	namespace sucked_yoshi_coin
	{
		struct CreateInfo
		{
		public:
			csl::math::Matrix34 Matrix;
			int PlayerNo;

			CreateInfo(csl::math::Matrix34 in_matrix, int in_playerNo)
			{
				Matrix = in_matrix;
				PlayerNo = in_playerNo;
			}
		};
	}

	class ObjSuckedYoshiCoin : public GameObject3D
	{
	private:
		inline static const char* ms_EffectName = "ef_dl2_coin_get";
		inline static const char* ms_SoundName = "obj_yossycoin_get";
		inline static const char* ms_ScoreName = "GET_YOSHICOIN";
		inline static size_t ms_ShapeCount = 1;
		inline static float ms_CollisionRadius = 3.0f;
		inline static float ms_ShadowRadius = 3.0f;

	public:
		csl::math::Matrix34 Matrix{};
		int PlayerNo{};
		Gimmick::CRingManager* pRingManager{ nullptr };
		float Unk3{ 0.0f };

		ObjSuckedYoshiCoin(const sucked_yoshi_coin::CreateInfo& in_rCreateInfo) : GameObject3D()
		{
			Matrix = in_rCreateInfo.Matrix;
			PlayerNo = in_rCreateInfo.PlayerNo;
		}

	protected:
		void AddCallback(GameDocument& in_rDocument) override
		{
			fnd::GOComponent::Create<fnd::GOCVisualModel>(*this);
			fnd::GOComponent::Create<game::GOCCollider>(*this);
			fnd::GOComponent::Create<game::GOCShadowSimple>(*this);
			fnd::GOComponent::Create<game::GOCEffect>(*this);
			fnd::GOComponent::Create<game::GOCSound>(*this);

			fnd::GOComponent::BeginSetup(*this);

			if (auto* pTransform = GetComponent<fnd::GOCTransform>())
			{
				auto position = Matrix.GetTransVector();
				auto rotation = Matrix.GetRotation();

				pTransform->SetLocalTranslationAndRotation(position, rotation);
			}

			auto* pInfo = ObjUtil::GetObjectInfo<ObjYoshiCoinInfo>(in_rDocument);

			pRingManager = in_rDocument.GetService<Gimmick::CRingManager>();
			pRingManager->RegisterRotateRing(this);

			if (auto* pVisualModel = GetComponent<fnd::GOCVisualModel>())
			{
				fnd::GOCVisualModel::Description description{};
				description.m_Model = pInfo->Model;

				pVisualModel->Setup(description);
				pVisualModel->SetLocalRotationXYZ(0.0f, pRingManager->Unk2, 0.0f);
			}

			if (auto* pCollider = GetComponent<game::GOCCollider>())
			{
				pCollider->Setup({ ms_ShapeCount });
				game::ColliSphereShapeCInfo collisionInfo{};
				collisionInfo.m_ShapeType = game::CollisionShapeType::ShapeType::ShapeType_Sphere;
				collisionInfo.m_MotionType = game::PhysicsMotionType::MotionType::MotionType_VALUE0;
				collisionInfo.m_Unk2 |= 1u;
				collisionInfo.m_Radius = ms_CollisionRadius;
				ObjUtil::SetupCollisionFilter(ObjUtil::eFilter_Unk12, collisionInfo);

				pCollider->CreateShape(collisionInfo);
			}

			if (auto* pShadowSimple = GetComponent<game::GOCShadowSimple>())
			{
				game::ShadowHemisphereShapeCInfo shadowInfo{ ms_ShadowRadius };
				shadowInfo.Unk2 = 5;

				game::GOCShadowSimple::Description description{ &shadowInfo };
				pShadowSimple->Setup(description);
			}

			if (GetComponent<game::GOCEffect>()) game::GOCEffect::SimpleSetup(this, 0, false);
			if (GetComponent<game::GOCSound>()) game::GOCSound::SimpleSetup(this, 0, 0);

			fnd::GOComponent::EndSetup(*this);
		}

		bool ProcessMessage(fnd::Message& in_rMessage) override
		{
			switch (in_rMessage.GetType())
			{
			case xgame::MsgHitEventCollision::MessageID:				return ProcMsgHitEventCollision(static_cast<xgame::MsgHitEventCollision&>(in_rMessage));
			default:													return GameObject3D::ProcessMessage(in_rMessage);
			}
		}

		void Update(const fnd::SUpdateInfo& in_rUpdateInfo) override
		{
			auto* pPlayerInfo = ObjUtil::GetPlayerInformation(*GetDocument(), PlayerNo);
			if (!pPlayerInfo)
				return;
		
			auto* pTransform = GetComponent<fnd::GOCTransform>();
			auto objectPos = pTransform->m_Transform.m_Position;

			Unk3 = csl::math::Min<float>(60.0f * in_rUpdateInfo.deltaTime + Unk3, 60.0f);
			auto distance = static_cast<csl::math::Vector3>(pPlayerInfo->Unk15 - objectPos);
			distance *= (Unk3 * in_rUpdateInfo.deltaTime);

			pTransform->SetLocalTranslation(static_cast<csl::math::Vector3>(distance + objectPos));
		}

		bool ProcMsgHitEventCollision(xgame::MsgHitEventCollision& in_rMessage)
		{
			xgame::MsgTakeObject msg{ xgame::MsgTakeObject::EType::eType_Ring };
			msg.SetShapeUserID(in_rMessage.m_pOther->m_ID);
			if (!SendMessageImm(in_rMessage.m_Sender, msg) || !msg.m_Taken)
				return true;

			if (auto* pEffect = GetComponent<game::GOCEffect>())
			{
				game::EffectCreateInfo effectInfo{};
				effectInfo.m_pName = ms_EffectName;
				effectInfo.m_Unk1 = 1.0f;
				effectInfo.m_Unk10 = true;

				pEffect->CreateEffectEx(effectInfo);
			}

			if (auto* pSound = GetComponent<game::GOCSound>()) pSound->Play(ms_SoundName, 0.0f);

			ObjUtil::AddScorePlayerAction(*this, ms_ScoreName, ObjUtil::GetPlayerNo(*this->m_pOwnerDocument, in_rMessage.m_Sender));

			Kill();

			return true;
		}
	};
}