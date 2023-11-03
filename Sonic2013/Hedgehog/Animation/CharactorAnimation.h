#pragma once

namespace app::animation
{
	class AnimationClip;
	
	class CharactorAnimation : public fnd::ReferencedObject
	{
	public:
		DEFINE_RTTI_PTR(ASLR(0x00FD3FB8));

		AnimationNodeManager NodeManager{ *GetAllocator() };
		CallbackExecutioner CallbackExecutor{ *GetAllocator() };
		bool Initialized{};
		void* pUnk2{};
		
		virtual const csl::ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const
		{
			return GetRuntimeTypeInfoStatic();
		}

		virtual void Update(float in_delta) = 0;
		virtual void ClearAll() = 0;

	protected:
		virtual bool SetupSub(const AnimationResContainer& in_rContainer) = 0;
		virtual void CleanupSub() = 0;

	public:
		virtual void SetAnimtionClip(AnimationClip* in_pClip) = 0;
		virtual void ChangeAnimationClip(AnimationClip* in_pClip) = 0;
		virtual const TransitionArray* GetTransition(uint in_layer) const = 0;
		virtual size_t GetTransitionLayerNum() const { return 1; }

	public:
		bool Setup(const AnimationResContainer& in_rContainer)
		{
			if (Initialized)
				Cleanup();

			if (!in_rContainer.Data.pFile)
				return false;

			CallbackExecutor.Setup(this, in_rContainer.Data.pFile->TriggerCount);
			NodeManager.Setup(this, in_rContainer.Data.pFile->pAnimations->SimpleAnimations.Count, 
				in_container.Data.pFile->pAnimations->ComplexAnimations.Count);
			NodeManager.ResisterAnimations(in_rContainer.Data);
			SetupSub(in_rContainer);

			Initialized = true;
			return true;
		}

		bool Extend(const AnimationResContainer& in_rContainer)
		{
			if (!in_rContainer.m_Data.m_pFile || !Initialized)
				return false;

			CallbackExecutor.Extend(in_rContainer.Data.pFile->TriggerCount);
			auto token = NodeManager.SetupExtend(in_rContainer.Data.pFile->pAnimations->SimpleAnimations.Count,
				rContainer.Data.pFile->pAnimations->ComplexAnimations.Count);
			NodeManager.ResisterAnimationsExtend(in_rContainer.Data, token);

			// Just in case someone tries to check (game doesn't)
			Initialized = false;
			SetupSub(in_rContainer);
			Initialized = true;

			return true;
		}

		void Cleanup()
		{
			if (!Initialized)
				return;

			CleanupSub();
			NodeManager.Cleanup();
			CallbackExecutor.Cleanup();

			Initialized = false;
		}

		void AttachAnimSkeletonBlender(AnimSkeletonBlender in_blender)
		{
			ClearAll();
			in_blender.BindAnimation(*this);
			NodeManager.AttachAnimSkeletonBlender(in_blender);
		}

		void SetAnimation(const char* in_pName)
		{
			auto* pClip = NodeManager.GetAnimationClip(in_pName);
			if (!pClip)
				return;
			
			SetAnimtionClip(pClip);
		}

		void SetAnimation(ExternalAnimtion* in_pAnim)
		{
			NodeManager.SetExternal(in_pAnim);
			SetAnimtionClip(in_pAnim->GetSimpleAnimation());
		}
		
		void ChangeAnimation(const char* in_pName)
		{
			auto* pClip = NodeManager.GetAnimationClip(in_pName);
			if (!pClip)
				return;

			ChangeAnimationClip(pClip);
		}

		void ChangeAnimation(ExternalAnimtion* in_pAnim)
		{
			NodeManager.SetExternal(in_pAnim);
			ChangeAnimationClip(in_pAnim->GetSimpleAnimation());
		}

		void ExitLoopSeqInsideAnimationClip(AnimationClip* in_pClip)
		{
			if (!in_pClip)
				return;

			auto* pSequence = static_cast<ComplexSequence*>(GetSequence(*in_pClip));
			if (!pSequence)
				return;
		
			pSequence->ExitLoop();
		}

		void RegisterCallback(int in_id, AnimationCallback* in_pCallback)
		{
			m_CallbackExecutor.RegisterCallback(in_id, in_pCallback);
		}

		void UnregisterCallback(int in_id)
		{
			m_CallbackExecutor.UnegisterCallback(in_id);
		}
		
		static bool SetGlobalWeight(const AnimationClip& in_rClip, const char* in_pName, float in_weight)
		{
			auto* pBlender = GetBlender(in_pName, in_rClip);
			if (!pBlender)
				return false;

			pBlender->GlobalWeight = in_weight;
			return true;
		}

		static bool SetBlendWeight(const AnimationClip& in_rClip, const char* in_pName, float in_weight)
		{
			auto* pBlender = GetBlender(in_pName, in_rClip);
			if (!pBlender)
				return false;

			pBlender->SetWeight(in_weight);
			return true;
		}
		
		static float GetGlobalWeight(const AnimationClip& in_rClip, const char* in_pName)
		{
			auto* pBlender = GetBlender(in_pName, in_rClip);
			if (!pBlender)
				return 0;

			return pBlender->GlobalWeight;
		}

		static float GetBlendWeight(const AnimationClip& in_rClip, const char* in_pName)
		{
			auto* pBlender = GetBlender(in_pName, in_rClip);
			if (!pBlender)
				return 0;

			return pBlender->GetWeight();
		}
	};
}