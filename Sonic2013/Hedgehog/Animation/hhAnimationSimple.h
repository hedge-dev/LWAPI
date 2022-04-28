#pragma once

namespace app::animation
{
	class AnimationSimple : public AnimationClip
	{
	protected:
		const SimpleDef* m_pDef{};
		PlayingData m_PlayData{};
		AnimSkeletonControl m_SkelControl{};
		uint m_Unk1{};

	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpUpdate, ASLR(0x00416070), AnimationSimple*, float);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpProcEvent, ASLR(0x00416130), AnimationSimple*, EEvent);
		inline static FUNCTION_PTR(float, __thiscall, ms_fpGetValue, ASLR(0x00415E80), const AnimationSimple*, EGetEvent);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetValue, ASLR(0x00415FD0), AnimationSimple*, ESetEvent, float);
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpGetStatus, ASLR(0x00416280), const AnimationSimple*, EPlayStatus);
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpSetStatus, ASLR(0x004162A0), const AnimationSimple*, EPlayStatus, bool);
		inline static FUNCTION_PTR(const InterpolateArray*, __thiscall, ms_fpGetInterpolateArray, ASLR(0x00415FC0), const AnimationSimple*);

	public:
		DEFINE_RTTI_PTR(ASLR(0x00F61178));

		AnimationSimple()
		{

		}

		void Setup(csl::fnd::IAllocator& in_allocator, const SimpleDef& in_def, const ResCharAnim& in_anim)
		{
			m_pDef = &in_def;
			m_SkelControl.Setup(in_allocator, in_anim, in_def.m_Data.m_Options == 0);
		}

		const csl::ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override { return GetRuntimeTypeInfoStatic(); }

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

		bool GetStatus(EPlayStatus in_status) const
		{
			return ms_fpGetStatus(this, in_status);
		}

		void SetStatus(EPlayStatus in_status, bool in_state) override
		{
			ms_fpSetStatus(this, in_status, in_state);
		}

		const SimpleDef* GetAnimationDef() const override
		{
			return m_pDef;
		}

		const InterpolateArray* GetInterpolateArray() const override
		{
			return ms_fpGetInterpolateArray(this);
		}

		void Cleanup()
		{
			m_SkelControl.Cleanup();
		}
	};
}