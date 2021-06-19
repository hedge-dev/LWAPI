#pragma once

namespace app::animation
{
	typedef uint UpdatingPhaze;
	class AnimationNodeManager;
	class AnimationNodeManager;
	
	class AnimationNode
	{
		friend AnimationNodeManager;
	
	protected:
		AnimationNodeManager* m_pManager{};
		AnimationObj* m_pOwner{};
		
	public:
		DEFINE_RTTI_PTR(ASLR(0x00FD3FBC));
		
		enum EEventType
		{
			eEventType_Attach,
			eEventType_Detach,
			eEventType_CallBack,
			eEventType_AttachExternal
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
		
		virtual csl::ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const
		{
			return nullptr;
		}
		
		virtual ~AnimationNode() = default;
		virtual void Update() = 0;
		virtual void ProcEvent(EEventType type) = 0;
		virtual float GetValue(EGetEvent event) const = 0;
		virtual void SetValue(ESetEvent event, float value) = 0;
		virtual void GetStatus(EPlayStatus status) const = 0;
		virtual void SetStatus(EPlayStatus status, bool state) const = 0;
	};
}