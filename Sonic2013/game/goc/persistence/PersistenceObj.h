#pragma once

namespace app::game
{
	class PersistenceObj : public GameObject3D
	{
	public:
		struct CreateInfo
		{
			app::fnd::GOCVisualModel* pVisualGoc{};
			csl::math::Vector3 MaterialColor{};
		};

		CreateInfo* pCreateInfo{};

		PersistenceObj(CreateInfo& in_rCreateInfo) : GameObject3D(), pCreateInfo(&in_rCreateInfo)
		{
			SetObjectCategory(8);
		}

		void AddCallback(GameDocument* in_pDocument) override
		{
			fnd::GOComponent::Create<fnd::GOCVisualModel>(*this);

			fnd::GOComponent::BeginSetup(*this);

			auto* pTransformGoc = GetComponent<fnd::GOCTransform>();
			pTransformGoc->SetLocalTranslation(pCreateInfo->pVisualGoc->pFrame->Unk3.GetTranslation());
			pTransformGoc->SetLocalRotation(pCreateInfo->pVisualGoc->pFrame->Unk3.GetRotationQuaternion());

			auto* pVisualGoc = GetComponent<fnd::GOCVisualModel>();
			fnd::GOCVisualModel::Description description{};
			description.Model = pCreateInfo->pVisualGoc->GetModelResource();
			description.Skeleton = pCreateInfo->pVisualGoc->GetSkeletonResource();

			pVisualGoc->Setup(description);

			pVisualGoc->CopyPose(*pCreateInfo->pVisualGoc);

			float color[4]{ 0.0f, 0.0f, 0.0f, 1.0f };
			color[0] = pCreateInfo->MaterialColor.x();
			color[1] = pCreateInfo->MaterialColor.y();
			color[2] = pCreateInfo->MaterialColor.z();
			pVisualGoc->SetMaterialColor(color);

			pVisualGoc->SetLocalScale(pCreateInfo->pVisualGoc->Transform.Scale);

			fnd::GOComponent::EndSetup(*this);

			pCreateInfo = nullptr;
		}
	};
}