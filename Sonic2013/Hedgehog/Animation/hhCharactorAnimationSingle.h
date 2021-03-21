#pragma once

namespace app::animation
{
	class AnimationTransition
	{
	protected:
		AnimationClip* m_pCurClip{};
		AnimationClip* m_pLastClip{};
		size_t m_Status{};
		csl::ut::Bitset<uint> m_PlaybackFlags{};
		INSERT_PADDING(16){};

	public:
		AnimationClip* GetClip(bool last = false) const
		{
			if (last)
				return m_pLastClip;
			
			return m_pCurClip;
		}

		bool IsInterpolate() const
		{
			return m_Status == 2;
		}

		bool IsFinished() const
		{
			return m_PlaybackFlags.test(1);
		}

		bool IsFinishedEdge() const
		{
			return m_PlaybackFlags.test(2);
		}

		void ExitLoop()
		{
			m_PlaybackFlags.set(0);
		}
	};
	
	class CharactorAnimationSingle : public CharactorAnimation
	{
	protected:
		AnimationTransition m_Transition{};

	public:
		CharactorAnimationSingle()
		{
			
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