#pragma once

namespace app::animation
{
	class CharactorAnimationSingle : public CharactorAnimation
	{
	protected:
		AnimationTransition m_Transition{};

	public:
		DEFINE_RTTI_PTR(ASLR(0x00F61088));
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

		bool SetupSub(const AnimationResContainer& in_container) override
		{
			m_Transition.Setup(&m_NodeManager, in_container.m_Data.m_pFile->m_pTransitions);
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

		AnimationClip* GetCurrentAnimationClip(bool last = false) const
		{
			return m_Transition.GetClip(last);
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

		void SetFrame(float frame)
		{
			auto* pClip = GetCurrentAnimationClip();
			if (!pClip)
				return;

			pClip->SetValue(AnimationNode::eSetEvent_Frame, frame);
		}

		void SetSpeed(float speed)
		{
			auto* pClip = GetCurrentAnimationClip();
			if (!pClip)
				return;
			
			pClip->SetValue(AnimationNode::eSetEvent_Speed, speed);
		}

		void ExitLoop()
		{
			m_Transition.ExitLoop();
		}
		
		const char* GetCurrentAnimationName() const
		{
			auto* pClip = GetCurrentAnimationClip();
			if (!pClip)
				return "";

			return pClip->GetAnimationDef()->m_pName;
		}

		const char* GetPrevAnimationName() const
		{
			auto* pClip = GetCurrentAnimationClip(true);
			if (!pClip)
				return "";

			return pClip->GetAnimationDef()->m_pName;
		}
		
		bool IsCurrentAnimation(const char* pName) const
		{
			return !strcmp(GetCurrentAnimationName(), pName);
		}
	};
}