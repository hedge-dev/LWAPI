#pragma once

namespace csl::ut
{
	struct Color8
	{
		uint8 R;
		uint8 G;
		uint8 B;
		uint8 A;

		inline operator const uint&() const
		{
			return *reinterpret_cast<const uint*>(this);
		}
	};

	struct ColorF
	{
		float A;
		float R;
		float G;
		float B;
	};

#define DEFINE_COLOR(NAME, R, G, B, A) inline static constexpr Color8 NAME{R, G, B, A};

	struct Colors
	{
	public:
		DEFINE_COLOR(Transparent, 0, 0, 0, 0);
		DEFINE_COLOR(White, 255, 255, 255, 255);
		DEFINE_COLOR(Black, 0, 0, 0, 255);
		DEFINE_COLOR(Red, 255, 0, 0, 255);
		DEFINE_COLOR(Green, 0, 255, 0, 255);
		DEFINE_COLOR(Blue, 0, 0, 255, 255);
	};
	using Colours = Colors;

#undef DEFINE_COLOR
}