#pragma once

namespace app::fnd
{
	inline void GOCVisualModelImpl::ChangeModel(GOCVisualModel& in_model, const Description& in_description)
	{
		auto* pAnimation = m_pAnimation;
		if (pAnimation)
			DetachAnimation(pAnimation);

		if (m_pModelNode)
			Cleanup();

		Setup(in_model, in_description);

		if (pAnimation)
		{
			AttachAnimation(&in_model, pAnimation);
		}
	}

	inline void GOCVisualModelImpl::DetachAnimation(game::GOCAnimationSingle* in_pAnimation)
	{
		in_pAnimation->ReleaseModel();
		m_pAnimation = nullptr;
	}

	inline void GOCVisualModelImpl::AttachAnimation(GOCVisualModel* in_pModel, game::GOCAnimationSingle* in_pAnimation)
	{
		m_pAnimation = in_pAnimation;
		in_pAnimation->SetModel(in_pModel);
	}

	inline hh::gfx::AnimMorphTargetControl* GOCVisualModelImpl::SetMorphAnimation(GOCVisualModel* in_pModel, hh::gfx::res::ResAnimMorphTarget in_resource)
	{
		auto* control = hh::gfx::AnimMorphTargetControl::Create(in_pModel->GetAllocator(), in_resource);
		m_pModelNode->SetAnimObject(control, 2);
		return control;
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
		return m_Impl.SetMorphAnimation(this, in_rDesc.animation);
	}

	class GOCVisualModelImpl::Description : public GOCVisualModel::Description
	{
	public:
		Description(const GOCVisualModel::Description& in_desc) : GOCVisualModel::Description(in_desc)
		{
			
		}
	};
}
