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
				EventType_Cleanup,
				EventType_SetAnimation,
				EventType_GoToEnd,
			};

		protected:
			virtual void OnGOCAnimationEvent(EventType eType, const void* data) = 0;

		public:
			void SetAnimation(const char* pName)
			{
				OnGOCAnimationEvent(EventType_SetAnimation, pName);
			}
		};
	}
}