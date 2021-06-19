#pragma once

namespace app::animation
{
	class AnimationSimple : public AnimationClip
	{
	protected:
		const SimpleDef* m_pDef{};
		INSERT_PADDING(24) {}; // PlayingData
		AnimSkeletonControl m_SkelControl{};
		
	public:
		AnimationSimple()
		{
			
		}

		void Cleanup()
		{
			m_SkelControl.Cleanup();
		}
	};
}