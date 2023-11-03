#pragma once

namespace app::debrisUtil
{
	class DebrisObjRandomSpace;

	inline DebrisObjRandomSpace* CreateRandomSpaceDebris(GameDocument& in_rDocument, const debris::SRandomSpaceDebrisInfo& in_rDebrisInfo)
	{
		FUNCTION_PTR(DebrisObjRandomSpace*, __cdecl, fpCreateRandomSpaceDebris, ASLR(0x00846F80), GameDocument&, const debris::SRandomSpaceDebrisInfo&);
		return fpCreateRandomSpaceDebris(in_rDocument, in_rDebrisInfo);
	}
}