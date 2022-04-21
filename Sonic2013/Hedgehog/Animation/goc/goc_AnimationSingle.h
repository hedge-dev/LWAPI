#pragma once

namespace app::game
{
	class GOCAnimationSingle : public GOCAnimation
	{
	public:
		animation::SkeletonBlenderBase* m_pSkeletalBlender{};
		animation::AnimationListener* m_pListener{};
		fnd::GOCVisualModel* m_pModel{};

		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetModel, ASLR(0x004B4060), GOCAnimationSingle*, fnd::GOCVisualModel*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpReleaseModel, ASLR(0x004B40C0), GOCAnimationSingle* );
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetBlenderUpdateFlag, ASLR(0x004B4020), GOCAnimationSingle* , bool);
		
		virtual void SetModel(fnd::GOCVisualModel* in_pModel)
		{
			ms_fpSetModel(this, in_pModel);
		}

		virtual void ReleaseModel()
		{
			ms_fpReleaseModel(this);
		}

		void AddListener(animation::AnimationListener* in_pListener)
		{
			m_pListener = in_pListener;
			csl::fnd::Singleton<animation::AnimationManager>::GetInstance()->AddListener(*in_pListener, GetGameObject()->GetObjectCategory());
		}
	
		void SetBlenderUpdateFlag(bool in_enabled)
		{
			ms_fpSetBlenderUpdateFlag(this, in_enabled);
		}
	};
}