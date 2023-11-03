#pragma once

namespace app::animation
{
	class Pose;
	class AnimationManager : public fnd::ReferencedObject, public csl::fnd::SingletonPointer<AnimationManager>
	{
	public:
		INSERT_PADDING(2960){};

		inline static FUNCTION_PTR(void, __thiscall, ms_fpAddListener, ASLR(0x0040B6B0), AnimationManager*, AnimationListener&, uint);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpAddPose, ASLR(0x0040B670), AnimationManager*, Pose&, uint);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpRemovePose, ASLR(0x0040B470), AnimationManager*, Pose&);

		void AddPose(Pose& in_rPose, uint category)
		{
			ms_fpAddPose(this, in_rPose, category);
		}

		void RemovePose(Pose& in_rPose)
		{
			ms_fpRemovePose(this, in_rPose);
		}

		void AddListener(AnimationListener& rListener, uint category)
		{
			ms_fpAddListener(this, rListener, category);
		}
	};
}

DEFINE_SINGLETONPTR(app::animation::AnimationManager, ASLR(0x00FD3FA0));