#pragma once

namespace app::animation
{
	class AnimationResContainer;
	class AnimationClip;
	
	class CharactorAnimation : public fnd::ReferencedObject
	{
	protected:
		AnimationNodeManager m_NodeManager{ *GetAllocator() };
		CallbackExecutioner m_CallbackExecutor{ *GetAllocator() };
		void* m_pUnk1{};
		void* m_pUnk2{};
		
		
	public:
		virtual void* GetRuntimeTypeInfo() const
		{
			return nullptr;
		}

	protected:
		virtual void Update(float delta) = 0;
		virtual void ClearAll() = 0;
		virtual void SetupSub(const AnimationResContainer& rContainer) = 0;
		virtual void CleanupSub() = 0;
		virtual void SetAnimtionClip(AnimationClip* pClip) = 0;
		virtual void ChangeAnimationClip(AnimationClip* pClip) = 0;
		virtual void* GetTransition(uint a1) const = 0;
		virtual size_t GetTransitionLayerNum() const { return 0; }

	public:
		void SetAnimation(const char* pName)
		{
			auto* pClip = m_NodeManager.GetAnimationClip(pName);
			if (!pClip)
				return;
			
			SetAnimtionClip(pClip);
		}

		void SetAnimation(ExternalAnimtion* pAnim)
		{
			m_NodeManager.SetExternal(pAnim);
			SetAnimtionClip(pAnim->GetSimpleAnimation());
		}
		
		void ChangeAnimation(const char* pName)
		{
			auto* pClip = m_NodeManager.GetAnimationClip(pName);
			if (!pClip)
				return;

			ChangeAnimationClip(pClip);
		}

		void ChangeAnimation(ExternalAnimtion* pAnim)
		{
			m_NodeManager.SetExternal(pAnim);
			ChangeAnimationClip(pAnim->GetSimpleAnimation());
		}

		void RegisterCallback(int id, AnimationCallback* pCallback)
		{
			m_CallbackExecutor.RegisterCallback(id, pCallback);
		}
		
		static bool SetGlobalWeight(const AnimationClip& rClip, const char* pName, float weight)
		{
			auto* pBlender = GetBlender(pName, rClip);
			if (!pBlender)
				return false;

			pBlender->m_GlobalWeight = weight;
			return true;
		}

		static bool SetBlendWeight(const AnimationClip& rClip, const char* pName, float weight)
		{
			auto* pBlender = GetBlender(pName, rClip);
			if (!pBlender)
				return false;

			pBlender->SetWeight(weight);
			return true;
		}
		
		static float GetGlobalWeight(const AnimationClip& rClip, const char* pName)
		{
			auto* pBlender = GetBlender(pName, rClip);
			if (!pBlender)
				return 0;

			return pBlender->m_GlobalWeight;
		}

		static float GetBlendWeight(const AnimationClip& rClip, const char* pName)
		{
			auto* pBlender = GetBlender(pName, rClip);
			if (!pBlender)
				return 0;

			return pBlender->GetWeight();
		}
	};
}