#pragma once

namespace app::game
{
	class GOCAnimationSingle : public GOCAnimation
	{
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetModel, ASLR(0x004B4060), GOCAnimationSingle*, fnd::GOCVisualModel*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpReleaseModel, ASLR(0x004B40C0), GOCAnimationSingle* );
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetBlenderUpdateFlag, ASLR(0x004B4020), GOCAnimationSingle* , bool);

	public:
		animation::SkeletonBlender* pBlender{};
		animation::AnimationListener* pListener{};
		fnd::GOCVisualModel* pModel{};
		
		virtual void SetModel(fnd::GOCVisualModel* in_pModel)
		{
			ms_fpSetModel(this, in_pModel);
		}

		virtual void ReleaseModel()
		{
			ms_fpReleaseModel(this);
		}

		void CreateBlender()
		{
			pBlender = animation::SkeletonBlender::Create(GetGameObject()->GetObjectCategory(), *GetAllocator());
		}

		void DestroyBlender()
		{
			if (!pBlender)
				return;

			pBlender->Release();
			pBlender = nullptr;
		}

		void AddListener(animation::AnimationListener* in_pListener)
		{
			pListener = in_pListener;
			csl::fnd::Singleton<animation::AnimationManager>::GetInstance()->AddListener(*in_pListener, GetGameObject()->GetObjectCategory());
		}
	
		void SetBlenderUpdateFlag(bool in_enabled)
		{
			ms_fpSetBlenderUpdateFlag(this, in_enabled);
		}
	};
}