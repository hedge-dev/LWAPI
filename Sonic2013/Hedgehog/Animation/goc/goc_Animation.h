#pragma once

namespace app
{
	namespace game
	{
		class GOCAnimation : public fnd::GOComponent
		{
		protected:
			enum EventType
			{
				eEventType_Cleanup,
				eEventType_SetAnimation,
				eEventType_GoToEnd,
			};

		protected:
			virtual void OnGOCAnimationEvent(EventType in_type, const void* in_pData) = 0;

		public:
			void SetAnimation(const char* in_pName)
			{
				OnGOCAnimationEvent(eEventType_SetAnimation, in_pName);
			}
		};
	}
}