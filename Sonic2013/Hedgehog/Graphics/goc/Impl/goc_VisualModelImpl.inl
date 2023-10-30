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

	class GOCVisualModelImpl::Description : public GOCVisualModel::Description
	{
	public:
		Description(const GOCVisualModel::Description& in_desc) : GOCVisualModel::Description(in_desc)
		{
			
		}
	};
}
