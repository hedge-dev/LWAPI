#pragma once

namespace app::animation
{
	class AnimationManager : public fnd::ReferencedObject, csl::fnd::SingletonPointer<AnimationManager>
	{
	public:
		INSERT_PADDING(2960){};

		inline static FUNCTION_PTR(void, __thiscall, ms_fpAddListener, ASLR(0x0040B6B0), AnimationManager*, AnimationListener&, uint);
		void AddListener(AnimationListener& rListener, uint category)
		{
			ms_fpAddListener(this, rListener, category);
		}
	};
}

DEFINE_SINGLETONPTR(app::animation::AnimationManager, ASLR(0x00FD3FA0));