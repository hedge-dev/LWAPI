#pragma once

namespace app
{
	class Event
	{
	public:
		int Unk1{};
	};

	class ObjPopupItemBase : public GameObject3D
	{
	private:
		inline static const char* ms_pEffectNames[] = { "ef_ob_com_yh1_ringget", "ef_ob_com_yh1_ringget_s", "ef_ob_com_yh1_1up", "ef_ob_com_wt1_battleitem_get" };
		inline static const char* ms_pWispEffectNames[] = { "ef_ob_com_wt1_wisp_la_locus", "ef_ob_com_wt1_wisp_ea_locus", "ef_ob_com_wt1_wisp_as_locus", "ef_ob_com_wt1_wisp_dr_locus",
			"ef_ob_com_wt1_wisp_ro_locus", "ef_ob_com_wt1_wisp_rh_locus", "ef_ob_com_wt1_wisp_ho_locus", "ef_ob_com_wt1_wisp_qu_locus" };
		inline static const char* ms_pSoundNames[] = { "obj_ring", "obj_superring", "obj_extended" };
		inline static const char* ms_pScoreNames[] = { "GET_RING", "GET_SUPER_RING", "GET_ONE_UP", "GET_SPPED_UP", "GET_INVINCIBLE", "GET_SLOWDOWN",
			"GET_MISSILE", "GET_WARP", "GET_STEAL_RING", "GET_THUNDER_BARRIER", "GET_CHANGE_RING", "GET_PHANTOM" };
		inline static const size_t ms_TakeType[] = { xgame::MsgTakeObject::eType_Ring, xgame::MsgTakeObject::eType_SuperRing, xgame::MsgTakeObject::eType_OneUp,
			xgame::MsgTakeObject::eType_SpeedUp, xgame::MsgTakeObject::eType_Invincibility, xgame::MsgTakeObject::eType_SlowDown, -1,
			xgame::MsgTakeObject::eType_Warp, xgame::MsgTakeObject::eType_StealRing, xgame::MsgTakeObject::eType_ThunderBarrier, xgame::MsgTakeObject::eType_ChangeRing,
			Game::EPhantomType::PHANTOM_LASER, Game::EPhantomType::PHANTOM_EAGLE, Game::EPhantomType::PHANTOM_ASTEROID, Game::EPhantomType::PHANTOM_DRILL,
			Game::EPhantomType::PHANTOM_ROCKET, Game::EPhantomType::PHANTOM_RHYTHM, Game::EPhantomType::PHANTOM_HOVER, Game::EPhantomType::PHANTOM_QUAKE };

	public:
		popup_item::EType Type{ static_cast<popup_item::EType>(-1) };
		Effect::CEffectHandle<hh::eff::CEffectInstance> EffectHandle{};

		ObjPopupItemBase() : GameObject3D()
		{
			
		}

		void Update(const fnd::SUpdateInfo& in_rUpdateInfo) override
		{
			UpdateExtra(in_rUpdateInfo);
		}

		virtual void UpdateExtra(const fnd::SUpdateInfo& in_rUpdateInfo)
		{

		}

		void CreateCommonGOC(popup_item::EType in_type)
		{
			Type = in_type;
			
			fnd::GOComponent::Create<fnd::GOCVisualModel>(*this);
			switch (Type)
			{
			case 0:
			case 1:
			case 5:
			case 6:
			case 8:
			case 9:
			case 10:
				break;
			default:
				fnd::GOComponent::Create<game::GOCAnimationSimple>(*this);
				break;
			}

			fnd::GOComponent::Create<game::GOCSound>(*this);
			fnd::GOComponent::Create<game::GOCEffect>(*this);
		}

		void CreateEndEffect()
		{
			if (auto* pEffect = GetComponent<game::GOCEffect>())
			{
				if (Type >= 3)
					pEffect->CreateEffect(ms_pEffectNames[3]);
				else
					pEffect->CreateEffect(ms_pEffectNames[Type]);
			}
		}

		popup_item::EType GetType() const
		{
			return Type;
		}

		bool IsPhantom() const
		{
			return Type - 11 < 8;
		}

		void OnStartPopupPhantom()
		{
			if (!IsPhantom())
				return;
		
			if (auto* pAnimation = GetComponent<game::GOCAnimationSimple>())
				pAnimation->SetAnimation("RELEASE_LOOP");
		
			Effect::CEffectHandle<hh::eff::CEffectInstance> effectHandle{};
			if (auto* pEffect = GetComponent<game::GOCEffect>())
				pEffect->CreateEffectLoop(&effectHandle, ms_pWispEffectNames[Type - 11]);
		}

		void PlayTakeSE()
		{
			if (auto* pSound = GetComponent<game::GOCSound>())
				pSound->Play(ms_pSoundNames[Type], 0.0f);
		}

		void SendScore(int in_playerNo)
		{
			if (IsPhantom())
				ObjUtil::AddScorePlayerAction(*this, ms_pScoreNames[11], in_playerNo);
			else
				ObjUtil::AddScorePlayerAction(*this, ms_pScoreNames[Type], in_playerNo);
			
		}

		bool SendTakeMessage(size_t in_playerActorID)
		{
			if (Type < 0)
				return false;
		
			if (ms_TakeType[Type] == -1)
				return true;

			if (IsPhantom())
			{
				if (Type == 18)
				{
					xgame::MsgPLRequestChangePhantom message{};
					message.Unk1 = 1;
					message.Unk2 = 8;
				
					SendMessageImm(in_playerActorID, message);
					return message.Changed;
				}
				
				xgame::MsgTakePixie message{ (Game::EPhantomType)ms_TakeType[Type], 7.0f };
				SendMessageImm(in_playerActorID, message);
				return message.Taken;
			}

			xgame::MsgTakeObject message{ (xgame::MsgTakeObject::EType)ms_TakeType[Type] };
			SendMessageImm(in_playerActorID, message);
			return message.m_Taken;
		}

		void SetupCommonGOC(GameDocument* in_pDocument)
		{
			switch (Type)
			{
			case popup_item::EType::eType_Ring:
			case popup_item::EType::eType_SuperRing:
			{
				auto* pInfo = ObjUtil::GetObjectInfo<CSharedObjInfo>(*in_pDocument);

				if (auto* pVisualModel = GetComponent<fnd::GOCVisualModel>())
				{
					fnd::GOCVisualModel::Description description{};
					if (Type == popup_item::EType::eType_SuperRing)
					{
						description.m_Model = pInfo->SuperRingModel;
						pVisualModel->SetLocalScale({ 0.7f, 0.7f, 0.7f });
					}
					else
					{
						description.m_Model = pInfo->RingModel;
					}
					
					pVisualModel->Setup(description);
				}
				break;
			}
			case popup_item::EType::eType_OneUp:
			{
				auto* pInfo = ObjUtil::GetObjectInfo<CObjOneUpInfo>(*in_pDocument);

				if (auto* pVisualModel = GetComponent<fnd::GOCVisualModel>())
				{
					fnd::GOCVisualModel::Description description{};
					description.m_Model = pInfo->Model;
					description.m_Skeleton = pInfo->Skeleton;

					pVisualModel->SetLocalScale({ 0.7f, 0.7f, 0.7f });
					pVisualModel->Setup(description);

					if (auto* pAnimation = GetComponent<game::GOCAnimationSimple>())
					{
						game::GOCAnimationSimple::Description animDescription{ 1 };

						pAnimation->Setup(animDescription);
						pVisualModel->AttachAnimation(pAnimation);

						pAnimation->Add("IDLE_LOOP", pInfo->Animation, game::PlayPolicy::Loop);
						pAnimation->SetAnimation("IDLE_LOOP");
					}
				}
				break;
			}
			case popup_item::EType::eType_SpeedUp:
			case popup_item::EType::eType_Invincible:
			case popup_item::EType::eType_Warp:
			{
				auto* pInfo = ObjUtil::GetObjectInfo<ObjItemBoxInfo>(*in_pDocument);

				if (auto* pVisualModel = GetComponent<fnd::GOCVisualModel>())
				{
					fnd::GOCVisualModel::Description description{};
					if (popup_item::EType::eType_SpeedUp)
						description.m_Model = pInfo->ItemModelContainer.Models[0];
					else if (popup_item::EType::eType_Invincible)
						description.m_Model = pInfo->ItemModelContainer.Models[1];
					else if (popup_item::EType::eType_Warp)
						description.m_Model = pInfo->ItemModelContainer.Models[2];

					pVisualModel->Setup(description);

					if (auto* pAnimation = GetComponent<game::GOCAnimationSimple>())
					{
						game::GOCAnimationSimple::Description animDescription{ 1 };

						pAnimation->Setup(animDescription);
						pVisualModel->AttachAnimation(pAnimation);

						if (popup_item::EType::eType_SpeedUp)
							pAnimation->Add("IDLE_LOOP", pInfo->ItemAnimationContainer.Animations[0], game::PlayPolicy::Loop);
						else if (popup_item::EType::eType_Invincible)
							pAnimation->Add("IDLE_LOOP", pInfo->ItemAnimationContainer.Animations[1], game::PlayPolicy::Loop);
						else if (popup_item::EType::eType_Warp)
							pAnimation->Add("IDLE_LOOP", pInfo->ItemAnimationContainer.Animations[2], game::PlayPolicy::Loop);
						
						pAnimation->SetAnimation("IDLE_LOOP");
					}
				}
				break;
			}
			case popup_item::EType::eType_SlowDown:
			case popup_item::EType::eType_Missile:
			case popup_item::EType::eType_StealRing:
			case popup_item::EType::eType_ThunderBarrier:
			case popup_item::EType::eType_ChangeRing:
			{
				auto* pInfo = ObjUtil::GetObjectInfo<ObjQuestionItemBoxInfo>(*in_pDocument);

				if (auto* pVisualModel = GetComponent<fnd::GOCVisualModel>())
				{
					fnd::GOCVisualModel::Description description{};
					description.m_Model = pInfo->ItemModelContainer.Models[Type - 1];

					pVisualModel->Setup(description);

					if (auto* pAnimation = GetComponent<game::GOCAnimationSimple>())
					{
						game::GOCAnimationSimple::Description animDescription{ 1 };

						pAnimation->Setup(animDescription);
						pVisualModel->AttachAnimation(pAnimation);

						if (popup_item::EType::eType_SpeedUp)
							pAnimation->Add("IDLE_LOOP", pInfo->ItemAnimationContainer.Animations[0], game::PlayPolicy::Loop);
						else if (popup_item::EType::eType_Invincible)
							pAnimation->Add("IDLE_LOOP", pInfo->ItemAnimationContainer.Animations[1], game::PlayPolicy::Loop);
						else if (popup_item::EType::eType_Warp)
							pAnimation->Add("IDLE_LOOP", pInfo->ItemAnimationContainer.Animations[2], game::PlayPolicy::Loop);

						pAnimation->SetAnimation("IDLE_LOOP");
					}
				}
				break;
			}
			case popup_item::EType::eType_PhantomLaser:
			case popup_item::EType::eType_PhantomEagle:
			case popup_item::EType::eType_PhantomAsteroid:
			case popup_item::EType::eType_PhantomDrill:
			case popup_item::EType::eType_PhantomRocket:
			case popup_item::EType::eType_PhantomRhythm:
			case popup_item::EType::eType_PhantomHover:
			{
				auto* pInfo = ObjUtil::GetObjectInfo<CObjPixieInfo>(*in_pDocument);

				if (auto* pVisualModel = GetComponent<fnd::GOCVisualModel>())
				{
					fnd::GOCVisualModel::Description description{};
					description.m_Model = pInfo->ModelContainer.Models[Type - 11];
					description.m_Skeleton = pInfo->SkeletonContainer.Skeletons[Type - 11];

					pVisualModel->Setup(description);

					if (Type == popup_item::EType::eType_PhantomRocket)
						pVisualModel->SetTexSrtAnimation({ pInfo->DrillTextureAnimation, 1 });
					
					if (auto* pAnimation = GetComponent<game::GOCAnimationSimple>())
					{
						game::GOCAnimationSimple::Description animDescription{ 2 };

						pAnimation->Setup(animDescription);
						pVisualModel->AttachAnimation(pAnimation);

						pAnimation->Add("IDLE_LOOP", pInfo->AnimationInboxContainer.Animations[Type - 11], game::PlayPolicy::Loop);
						pAnimation->Add("RELEASE_LOOP", pInfo->AnimationReleaseContainer.Animations[Type - 11], game::PlayPolicy::Loop);

						pAnimation->SetAnimation("IDLE_LOOP");
					}
				}
				break;
			}
			case popup_item::EType::eType_PhantomQuake:
			{
				auto* pInfo = ObjUtil::GetObjectInfo<ObjQuestionItemBoxInfo>(*in_pDocument);

				if (auto* pVisualModel = GetComponent<fnd::GOCVisualModel>())
				{
					fnd::GOCVisualModel::Description description{};
					description.m_Model = pInfo->ItemModelContainer.Models[1];
					description.m_Skeleton = pInfo->ItemSkeletonContainer.Skeletons[1];
					
					pVisualModel->Setup(description);

					if (auto* pAnimation = GetComponent<game::GOCAnimationSimple>())
					{
						game::GOCAnimationSimple::Description animDescription{ 1 };

						pAnimation->Setup(animDescription);
						pVisualModel->AttachAnimation(pAnimation);

						pAnimation->Add("RELEASE_LOOP", pInfo->ItemAnimationContainer.Animations[1], game::PlayPolicy::Loop);
					}
				}
				break;
			}
			}

			if (GetComponent<game::GOCEffect>()) game::GOCEffect::SimpleSetup(this, 1, false);
			game::GOCSound::SimpleSetup(this, 0, 0);
		}

		void OnPopupEvent(Event in_event, bool in_unk)
		{
			if (in_event.Unk1 == 1)
			{
				if (in_unk)
					CreateEndEffect();

				Kill();
			}
			else if (in_event.Unk1 == 0)
			{
				if (in_unk)
					PlayTakeSE();

				OnStartPopupPhantom();
			}
		}
	};
}