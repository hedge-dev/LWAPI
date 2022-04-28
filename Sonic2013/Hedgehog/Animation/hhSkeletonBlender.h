#pragma once
class hkaAnimatedSkeleton;

namespace app::animation
{
	class SkeletonBlenderBase : public AnimationObj
	{
	public:
		INSERT_PADDING(40) {};
		CharactorAnimation* m_pAnimation{};
		INSERT_PADDING(8) {};
		
	public:
		virtual void SetWeight(float weight) = 0;
		virtual float GetWeight() const = 0;
		virtual void SetLocalTime(float time) = 0;
		virtual float GetLocalTime() const = 0;
		virtual void SetPlaybackSpeed(float speed) = 0;
		virtual float GetPlaybackSpeed() const = 0;
		virtual void SetupSub(uint sub) = 0;
		virtual void CleanupSub() = 0;
		virtual void Update(UpdatingPhaze phase, fnd::SUpdateInfo& info) = 0;

		void BindAnimation(CharactorAnimation& in_animation)
		{
			m_pAnimation = &in_animation;
		}
	};

	class SkeletonBlenderHavok : public SkeletonBlenderBase
	{
	protected:
		hkaAnimatedSkeleton* m_pSkel{};
	};

	class SkeletonBlender : public SkeletonBlenderHavok
	{
	public:
		inline static FUNCTION_PTR(SkeletonBlender*, __cdecl, ms_fpCreate, ASLR(0x0040C470), uint, csl::fnd::IAllocator&);

		static SkeletonBlender* Create(uint in_category, csl::fnd::IAllocator& in_allocator)
		{
			return ms_fpCreate(in_category, in_allocator);
		}
	};
	
	class AnimSkeletonBlender : public app::ut::RefPtr<SkeletonBlender>
	{
	public:
		AnimSkeletonBlender()
		{
			
		}

		AnimSkeletonBlender(SkeletonBlender* in_pBlender) : RefPtr<app::animation::SkeletonBlender>(in_pBlender)
		{

		}

		void BindAnimation(CharactorAnimation& in_anim)
		{
			if (!get())
				return;

			ref().BindAnimation(in_anim);
		}
	};
}