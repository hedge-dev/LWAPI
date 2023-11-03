#pragma once

namespace app::game
{
	class GOCAnimationScript : public GOCAnimationSingle
	{
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetup, ASLR(0x004B35B0), GOCAnimationScript*, const Description&);
		inline static fnd::GOComponentClass* ms_pStaticClass = reinterpret_cast<fnd::GOComponentClass*>(ASLR(0x00FD7518));

	public:
		struct Description
		{
			const animation::AnimationResContainer* pContainer;
		};

	protected:
		ut::RefPtr<animation::CharactorAnimationSingle> m_rpCharAnimation{};

	public:
		static fnd::GOComponentClass* staticClass()
		{
			return ms_pStaticClass;
		}

		void Setup(const Description& in_rDesc)
		{
			m_rpCharAnimation = new(GetAllocator()) animation::CharactorAnimationSingle();
			m_rpCharAnimation->Setup(*in_rDesc.pContainer);
			CreateBlender();

			m_rpCharAnimation->AttachAnimSkeletonBlender(pBlender);
		}

		void Extend(const Description& in_rDesc)
		{
			if (!m_rpCharAnimation)
				return;

			m_rpCharAnimation->Extend(*in_rDesc.m_pContainer);
			m_rpCharAnimation->AttachAnimSkeletonBlender(pBlender);
		}

		float GetFrame() const
		{
			if (!m_rpCharAnimation)
				return 0;

			return m_rpCharAnimation->GetFrame();
		}

		float GetEndFrame() const
		{
			if (!m_rpCharAnimation)
				return 0;

			return m_rpCharAnimation->GetEndFrame();
		}

		float GetSpeed() const
		{
			if (!m_rpCharAnimation)
				return 0;

			return m_rpCharAnimation->GetSpeed();
		}

		bool IsEnableCurrentBlend(const char* in_pName) const
		{
			if (!m_rpCharAnimation)
				return false;

			auto* pClip = m_rpCharAnimation->GetCurrentAnimationClip();
			if (!pClip)
				return false;

			return abs(m_rpCharAnimation->GetGlobalWeight(*pClip, in_pName)) > FLT_EPSILON;
		}
		
		float GetCurrentBlendWeight(const char* in_pName) const
		{
			if (!m_rpCharAnimation)
				return 0;

			auto* pClip = m_rpCharAnimation->GetCurrentAnimationClip();
			if (!pClip)
				return 0;

			return m_rpCharAnimation->GetBlendWeight(*pClip, in_pName);
		}
		
		void SetFrame(float in_frame)
		{
			if (m_rpCharAnimation)
				m_rpCharAnimation->SetFrame(in_frame);
		}

		void SetSpeed(float in_speed)
		{
			if (m_rpCharAnimation)
				m_rpCharAnimation->SetSpeed(in_speed);
		}
		
		void SetAnimation(const char* in_pName)
		{
			if (m_rpCharAnimation)
				m_rpCharAnimation->SetAnimation(in_pName);
		}

		void SetAnimation(animation::ExternalAnimtion* in_pAnim)
		{
			if (m_rpCharAnimation && in_pAnim)
				m_rpCharAnimation->SetAnimation(in_pAnim);
		}

		void ChangeAnimation(const char* in_pName)
		{
			if (m_rpCharAnimation)
				m_rpCharAnimation->ChangeAnimation(in_pName);
		}

		void ChangeAnimation(animation::ExternalAnimtion* in_pAnim)
		{
			if (m_rpCharAnimation && in_pAnim)
				m_rpCharAnimation->ChangeAnimation(in_pAnim);
		}
		
		void EnableCurrentBlend(const char* in_pName)
		{
			if (!m_rpCharAnimation)
				return;
			
			auto* pClip = m_rpCharAnimation->GetCurrentAnimationClip();
			if (pClip)
				m_rpCharAnimation->SetGlobalWeight(*pClip, in_pName, 1);
		}

		void DisableCurrentBlend(const char* in_pName)
		{
			if (!m_rpCharAnimation)
				return;

			auto* pClip = m_rpCharAnimation->GetCurrentAnimationClip();
			if (pClip)
				m_rpCharAnimation->SetGlobalWeight(*pClip, in_pName, 0);
		}

		void SetCurrentBlendWeight(const char* in_pName, float in_weight)
		{
			if (!m_rpCharAnimation)
				return;

			auto* pClip = m_rpCharAnimation->GetCurrentAnimationClip();
			if (pClip)
				m_rpCharAnimation->SetBlendWeight(*pClip, in_pName, in_weight);
		}

		void RegisterCallback(int in_id, animation::AnimationCallback* in_pCallback)
		{
			m_rpCharAnimation->RegisterCallback(in_id, in_pCallback);
		}

		void UnregisterCallback(int in_id)
		{
			m_rpCharAnimation->UnregisterCallback(in_id);
		}

		void ExitLoop()
		{
			if (m_rpCharAnimation)
				m_rpCharAnimation->ExitLoop();
		}

		void ExitLoopSeqInsideAnimation()
		{
			if (m_rpCharAnimation)
				m_rpCharAnimation->ExitLoopSeqInsideAnimation();
		}
		
		const char* GetAnimation() const
		{
			if (!m_rpCharAnimation)
				return "";
			
			return m_rpCharAnimation->GetCurrentAnimationName();
		}

		bool IsCurrentAnimation(const char* in_pName) const
		{
			if (!m_rpCharAnimation)
				return false;

			return m_rpCharAnimation->IsCurrentAnimation(in_pName);
		}

		bool IsFinished() const
		{
			if (!m_rpCharAnimation)
				return false;

			return m_rpCharAnimation->IsFinished();
		}
	};
}