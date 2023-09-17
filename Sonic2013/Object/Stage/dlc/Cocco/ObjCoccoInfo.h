#pragma once

namespace app
{
	class ObjCoccoInfo : public CObjInfo
	{
	private:
		inline static const char* ms_pModelName = "zdlc03_obj_cocco";
		inline static const char* ms_pSkeletonName = "zdlc03_obj_cocco";
		inline static const char* ms_pAnimationScriptName = "cocco";

	public:
		inline static const char* ms_pName = "ObjCoccoInfo";

		hh::gfx::res::ResModel Model{};
		hh::gfx::res::ResSkeleton Skeleton{};
		animation::AnimationResContainer AnimationContainer{ *m_pAllocator };

		ObjCoccoInfo() { }

	protected:
		void Initialize(GameDocument& in_rDocument) override
		{
			auto packFile = ObjUtil::GetPackFile(ObjUtil::GetStagePackName(in_rDocument));

			Model = ObjUtil::GetModelResource(ms_pModelName, packFile);

			Skeleton = ObjUtil::GetSkeletonResource(ms_pSkeletonName, packFile);

			auto animScript = ObjUtil::GetAnimationScriptResource(ms_pAnimationScriptName, packFile);
			animation::AnimationResContainer::LoadInfo animLoadInfo{ animScript, Skeleton, nullptr };
			AnimationContainer.LoadFromBuffer(animLoadInfo, packFile);
		}

		const char* GetInfoName() override
		{
			return ms_pName;
		}
	};
}