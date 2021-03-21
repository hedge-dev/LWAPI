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

	protected:
		AnimationManager* m_pManager{};
		csl::ut::LinkListNode m_ListNode{};
		size_t m_Category{};
		void* m_Unk1{};
		NotifyTiming m_Timing{};
		ut::RefPtr<DebugInfo> m_rpDebugInfo{};

		virtual void OnEvent(NotifyTiming timing) = 0;

	public:
		AnimationListener()
		{
			
		}
	};
}