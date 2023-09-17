#pragma once

namespace app
{
	class ObjZeldaItemTreeInfo : public CObjInfo
	{
	private:
		inline static const char* ms_ModelName = "zdlc03_obj_itemtree";
		inline static const char* ms_SkeletoName = "zdlc03_obj_itemtree";
		inline static const char* ms_AnimationName = "zdlc03_obj_itemtree";

	public:
		inline static const char* ms_pName = "ObjZeldaItemTreeInfo";

		hh::gfx::res::ResModel Model{};
		hh::gfx::res::ResSkeleton Skeleton{};
		hh::gfx::res::ResAnimSkeleton Animation{};

		ObjZeldaItemTreeInfo() { }

	protected:
		void Initialize(GameDocument& in_rDocument) override
		{
			auto packFile = ObjUtil::GetPackFile(ObjUtil::GetStagePackName(in_rDocument));

			Model = ObjUtil::GetModelResource(ms_ModelName, packFile);
			Skeleton = ObjUtil::GetSkeletonResource(ms_SkeletoName, packFile);
			Animation = ObjUtil::GetAnimationResource(ms_AnimationName, packFile);
		}

		const char* GetInfoName() override
		{
			return ms_pName;
		}
	};
}