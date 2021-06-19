#pragma once
class hkaAnimatedSkeleton;

namespace app::animation
{
	class SkeletonBlenderBase : public AnimationObj
	{
		INSERT_PADDING(52);
		
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
	};

	class SkeletonBlenderHavok : public SkeletonBlenderBase
	{
	protected:
		hkaAnimatedSkeleton* m_pSkel{};
	};

	class SkeletonBlender : public SkeletonBlenderHavok
	{
		
	};
	
	class AnimSkeletonBlender
	{
	protected:
		SkeletonBlender* m_pBlender{};

		void swap(SkeletonBlender* pBlender)
		{
			if (m_pBlender == pBlender)
				return;

			if (m_pBlender)
				m_pBlender->Release();

			m_pBlender = pBlender;
			if (pBlender)
				pBlender->AddRef();
		}
		
	public:
		AnimSkeletonBlender(SkeletonBlender* pBlender) : m_pBlender(pBlender)
		{
			
		}

		AnimSkeletonBlender& operator=(SkeletonBlender* pBlender)
		{
			m_pBlender = pBlender;
			return *this;
		}

		operator SkeletonBlender*() const
		{
			return m_pBlender;
		}
		
		SkeletonBlender* operator->() const
		{
			return m_pBlender;
		}
	};
}