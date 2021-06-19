#pragma once

namespace app::game
{
	class GOCAnimationScriptLayer : public GOCAnimationSingle
	{
	public:
		struct Description
		{
			const animation::AnimationResContainer* m_pContainer;
		};

	protected:
		ut::RefPtr<animation::CharactorAnimationMultiLayer> m_rpLayerAnimation{};

		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetup, ASLR(0x004B37F0), GOCAnimationScriptLayer*, const Description&);
	public:
		inline static fnd::GOComponentClass* ms_pStaticClass = reinterpret_cast<fnd::GOComponentClass*>(ASLR(0x00FD756C));

		static fnd::GOComponentClass* staticClass()
		{
			return ms_pStaticClass;
		}

		void Setup(const Description& rDesc)
		{
			ms_fpSetup(this, rDesc);
		}

		float GetFrame(size_t layer) const
		{
			if (!m_rpLayerAnimation)
				return 0;

			return m_rpLayerAnimation->GetFrame(layer);
		}

		float GetEndFrame(size_t layer) const
		{
			if (!m_rpLayerAnimation)
				return 0;

			return m_rpLayerAnimation->GetEndFrame(layer);
		}

		float GetSpeed(size_t layer) const
		{
			if (!m_rpLayerAnimation)
				return 0;

			return m_rpLayerAnimation->GetSpeed(layer);
		}

		bool IsEnableCurrentBlend(const char* pName, size_t layer) const
		{
			if (!m_rpLayerAnimation)
				return false;

			auto* pClip = m_rpLayerAnimation->GetCurrentAnimationClip(layer);
			if (!pClip)
				return false;

			return abs(m_rpLayerAnimation->GetGlobalWeight(*pClip, pName)) > FLT_EPSILON;
		}

		float GetCurrentBlendWeight(const char* pName, size_t layer) const
		{
			if (!m_rpLayerAnimation)
				return 0;

			auto* pClip = m_rpLayerAnimation->GetCurrentAnimationClip(layer);
			if (!pClip)
				return 0;

			return m_rpLayerAnimation->GetBlendWeight(*pClip, pName);
		}

		void SetFrame(float frame, size_t layer)
		{
			if (m_rpLayerAnimation)
				m_rpLayerAnimation->SetFrame(frame, layer);
		}

		void SetSpeed(float speed, size_t layer)
		{
			if (m_rpLayerAnimation)
				m_rpLayerAnimation->SetSpeed(speed, layer);
		}
		
		void SetAnimation(const char* pName)
		{
			if (m_rpLayerAnimation)
				m_rpLayerAnimation->SetAnimation(pName);
		}

		void SetAnimation(animation::ExternalAnimtion* pAnim)
		{
			if (m_rpLayerAnimation && pAnim)
				m_rpLayerAnimation->SetAnimation(pAnim);
		}

		void ChangeAnimation(const char* pName)
		{
			if (m_rpLayerAnimation)
				m_rpLayerAnimation->ChangeAnimation(pName);
		}

		void ChangeAnimation(animation::ExternalAnimtion* pAnim)
		{
			if (m_rpLayerAnimation && pAnim)
				m_rpLayerAnimation->ChangeAnimation(pAnim);
		}

		void EnableCurrentBlend(const char* pName, size_t layer)
		{
			if (!m_rpLayerAnimation)
				return;

			auto* pClip = m_rpLayerAnimation->GetCurrentAnimationClip(layer);
			if (pClip)
				m_rpLayerAnimation->SetGlobalWeight(*pClip, pName, 1);
		}

		void DisableCurrentBlend(const char* pName, size_t layer)
		{
			if (!m_rpLayerAnimation)
				return;

			auto* pClip = m_rpLayerAnimation->GetCurrentAnimationClip(layer);
			if (pClip)
				m_rpLayerAnimation->SetGlobalWeight(*pClip, pName, 0);
		}

		void SetCurrentBlendWeight(const char* pName, float weight, size_t layer)
		{
			if (!m_rpLayerAnimation)
				return;

			auto* pClip = m_rpLayerAnimation->GetCurrentAnimationClip(layer);
			if (pClip)
				m_rpLayerAnimation->SetBlendWeight(*pClip, pName, weight);
		}

		void RegisterCallback(int id, animation::AnimationCallback* pCallback)
		{
			m_rpLayerAnimation->RegisterCallback(id, pCallback);
		}

		const char* GetAnimation(size_t layer) const
		{
			if (!m_rpLayerAnimation)
				return "";

			return m_rpLayerAnimation->GetCurrentAnimationName(layer);
		}

		bool IsCurrentAnimation(const char* pName, size_t layer) const
		{
			if (!m_rpLayerAnimation)
				return false;

			return m_rpLayerAnimation->IsCurrentAnimation(pName, layer);
		}
	};
}