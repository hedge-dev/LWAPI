#pragma once
class hkaAnimatedSkeleton;

namespace app::animation
{
	class SkeletonBlenderBase : public AnimationObj
	{
	public:
		INSERT_PADDING(40) {};
		CharactorAnimation* pAnimation{};
		INSERT_PADDING(8) {};
		
	public:
		virtual void SetWeight(float in_weight) = 0;
		virtual float GetWeight() const = 0;
		virtual void SetLocalTime(float in_time) = 0;
		virtual float GetLocalTime() const = 0;
		virtual void SetPlaybackSpeed(float in_speed) = 0;
		virtual float GetPlaybackSpeed() const = 0;
		virtual void SetupSub(uint in_sub) = 0;
		virtual void CleanupSub() = 0;
		virtual void Update(UpdatingPhaze phase, fnd::SUpdateInfo& in_rInfo) = 0;

		void BindAnimation(CharactorAnimation& in_rAnimation)
		{
			pAnimation = &in_rAnimation;
		}
	};

	class SkeletonBlenderHavok : public SkeletonBlenderBase
	{
	protected:
		hkaAnimatedSkeleton* m_pSkel{};
	};

	class SkeletonBlender : public SkeletonBlenderHavok
	{
	private:
		inline static FUNCTION_PTR(SkeletonBlender*, __cdecl, ms_fpCreate, ASLR(0x0040C470), uint, csl::fnd::IAllocator&);

	public:
		static SkeletonBlender* Create(uint in_category, csl::fnd::IAllocator& in_rAllocator)
		{
			return ms_fpCreate(in_category, in_rAllocator);
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

		void BindAnimation(CharactorAnimation& in_rAnim)
		{
			if (!get())
				return;

			ref().BindAnimation(in_rAnim);
		}
	};
}