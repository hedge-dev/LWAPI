#pragma once

namespace app::animation
{
	class SkeletonBlenderBase : public AnimationObj
	{
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
}