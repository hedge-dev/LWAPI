#pragma once

namespace app::xgame
{
	class MarkerStatus
	{
	public:
		csl::math::Vector3 Position{};
		csl::math::Quaternion Rotation{};
		bool Unk1{};
		char Unk2{};
		int Unk3{};
		float Unk4{};
	};

	class StatusCheckPoint : public GameStatusBase
	{
	public:
		inline static const char* ms_pName = (const char*)ASLR(0x00E09418);

		MarkerStatus Unk1{};
		MarkerStatus Unk2{};
		INSERT_PADDING(112);

	public:
		const MarkerStatus* GetMarker() const
		{
			return &Unk1;
		}
	};
}