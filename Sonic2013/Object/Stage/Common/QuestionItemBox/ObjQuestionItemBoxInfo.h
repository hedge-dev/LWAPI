#pragma once

namespace app
{
	class ObjQuestionItemBoxInfo : public CObjInfo
	{
	private:
		inline static const char* ms_pCommonPackFileName = "CommonObject.pac";
		inline static const char* ms_pBattlePackFileName = "zbatl_obj.pac";
		inline static const char* ms_pItemModelNames[] = { "batl_obj_item_question", "batl_obj_wispqua", "batl_obj_hand", "batl_obj_missile", "batl_obj_item_slowdown",
			"batl_obj_item_missile", "cmn_obj_item_warp", "batl_obj_item_ringsteal", "cmn_obj_item_thunder", "batl_obj_item_changering" };
		inline static const char* ms_pItemSkeletonNames[] = { "batl_obj_item_question", "batl_obj_wispqua", "batl_obj_hand", "batl_obj_missile" };
		inline static const char* ms_pItemAnimationNames[] = { "batl_obj_item_question", "batl_obj_wispqua_release", "batl_obj_hand_steal" };
		
		inline static FUNCTION_PTR(uint8, __thiscall, ms_fpGetRingRaceItemType, ASLR(0x0064EB50), ObjQuestionItemBoxInfo*, uint8);
		inline static FUNCTION_PTR(uint8, __thiscall, ms_fpGetSpeedRaceItemType, ASLR(0x004BDDC0), ObjQuestionItemBoxInfo*, uint8);

	public:
		inline static const char* ms_pName = "ObjQuestionItemBoxInfo";

		inline static const size_t ms_ItemModelCount = ARRAYSIZE(ms_pItemModelNames);
		inline static const size_t ms_ItemSkeletonCount = ARRAYSIZE(ms_pItemSkeletonNames);
		inline static const size_t ms_ItemAnimationCount = ARRAYSIZE(ms_pItemAnimationNames);

		ObjUtil::ResModelFixedContainer<ms_ItemModelCount> ItemModelContainer{};
		ObjUtil::ResSkeletonFixedContainer<ms_ItemSkeletonCount> ItemSkeletonContainer{};
		ObjUtil::ResCharAnimFixedContainer<ms_ItemAnimationCount> ItemAnimationContainer{};
		csl::ut::FixedArray<csl::ut::FixedArray<uint8, 20>, 5> Unk1{};
		csl::ut::FixedArray<csl::ut::FixedArray<uint8, 20>, 5> Unk2{};
		csl::ut::FixedArray<uint8, 5> Unk3{};
		csl::ut::FixedArray<uint8, 5> Unk4{};

		void Initialize(GameDocument& in_rDocument) override
		{
			auto commonPackFile = ObjUtil::GetPackFile(ms_pCommonPackFileName);
			auto battlePackFile = ObjUtil::GetPackFile(ms_pBattlePackFileName);
			for (size_t i = 0; i < ItemModelContainer.Models.size(); i++)
			{
				if (i == 6 || i == 8)
				{
					ItemModelContainer.Models[i] = ObjUtil::GetModelResource(ms_pItemModelNames[i], commonPackFile);
					continue;
				}
				
				ItemModelContainer.Models[i] = ObjUtil::GetModelResource(ms_pItemModelNames[i], battlePackFile);
			}

			for (size_t i = 0; i < ItemSkeletonContainer.Skeletons.size(); i++)
				ItemSkeletonContainer.Skeletons[i] = ObjUtil::GetSkeletonResource(ms_pItemSkeletonNames[i], battlePackFile);

			for (size_t i = 0; i < ItemAnimationContainer.Animations.size(); i++)
				ItemAnimationContainer.Animations[i] = ObjUtil::GetAnimationResource(ms_pItemAnimationNames[i], battlePackFile);
		}

		const char* GetInfoName() override
		{
			return ms_pName;
		}

		uint8 GetRingRaceItemType(uint8 in_unk)
		{
			return ms_fpGetRingRaceItemType(this, in_unk);
		}

		uint8 GetSpeedRaceItemType(uint8 in_unk)
		{
			return ms_fpGetSpeedRaceItemType(this, in_unk);
		}

		void RegistCallback(CObjInfoContainer* in_pContainer)
		{
			auto* pObjInfo = new(GetAllocator()) ObjItemBoxInfo();
			if (!pObjInfo)
				return;

			in_pContainer->Register(pObjInfo->GetInfoName(), pObjInfo);
		}
	};
}