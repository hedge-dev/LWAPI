#pragma once

namespace app
{
	class ObjGolonRockGenerator : public CSetObjectListener
	{
	protected:
		inline static const size_t ms_ShapeCount = 1;
		inline static const csl::math::Vector3 ms_CollisionSize = { 17.5f, 30.0f, 17.5f };
		inline static const csl::math::Vector3 ms_CollisionOffset = { 0.0f, 30.0f, 0.0f };
		inline static const char* ms_pSoundName = "obj_goron_generate";
		inline static const char* ms_pEffectName = "ef_dl3_goron_appear";

	public:
		csl::ut::Bitset<byte> Flags{};
		float Speed{};
		float CreateInterval{};
		float ElapsedTime{};

		ObjGolonRockGenerator() : CSetObjectListener()
		{

		}

		void AddCallback(GameDocument& in_rDocument) override
		{
			fnd::GOComponent::Create<game::GOCCollider>(*this);
			fnd::GOComponent::Create<game::GOCEffect>(*this);
			fnd::GOComponent::Create<game::GOCSound>(*this);
			
			fnd::GOComponent::BeginSetup(*this);

			auto* pParam = GetAdapter()->GetData<SGolonRockGeneratorParam>();
			if (pParam->IsCheckFall)
				Flags.set(0);

			if (!pParam->IsEventOn)
				Flags.set(1);

			Speed = pParam->Speed * 10.0f;
			CreateInterval = pParam->CreateInterval;
			ElapsedTime = pParam->CreateInterval;

			if (auto* pCollider = GetComponent<game::GOCCollider>())
			{
				pCollider->Setup({ ms_ShapeCount });

				game::ColliBoxShapeCInfo collisionInfo{};
				collisionInfo.m_ShapeType = game::CollisionShapeType::ShapeType::ShapeType_Box;
				collisionInfo.m_MotionType = game::PhysicsMotionType::MotionType::MotionType_VALUE2;
				collisionInfo.m_Unk2 |= 3;
				collisionInfo.m_Size = ms_CollisionSize;
				collisionInfo.SetLocalPosition(ms_CollisionOffset);
				ObjUtil::SetupCollisionFilter(ObjUtil::eFilter_Unk6, collisionInfo);
				pCollider->CreateShape(collisionInfo);
			}

			if (GetComponent<game::GOCEffect>())
				game::GOCEffect::SimpleSetup(this, 0, 0);

			game::GOCSound::SimpleSetup(this, 0, 0);

			fnd::GOComponent::EndSetup(*this);
		}

		void Update(const fnd::SUpdateInfo& in_rUpdateInfo) override
		{
			if (!Flags.test(1))
				return;
		
			ElapsedTime += in_rUpdateInfo.deltaTime;

			if (Flags.test(2) || ElapsedTime <= CreateInterval)
				return;
		
			ElapsedTime = 0.0f;

			golon_rock::GolonRockCreateInfo createInfo{};
			createInfo.TransformMtx = GetComponent<fnd::GOCTransform>()->m_Frame.m_Unk3.m_Mtx;
			createInfo.Speed = -Speed;
			createInfo.IsCheckFall = Flags.test(0);

			golon_rock::CreateGolonRock(GetAllocator(), GetDocument(), createInfo);

			GetComponent<game::GOCSound>()->Play3D(ms_pSoundName, 0.0f);
			GetComponent<game::GOCEffect>()->CreateEffect(ms_pEffectName);
		}

		bool ProcessMessage(fnd::Message& in_rMessage) override
		{
			if (PreProcessMessage(in_rMessage))
				return true;

			switch (in_rMessage.GetType())
			{
			case xgame::MsgNotifyObjectEvent::MessageID:			return ProcMsgNotifyObjectEvent(static_cast<xgame::MsgNotifyObjectEvent&>(in_rMessage));
			case xgame::MsgHitEventCollision::MessageID:			return ProcMsgHitEventCollision(static_cast<xgame::MsgHitEventCollision&>(in_rMessage));
			case xgame::MsgLeaveEventCollision::MessageID:			return ProcMsgLeaveEventCollision(static_cast<xgame::MsgLeaveEventCollision&>(in_rMessage));
			case xgame::MsgDlcZeldaNoticeStopEnemy::MessageID:		return ProcMsgDlcZeldaNoticeStopEnemy(static_cast<xgame::MsgDlcZeldaNoticeStopEnemy&>(in_rMessage));
			case xgame::MsgDlcZeldaNoticeActiveEnemy::MessageID:	return ProcMsgDlcZeldaNoticeActiveEnemy(static_cast<xgame::MsgDlcZeldaNoticeActiveEnemy&>(in_rMessage));
			default:												return CSetObjectListener::ProcessMessage(in_rMessage);
			}
		}

		bool ProcMsgNotifyObjectEvent(xgame::MsgNotifyObjectEvent& in_rMessage)
		{
			if (in_rMessage.GetEventType() == 1)
				Flags.set(1);
			
			return true;
		}

		bool ProcMsgHitEventCollision(xgame::MsgHitEventCollision& in_rMessage)
		{
			Flags.set(2);
			return true;
		}

		bool ProcMsgLeaveEventCollision(xgame::MsgLeaveEventCollision& in_rMessage)
		{
			Flags.reset(2);
			return true;
		}

		bool ProcMsgDlcZeldaNoticeStopEnemy(xgame::MsgDlcZeldaNoticeStopEnemy& in_rMessage)
		{
			Flags.set(2);
			return true;
		}

		bool ProcMsgDlcZeldaNoticeActiveEnemy(xgame::MsgDlcZeldaNoticeActiveEnemy& in_rMessage)
		{
			Flags.reset(2);
			return true;
		}
	};
}