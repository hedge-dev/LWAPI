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
		float m_Weight{ 1 };

	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpUpdate, ASLR(0x00415E10), AnimationComplex*, float);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpProcEvent, ASLR(0x00415DC0), AnimationComplex*, EEvent);
		inline static FUNCTION_PTR(float, __thiscall, ms_fpGetValue, ASLR(0x00415840), const AnimationComplex*, EGetEvent);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetValue, ASLR(0x004158A0), AnimationComplex*, ESetEvent, float);
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpGetStatus, ASLR(0x004158E0), const AnimationComplex*, EPlayStatus);
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpSetStatus, ASLR(0x00415900), const AnimationComplex*, EPlayStatus, bool);
		inline static FUNCTION_PTR(const InterpolateArray*, __thiscall, ms_fpGetInterpolateArray, ASLR(0x00415920), const AnimationComplex*);

		AnimationComplex()
		{
			
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

		void SetStatus(EPlayStatus in_status, bool in_state) const override
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
	};

	inline static ComplexBlender* GetBlender(const char* pName, const AnimationClip& rClip)
	{
		auto* pComplex = csl::ut::DynamicCast<const AnimationComplex>(&rClip);
		if (!pComplex)
			return nullptr;

		if (!pComplex->m_pDef->m_pData->m_BlenderInfo.IsValid())
			return nullptr;

		return pComplex->m_pImpl->GetBlenders().find(pName);
	}
}