#pragma once

namespace csl::ut
{
	struct Color8
	{
		uint8 r;
		uint8 g;
		uint8 b;
		uint8 a;
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