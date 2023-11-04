#pragma once

namespace app::game
{
	class GOCAnimationScript : public GOCAnimationSingle
	{
	public:
		struct Description
		{
			const animation::AnimationResContainer* pContainer;
		};

	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetup, ASLR(0x004B35B0), GOCAnimationScript*, const Description&);
		inline static fnd::GOComponentClass* ms_pStaticClass = reinterpret_cast<fnd::GOComponentClass*>(ASLR(0x00FD7518));

	public:
		ut::RefPtr<animation::CharactorAnimationSingle> rpCharAnimation{};

		static fnd::GOComponentClass* staticClass()
		{
			return ms_pStaticClass;
		}

		void Setup(const Description& in_rDesc)
		{
			rpCharAnimation = new(GetAllocator()) animation::CharactorAnimationSingle();
			rpCharAnimation->Setup(*in_rDesc.pContainer);
			CreateBlender();

			rpCharAnimation->AttachAnimSkeletonBlender(pBlender);
		}

		void Extend(const Description& in_rDesc)
		{
			if (!rpCharAnimation)
				return;

			rpCharAnimation->Extend(*in_rDesc.pContainer);
			rpCharAnimation->AttachAnimSkeletonBlender(pBlender);
		}

		float GetFrame() const
		{
			if (!rpCharAnimation)
				return 0;

			return rpCharAnimation->GetFrame();
		}

		float GetEndFrame() const
		{
			if (!rpCharAnimation)
				return 0;

			return rpCharAnimation->GetEndFrame();
		}

		float GetSpeed() const
		{
			if (!rpCharAnimation)
				return 0;

			return rpCharAnimation->GetSpeed();
		}

		bool IsEnableCurrentBlend(const char* in_pName) const
		{
			if (!rpCharAnimation)
				return false;

			auto* pClip = rpCharAnimation->GetCurrentAnimationClip();
			if (!pClip)
				return false;

			return abs(rpCharAnimation->GetGlobalWeight(*pClip, in_pName)) > FLT_EPSILON;
		}
		
		float GetCurrentBlendWeight(const char* in_pName) const
		{
			if (!rpCharAnimation)
				return 0;

			auto* pClip = rpCharAnimation->GetCurrentAnimationClip();
			if (!pClip)
				return 0;

			return rpCharAnimation->GetBlendWeight(*pClip, in_pName);
		}
		
		void SetFrame(float in_frame)
		{
			if (rpCharAnimation)
				rpCharAnimation->SetFrame(in_frame);
		}

		void SetSpeed(float in_speed)
		{
			if (rpCharAnimation)
				rpCharAnimation->SetSpeed(in_speed);
		}
		
		void SetAnimation(const char* in_pName)
		{
			if (rpCharAnimation)
				rpCharAnimation->SetAnimation(in_pName);
		}

		void SetAnimation(animation::ExternalAnimtion* in_pAnim)
		{
			if (rpCharAnimation && in_pAnim)
				rpCharAnimation->SetAnimation(in_pAnim);
		}

		void ChangeAnimation(const char* in_pName)
		{
			if (rpCharAnimation)
				rpCharAnimation->ChangeAnimation(in_pName);
		}

		void ChangeAnimation(animation::ExternalAnimtion* in_pAnim)
		{
			if (rpCharAnimation && in_pAnim)
				rpCharAnimation->ChangeAnimation(in_pAnim);
		}
		
		void EnableCurrentBlend(const char* in_pName)
		{
			if (!rpCharAnimation)
				return;
			
			auto* pClip = rpCharAnimation->GetCurrentAnimationClip();
			if (pClip)
				rpCharAnimation->SetGlobalWeight(*pClip, in_pName, 1);
		}

		void DisableCurrentBlend(const char* in_pName)
		{
			if (!rpCharAnimation)
				return;

			auto* pClip = rpCharAnimation->GetCurrentAnimationClip();
			if (pClip)
				rpCharAnimation->SetGlobalWeight(*pClip, in_pName, 0);
		}

		void SetCurrentBlendWeight(const char* in_pName, float in_weight)
		{
			if (!rpCharAnimation)
				return;

			auto* pClip = rpCharAnimation->GetCurrentAnimationClip();
			if (pClip)
				rpCharAnimation->SetBlendWeight(*pClip, in_pName, in_weight);
		}

		void RegisterCallback(int in_id, animation::AnimationCallback* in_pCallback)
		{
			rpCharAnimation->RegisterCallback(in_id, in_pCallback);
		}

		void UnregisterCallback(int in_id)
		{
			rpCharAnimation->UnregisterCallback(in_id);
		}

		void ExitLoop()
		{
			if (rpCharAnimation)
				rpCharAnimation->ExitLoop();
		}

		void ExitLoopSeqInsideAnimation()
		{
			if (rpCharAnimation)
				rpCharAnimation->ExitLoopSeqInsideAnimation();
		}
		
		const char* GetAnimation() const
		{
			if (!rpCharAnimation)
				return "";
			
			return rpCharAnimation->GetCurrentAnimationName();
		}

		bool IsCurrentAnimation(const char* in_pName) const
		{
			if (!rpCharAnimation)
				return false;

			return rpCharAnimation->IsCurrentAnimation(in_pName);
		}

		bool IsFinished() const
		{
			if (!rpCharAnimation)
				return false;

			return rpCharAnimation->IsFinished();
		}
	};
}