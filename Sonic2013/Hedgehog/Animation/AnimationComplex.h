#pragma once

namespace app::animation
{
	class AnimationSimple;
	class AnimationComplex : public AnimationClip
	{
	public:
		DEFINE_RTTI_PTR(ASLR(0x00F61148))
		
	public:
		const ComplexDef* m_pDef{};
		ut::RefPtr<ComplexImpl> m_pImpl{};
		csl::ut::ObjectMoveArray<AnimationSimple> m_Animations{ nullptr };
		csl::ut::LinkList<AnimationClip> m_Clips{ 12 };
		uint m_Unk1{ 0 };

	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpUpdate, ASLR(0x00415E10), AnimationComplex*, float);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpProcEvent, ASLR(0x00415DC0), AnimationComplex*, EEvent);
		inline static FUNCTION_PTR(float, __thiscall, ms_fpGetValue, ASLR(0x00415840), const AnimationComplex*, EGetEvent);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetValue, ASLR(0x004158A0), AnimationComplex*, ESetEvent, float);
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpGetStatus, ASLR(0x004158E0), const AnimationComplex*, EPlayStatus);
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpSetStatus, ASLR(0x00415900), const AnimationComplex*, EPlayStatus, bool);
		inline static FUNCTION_PTR(const InterpolateArray*, __thiscall, ms_fpGetInterpolateArray, ASLR(0x00415920), const AnimationComplex*);

	public:
		AnimationComplex()
		{
			sizeof(AnimationClip);
		}

		void Setup(csl::fnd::IAllocator& in_allocator, const ComplexDef& in_def, const csl::ut::ObjectMoveArray<ResCharAnim>& in_anims, size_t in_animStartIdx)
		{
			m_pDef = &in_def;
			m_Animations.clear();

			m_Animations.change_allocator(&in_allocator);
			m_Animations.resize(in_def.m_Animations.m_Count);
			for(size_t i = 0; i < m_Animations.size(); ++i)
			{
				m_Animations[i].m_pManager = m_pManager;
				m_Animations[i].m_pOwner = m_pOwner;
				m_Animations[i].m_pParent = this;
				m_Animations[i].ProcEvent(eEvent_AttachExternal);

				m_Animations[i].Setup(in_allocator, in_def.m_Animations.m_pAnimations[i], in_anims[in_animStartIdx + i]);
			}

			if (m_pDef->m_pData->m_BlenderInfo.IsValid())
			{
				m_pImpl = new(in_allocator) ComplexBlend();
			}
			else
			{
				m_pImpl = new(in_allocator) ComplexSequence();
			}

			m_pImpl->m_pParent = this;
			m_pImpl->ProcEvent(eEvent_AttachExternal);
			m_pImpl->Setup();
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
			return m_pDef;
		}

		const InterpolateArray* GetInterpolateArray() const override
		{
			return ms_fpGetInterpolateArray(this);
		}

		void Cleanup()
		{
			if (m_pImpl)
			{
				m_pImpl->Cleanup();
				m_pImpl->ProcEvent(eEvent_FinishCleanup);

				m_pImpl->m_pParent = nullptr;
				m_pImpl = nullptr;
			}

			for (auto& anim : m_Animations)
			{
				anim.Cleanup();
				anim.ProcEvent(AnimationNode::eEvent_FinishCleanup);
			}

			m_Animations.clear();
		}
	};

	inline static ComplexBlender* GetBlender(const char* pName, const AnimationClip& rClip)
	{
		auto* pComplex = csl::ut::DynamicCast<const AnimationComplex>(&rClip);
		if (!pComplex)
			return nullptr;

		if (!pComplex->m_pDef->m_pData->m_BlenderInfo.IsValid())
			return nullptr;

		return static_cast<ComplexBlend*>(pComplex->m_pImpl.get())->m_BlenderMap.find(pName);
	}

	inline static ComplexImpl* GetSequence(const AnimationClip& in_rClip)
	{
		auto* pComplex = csl::ut::DynamicCast<const AnimationComplex>(&in_rClip);
		if (pComplex && !*(size_t*)pComplex->m_pDef->m_pData)
		{
			return pComplex->m_pImpl.get();
		}
		else
		{
			return { nullptr };
		}
	}
}