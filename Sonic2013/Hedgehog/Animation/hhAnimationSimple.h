#pragma once

namespace app::animation
{
	class AnimationSimple : public AnimationClip
	{
	protected:
		const SimpleDef* m_pDef{};
		INSERT_PADDING(24) {}; // PlayingData
		INSERT_PADDING(8) {}; // AnimSkeltonControl
		
	public:
		AnimationSimple()
		{
			sizeof(AnimationSimple);
		}
	};
}