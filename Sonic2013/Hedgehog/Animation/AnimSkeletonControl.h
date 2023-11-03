#pragma once

namespace app::animation
{
	class AnimSkeletonControl
	{
	protected:
		SkeletonControl* m_pSkelControl{};
		bool m_HasBlender{};

	public:
		AnimSkeletonControl()
		{
			
		}

		void Setup(csl::fnd::IAllocator& in_rAllocator, const ResCharAnim& in_rAnim, bool in_stop)
		{
			Cleanup();
			if (in_rAnim.IsValid())
			{
				m_pSkelControl = SkeletonControl::Create(hh::gfx::res::ResAnimSkeleton{ in_rAnim }, in_stop, in_rAllocator);
				if (m_pSkelControl)
					m_pSkelControl->SetPlaybackSpeed(0);
			}
		}

		void Cleanup()
		{
			if (m_pSkelControl)
				m_pSkelControl->Release();

			m_pSkelControl = nullptr;
		}
		
		~AnimSkeletonControl()
		{
			Cleanup();
		}
	};
}