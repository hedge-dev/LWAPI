#pragma once

namespace app
{
	struct SSaveDataData
	{
		INSERT_PADDING(4) {};
		SGameDataData* pGameData{};
	};
}

namespace app::SaveData
{
	class CSaveData : CResCommon<SSaveDataData>
	{
	public:
		CSaveData(SSaveDataData* in_pData) : CResCommon<SSaveDataData>(in_pData)
		{

		}

		CGameData GetCurrentGameData() const
		{
			return CGameData(ref().pGameData);
		}
	};
}