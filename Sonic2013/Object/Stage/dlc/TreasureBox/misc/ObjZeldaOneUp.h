#pragma once
namespace app
{
	class ObjZeldaOneUp : public GameObject3D
	{
	private:
		inline static const size_t ms_AnimationCount = 1;
		inline static csl::math::Vector3 ms_Scale = { 0.7f, 0.7f, 0.7f };
		inline static const char* ms_pAnimationName = "IDLE_LOOP";
		inline static const char* ms_pEffectName = "ef_ob_com_yh1_1up";
		inline static const char* ms_pSoundName = "obj_extended";

	public:
		class CInfo
		{
		public:
			int PlayerNo{};
			csl::math::Vector3 Position{};
			csl::math::Quaternion Rotation{};
		};

	private:
		CInfo* pCreateInfo = new CInfo();
		int PlayerNo{};

	public:
		ObjZeldaOneUp(const CInfo& in_rInfo) : GameObject3D()
		{
			PlayerNo = in_rInfo.PlayerNo;
			*pCreateInfo = in_rInfo;
		}

		~ObjZeldaOneUp()
		{
			delete pCreateInfo;
		}

		void AddCallback(GameDocument& in_rDocument) override
		{
			fnd::GOComponent::Create<fnd::GOCVisualModel>(*this);
			fnd::GOComponent::Create<game::GOCAnimationSimple>(*this);
			fnd::GOComponent::Create<game::GOCEffect>(*this);
			fnd::GOComponent::Create<game::GOCSound>(*this);
			fnd::GOComponent::Create<game::GOCMovementComplex>(*this);

			fnd::GOComponent::BeginSetup(*this);

			auto* pInfo = ObjUtil::GetObjectInfo<CObjOneUpInfo>(in_rDocument);
			
			if (auto* pTransform = GetComponent<fnd::GOCTransform>())
			{
				pTransform->SetLocalTranslation({ pCreateInfo->Position + math::Vector3Rotate(pCreateInfo->Rotation, { csl::math::Vector3::UnitY() }) * 11.0f });
				pTransform->SetLocalRotation(pCreateInfo->Rotation);
			}

			if (auto* pVisualModel = GetComponent<fnd::GOCVisualModel>())
			{
				fnd::GOCVisualModel::Description description{};
				description.m_Model = pInfo->Model;
				description.m_Skeleton = pInfo->Skeleton;

				pVisualModel->Setup(description);

				pVisualModel->SetLocalScale(ms_Scale);

				if (auto* pAnimation = GetComponent<game::GOCAnimationSimple>())
				{
					pAnimation->Setup({ ms_AnimationCount });
					pVisualModel->AttachAnimation(pAnimation);

					pAnimation->Add(ms_pAnimationName, pInfo->Animation, game::PlayPolicy::Loop);
					pAnimation->SetAnimation(ms_pAnimationName);
				}
			}

			if (auto* pEffect = GetComponent<game::GOCEffect>())
				game::GOCEffect::SimpleSetup(this, 0, 0);

			game::GOCSound::SimpleSetup(this, 0, 0);

			if (auto* pMovement = GetComponent<game::GOCMovementComplex>())
			{
				if (auto* pMovePopup = pMovement->SetMoveController<game::MovePopup>())
				{
					game::MovePopup::SDesc description{};
					description.Unk1 = 10.0f;
					description.Unk2 = 20.0f;
					description.Unk3 = 11.0f;
					description.Unk4.Set(0);

					pMovePopup->Setup(description);
					pMovePopup->SetBaseTransform(pCreateInfo->Position, pCreateInfo->Rotation);
				}
			}

			fnd::GOComponent::EndSetup(*this);

			if (auto* pSound = GetComponent<game::GOCSound>())
				pSound->Play(ms_pSoundName, 0.0f);
		}

		bool ProcessMessage(fnd::Message& in_rMessage) override
		{
			if (PreProcessMessage(in_rMessage))
				return true;

			switch (in_rMessage.GetType())
			{
			default:													return GameObject3D::ProcessMessage(in_rMessage);
			}
		}

		void Update(const fnd::SUpdateInfo& in_rUpdateInfo) override
		{
			auto* pMovement = GetComponent<game::GOCMovementComplex>();
			if (!pMovement)
				return;

			auto* pController = static_cast<game::MovePopup*>(pMovement->GetMoveController(4));
			if (!pController)
				return;

			if (auto* pPlayerInfo = ObjUtil::GetPlayerInformation(*GetDocument(), PlayerNo))
				pController->SetBaseTransform(pPlayerInfo->Position, pPlayerInfo->Rotation);

			if (pController->Unk8 < 0.5f)
				return;
		
			xgame::MsgTakeObject msg{ xgame::MsgTakeObject::EType::eType_ZeldaOneUp };
			ObjUtil::SendMessageImmToPlayer(*this, PlayerNo, msg);
			if (msg.m_Taken)
			{
				for (size_t i = 0; i < 10; i++)
					ObjUtil::AddScorePlayerAction(*this, "GET_ONE_UP", PlayerNo);
			}

			GetComponent<game::GOCEffect>()->CreateEffect(ms_pEffectName);

			Kill();
		}

		static ObjZeldaOneUp* Create(GameDocument& in_rDocument, const ObjZeldaOneUp::CInfo& in_rInfo);
	};
}