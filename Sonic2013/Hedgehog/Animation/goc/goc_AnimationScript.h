#pragma once

namespace app::game
{
	class GOCAnimationScript : public GOCAnimationSingle
	{
	public:
		struct Description
		{
			const animation::AnimationResContainer* m_pContainer;
		};
		
	protected:
		ut::RefPtr<animation::CharactorAnimationSingle> m_rpCharAnimation{};

		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetup, ASLR(0x004B35B0), GOCAnimationScript*, const Description&);
	public:
		inline static fnd::GOComponentClass* ms_pStaticClass = reinterpret_cast<fnd::GOComponentClass*>(ASLR(0x00FD7518));

		static fnd::GOComponentClass* staticClass()
		{
			return ms_pStaticClass;
		}

		void Setup(const Description& rDesc)
		{
			ms_fpSetup(this, rDesc);
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

		bool IsEnableCurrentBlend(const char* pName) const
		{
			if (!m_rpCharAnimation)
				return false;

			auto* pClip = m_rpCharAnimation->GetCurrentAnimationClip();
			if (!pClip)
				return false;

			return abs(m_rpCharAnimation->GetGlobalWeight(*pClip, pName)) > FLT_EPSILON;
		}
		
		float GetCurrentBlendWeight(const char* pName) const
		{
			if (!m_rpCharAnimation)
				return 0;

			auto* pClip = m_rpCharAnimation->GetCurrentAnimationClip();
			if (!pClip)
				return 0;

			return m_rpCharAnimation->GetBlendWeight(*pClip, pName);
		}
		
		void SetFrame(float frame)
		{
			if (m_rpCharAnimation)
				m_rpCharAnimation->SetFrame(frame);
		}

		void SetSpeed(float speed)
		{
			if (m_rpCharAnimation)
				m_rpCharAnimation->SetSpeed(speed);
		}
		
		void SetAnimation(const char* pName)
		{
			if (m_rpCharAnimation)
				m_rpCharAnimation->SetAnimation(pName);
		}

		void SetAnimation(animation::ExternalAnimtion* pAnim)
		{
			if (m_rpCharAnimation && pAnim)
				m_rpCharAnimation->SetAnimation(pAnim);
		}

		void ChangeAnimation(const char* pName)
		{
			if (m_rpCharAnimation)
				m_rpCharAnimation->ChangeAnimation(pName);
		}

		void ChangeAnimation(animation::ExternalAnimtion* pAnim)
		{
			if (m_rpCharAnimation && pAnim)
				m_rpCharAnimation->ChangeAnimation(pAnim);
		}
		
		void EnableCurrentBlend(const char* pName)
		{
			if (!m_rpCharAnimation)
				return;
			
			auto* pClip = m_rpCharAnimation->GetCurrentAnimationClip();
			if (pClip)
				m_rpCharAnimation->SetGlobalWeight(*pClip, pName, 1);
		}

		void DisableCurrentBlend(const char* pName)
		{
			if (!m_rpCharAnimation)
				return;

			auto* pClip = m_rpCharAnimation->GetCurrentAnimationClip();
			if (pClip)
				m_rpCharAnimation->SetGlobalWeight(*pClip, pName, 0);
		}

		void SetCurrentBlendWeight(const char* pName, float weight)
		{
			if (!m_rpCharAnimation)
				return;

			auto* pClip = m_rpCharAnimation->GetCurrentAnimationClip();
			if (pClip)
				m_rpCharAnimation->SetBlendWeight(*pClip, pName, weight);
		}

		void RegisterCallback(int id, animation::AnimationCallback* pCallback)
		{
			m_rpCharAnimation->RegisterCallback(id, pCallback);
		}

		void ExitLoop()
		{
			if (m_rpCharAnimation)
				m_rpCharAnimation->ExitLoop();
		}
		
		const char* GetAnimation() const
		{
			if (!m_rpCharAnimation)
				return "";
			
			return m_rpCharAnimation->GetCurrentAnimationName();
		}

		bool IsCurrentAnimation(const char* pName) const
		{
			if (!m_rpCharAnimation)
				return false;

			return m_rpCharAnimation->IsCurrentAnimation(pName);
		}
	};
}