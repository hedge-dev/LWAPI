#pragma once

namespace app::SaveData
{
	class CSaveManager : public fnd::ReferencedObject, public csl::fnd::SingletonPointer<CSaveManager>
	{
	public:
		CResCommon<SSaveDataData> Data{};

		CSaveData GetSaveData() const
		{
			return CSaveData(Data);
		}
	};
}

DEFINE_SINGLETONPTR(app::SaveData::CSaveManager, ASLR(0x00FD3F9C));