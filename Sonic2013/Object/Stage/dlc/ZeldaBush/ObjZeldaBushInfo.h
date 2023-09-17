#pragma once

namespace app
{
	class ObjZeldaBushInfo : public CObjInfo
	{
	private:
		inline static const char* ms_pModelNames[] = { "zdlc03_obj_bushA", "zdlc03_obj_bushB" };
		inline static const char* ms_pShadowModelNames[] = { "zdlc03_obj_bushA_shadow", "zdlc03_obj_bushB_shadow" };
		inline static const char* ms_pSkeletonNames[] = { "zdlc03_obj_bushA", "zdlc03_obj_bushB" };
		inline static const char* ms_pAnimationNames[] = { "zdlc03_obj_bushA", "zdlc03_obj_bushB" };

	public:
		inline static const char* ms_pName = "ObjZeldaBushInfo";

		inline static const size_t ms_ModelCount = ARRAYSIZE(ms_pModelNames);
		inline static const size_t ms_ShadowModelCount = ARRAYSIZE(ms_pShadowModelNames);
		inline static const size_t ms_SkeletonCount = ARRAYSIZE(ms_pSkeletonNames);
		inline static const size_t ms_AnimationCount = ARRAYSIZE(ms_pAnimationNames);

		ObjUtil::ResModelFixedContainer<ms_ModelCount> ModelContainer{};
		ObjUtil::ResSkeletonFixedContainer<ms_SkeletonCount> SkeletonContainer{};
		ObjUtil::ResCharAnimFixedContainer<ms_AnimationCount> AnimationContainer{};
		ObjUtil::ResModelFixedContainer<ms_ShadowModelCount> ShadowModelContainer{};

		ObjZeldaBushInfo() { }

	protected:
		void Initialize(GameDocument& in_rDocument) override
		{
			auto packFile = ObjUtil::GetPackFile(ObjUtil::GetStagePackName(in_rDocument));
			for (size_t i = 0; i < ModelContainer.Models.size(); i++)
				ModelContainer.Models[i] = ObjUtil::GetModelResource(ms_pModelNames[i], packFile);

			for (size_t i = 0; i < SkeletonContainer.Skeletons.size(); i++)
				SkeletonContainer.Skeletons[i] = ObjUtil::GetSkeletonResource(ms_pSkeletonNames[i], packFile);

			for (size_t i = 0; i < AnimationContainer.Animations.size(); i++)
				AnimationContainer.Animations[i] = ObjUtil::GetAnimationResource(ms_pAnimationNames[i], packFile);

			for (size_t i = 0; i < ShadowModelContainer.Models.size(); i++)
				ShadowModelContainer.Models[i] = ObjUtil::GetModelResource(ms_pShadowModelNames[i], packFile);
		}

		const char* GetInfoName() override
		{
			return ms_pName;
		}

		void RegisterCallback(CObjInfoContainer& container) override
		{
			auto* pPopupInfo = new(GetAllocator()) ObjZeldaPopupItemInfo();
			if (pPopupInfo)
				container.Register(pPopupInfo->GetInfoName(), pPopupInfo);
		}
	};
}