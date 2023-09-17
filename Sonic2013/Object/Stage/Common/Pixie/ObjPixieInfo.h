#pragma once

namespace app
{
	class CObjPixieInfo : public CObjInfo
	{
	private:
		inline static const char* ms_pPackFileName = "CommonObject.pac";
		inline static const char* ms_pNames[] = { "cmn_obj_wisplas", "cmn_obj_wispegl", "cmn_obj_wispaste", "cmn_obj_wispdrl",
			"cmn_obj_wisprkt", "cmn_obj_wisprtm", "cmn_obj_wisphvr", ""};
		inline static const char* ms_pAnimationInboxNames[] = { "cmn_obj_wisplas_inbox", "cmn_obj_wispegl_inbox", "cmn_obj_wispaste_inbox", "cmn_obj_wispdrl_inbox",
			"cmn_obj_wisprkt_inbox", "cmn_obj_wisprtm_inbox", "cmn_obj_wisphvr_inbox", "" };
		inline static const char* ms_pAnimationReleaseNames[] = { "cmn_obj_wisplas_release", "cmn_obj_wispegl_release", "cmn_obj_wispaste_release", "cmn_obj_wispdrl_release",
			"cmn_obj_wisprkt_release", "cmn_obj_wisprtm_release", "cmn_obj_wisphvr_release", "" };
		inline static const char* ms_pDrillTextureAnimationName = "cmn_obj_wispdrl_stripe";

	public:
		inline static const char* ms_pName = "CObjPixieInfo";

		inline static const size_t ms_PixieCount = ARRAYSIZE(ms_pNames);

		ObjUtil::ResModelFixedContainer<ms_PixieCount> ModelContainer{};
		ObjUtil::ResSkeletonFixedContainer<ms_PixieCount> SkeletonContainer{};
		ObjUtil::ResCharAnimFixedContainer<ms_PixieCount> AnimationInboxContainer{};
		ObjUtil::ResCharAnimFixedContainer<ms_PixieCount> AnimationReleaseContainer{};
		hh::gfx::res::ResAnimTexSrt DrillTextureAnimation{};

		CObjPixieInfo() : CObjInfo()
		{
			
		}

		void Initialize(GameDocument& in_rDocument) override
		{
			auto packFile = ObjUtil::GetPackFile(ms_pPackFileName);
			
			for (size_t i = 0; i < ms_PixieCount; i++)
			{
				ModelContainer.Models[i] = ObjUtil::GetModelResource(ms_pNames[i], packFile);
				SkeletonContainer.Skeletons[i] = ObjUtil::GetSkeletonResource(ms_pNames[i], packFile);
				AnimationInboxContainer.Animations[i] = ObjUtil::GetAnimationResource(ms_pAnimationInboxNames[i], packFile);
				AnimationReleaseContainer.Animations[i] = ObjUtil::GetAnimationResource(ms_pAnimationReleaseNames[i], packFile);
			}
			
			DrillTextureAnimation = ObjUtil::GetTexSrtAnimationResource(ms_pDrillTextureAnimationName, packFile);
		}

		const char* GetInfoName() override
		{
			return ms_pName;
		}
	};
}