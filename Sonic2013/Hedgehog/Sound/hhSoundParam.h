#pragma once

namespace app::fnd
{
	struct SoundParam
	{
		float Volume{ 1.0f };
		float TweenFactor{}; // Used in a function called MoveToTweenReset
		size_t Unk1{};
		SoundDeviceTag Device{};
		hhLong StartTime{};
		bool Paused{};
		
		SoundParam()
		{
			
		}
	};
}