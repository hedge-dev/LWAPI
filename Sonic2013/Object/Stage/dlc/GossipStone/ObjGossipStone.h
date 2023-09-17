#pragma once

namespace app
{
	class ObjGossipStone : public CSetObjectListener, public TTinyFsm<ObjGossipStone>
	{
	protected:
		inline static const char* ms_pAnimationName = "ACTION";
		inline static const char* ms_pBibeSoundName = "obj_gossipstone_bibe";
		inline static const char* ms_pRocketSoundName = "obj_gossipstone_rocket";
		inline static const char* ms_pCheckSoundName = "obj_gossipstone_check";
		inline static const char* ms_pFogEffectName = "ef_dl3_gossipstone_fog";
		inline static const char* ms_pFireEffectName = "ef_dl3_gossipstone_fire";
		inline static const char* ms_pCountdownSoundNames[] = { "obj_gossipstone_count1", "obj_gossipstone_count2" };
		inline static size_t ms_AnimationCount = 1;
		inline static size_t ms_ShapeCount = 3;
		inline static const float ms_CollisionRadius = 6.0f;
		inline static const float ms_CollisionHeight = 8.0f;
		inline static const float ms_BombCollisionRadius = 8.0f;
		inline static const float ms_BombCollisionHeight = 10.0f;
		inline static const csl::math::Vector3 ms_CollisionOffset = { 0.0f, ms_CollisionHeight / 2.0f, 0.0f };
		inline static const csl::math::Vector3 ms_BombCollisionOffset = { 0.0f, ms_BombCollisionHeight / 2.0f, 0.0f };
		inline static const float ms_CountdownColors[][4] = { { 2.0f, 0.5f, 0.5f, 1.0f }, { 0.55f, 0.55f, 0.55f, 1.0f } };

	public:
		GameObjectHandle<ObjGossipStoneFairy> FairyHandle{};
		Effect::CEffectHandle<hh::eff::CEffectInstance> FogEffectHandle{};
		bool IsDamaged{};
		float ElapsedTime{};
		float RocketTime{};
		float VerticalPosition{};

	public:
		ObjGossipStone() : CSetObjectListener(), TTinyFsm<ObjGossipStone>(&ObjGossipStone::StateIdle)
		{
			
		}

		void AddCallback(GameDocument& in_rDocument) override
		{
			fnd::GOComponent::Create<fnd::GOCVisualModel>(*this);
			fnd::GOComponent::Create<game::GOCAnimationSimple>(*this);
			fnd::GOComponent::Create<game::GOCEffect>(*this);
			fnd::GOComponent::Create<game::GOCSound>(*this);
			fnd::GOComponent::Create<game::GOCCollider>(*this);

			fnd::GOComponent::BeginSetup(*this);

			auto* pInfo = ObjUtil::GetObjectInfo<ObjGossipStoneInfo>(in_rDocument);
			auto* pParam = GetAdapter()->GetData<SGossipStoneParam>();

			if (auto* pVisualGoc = GetComponent<fnd::GOCVisualModel>())
			{
				fnd::GOCVisualModel::Description description{};
				description.m_Model = pInfo->Model;
				description.m_Skeleton = pInfo->Skeleton;

				pVisualGoc->Setup(description);

				if (auto* pAnimationGoc = GetComponent<game::GOCAnimationSimple>())
				{
					pAnimationGoc->Setup({ ms_AnimationCount });
					pAnimationGoc->Add(ms_pAnimationName, pInfo->Animation, game::PlayPolicy::Once);

					pVisualGoc->AttachAnimation(pAnimationGoc);
				}
			}

			if (auto* pColliderGoc = GetComponent<game::GOCCollider>())
			{
				pColliderGoc->Setup({ ms_ShapeCount });

				game::ColliSphereShapeCInfo playerCheckCollisionInfo{};
				playerCheckCollisionInfo.m_ShapeType = game::CollisionShapeType::ShapeType::ShapeType_Sphere;
				playerCheckCollisionInfo.m_MotionType = game::PhysicsMotionType::MotionType::MotionType_VALUE2;
				playerCheckCollisionInfo.m_Unk2 |= 1;
				playerCheckCollisionInfo.m_Radius = pParam->CheckRadius;
				playerCheckCollisionInfo.m_ShapeID = 0;
				ObjUtil::SetupCollisionFilter(ObjUtil::EFilter::eFilter_Unk7, playerCheckCollisionInfo);
				pColliderGoc->CreateShape(playerCheckCollisionInfo);

				game::ColliCapsuleShapeCInfo bombCollisionInfo{};
				bombCollisionInfo.m_ShapeType = game::CollisionShapeType::ShapeType::ShapeType_Capsule;
				bombCollisionInfo.m_MotionType = game::PhysicsMotionType::MotionType::MotionType_VALUE0;
				bombCollisionInfo.m_Unk2 |= 1;
				bombCollisionInfo.m_Radius = ms_BombCollisionRadius;
				bombCollisionInfo.m_Height = ms_BombCollisionHeight;
				bombCollisionInfo.m_ShapeID = 1;
				ObjUtil::SetupCollisionFilter(ObjUtil::EFilter::eFilter_Default, bombCollisionInfo);
				bombCollisionInfo.SetLocalPosition(ms_BombCollisionOffset);
				pColliderGoc->CreateShape(bombCollisionInfo);

				game::ColliCapsuleShapeCInfo collisionInfo{};
				collisionInfo.m_ShapeType = game::CollisionShapeType::ShapeType::ShapeType_Capsule;
				collisionInfo.m_MotionType = game::PhysicsMotionType::MotionType::MotionType_VALUE0;
				collisionInfo.m_Unk2 |= 0x100;
				collisionInfo.m_Unk3 = 0x40053;
				collisionInfo.m_Radius = ms_CollisionRadius;
				collisionInfo.m_Height = ms_CollisionHeight;
				collisionInfo.m_ShapeID = 2;
				collisionInfo.SetLocalPosition(ms_CollisionOffset);
				pColliderGoc->CreateShape(collisionInfo);
			}

			if (GetComponent<game::GOCEffect>())
				game::GOCEffect::SimpleSetup(this, 2, 0);

			game::GOCSound::SimpleSetup(this, 0, 0);

			fnd::GOComponent::EndSetup(*this);

			InitFSM();
		}

		bool ProcessMessage(fnd::Message& in_rMessage) override
		{
			if (PreProcessMessage(in_rMessage))
				return true;

			switch (in_rMessage.GetType())
			{
			case xgame::MsgDamage::MessageID:							return ProcMsgDamage(static_cast<xgame::MsgDamage&>(in_rMessage));
			case xgame::MsgHitEventCollision::MessageID:				return ProcMsgHitEventCollision(static_cast<xgame::MsgHitEventCollision&>(in_rMessage));
			default:													return CSetObjectListener::ProcessMessage(in_rMessage);
			}
		}

		bool ProcMsgDamage(xgame::MsgDamage& in_rMessage)
		{
			auto* pPlayerInfo = ObjUtil::GetPlayerInformation(*GetDocument(), 0);
			if (!pPlayerInfo)
				return false;

			if (pPlayerInfo->PixieNo == static_cast<Game::EPhantomType>(-1))
			{
				if (in_rMessage.m_Unk3.dot(GetComponent<fnd::GOCTransform>()->m_Frame.m_Unk3.m_Mtx.GetColumn(1)) >= 0.9f)
					return false;
			}
			
			DispatchFSM(TiFsmEvent_t::CreateMessage(in_rMessage));
			
			in_rMessage.SetReply(in_rMessage.m_Unk2, false, { -in_rMessage.m_Unk3 });
			in_rMessage.m_ReplyStatus.set(0);

			if (pPlayerInfo->PixieNo != static_cast<Game::EPhantomType>(-1))
				in_rMessage.m_ReplyStatus.set(5);
			
			return true;
		}

		bool ProcMsgHitEventCollision(xgame::MsgHitEventCollision& in_rMessage)
		{
			if (ObjUtil::CheckShapeUserID(in_rMessage.m_pSelf, 0))
				return OnSnapshot();

			if (!ObjUtil::CheckShapeUserID(in_rMessage.m_pSelf, 1))
				return false;

			auto* pPlayerInfo = ObjUtil::GetPlayerInformation(*GetDocument(), 0);
			if (!pPlayerInfo || pPlayerInfo->IsOnGround)
				return false;

			csl::math::Vector3 upVector = GetComponent<fnd::GOCTransform>()->m_Frame.m_Unk3.m_Mtx.GetColumn(1);
			csl::math::Vector3 contactNormal { -(*in_rMessage.GetContactPointNormal()) };

			csl::math::Vector3 velocity{ contactNormal - csl::math::Vector3(upVector * upVector.dot(contactNormal)) };
			math::Vector3NormalizeZero(velocity, &velocity);

			xgame::MsgAppeareKnockback msg{};
			msg.Velocity = { csl::math::Vector3(upVector * upVector.dot(contactNormal)) + csl::math::Vector3(velocity * 30.0f * 2.0f) };
			SendMessageImm(in_rMessage.m_Sender, msg);
			
			DispatchFSM(TiFsmEvent_t::CreateMessage(in_rMessage));
			return true;
		}

		void Update(const fnd::SUpdateInfo& in_rUpdateInfo) override
		{
			DispatchFSM(TiFsmEvent_t::CreateUpdate(in_rUpdateInfo.deltaTime));
		}

		bool OnSnapshot()
		{
			bool isFairyValid = FairyHandle.IsValid();
			if (!isFairyValid)
			{
				ObjGossipStoneFairy::CInfo createInfo{};
				createInfo.TransformMtx = GetComponent<fnd::GOCTransform>()->m_Frame.m_Unk3.m_Mtx;
				auto* pFairyObject = ObjGossipStoneFairy::Create(createInfo);
				if (pFairyObject)
				{
					GetDocument()->AddGameObject(pFairyObject);
					FairyHandle = pFairyObject;
				}

				xgame::MsgDlcZeldaHeartAllRecovery msg{};
				ObjUtil::SendMessageImmToGameActor(*this, msg);

				GetComponent<game::GOCSound>()->Play3D(ms_pCheckSoundName, 0.0f);
			}

			return isFairyValid;
		}

		void ChangeState(TiFsmState_t in_state)
		{
			FSM_TRAN(in_state);
		}

		TiFsmState_t StateIdle(const TiFsmEvent_t& in_rEvent)
		{
			switch (in_rEvent.getSignal())
			{
			case TiFSM_SIGNAL_UPDATE:
			case TiFSM_SIGNAL_ENTER:
			case TiFSM_SIGNAL_LEAVE:
			{
				break;
			}
			case TiFSM_SIGNAL_MESSAGE:
			{
				auto& msg = in_rEvent.getMessage();

				switch (msg.GetType())
				{
				case xgame::MsgHitEventCollision::MessageID:
				{
					ChangeState(&ObjGossipStone::StateShake);

					msg.m_Handled = true;
					break;
				}
				case xgame::MsgDamage::MessageID:
				{
					auto* pPlayerInfo = ObjUtil::GetPlayerInformation(*GetDocument(), 0);

					if (reinterpret_cast<xgame::MsgDamage&>(msg).m_Bonus.m_Unk1 == 3 && pPlayerInfo && pPlayerInfo->PixieNo == Game::EPhantomType::PHANTOM_BOMB)
						ChangeState(&ObjGossipStone::StateCountdown);
					else
						ChangeState(&ObjGossipStone::StateShake);

					msg.m_Handled = true;
					return {};
				}
				default:
					return FSM_TOP();
				}
				
				break;
			}
			}

			return FSM_TOP();
		}
		
		TiFsmState_t StateShake(const TiFsmEvent_t& in_rEvent)
		{
			switch (in_rEvent.getSignal())
			{
			case TiFSM_SIGNAL_UPDATE:
			{
				if (GetComponent<game::GOCAnimationSimple>()->IsFinished())
				{
					if (IsDamaged)
					{
						ChangeState(&ObjGossipStone::StateCountdown);
						return {};
					}

					ChangeState(&ObjGossipStone::StateIdle);
				}

				return {};
			}
			case TiFSM_SIGNAL_ENTER:
			{
				GetComponent<game::GOCAnimationSimple>()->SetAnimation(ms_pAnimationName);
				GetComponent<game::GOCSound>()->Play3D(ms_pBibeSoundName, 0.0f);
				
				return{};
			}
			case TiFSM_SIGNAL_LEAVE:
			{
				break;
			}
			case TiFSM_SIGNAL_MESSAGE:
			{
				auto& msg = in_rEvent.getMessage();

				switch (msg.GetType())
				{
				case xgame::MsgHitEventCollision::MessageID:
				{
					ChangeState(&ObjGossipStone::StateShake);

					msg.m_Handled = true;
					break;
				}
				case xgame::MsgDamage::MessageID:
				{
					xgame::MsgDamage msg = reinterpret_cast<xgame::MsgDamage&>(in_rEvent.getMessage());
					auto* pPlayerInfo = ObjUtil::GetPlayerInformation(*GetDocument(), 0);

					if (reinterpret_cast<xgame::MsgDamage&>(msg).m_Bonus.m_Unk1 == 3 && pPlayerInfo && pPlayerInfo->PixieNo == Game::EPhantomType::PHANTOM_BOMB)
					{
						IsDamaged = true;
					}
					else
					{
						if (!IsDamaged)
						{
							GetComponent<game::GOCAnimationSimple>()->SetAnimation(ms_pAnimationName);
							GetComponent<game::GOCSound>()->Play3D(ms_pBibeSoundName, 0.0f);
						}
					}

					msg.m_Handled = true;
					break;
				}
				default:
					return FSM_TOP();
				}

				return {};
			}
			default:
				return FSM_TOP();
			}

			return FSM_TOP();
		}

		TiFsmState_t StateCountdown(const TiFsmEvent_t& in_rEvent)
		{
			switch (in_rEvent.getSignal())
			{
			case TiFSM_SIGNAL_UPDATE:
			{
				float oldTime = ElapsedTime;
				ElapsedTime += in_rEvent.getFloat();

				if (ElapsedTime >= 5)
				{
					ChangeState(&ObjGossipStone::StateRocket);

					return {};
				}

				if ((int)oldTime < (int)ElapsedTime)
				{
					auto* pVisualGoc = GetComponent<fnd::GOCVisualModel>();
					auto* pSoundGoc = GetComponent<game::GOCSound>();

					if ((int)ElapsedTime == 4)
					{
						pVisualGoc->SetMaterialColor(ms_CountdownColors[0]);
						pSoundGoc->Play(ms_pCountdownSoundNames[0], 0.0f);
					}
					else
					{
						pVisualGoc->SetMaterialColor(ms_CountdownColors[1]);
						pSoundGoc->Play(ms_pCountdownSoundNames[1], 0.0f);
					}

					return {};
				}

				if (oldTime - (int)oldTime < 0.3f && ElapsedTime - (int)ElapsedTime >= 0.3f)
				{
					GetComponent<fnd::GOCVisualModel>()->SetMaterialColor(nullptr);
					if ((int)ElapsedTime == 4)
						GetComponent<game::GOCEffect>()->CreateEffectLoop(&FogEffectHandle, ms_pFogEffectName);
				}

				return {};
			}
			case TiFSM_SIGNAL_ENTER:
			{
				ObjUtil::SetEnableColliShape(GetComponent<game::GOCCollider>(), 0, false);
				
				ElapsedTime = 0.0f;

				return {};
			}
			case TiFSM_SIGNAL_LEAVE:
			{
				return {};
			}
			}

			return FSM_TOP();
		}

		TiFsmState_t StateRocket(const TiFsmEvent_t& in_rEvent)
		{
			switch (in_rEvent.getSignal())
			{
			case TiFSM_SIGNAL_UPDATE:
			{
				RocketTime += in_rEvent.getFloat();
				VerticalPosition += in_rEvent.getFloat() * 100.0f;

				auto* pTransform = GetComponent<fnd::GOCTransform>();
				
				pTransform->SetLocalTranslation(pTransform->m_Frame.m_Unk3.m_Mtx * csl::math::Vector4(0.0f, VerticalPosition * in_rEvent.getFloat(), 0.0f, 1.0f));
				if (RocketTime >= 5.0f)
				{
					SetStatusRetire();
					Kill();
				}

				return {};
			}
			case TiFSM_SIGNAL_ENTER:
			{
				RocketTime = 0.0f;
				VerticalPosition = 0.0f;
				FogEffectHandle.Stop(false);

				Effect::CEffectHandle<hh::eff::CEffectInstance> fireEffectHandle{};
				GetComponent<game::GOCEffect>()->CreateEffectLoop(&FogEffectHandle, ms_pFireEffectName);
				GetComponent<game::GOCSound>()->Play3D(ms_pRocketSoundName, 0.0f);
				
				return {};
			}
			case TiFSM_SIGNAL_LEAVE:
			{
				return {};
			}
			}

			return FSM_TOP();
		}

		TiFsmState_t StateLost(const TiFsmEvent_t& in_rEvent)
		{
			switch (in_rEvent.getSignal())
			{
			case TiFSM_SIGNAL_ENTER:
			case TiFSM_SIGNAL_LEAVE:
				return {};
			}

			return FSM_TOP();
		}
	};
}