#pragma once

namespace app
{
	class ObjTreasureBoxInfo : public CObjInfo
	{
	private:
		inline static const char* ms_pModelName = "zdlc03_obj_treasurebox";
		inline static const char* ms_pSkeletonName = "zdlc03_obj_treasurebox";
		inline static const char* ms_pAnimationName = "treasurebox_open";
		inline static const char* ms_pHeartContainerModelName = "zdlc03_obj_heartcase";

	public:
		inline static const char* ms_pName = "ObjTreasureBoxInfo";

		hh::gfx::res::ResModel Model{};
		hh::gfx::res::ResSkeleton Skeleton{};
		hh::gfx::res::ResAnimSkeleton Animation{};
		hh::gfx::res::ResModel HeartContainerModel{};

		ObjTreasureBoxInfo() { }

	protected:
		void Initialize(GameDocument& in_rDocument) override
		{
			auto packFile = ObjUtil::GetPackFile(ObjUtil::GetStagePackName(in_rDocument));

			Model = ObjUtil::GetModelResource(ms_pModelName, packFile);
			Skeleton = ObjUtil::GetSkeletonResource(ms_pSkeletonName, packFile);
			Animation = ObjUtil::GetAnimationResource(ms_pAnimationName, packFile);

			HeartContainerModel = ObjUtil::GetModelResource(ms_pHeartContainerModelName, packFile);
		}

		const char* GetInfoName() override
		{
			return ms_pName;
		}

		void RegisterCallback(CObjInfoContainer& container) override
		{
			auto* pItemInfo = new(GetAllocator()) ObjZeldaPopupItemInfo();
			if (pItemInfo)
				container.Register(pItemInfo->GetInfoName(), pItemInfo);
		}
	};
}