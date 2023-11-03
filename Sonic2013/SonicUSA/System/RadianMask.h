#pragma once

namespace SonicUSA::System
{
	inline float RadianMaskU(float in_value)
	{
		FUNCTION_PTR(float, __cdecl, fpRadianMaskU, ASLR(0x0097B280), float);
		return fpRadianMaskU(in_value);
	}

	inline float RadianMaskS(float in_value)
	{
		FUNCTION_PTR(float, __cdecl, fpRadianMaskS, ASLR(0x0097B2E0), float);
		return fpRadianMaskS(in_value);
	}
}