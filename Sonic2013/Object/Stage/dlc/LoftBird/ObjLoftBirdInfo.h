#pragma once

namespace app
{
	class ObjLoftBirdInfo : public CObjInfo
	{
	private:
		inline static const char* ms_pModelNames[] = { "zdlc03_obj_link", "zdlc03_obj_loftbird" };
		inline static const char* ms_pTexSrtAnimNames[] = { "lnk_event01_Eye_L", "lnk_event01_Eye_R", "lnk_event02_Eye_L", "lnk_event02_Eye_R" };
		inline static const char* ms_pLinkAnimScriptName = "zdlc03_obj_link";
		inline static const char* ms_pLoftBirdAnimScriptName = "zdlc03_obj_loftbird";

	public:
		inline static const char* ms_pName = "ObjLoftBirdInfo";

		inline static const size_t ms_ModelCount = ARRAYSIZE(ms_pModelNames);
		inline static const size_t ms_TexSrtAnimCount = ARRAYSIZE(ms_pTexSrtAnimNames);

		ObjUtil::ResModelFixedContainer<ms_ModelCount> ModelContainer{};
		ObjUtil::ResSkeletonFixedContainer<ms_ModelCount> SkeletonContainer{};
		animation::AnimationResContainer LinkAnimationContainer{ *m_pAllocator };
		animation::AnimationResContainer LoftBirdAnimationContainer{ *m_pAllocator };
		ObjUtil::ResTexSrtAnimFixedContainer<ms_TexSrtAnimCount> TexSrtAnimContainer{};

		ObjLoftBirdInfo() { }

	protected:
		void Initialize(GameDocument& in_rDocument) override
		{
			auto packFile = ObjUtil::GetPackFile(ObjUtil::GetStagePackName(in_rDocument));
			for (size_t i = 0; i < ms_ModelCount; i++)
			{
				ModelContainer.Models[i] = ObjUtil::GetModelResource(ms_pModelNames[i], packFile);
				SkeletonContainer.Skeletons[i] = ObjUtil::GetSkeletonResource(ms_pModelNames[i], packFile);
			}

			auto animScript = ObjUtil::GetAnimationScriptResource(ms_pLinkAnimScriptName, packFile);
			animation::AnimationResContainer::LoadInfo animLoadInfo{ animScript, SkeletonContainer.Skeletons[0], nullptr};
			LinkAnimationContainer.LoadFromBuffer(animLoadInfo, packFile);

			for (size_t i = 0; i < ms_TexSrtAnimCount; i++)
			{
				TexSrtAnimContainer.Animations[i] = ObjUtil::GetTexSrtAnimationResource(ms_pTexSrtAnimNames[i], packFile);
			}

			animScript = ObjUtil::GetAnimationScriptResource(ms_pLoftBirdAnimScriptName, packFile);
			animLoadInfo = { animScript, SkeletonContainer.Skeletons[1], nullptr };
			LoftBirdAnimationContainer.LoadFromBuffer(animLoadInfo, packFile);
		}

		const char* GetInfoName() override
		{
			return ms_pName;
		}
	};
}