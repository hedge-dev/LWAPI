#pragma once

namespace app
{
	class ObjYoshiInfo : public CObjInfo
	{
	private:
		inline static const char* ms_ModelNames[] = { "zdlc02_obj_yoshi_green", "zdlc02_obj_yoshi_red", "zdlc02_obj_yoshi_blue", "zdlc02_obj_yoshi_yellow" };
		inline static const char* ms_SkeletonName = "zdlc02_obj_yoshi";
		inline static const char* ms_pAnimScriptName = "yoshi";
		inline static const char* ms_TexSrtAnimNames[] = {
			"yos_result01_start_Eye_L", "yos_result01_start_Eye_R", "yos_result01_loop_Eye_L", "yos_result01_loop_Eye_R",
			"yos_result02_start_Eye_L", "yos_result02_start_Eye_R", "yos_result02_loop_Eye_L", "yos_result02_loop_Eye_R",
			"yos_result03_start_Eye_L", "yos_result03_start_Eye_R", "yos_result03_loop_Eye_L", "yos_result03_loop_Eye_R",
			"yos_result04_start_Eye_L", "yos_result04_start_Eye_R", "yos_result04_loop_Eye_L", "yos_result04_loop_Eye_R",
			"yos_result05_start_Eye_L", "yos_result05_start_Eye_R", "yos_result05_loop_Eye_L", "yos_result05_loop_Eye_R",
			"yos_result06_start_Eye_L", "yos_result06_start_Eye_R", "yos_result06_loop_Eye_L", "yos_result06_loop_Eye_R"
		};

	public:
		inline static const char* ms_pName = "ObjYoshiInfo";

		inline static const size_t ms_ModelCount = ARRAYSIZE(ms_ModelNames);
		inline static const size_t ms_TexSrtAnimCount = ARRAYSIZE(ms_TexSrtAnimNames);

		ObjUtil::ResModelFixedContainer<ms_ModelCount> ModelContainer{};
		hh::gfx::res::ResSkeleton Skeleton{};
		animation::AnimationResContainer AnimationContainer{ *m_pAllocator };
		csl::ut::FixedArray<int, 12> AnimationIndices{};
		ObjUtil::ResTexSrtAnimFixedContainer<ms_TexSrtAnimCount> TexSrtAnimContainer{};

		ObjYoshiInfo() { }

		void Initialize(GameDocument& in_rDocument) override
		{
			auto packFile = ObjUtil::GetPackFile(ObjUtil::GetStagePackName(in_rDocument));
			for (size_t i = 0; i < ModelContainer.Models.size(); i++)
				ModelContainer.Models[i] = ObjUtil::GetModelResource(ms_ModelNames[i], packFile);

			Skeleton = ObjUtil::GetSkeletonResource(ms_SkeletonName, packFile);

			auto animScript = ObjUtil::GetAnimationScriptResource(ms_pAnimScriptName, packFile);
			animation::AnimationResContainer::LoadInfo animLoadInfo{ animScript, Skeleton, nullptr };
			AnimationContainer.LoadFromBuffer(animLoadInfo, packFile);

			for (size_t i = 0; i < AnimationIndices.size(); i++)
			{
				AnimationIndices[i] = i % 6;
			}

			for (size_t i = 0; i < TexSrtAnimContainer.Animations.size(); i++)
				TexSrtAnimContainer.Animations[i] = ObjUtil::GetTexSrtAnimationResource(ms_TexSrtAnimNames[i], packFile);
		}

		const char* GetInfoName() override
		{
			return ms_pName;
		}
	};
}