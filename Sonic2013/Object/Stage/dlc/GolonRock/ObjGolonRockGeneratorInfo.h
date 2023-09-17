#pragma once

namespace app
{
	class ObjGolonRockGeneratorInfo : public CObjInfo
	{
	private:
		inline static const char* ms_ModelNames[] = { "zdlc03_obj_goron", "zdlc03_obj_goronrock" };
		inline static const char* ms_SkeletonName = "zdlc03_obj_goron";
		inline static const char* ms_AnimationName = "grn_appear";

	public:
		inline static const char* ms_pName = "ObjGolonRockGeneratorInfo";

		inline static const size_t ms_ModelCount = ARRAYSIZE(ms_ModelNames);
		
		ObjUtil::ResModelFixedContainer<ms_ModelCount> ModelContainer{};
		hh::gfx::res::ResSkeleton Skeleton{};;
		hh::gfx::res::ResAnimSkeleton Animation{};

		ObjGolonRockGeneratorInfo() { }

	protected:
		void Initialize(GameDocument& in_rDocument) override
		{
			auto packFile = ObjUtil::GetPackFile(ObjUtil::GetStagePackName(in_rDocument));
			for (size_t i = 0; i < ms_ModelCount; i++)
				ModelContainer.Models[i] = ObjUtil::GetModelResource(ms_ModelNames[i], packFile);

			Skeleton = ObjUtil::GetSkeletonResource(ms_SkeletonName, packFile);

			Animation = ObjUtil::GetAnimationResource(ms_AnimationName, packFile);
		}

	public:
		const char* GetInfoName() override
		{
			return ms_pName;
		}
	};
}