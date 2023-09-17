#pragma once

namespace app
{
	class ObjEggBlockInfo : public CObjInfo
	{
	private:
		inline static const char* ms_ModelName = "zdlc02_obj_eggblock";

	public:
		inline static const char* ms_pName = "ObjEggBlockInfo";

		hh::gfx::res::ResModel Model{};

		ObjEggBlockInfo() { }

	protected:
		void Initialize(GameDocument& in_rDocument) override
		{
			auto packFile = ObjUtil::GetPackFile(ObjUtil::GetStagePackName(in_rDocument));
			Model = ObjUtil::GetModelResource(ms_ModelName, packFile);
		}

		const char* GetInfoName() override
		{
			return ms_pName;
		}

		void RegisterCallback(CObjInfoContainer& container) override
		{
			auto* pEggInfo = new(GetAllocator()) ObjEggInfo();
			if (pEggInfo)
				container.Register(pEggInfo->GetInfoName(), pEggInfo);
			
			auto* pYoshiInfo = new(GetAllocator()) ObjYoshiInfo();
			if (pYoshiInfo)
				container.Register(pYoshiInfo->GetInfoName(), pYoshiInfo);
		}
	};
}