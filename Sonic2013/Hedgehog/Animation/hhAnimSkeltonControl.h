#pragma once

namespace app::animation
{
	class AnimSkeletonControl
	{
	protected:
		ut::RefPtr<SkeletonControl> m_pSkelControl{};
		bool m_HasBlender{};

	public:
		AnimSkeletonControl()
		{
			
		}

		void Cleanup()
		{
			m_pSkelControl = nullptr;
		}
		
		~AnimSkeletonControl()
		{
			
		}
	};
}