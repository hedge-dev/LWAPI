#pragma once

namespace app::animation
{
	class ComplexBlender;
	class ComplexSequence : public ComplexImpl
	{
	public:
		AnimationTransition m_Transition{};
		uint m_Unk1{ 0 };
		uint m_Unk2{ (uint)-1 };
		uint m_Unk3{ (uint)-1 };
		csl::ut::Bitset<uint> m_Flags{};
		bool m_FinishLoop{};
		
		inline static FUNCTION_PTR(void, __thiscall, ms_fpCleanup, ASLR(0x00417020), ComplexSequence*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpUpdate, ASLR(0x00417110), AnimationNode*, float);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpProcEvent, ASLR(0x004172B0), AnimationNode*, EEvent);
		inline static FUNCTION_PTR(float, __thiscall, ms_fpGetValue, ASLR(0x00417030), const AnimationNode*, EGetEvent);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetValue, ASLR(0x004173B0), AnimationNode*, ESetEvent, float);
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpGetStatus, ASLR(0x004171E0), const AnimationNode*, EPlayStatus);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetStatus, ASLR(0x00417410), AnimationNode*, EPlayStatus, bool);

		ComplexSequence()
		{

		}

		void Setup() override
		{
			m_Transition.Setup(nullptr, nullptr);
		}

		void Cleanup() override
		{
			ms_fpCleanup(this);
		}

		AnimationClip* GetCurrentClip() override
		{
			return m_Transition.GetClip();
		}

		void Update(float in_time) override
		{
			return ms_fpUpdate(this, in_time);
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
			return ms_fpSetValue(this, in_event, in_value);
		}

		bool GetStatus(EPlayStatus in_status) const override
		{
			return ms_fpGetStatus(this, in_status);
		}

		void SetStatus(EPlayStatus in_status, bool in_state) override
		{
			return ms_fpSetStatus(this, in_status, in_state);
		}

		void ExitLoop()
		{
			m_FinishLoop = true;
		}
	};
}