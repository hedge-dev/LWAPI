#pragma once

namespace app::animation
{
	class AnimationSimple;
	
	class AnimationComplex : public AnimationClip
	{
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpUpdate, ASLR(0x00415E10), AnimationComplex*, float);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpProcEvent, ASLR(0x00415DC0), AnimationComplex*, EEvent);
		inline static FUNCTION_PTR(float, __thiscall, ms_fpGetValue, ASLR(0x00415840), const AnimationComplex*, EGetEvent);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetValue, ASLR(0x004158A0), AnimationComplex*, ESetEvent, float);
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpGetStatus, ASLR(0x004158E0), const AnimationComplex*, EPlayStatus);
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpSetStatus, ASLR(0x00415900), const AnimationComplex*, EPlayStatus, bool);
		inline static FUNCTION_PTR(const InterpolateArray*, __thiscall, ms_fpGetInterpolateArray, ASLR(0x00415920), const AnimationComplex*);

	public:
		DEFINE_RTTI_PTR(ASLR(0x00F61148))
		
	public:
		const ComplexDef* pDef{};
		ut::RefPtr<ComplexImpl> pImpl{};
		csl::ut::ObjectMoveArray<AnimationSimple> Animations{ nullptr };
		csl::ut::LinkList<AnimationClip> Clips{ 12 };
		uint Unk1{ 0 };

	public:
		AnimationComplex()
		{
			
		}

		void Setup(csl::fnd::IAllocator& in_rAllocator, const ComplexDef& in_rDef, const csl::ut::ObjectMoveArray<ResCharAnim>& in_rAnims, size_t in_animStartIdx)
		{
			pDef = &in_rDef;
			Animations.clear();

			Animations.change_allocator(&in_rAllocator);
			Animations.resize(in_rDef.Animations.Count);
			for(size_t i = 0; i < Animations.size(); ++i)
			{
				Animations[i].pManager = pManager;
				Animations[i].pOwner = pOwner;
				Animations[i].pParent = this;
				Animations[i].ProcEvent(eEvent_AttachExternal);

				Animations[i].Setup(in_rAllocator, in_rDef.Animations.pAnimations[i], in_rAnims[in_animStartIdx + i]);
			}

			if (pDef->pData->BlenderInfo.IsValid())
			{
				pImpl = new(in_rAllocator) ComplexBlend();
			}
			else
			{
				pImpl = new(in_rAllocator) ComplexSequence();
			}

			pImpl->pParent = this;
			pImpl->ProcEvent(eEvent_AttachExternal);
			pImpl->Setup();
		}

		void Update(float in_deltaTime) override
		{
			ms_fpUpdate(this, in_deltaTime);
		}

		void ProcEvent(EEvent in_type) override
		{
			ms_fpProcEvent(this, in_type);
		}

		float GetValue(EGetEvent in_event) const override
		{
			return ms_fpGetValue(this, in_event);
		}

		void SetValue(ESetEvent in_event, float in_value) override
		{
			ms_fpSetValue(this, in_event, in_value);
		}

		bool GetStatus(EPlayStatus in_status) const override
		{
			return ms_fpGetStatus(this, in_status);
		}

		void SetStatus(EPlayStatus in_status, bool in_state) override
		{
			ms_fpSetStatus(this, in_status, in_state);
		}

		const ComplexDef* GetAnimationDef() const override
		{
			return pDef;
		}

		const InterpolateArray* GetInterpolateArray() const override
		{
			return ms_fpGetInterpolateArray(this);
		}

		void Cleanup()
		{
			if (pImpl)
			{
				pImpl->Cleanup();
				pImpl->ProcEvent(eEvent_FinishCleanup);

				pImpl->pParent = nullptr;
				pImpl = nullptr;
			}

			for (auto& anim : Animations)
			{
				anim.Cleanup();
				anim.ProcEvent(AnimationNode::eEvent_FinishCleanup);
			}

			Animations.clear();
		}
	};

	inline static ComplexBlender* GetBlender(const char* in_pName, const AnimationClip& in_rClip)
	{
		auto* pComplex = csl::ut::DynamicCast<const AnimationComplex>(&in_rClip);
		if (!pComplex)
			return nullptr;

		if (!pComplex->pDef->pData->BlenderInfo.IsValid())
			return nullptr;

		return static_cast<ComplexBlend*>(pComplex->pImpl.get())->BlenderMap.find(in_pName);
	}

	inline static ComplexImpl* GetSequence(const AnimationClip& in_rClip)
	{
		auto* pComplex = csl::ut::DynamicCast<const AnimationComplex>(&in_rClip);
		if (pComplex && !*(size_t*)pComplex->pDef->pData)
		{
			return pComplex->pImpl.get();
		}
		else
		{
			return { nullptr };
		}
	}
}