#pragma once

namespace app::animation
{
	class CharactorAnimationSingle : public CharactorAnimation
	{
	public:
		DEFINE_RTTI_PTR(ASLR(0x00F61088));

	protected:
		AnimationTransition m_Transition{};

	public:
		CharactorAnimationSingle()
		{

		}

		const csl::ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override
		{
			return GetRuntimeTypeInfoStatic();
		}

		void Update(float in_delta) override
		{
			m_Transition.Update(in_delta);
		}

		void ClearAll() override
		{
			m_Transition.ClearAll();
		}

		bool SetupSub(const AnimationResContainer& in_rContainer) override
		{
			m_Transition.Setup(&NodeManager, in_rContainer.Data.pFile->pTransitions);
			return true;
		}

		void CleanupSub() override
		{
			m_Transition.Cleanup();
		}

		void SetAnimtionClip(AnimationClip* in_pClip) override
		{
			m_Transition.SetAnimation(in_pClip);
		}

		void ChangeAnimationClip(AnimationClip* in_pClip) override
		{
			m_Transition.ChangeAnimation(in_pClip);
		}

		const TransitionArray* GetTransition(uint in_layer) const override
		{
			return m_Transition.m_pTransitions;
		}

		AnimationClip* GetCurrentAnimationClip(bool in_last = false) const
		{
			return m_Transition.GetClip(in_last);
		}

		float GetFrame() const
		{
			auto* pClip = GetCurrentAnimationClip();
			if (!pClip)
				return 0;

			return pClip->GetValue(AnimationNode::eGetEvent_Frame);
		}

		float GetEndFrame() const
		{
			auto* pClip = GetCurrentAnimationClip();
			if (!pClip)
				return 0;

			return pClip->GetValue(AnimationNode::eGetEvent_EndFrame);
		}
		
		float GetSpeed() const
		{
			auto* pClip = GetCurrentAnimationClip();
			if (!pClip)
				return 0;

			return pClip->GetValue(AnimationNode::eGetEvent_Speed);
		}

		void SetFrame(float in_frame)
		{
			auto* pClip = GetCurrentAnimationClip();
			if (!pClip)
				return;

			pClip->SetValue(AnimationNode::eSetEvent_Frame, in_frame);
		}

		void SetSpeed(float in_speed)
		{
			auto* pClip = GetCurrentAnimationClip();
			if (!pClip)
				return;
			
			pClip->SetValue(AnimationNode::eSetEvent_Speed, in_speed);
		}

		void ExitLoop()
		{
			m_Transition.ExitLoop();
		}

		void ExitLoopSeqInsideAnimation()
		{
			auto* pClip = m_Transition.GetClip();
			ExitLoopSeqInsideAnimationClip(pClip);
		}
		
		const char* GetCurrentAnimationName() const
		{
			auto* pClip = GetCurrentAnimationClip();
			if (!pClip)
				return "";

			return pClip->GetAnimationDef()->pName;
		}

		const char* GetPrevAnimationName() const
		{
			auto* pClip = GetCurrentAnimationClip(true);
			if (!pClip)
				return "";

			return pClip->GetAnimationDef()->pName;
		}
		
		bool IsCurrentAnimation(const char* in_pName) const
		{
			return !strcmp(GetCurrentAnimationName(), in_pName);
		}

		bool IsFinished() const
		{
			return m_Transition.PlaybackFlags.test(1);
		}
	};
}