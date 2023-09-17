#pragma once

namespace app
{
	class ObjGossipStoneInfo : public CObjInfo
	{
	private:
		inline static const char* ms_pModelName = "zdlc03_obj_gossipstone";
		inline static const char* ms_pSkeletonName = "zdlc03_obj_gossipstone";
		inline static const char* ms_pAnimationName = "zdlc03_obj_gossipstone";
		inline static const char* ms_pFairyModelName = "zdlc03_obj_fairy";
		inline static const char* ms_pFairySkeletonName = "zdlc03_obj_fairy";
		inline static const char* ms_pFairyAnimationName = "zdlc03_obj_fairy";

	public:
		inline static const char* ms_pName = "ObjGossipStoneInfo";

		hh::gfx::res::ResModel Model{};
		hh::gfx::res::ResSkeleton Skeleton{};
		hh::gfx::res::ResAnimSkeleton Animation{};
		hh::gfx::res::ResModel FairyModel{};
		hh::gfx::res::ResSkeleton FairySkeleton{};
		hh::gfx::res::ResAnimSkeleton FairyAnimation{};

		ObjGossipStoneInfo() { }

	protected:
		void Initialize(GameDocument& in_rDocument) override
		{
			auto packFile = ObjUtil::GetPackFile(ObjUtil::GetStagePackName(in_rDocument));

			Model = ObjUtil::GetModelResource(ms_pModelName, packFile);
			Skeleton = ObjUtil::GetSkeletonResource(ms_pSkeletonName, packFile);
			Animation = ObjUtil::GetAnimationResource(ms_pAnimationName, packFile);
			
			FairyModel = ObjUtil::GetModelResource(ms_pFairyModelName, packFile);
			FairySkeleton = ObjUtil::GetSkeletonResource(ms_pFairySkeletonName, packFile);
			FairyAnimation = ObjUtil::GetAnimationResource(ms_pFairyAnimationName, packFile);
		}

		const char* GetInfoName() override
		{
			return ms_pName;
		}
	};
}