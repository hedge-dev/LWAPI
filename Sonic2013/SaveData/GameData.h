#pragma once

namespace app
{
	struct SGameDataData
	{
		INSERT_PADDING(32);
		SFlagSetData* pFlagData{};
	};
}

namespace app::SaveData
{
	class CGameData : CResCommon<SGameDataData>
	{
	public:
		CGameData(SGameDataData* in_pData) : CResCommon<SGameDataData>(in_pData)
		{

		}

		CFlagSet GetFlagSet() const
		{
			return CFlagSet(ref().pFlagData);
		}
	};
}