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

		void Setup(csl::fnd::IAllocator& in_allocator, const ResCharAnim& in_anim, bool in_stop)
		{
			Cleanup();
			if (in_anim.IsValid())
			{
				m_pSkelControl = SkeletonControl::Create(hh::gfx::res::ResAnimSkeleton{ in_anim }, in_stop, in_allocator);
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