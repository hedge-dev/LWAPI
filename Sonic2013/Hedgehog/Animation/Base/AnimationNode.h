#pragma once

namespace app::animation
{
	typedef uint UpdatingPhaze;
	class AnimationNodeManager;
	class CharactorAnimation;
	
	class AnimationNode
	{
		friend AnimationNodeManager;

	public:
		AnimationNodeManager* m_pManager{};
		CharactorAnimation* m_pOwner{};
		
		DEFINE_RTTI_PTR(ASLR(0x00FD3FBC));
		
		enum EEvent
		{
			eEvent_Attach,
			eEvent_Detach,
			eEvent_CallBack,
			eEvent_AttachExternal,
			eEvent_FinishCleanup,
		};
		
		enum EGetEvent
		{
			eGetEvent_Frame,
			eGetEvent_Speed,
			eGetEvent_EndFrame = 3,
		};
		
		enum ESetEvent
		{
			eSetEvent_Frame,
			eSetEvent_Speed = 2,
			eSetEvent_Weight = 3
		};
		
		typedef size_t EPlayStatus;
		
		virtual const csl::ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const
		{
			return nullptr;
		}
		
		virtual ~AnimationNode() = default;
		virtual void Update(float in_time) = 0;
		virtual void ProcEvent(EEvent in_type) = 0;
		virtual float GetValue(EGetEvent in_event) const = 0;
		virtual void SetValue(ESetEvent in_event, float in_value) = 0;
		virtual bool GetStatus(EPlayStatus in_status) const = 0;
		virtual void SetStatus(EPlayStatus in_status, bool in_state) = 0;
	};
}