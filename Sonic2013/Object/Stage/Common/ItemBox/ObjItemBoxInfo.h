#pragma once

namespace app
{
	class ObjItemBoxInfo : public CObjInfo
	{
	private:
		inline static const char* ms_pPackFileName = "CommonObject.pac";
		inline static const char* ms_pModelNames[] = { "cmn_obj_itembox", "cmn_obj_itembox_fly" };
		inline static const char* ms_pItemNames[] = { "cmn_obj_item_speedup", "cmn_obj_item_muteki", "cmn_obj_item_warp" };
		inline static const char* ms_pTexSrtAnimName = "cmn_obj_itembox_opa";
		inline static const char* ms_pAnimationName = "cmn_obj_oneup";

	public:
		inline static const char* ms_pName = "ObjItemBoxInfo";

		inline static const size_t ms_ModelCount = ARRAYSIZE(ms_pModelNames);
		inline static const size_t ms_ItemCount = ARRAYSIZE(ms_pItemNames);

		ObjUtil::ResModelFixedContainer<ms_ModelCount> ModelContainer{};
		hh::gfx::res::ResAnimTexSrt TextureAnimation{};
		ObjUtil::ResModelFixedContainer<ms_ItemCount> ItemModelContainer{};
		ObjUtil::ResSkeletonFixedContainer<ms_ItemCount> ItemSkeletonContainer{};
		ObjUtil::ResCharAnimFixedContainer<ms_ItemCount> ItemAnimationContainer{};

		ObjItemBoxInfo() : CObjInfo()
		{
			
		}

		void Initialize(GameDocument& in_rDocument) override
		{
			auto packFile = ObjUtil::GetPackFile(ms_pPackFileName);
			for (size_t i = 0; i < ModelContainer.Models.size(); i++)
				ModelContainer.Models[i] = ObjUtil::GetModelResource(ms_pModelNames[i], packFile);

			TextureAnimation = ObjUtil::GetTexSrtAnimationResource(ms_pTexSrtAnimName, packFile);
			
			for (size_t i = 0; i < ItemModelContainer.Models.size(); i++)
			{
				ItemModelContainer.Models[i] = ObjUtil::GetModelResource(ms_pItemNames[i], packFile);
				ItemSkeletonContainer.Skeletons[i] = ObjUtil::GetSkeletonResource(ms_pItemNames[i], packFile);
				ItemAnimationContainer.Animations[i] = ObjUtil::GetAnimationResource(ms_pItemNames[i], packFile);
			}
		}

		const char* GetInfoName() override
		{
			return ms_pName;
		}
	};
}