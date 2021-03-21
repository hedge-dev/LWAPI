#pragma once

namespace app::game
{
	class GOCAnimationSingle : public GOCAnimation
	{
	protected:
		animation::SkeletonBlenderBase* m_pSkeletalBlender{};
		animation::AnimationListener* m_pListener{};
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

		void AddListener(animation::AnimationListener* pListener)
		{
			//FUNCTION_PTR(void, __thiscall, pAddListener, ASLR(0x004B3FA0), void*, void*);
			//pAddListener(this, pListener);
			//return;
			m_pListener = pListener;
			csl::fnd::Singleton<animation::AnimationManager>::GetInstance()->AddListener(*pListener, GetGameObject()->GetObjectCategory());
		}
	};
}