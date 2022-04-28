#pragma once

namespace app::animation
{
	class SkeletonControlBase : public AnimationObj
	{
	public:
		virtual void SetWeight(float weight) = 0;
		virtual float GetWeight() const = 0;
		virtual void SetLocalTime(float time) = 0;
		virtual float GetLocalTime() = 0;
		virtual void SetPlaybackSpeed(float speed) = 0;
		virtual float GetPlaybackSpeed() const = 0;
		virtual void SetupSub(uint) = 0;
		virtual void CleanupSub() = 0;
		virtual void Update(UpdatingPhaze phase, app::fnd::SUpdateInfo& info) = 0;
	};

	class SkeletonControl : public SkeletonControlBase
	{
	public:
		inline static FUNCTION_PTR(SkeletonControl*, __cdecl, ms_fpCreate, ASLR(0x0040C820), hh::gfx::res::ResAnimSkeleton, uint, csl::fnd::IAllocator&);

		static SkeletonControl* Create(hh::gfx::res::ResAnimSkeleton in_anim, uint in_a2, csl::fnd::IAllocator& in_allocator)
		{
			return ms_fpCreate(in_anim, in_a2, in_allocator);
		}
	};
}
