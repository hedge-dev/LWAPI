#pragma once

namespace app::worldmap
{
	class CWorldMapDioramaStage : public CSetObjectListener
	{
	private:
		inline static FUNCTION_PTR(void, __cdecl, ms_fpRegisterResourceInfo, ASLR(0x0094D450), GameDocument&, const char*, csl::fnd::IAllocator&);
		
		INSERT_PADDING(320);

	public:
		static void RegisterResourceInfo(GameDocument& in_rDocument, const char* in_pDioramaName, csl::fnd::IAllocator& in_rAllocator)
		{
			ms_fpRegisterResourceInfo(in_rDocument, in_pDioramaName, in_rAllocator);

			/*auto* pInfoContainer = in_rDocument.GetService<CObjInfoContainer>();
			
			CWorldMapDioramaInfo* pInfo = new(in_rAllocator) CWorldMapDioramaInfo(in_pDioramaName);
			if (!pInfo)
				return;

			pInfoContainer->Register(pInfo->GetInfoName(), pInfo);*/
		}
	};
}