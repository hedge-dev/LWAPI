#pragma once

namespace app::fnd
{
	inline void GOCVisualModelImpl::ChangeModel(GOCVisualModel& in_rModel, const Description& in_rDescription)
	{
		auto* pCurrentAnimation = pAnimation;
		if (pCurrentAnimation)
			DetachAnimation(pCurrentAnimation);

		if (pModelNode)
			Cleanup();

		Setup(in_rModel, in_rDescription);

		if (pCurrentAnimation)
		{
			AttachAnimation(&in_rModel, pCurrentAnimation);
		}
	}

	inline void GOCVisualModelImpl::DetachAnimation(game::GOCAnimationSingle* in_pAnimation)
	{
		in_pAnimation->ReleaseModel();
		pAnimation = nullptr;
	}

	inline void GOCVisualModelImpl::AttachAnimation(GOCVisualModel* in_pModel, game::GOCAnimationSingle* in_pAnimation)
	{
		pAnimation = in_pAnimation;
		in_pAnimation->SetModel(in_pModel);
	}

	inline hh::gfx::AnimMorphTargetControl* GOCVisualModelImpl::SetMorphAnimation(GOCVisualModel* in_pModel, hh::gfx::res::ResAnimMorphTarget in_resource)
	{
		auto* pControl = hh::gfx::AnimMorphTargetControl::Create(in_pModel->GetAllocator(), in_resource);
		pModelNode->SetAnimObject(pControl, 2);
		return pControl;
	}

	inline hh::gfx::res::ResSkeleton GOCVisualModelImpl::GetSkeletonResource()
	{
		if (pSkeleton)
		{
			return { &pSkeleton->Skeleton.ref() };
		}
		else
		{
			return { nullptr };
		}
	}

	inline hh::gfx::AnimMorphTargetControl* GOCVisualModel::SetMorphAnimation(const MorphTargetDesc& in_rDesc)
	{
		return Impl.SetMorphAnimation(this, in_rDesc.Animation);
	}

	class GOCVisualModelImpl::Description : public GOCVisualModel::Description
	{
	public:
		Description(const GOCVisualModel::Description& in_rDesc) : GOCVisualModel::Description(in_rDesc)
		{
			
		}
	};
}
