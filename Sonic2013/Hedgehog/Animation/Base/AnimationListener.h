#pragma once

namespace app::animation
{
	class AnimationManager;
	typedef int NotifyTiming;
	
	class AnimationListener : public AnimationObj
	{
	public:
		// What is this?
		class DebugInfo : public ReferencedObject
		{
		public:
			INSERT_PADDING(8){};
		};

		AnimationManager* pManager{};
		csl::ut::LinkListNode ListNode{};
		size_t Category{};
		void* Unk1{};
		NotifyTiming Timing{};
		ut::RefPtr<DebugInfo> rpDebugInfo{};

		virtual void OnEvent(NotifyTiming in_timing) = 0;

	public:
		AnimationListener()
		{
			
		}
	};
}