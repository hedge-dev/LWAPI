#pragma once

namespace app::game
{
	class GOCAnimationScriptLayer : public GOCAnimationSingle
	{
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetup, ASLR(0x004B37F0), GOCAnimationScriptLayer*, const Description&);
		inline static fnd::GOComponentClass* ms_pStaticClass = reinterpret_cast<fnd::GOComponentClass*>(ASLR(0x00FD756C));

	public:
		struct Description
		{
			const animation::AnimationResContainer* pContainer;
		};

	protected:
		ut::RefPtr<animation::CharactorAnimationMultiLayer> m_rpLayerAnimation{};

	public:
		static fnd::GOComponentClass* staticClass()
		{
			return ms_pStaticClass;
		}

		void Setup(const Description& in_rDesc)
		{
			ms_fpSetup(this, in_rDesc);
		}

		float GetFrame(size_t in_layer) const
		{
			if (!m_rpLayerAnimation)
				return 0;

			return m_rpLayerAnimation->GetFrame(in_layer);
		}

		float GetEndFrame(size_t in_layer) const
		{
			if (!m_rpLayerAnimation)
				return 0;

			return m_rpLayerAnimation->GetEndFrame(in_layer);
		}

		float GetSpeed(size_t in_layer) const
		{
			if (!m_rpLayerAnimation)
				return 0;

			return m_rpLayerAnimation->GetSpeed(in_layer);
		}

		bool IsEnableCurrentBlend(const char* in_pName, size_t in_layer) const
		{
			if (!m_rpLayerAnimation)
				return false;

			auto* pClip = m_rpLayerAnimation->GetCurrentAnimationClip(in_layer);
			if (!pClip)
				return false;

			return abs(m_rpLayerAnimation->GetGlobalWeight(*pClip, in_pName)) > FLT_EPSILON;
		}

		float GetCurrentBlendWeight(const char* in_pName, size_t in_layer) const
		{
			if (!m_rpLayerAnimation)
				return 0;

			auto* pClip = m_rpLayerAnimation->GetCurrentAnimationClip(in_layer);
			if (!pClip)
				return 0;

			return m_rpLayerAnimation->GetBlendWeight(*pClip, in_pName);
		}

		void SetFrame(float in_frame, size_t in_layer)
		{
			if (m_rpLayerAnimation)
				m_rpLayerAnimation->SetFrame(in_frame, in_layer);
		}

		void SetSpeed(float in_speed, size_t in_layer)
		{
			if (m_rpLayerAnimation)
				m_rpLayerAnimation->SetSpeed(in_speed, in_layer);
		}
		
		void SetAnimation(const char* in_pName)
		{
			if (m_rpLayerAnimation)
				m_rpLayerAnimation->SetAnimation(in_pName);
		}

		void SetAnimation(animation::ExternalAnimtion* in_pAnim)
		{
			if (m_rpLayerAnimation && in_pAnim)
				m_rpLayerAnimation->SetAnimation(in_pAnim);
		}

		void ChangeAnimation(const char* in_pName)
		{
			if (m_rpLayerAnimation)
				m_rpLayerAnimation->ChangeAnimation(in_pName);
		}

		void ChangeAnimation(animation::ExternalAnimtion* in_pAnim)
		{
			if (m_rpLayerAnimation && in_pAnim)
				m_rpLayerAnimation->ChangeAnimation(in_pAnim);
		}

		void EnableCurrentBlend(const char* in_pName, size_t in_layer)
		{
			if (!m_rpLayerAnimation)
				return;

			auto* pClip = m_rpLayerAnimation->GetCurrentAnimationClip(in_layer);
			if (pClip)
				m_rpLayerAnimation->SetGlobalWeight(*pClip, in_pName, 1);
		}

		void DisableCurrentBlend(const char* in_pName, size_t in_layer)
		{
			if (!m_rpLayerAnimation)
				return;

			auto* pClip = m_rpLayerAnimation->GetCurrentAnimationClip(in_layer);
			if (pClip)
				m_rpLayerAnimation->SetGlobalWeight(*pClip, in_pName, 0);
		}

		void SetCurrentBlendWeight(const char* in_pName, float in_weight, size_t in_layer)
		{
			if (!m_rpLayerAnimation)
				return;

			auto* pClip = m_rpLayerAnimation->GetCurrentAnimationClip(in_layer);
			if (pClip)
				m_rpLayerAnimation->SetBlendWeight(*pClip, in_pName, in_weight);
		}

		void RegisterCallback(int in_id, animation::AnimationCallback* in_pCallback)
		{
			m_rpLayerAnimation->RegisterCallback(in_id, in_pCallback);
		}

		const char* GetAnimation(size_t in_layer) const
		{
			if (!m_rpLayerAnimation)
				return "";

			return m_rpLayerAnimation->GetCurrentAnimationName(in_layer);
		}

		bool IsCurrentAnimation(const char* pName, size_t in_layer) const
		{
			if (!m_rpLayerAnimation)
				return false;

			return m_rpLayerAnimation->IsCurrentAnimation(pName, in_layer);
		}
	};
}