#pragma once

namespace app
{
	class CObjOneUpInfo : public CObjInfo
	{
	private:
		inline static const char* ms_pPackFileName = "CommonObject.pac";
		inline static const char* ms_pModelName = "cmn_obj_oneup";
		inline static const char* ms_pSkeletonName = "cmn_obj_oneup";
		inline static const char* ms_pAnimationName = "cmn_obj_oneup";

	public:
		inline static const char* ms_pName = "CObjOneUpInfo";

		hh::gfx::res::ResModel Model{};
		hh::gfx::res::ResSkeleton Skeleton{};
		hh::gfx::res::ResAnimSkeleton Animation{};

		void Initialize(GameDocument& in_rDocument) override
		{
			auto packFile = ObjUtil::GetPackFile(ms_pPackFileName);
			Model = ObjUtil::GetModelResource(ms_pModelName, packFile);
			Skeleton = ObjUtil::GetSkeletonResource(ms_pSkeletonName, packFile);
			Animation = ObjUtil::GetAnimationResource(ms_pAnimationName, packFile);
		}

		const char* GetInfoName() override
		{
			return ms_pName;
		}
	};
}