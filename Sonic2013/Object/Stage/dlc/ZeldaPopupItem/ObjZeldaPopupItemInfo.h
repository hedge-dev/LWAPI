#pragma once

namespace app
{
	class ObjZeldaPopupItem;

	class ObjZeldaPopupItemInfo : public CObjInfo
	{
	private:
		inline static const char* ms_ModelNames[] = { "zdlc03_obj_rupee_green", "zdlc03_obj_rupee_blue", "zdlc03_obj_rupee_red", "zdlc03_obj_rupee_purple", "zdlc03_obj_rupee_gold", "zdlc03_obj_heart" };
		inline static const char* ms_SkeletonNames[] = { "zdlc03_obj_rupee", "zdlc03_obj_heart" };
		inline static const char* ms_AnimationNames[] = { "zdlc03_obj_rupee_popup", "zdlc03_obj_heart_popup" };

	public:
		inline static const char* ms_pName = "ObjZeldaPopupItemInfo";

		inline static size_t ms_ModelCount = ARRAYSIZE(ms_ModelNames);
		inline static size_t ms_SkeletonCount = ARRAYSIZE(ms_SkeletonNames);
		inline static size_t ms_AnimationCount = ARRAYSIZE(ms_AnimationNames);
		
		hh::gfx::res::ResModel Models[ARRAYSIZE(ms_ModelNames)]{};
		hh::gfx::res::ResSkeleton Skeletons[ARRAYSIZE(ms_SkeletonNames)]{};
		hh::gfx::res::ResAnimSkeleton Animations[ARRAYSIZE(ms_AnimationNames)]{};
		GameObjectHandle<ObjZeldaPopupItem> PopupHandle{};

		ObjZeldaPopupItemInfo() { }

	protected:
		void Initialize(GameDocument& in_rDocument) override
		{
			auto packFile = ObjUtil::GetPackFile(ObjUtil::GetStagePackName(in_rDocument));
			for (size_t i = 0; i < ms_ModelCount; i++)
				Models[i] = ObjUtil::GetModelResource(ms_ModelNames[i], packFile);

			for (size_t i = 0; i < ms_SkeletonCount; i++)
				Skeletons[i] = ObjUtil::GetSkeletonResource(ms_SkeletonNames[i], packFile);

			for (size_t i = 0; i < ms_AnimationCount; i++)
				Animations[i] = ObjUtil::GetAnimationResource(ms_AnimationNames[i], packFile);
		}

	public:
		const char* GetInfoName() override
		{
			return ms_pName;
		}

		void SetPopupItem(ObjZeldaPopupItem* in_pObject);
	};
}