#pragma once

namespace app
{
	class ObjYoshiSpecialFlower : public CSetObjectListener
	{
	private:
		inline static const char* ms_pEffectName = "ef_dl2_coin_get";
		inline static const char* ms_pSoundName = "obj_specialflower_get";
		inline static const size_t ms_ShapeCount = 1;
		inline static const size_t ms_AnimationCount = 1;
		inline static const float ms_CollisionRadius = 7.5f;

	public:
		size_t FlowerId{};

	public:
		ObjYoshiSpecialFlower() : CSetObjectListener()
		{
			
		}

	protected:
		void AddCallback(GameDocument& in_rDocument) override
		{
			fnd::GOComponent::Create<fnd::GOCVisualModel>(*this);
			fnd::GOComponent::Create<game::GOCAnimationSimple>(*this);
			fnd::GOComponent::Create<game::GOCCollider>(*this);
			fnd::GOComponent::Create<game::GOCEffect>(*this);
			fnd::GOComponent::Create<game::GOCSound>(*this);

			fnd::GOComponent::BeginSetup(*this);

			auto* pParam = GetAdapter()->GetData<SYoshiSpecialFlowerParam>();
			FlowerId = pParam->FlowerId;
			
			auto* pInfo = ObjUtil::GetObjectInfo<ObjYoshiSpecialFlowerInfo>(in_rDocument);
			
			if (auto* pVisualModel = GetComponent<fnd::GOCVisualModel>())
			{
				fnd::GOCVisualModel::Description description{};
				description.m_Model = pInfo->Model;
				description.m_Skeleton = pInfo->Skeleton;
				
				pVisualModel->Setup(description);
			
				if (auto* pAnimation = GetComponent<game::GOCAnimationSimple>())
				{
					pAnimation->Setup({ ms_AnimationCount });
					pVisualModel->AttachAnimation(pAnimation);

					pAnimation->Add("IDLE_LOOP", pInfo->Animation, game::PlayPolicy::Loop);
					pAnimation->SetAnimation("IDLE_LOOP");
				}
			}

			if (auto* pCollider = GetComponent<game::GOCCollider>())
			{
				pCollider->Setup({ ms_ShapeCount });
				game::ColliSphereShapeCInfo collisionInfo{};
				collisionInfo.m_ShapeType = game::CollisionShapeType::ShapeType::ShapeType_Sphere;
				collisionInfo.m_MotionType = game::PhysicsMotionType::MotionType::MotionType_VALUE0;
				collisionInfo.m_Unk2 |= 1;
				collisionInfo.m_Radius = ms_CollisionRadius;
				ObjUtil::SetupCollisionFilter(ObjUtil::eFilter_Unk6, collisionInfo);
				
				pCollider->CreateShape(collisionInfo);
			}

			if (GetComponent<game::GOCEffect>()) game::GOCEffect::SimpleSetup(this, 0, false);
			game::GOCSound::SimpleSetup(this, 0, 0);

			fnd::GOComponent::EndSetup(*this);
		}

		bool ProcessMessage(fnd::Message& in_rMessage) override
		{
			if (PreProcessMessage(in_rMessage))
				return true;

			switch (in_rMessage.GetType())
			{
			case xgame::MsgHitEventCollision::MessageID:				return ProcMsgHitEventCollision(static_cast<xgame::MsgHitEventCollision&>(in_rMessage));
			default:													return CSetObjectListener::ProcessMessage(in_rMessage);
			}
		}

		bool ProcMsgHitEventCollision(xgame::MsgHitEventCollision& in_rMessage)
		{
			if (auto* pEggManager = GetDocument()->GetService<EggManager>())
				pEggManager->TakeYoshiSpecialFlower(FlowerId);

			if (auto* pEffect = GetComponent<game::GOCEffect>())
				pEffect->CreateEffect(ms_pEffectName);

			if (auto* pSound = GetComponent<game::GOCSound>())
				pSound->Play(ms_pSoundName, 0.0f);
			
			Kill();
			SetStatusRetire();
			
			return true;
		}
	};
}