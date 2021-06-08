#pragma once

namespace app::fnd
{
	struct SoundParam
	{
		float m_Volume{};
		float m_TweenFactor{}; // Used in a function called MoveToTweenReset
		size_t m_Unk1;
		SoundDeviceTag m_Device{};
		hhLong m_StartTime{};
		bool m_Paused{};
		
		SoundParam()
		{
			
		}
	};
}