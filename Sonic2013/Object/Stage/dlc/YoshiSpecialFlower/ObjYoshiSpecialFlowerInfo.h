#pragma once

namespace app
{
	class ObjYoshiSpecialFlowerInfo : public CObjInfo
	{
	private:
		inline static const char* ms_ModelName = "zdlc02_obj_goalA_on";
		inline static const char* ms_SkeletoName = "zdlc02_obj_goalA_on";
		inline static const char* ms_AnimationName = "zdlc02_obj_goalA_on_idle";

	public:
		inline static const char* ms_pName = "ObjYoshiSpecialFlowerInfo";

		hh::gfx::res::ResModel Model{};
		hh::gfx::res::ResSkeleton Skeleton{};
		hh::gfx::res::ResAnimSkeleton Animation{};

		ObjYoshiSpecialFlowerInfo() { }

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