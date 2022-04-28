#pragma once

namespace app::animation
{
	class AnimationClip;
	
	class CharactorAnimation : public fnd::ReferencedObject
	{
	public:
		DEFINE_RTTI_PTR(ASLR(0x00FD3FB8));

		AnimationNodeManager m_NodeManager{ *GetAllocator() };
		CallbackExecutioner m_CallbackExecutor{ *GetAllocator() };
		bool m_Initialized{};
		void* m_pUnk2{};
		
		virtual const csl::ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const
		{
			return GetRuntimeTypeInfoStatic();
		}

		virtual void Update(float in_delta) = 0;
		virtual void ClearAll() = 0;

	protected:
		virtual bool SetupSub(const AnimationResContainer& in_container) = 0;
		virtual void CleanupSub() = 0;

	public:
		virtual void SetAnimtionClip(AnimationClip* in_pClip) = 0;
		virtual void ChangeAnimationClip(AnimationClip* in_pClip) = 0;
		virtual const TransitionArray* GetTransition(uint in_layer) const = 0;
		virtual size_t GetTransitionLayerNum() const { return 1; }

	public:
		bool Setup(const AnimationResContainer& in_container)
		{
			if (m_Initialized)
				Cleanup();

			if (!in_container.m_Data.m_pFile)
				return false;

			m_CallbackExecutor.Setup(this, in_container.m_Data.m_pFile->m_TriggerCount);
			m_NodeManager.Setup(this, in_container.m_Data.m_pFile->m_pAnimations->m_SimpleAnimations.m_Count, 
				in_container.m_Data.m_pFile->m_pAnimations->m_ComplexAnimations.m_Count);
			m_NodeManager.ResisterAnimations(in_container.m_Data);
			SetupSub(in_container);

			m_Initialized = true;
			return true;
		}

		void Cleanup()
		{
			if (!m_Initialized)
				return;

			CleanupSub();
			m_NodeManager.Cleanup();
			m_CallbackExecutor.Cleanup();

			m_Initialized = false;
		}

		void AttachAnimSkeletonBlender(AnimSkeletonBlender blender)
		{
			ClearAll();
			blender.BindAnimation(*this);
			m_NodeManager.AttachAnimSkeletonBlender(blender);
		}

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