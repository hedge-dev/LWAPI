#pragma once

namespace app
{
	class ObjPopupItem : public ObjPopupItemBase
	{
	public:
		popup_item::SParam Param{};
		fnd::GOCTransform* pTransform{};
		game::MovePopup* pMovePopup{};

		ObjPopupItem(const popup_item::SParam& in_rParam) : ObjPopupItemBase()
		{
			Param = in_rParam;
		}

		void AddCallback(GameDocument* in_pDocument) override
		{
			pTransform = GetComponent<fnd::GOCTransform>();
			
			csl::math::Vector3 movePos{};
			csl::math::Quaternion moveRot{};
			if (Param.Unk6)
			{
				movePos = Param.Position;
				moveRot = Param.Rotation;

				csl::math::Vector3 positionOffset(app::math::Vector3Rotate(Param.Rotation, csl::math::Vector3(csl::math::Vector3::UnitY())) * 11.0f);
				pTransform->SetLocalTranslation(csl::math::Vector3(Param.Position + positionOffset));

				if (Param.Type == popup_item::EType::eType_OneUp)
				{
					auto* pCamera = in_pDocument->pWorld->GetCamera(0);
					pTransform->SetLocalRotation(pCamera->GetInvViewMatrix().GetRotation());
				}
			}
			else
			{
				xgame::MsgGetPosition msgGetPos{ movePos };
				SendMessageImm(Param.PlayerActorID, msgGetPos);

				xgame::MsgGetRotation msgGetRot{ moveRot };
				SendMessageImm(Param.PlayerActorID, msgGetRot);

				csl::math::Vector3 positionOffset(app::math::Vector3Rotate(msgGetRot.GetRotation(), csl::math::Vector3(csl::math::Vector3::UnitY())) * 11.0f);
				pTransform->SetLocalTranslation(csl::math::Vector3(msgGetPos.GetPosition() + positionOffset));

				if (Param.Type == popup_item::EType::eType_OneUp)
				{
					auto* pCamera = in_pDocument->pWorld->GetCamera(0);
					pTransform->SetLocalRotation(pCamera->GetInvViewMatrix().GetRotation());
				}
			}

			fnd::GOComponent::Create<game::GOCMovementComplex>(*this);
			CreateCommonGOC(Param.Type);
			fnd::GOComponent::BeginSetup(*this);
			SetupCommonGOC(in_pDocument);

			if (auto* pMovement = GetComponent<game::GOCMovementComplex>())
			{
				if (pMovePopup = pMovement->SetMoveController<game::MovePopup>())
				{
					game::MovePopup::SDesc description{};
					description.Unk1 = Param.Unk2;
					description.Unk2 = Param.Unk3;
					description.Unk3 = 11.0f;

					if (Param.Type == popup_item::EType::eType_OneUp)
						description.Unk4.set(0);

					pMovePopup->Setup(description);
					pMovePopup->SetBaseTransform(movePos, moveRot);
				}
			}

			fnd::GOComponent::EndSetup(*this);
			OnPopupEvent({ 0 }, Param.Unk5);
		}
		
		void UpdateExtra(const fnd::SUpdateInfo& in_rUpdateInfo) override
		{
			if (!Param.Unk6)
			{
				csl::math::Vector3 position{};
				xgame::MsgGetPosition msgGetPos{ position };
				SendMessageImm(Param.PlayerActorID, msgGetPos);

				csl::math::Quaternion rotation{};
				xgame::MsgGetRotation msgGetRot{ rotation };
				SendMessageImm(Param.PlayerActorID, msgGetRot);
				
				if (!SendMessageImm(Param.PlayerActorID, msgGetPos) || !SendMessageImm(Param.PlayerActorID, msgGetRot))
					Kill();
			
				pMovePopup->SetBaseTransform(msgGetPos.GetPosition(), msgGetRot.GetRotation());
			}

			if (pMovePopup->Unk8 >= Param.Unk4)
			{
				if (SendTakeMessage(Param.PlayerActorID))
					SendScore(ObjUtil::GetPlayerNo(*GetDocument(), Param.PlayerActorID));
				
				OnPopupEvent({ 1 }, true);
			}
		}
	};
}