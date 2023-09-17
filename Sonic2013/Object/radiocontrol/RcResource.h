#pragma once

namespace app
{
	struct RcInfo
	{
		byte Type{};
		byte Variant{};
		char Unk2{};
	};

	struct RcCreateInfo
	{
		csl::math::Vector3 Position{};
		csl::math::Quaternion Rotation{};
		byte Type{};
		byte Variant{};
		char Unk1{};
		int Unk2{ 1 };
	};
}