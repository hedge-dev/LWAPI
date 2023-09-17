#pragma once

namespace SonicUSA::System
{
	inline static FUNCTION_PTR(float, __cdecl, ms_fpRadianMaskU, ASLR(0x0097B280), float);
	inline static FUNCTION_PTR(float, __cdecl, ms_fpRadianMaskS, ASLR(0x0097B2E0), float);

	inline float RadianMaskU(float in_value)
	{
		return ms_fpRadianMaskU(in_value);
	}

	inline float RadianMaskS(float in_value)
	{
		return ms_fpRadianMaskS(in_value);
	}
}