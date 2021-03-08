#pragma once

namespace app::game
{
	class GOCAnimationSingle : public GOCAnimation
	{
	protected:
		animation::SkeletonBlenderBase* m_pSkeletalBlender{};
		fnd::GOCVisualModel* m_pModel{};

		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetModel, ASLR(0x004B4060), GOCAnimationSingle* pThis, fnd::GOCVisualModel* pModel);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpReleaseModel, ASLR(0x004B40C0), GOCAnimationSingle* pThis);
	public:
		
		virtual void SetModel(fnd::GOCVisualModel* pModel)
		{
			ms_fpSetModel(this, pModel);
		}

		virtual void ReleaseModel()
		{
			ms_fpReleaseModel(this);
		}
	};
}