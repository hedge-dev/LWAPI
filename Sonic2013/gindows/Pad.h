#pragma once

namespace gindows
{
	class Pad : Object
	{
	public:
		size_t Unk1;
		size_t Unk2;
		size_t Unk3;
		size_t Unk4;
		uint ButtonStates[14]{};
		size_t Unk5;
	};
}