#pragma once
#define HH_SOUND_DEVICE_AUTO csl::ut::SIGN_BIT

namespace app::fnd
{
	struct SoundDeviceTag
	{
		size_t Device{ HH_SOUND_DEVICE_AUTO };
	};
}