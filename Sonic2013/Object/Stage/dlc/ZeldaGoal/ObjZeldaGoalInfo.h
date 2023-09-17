#pragma once

namespace app
{
	class ObjZeldaGoalInfo : public CObjInfo
	{
	private:
		inline static const char* ms_pModelName = "zdlc03_obj_triforce";
		inline static const char* ms_pSkeletonName = "zdlc03_obj_triforce";
		inline static const char* ms_pAnimationScriptName = "zdlc03_obj_triforce";
		inline static const char* ms_pShadowModelName = "zdlc03_obj_triforce";

	public:
		inline static const char* ms_pName = "ObjZeldaGoalInfo";

		hh::gfx::res::ResModel Model{};
		hh::gfx::res::ResSkeleton Skeleton{};
		animation::AnimationResContainer AnimationContainer{ *m_pAllocator };
		res::ResShadowModel ShadowModel{};

		ObjZeldaGoalInfo() { }

	protected:
		void Initialize(GameDocument& in_rDocument) override
		{
			auto packFile = ObjUtil::GetPackFile(ObjUtil::GetStagePackName(in_rDocument));
			
			Model = ObjUtil::GetModelResource(ms_pModelName, packFile);
			
			Skeleton = ObjUtil::GetSkeletonResource(ms_pSkeletonName, packFile);

			auto animScript = ObjUtil::GetAnimationScriptResource(ms_pAnimationScriptName, packFile);
			animation::AnimationResContainer::LoadInfo animLoadInfo{ animScript, Skeleton, nullptr };
			AnimationContainer.LoadFromBuffer(animLoadInfo, packFile);

			ShadowModel = ObjUtil::GetShadowModel(ms_pShadowModelName, packFile);
		}

		const char* GetInfoName() override
		{
			return ms_pName;
		}
	};
}