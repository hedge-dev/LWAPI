#pragma once

namespace app
{
	class ObjZeldaPopupItem : public GameObject3D
	{
	private:
		inline static size_t ms_AnimCount = 1;
		inline static size_t ms_RupeeToAnimalCounts[] = { 1, 5, 20, 50, 200 };
		inline static const char* ms_pEffectName = "ef_dl3_itemget_locus";
		inline static const char* ms_pSoundNames[] = { "obj_zeldarupy_get", "obj_zeldaheart_get" };

	public:
		const csl::math::Matrix34* Mtx{};
		ZeldaPopupItemType Type{};
		uint PlayerNo{};
		Effect::CEffectHandle<hh::eff::CEffectInstance> EffectHandle{};

		ObjZeldaPopupItem(const zelda_popupitem::ZeldaPopupItemCinfo* in_rCreateInfo) : GameObject3D()
		{
			Mtx = &in_rCreateInfo->Matrix;
			Type = in_rCreateInfo->Type;
			PlayerNo = in_rCreateInfo->PlayerNo;
		}

	protected:
		void AddCallback(GameDocument& in_rDocument) override
		{
			fnd::GOComponent::Create<game::GOCAnimationSimple>(*this);
			fnd::GOComponent::Create<fnd::GOCVisualModel>(*this);
			fnd::GOComponent::Create<game::GOCEffect>(*this);
			fnd::GOComponent::Create<game::GOCSound>(*this);

			auto* pInfo = ObjUtil::GetObjectInfo<ObjZeldaPopupItemInfo>(in_rDocument);
			pInfo->SetPopupItem(this);
			
			fnd::GOComponent::BeginSetup(*this);

			if (auto* pTransform = GetComponent<fnd::GOCTransform>())
			{
				pTransform->SetLocalTranslation(Mtx->GetTransVector());
				pTransform->SetLocalRotation(Mtx->GetRotation());
			}

			if (auto* pVisualModel = GetComponent<fnd::GOCVisualModel>())
			{
				fnd::GOCVisualModel::Description description{};
				description.m_Model = pInfo->Models[(int)Type];
				description.m_Skeleton = pInfo->Skeletons[0];
				if (Type == ZeldaPopupItemType::eZeldaPopupItemType_Heart)
					description.m_Skeleton = pInfo->Skeletons[1];
				description.field_0C |= 0x400000u;

				pVisualModel->Setup(description);

				if (auto* pAnimation = GetComponent<game::GOCAnimationSimple>())
				{
					game::GOCAnimationSimple::Description animDesc{ ms_AnimCount };
					pAnimation->Setup(animDesc);
					
					pVisualModel->AttachAnimation(pAnimation);
					
					if (Type != ZeldaPopupItemType::eZeldaPopupItemType_Heart)
						pAnimation->Add("POPUP", pInfo->Animations[0], game::PlayPolicy::Once);
					else
						pAnimation->Add("POPUP", pInfo->Animations[1], game::PlayPolicy::Once);

					pAnimation->SetAnimation("POPUP");
				}
			}

			game::GOCSound::SimpleSetup(this, 0, 0);
			if (GetComponent<game::GOCEffect>()) game::GOCEffect::SimpleSetup(this, 1, true);

			fnd::GOComponent::EndSetup(*this);

			if (auto* pSound = GetComponent<game::GOCSound>())
			{
				if (Type < ZeldaPopupItemType::eZeldaPopupItemType_Heart)
					pSound->Play(ms_pSoundNames[0], 0.0f);
				else
					pSound->Play(ms_pSoundNames[1], 0.0f);
			}
			
			if (auto* pEffect = GetComponent<game::GOCEffect>())
			{
				game::EffectCreateInfo effectInfo{};
				effectInfo.m_pName = ms_pEffectName;
				effectInfo.m_Unk1 = 1.0f;
				effectInfo.m_Unk2 = 1;
				effectInfo.m_pVisual = GetComponent<fnd::GOCVisualModel>();
				effectInfo.m_pBoneName = "Body";
				effectInfo.m_Unk9 = -1;

				pEffect->CreateEffectLoopEx(&EffectHandle, effectInfo);
			}

			if (Type >= ZeldaPopupItemType::eZeldaPopupItemType_Heart)
			{
				xgame::MsgDlcZeldaTakeHeart message{};
				ObjUtil::SendMessageImmToGameActor(*this, message);
			}
			else
			{
				xgame::MsgGetAnimal message{ ms_RupeeToAnimalCounts[Type] };
				ObjUtil::SendMessageImmToGameActor(*this, message);
			}
		}

		void Update(const fnd::SUpdateInfo& in_rUpdateInfo) override
		{
			if (auto* playerInfo = ObjUtil::GetPlayerInformation(*GetDocument(), PlayerNo))
			{
				if (auto* pTransform = GetComponent<fnd::GOCTransform>())
				{
					pTransform->SetLocalTranslation(playerInfo->Position);
					pTransform->SetLocalRotation(playerInfo->Rotation);
				}
			}

			if (auto* pAnimation = GetComponent<game::GOCAnimationSimple>())
			{
				if (pAnimation->IsFinished())
					toKill();
			}
		}

	public:
		void EndPopup()
		{
			toKill();
		}
			
	private:
		void toKill()
		{
			if (EffectHandle.IsValid())
				EffectHandle.Stop(false);
			
			Kill();
		}
	};

	inline void ObjZeldaPopupItemInfo::SetPopupItem(ObjZeldaPopupItem* in_pObject)
	{
		if (auto* pObject = PopupHandle.Get())
			pObject->EndPopup();

		PopupHandle = in_pObject;
	}
}