#pragma once

namespace app::debris
{
	typedef int EInfoType;

	struct SDebrisBaseInfo
	{
		math::Transform Transform{};
		float Unk1{};
		float Unk2{};
		float Unk3{};
		csl::ut::Bitset<uint> Unk4{};
		csl::math::Vector3 Unk5{};
		csl::math::Vector3 Unk6{};
		float Unk7{};
		float Unk8{};
		INSERT_PADDING(8) {};
		csl::math::Vector3 Unk14{};
		float Unk9{};
		INSERT_PADDING(12) {};
		float Unk10{};
		float Unk11{};
		int Unk12{ 176 };
		int Unk13{};
		EInfoType Type{};

		SDebrisBaseInfo(EInfoType in_infoType)
		{
			Type = in_infoType;
		}
	};
}