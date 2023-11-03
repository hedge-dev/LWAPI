#pragma once

namespace app::animation
{
	class SimpleBlender;
	class ComplexBlender;

	class ComplexBlend : public ComplexImpl
	{
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetup, ASLR(0x00416420), ComplexBlend*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpCleanup, ASLR(0x004165A0), ComplexBlend*);
		inline static FUNCTION_PTR(AnimationClip*, __thiscall, ms_fpGetCurrentClip, ASLR(0x004163A0), ComplexBlend*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpUpdate, ASLR(0x004166A0), AnimationNode*, float);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpProcEvent, ASLR(0x00416750), AnimationNode*, EEvent);
		inline static FUNCTION_PTR(float, __thiscall, ms_fpGetValue, ASLR(0x00416340), const AnimationNode*, EGetEvent);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetValue, ASLR(0x004167E0), AnimationNode*, ESetEvent, float);
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpGetStatus, ASLR(0x00416370), const AnimationNode*, EPlayStatus);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetStatus, ASLR(0x00416840), AnimationNode*, EPlayStatus, bool);

	public:
		csl::ut::InplaceObjectMoveArray<ut::RefPtr<ComplexBlender>, 3> Blenders{ GetAllocator() };
		csl::ut::StringMap<ComplexBlender*> BlenderMap{ GetAllocator() };
		SimpleBlender* pSimple{};
		BlenderData* pData{};

		ComplexBlend()
		{

		}

		void Setup() override
		{
			ms_fpSetup(this);
		}

		void Cleanup() override
		{
			ms_fpCleanup(this);
		}

		AnimationClip* GetCurrentClip() override
		{
			return ms_fpGetCurrentClip(this);
		}

		void Update(float in_time) override
		{
			ms_fpUpdate(this, in_time);
		}

		void ProcEvent(EEvent in_type) override
		{
			ms_fpProcEvent(this, in_type);
		}

		bool GetStatus(EPlayStatus in_status) const override
		{
			return ms_fpGetStatus(this, in_status);
		}

		void SetStatus(EPlayStatus in_status, bool in_state) override
		{
			ms_fpSetStatus(this, in_status, in_state);
		}

		float GetValue(EGetEvent in_event) const override
		{
			return ms_fpGetValue(this, in_event);
		}

		void SetValue(ESetEvent in_event, float in_value) override
		{
			ms_fpSetValue(this, in_event, in_value);
		}
	};

	class ComplexBlender : public fnd::ReferencedObject
	{
	public:
		float GlobalWeight{};

		virtual void SetWeight(float in_weight) = 0;
		virtual float GetWeight() const = 0;
		virtual void Update() = 0;
		virtual void ResetParameter() = 0;
		virtual SimpleBlender* GetSimpleBlender() = 0;
	};
}
