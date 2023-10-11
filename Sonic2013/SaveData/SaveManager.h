#pragma once

namespace app::SaveData
{
	class CSaveManager : public fnd::ReferencedObject, public csl::fnd::SingletonPointer<CSaveManager>
	{
	private:
		inline static FUNCTION_PTR(CSaveData*, __thiscall, ms_fpGetSaveData, ASLR(0x00901220), const CSaveManager*, void*);

	public:
		class CImpl;

		CImpl* pImpl{};

		CSaveData* GetSaveData(void* out_pValue) const
		{
			return ms_fpGetSaveData(this, out_pValue);
		}
	};
}

DEFINE_SINGLETONPTR(app::SaveData::CSaveManager, ASLR(0x00FD3F9C));