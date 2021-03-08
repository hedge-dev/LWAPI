#pragma once

namespace app
{
	namespace game
	{
		class GOCAnimation : public fnd::GOComponent
		{
		protected:
			typedef uint EventType;

		protected:
			virtual void OnGOCAnimationEvent(EventType eType, const void* data) = 0;
		};
	}
}