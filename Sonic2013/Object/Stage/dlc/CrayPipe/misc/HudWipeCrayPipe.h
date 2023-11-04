#pragma once

namespace app::HUD
{
	class HudWipeCrayPipe : public GameObject
	{
	protected:
		game::HudLayerController* pLayerController;

	public:
		HudWipeCrayPipe() : GameObject()
		{
			SetObjectCategory(11);
		}

	protected:
		void AddCallback(GameDocument* in_pDocument) override
		{
			fnd::GOComponent::Create<game::GOCHud>(*this);

			fnd::GOComponent::BeginSetup(*this);

			if (auto* pHudGoc = GetComponent<game::GOCHud>())
			{
				pHudGoc->Setup({ "HudMissionBanner", 8, 9, -21, 2, 2048, 0 });

				SurfRide::ReferenceCount<SurfRide::Project> rcProject{};
				pHudGoc->SetupProject(&rcProject, "ui_wipe_zdlc02", ObjUtil::GetPackFile("ui_zdlc02_gamemodestage.pac"));
				pLayerController = pHudGoc->CreateLayerController({ rcProject }, "ui_wipe_zdlc02", "wipe_mask", 0);

				pLayerController->ReserveAnimation("Outro_Anim", game::HudPlayPolicy::eHudPlayPolicy_Once, 0);
				pLayerController->PlayReservedAnimation();
			}

			fnd::GOComponent::EndSetup(*this);
		}

		void Update(const fnd::SUpdateInfo& in_rUpdateInfo) override
		{
			if (!pLayerController)
				return;
		
			if (!pLayerController->IsEndReservedAnimation())
				return;
		
			Kill();
		}
	};
}
