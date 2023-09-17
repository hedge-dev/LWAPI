#pragma once

namespace app
{
	class CSharedObjInfo : CObjInfo
	{
	private:
		inline static const char* ms_pPackFileName = "CommonObject.pac";
		inline static const char* ms_pRingModelName = "cmn_obj_ring";
		inline static const char* ms_pSuperRingModelName = "cmn_obj_superring";
		inline static const char* ms_pSpikeBallModelName = "cmn_obj_thornball";
		inline static const size_t ms_RingModelLodCount = 3;

	public:
		inline static const char* ms_pName = "CSharedObjInfo";

		hh::gfx::res::ResModel RingModel{};
		hh::gfx::res::ResModel SuperRingModel{};
		hh::gfx::res::ResModel SpikeBallModel{};
		ObjUtil::ResModelFixedContainer<ms_RingModelLodCount> RingModelLods{};
		
		void Initialize(GameDocument& in_rDocument) override
		{
			auto packFile = ObjUtil::GetPackFile(ms_pPackFileName);
			RingModel = ObjUtil::GetModelResource(ms_pRingModelName, packFile);
			SuperRingModel = ObjUtil::GetModelResource(ms_pSuperRingModelName, packFile);
			SpikeBallModel = ObjUtil::GetModelResource(ms_pSpikeBallModelName, packFile);
			RingModelLods = ObjUtil::GetLodModelResource<ms_RingModelLodCount>(ms_pRingModelName, packFile);
		}

		const char* GetInfoName() override
		{
			return ms_pName;
		}
	};
}