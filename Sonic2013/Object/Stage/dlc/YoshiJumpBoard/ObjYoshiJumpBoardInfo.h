#pragma once

namespace app
{
	class ObjYoshiJumpBoardInfo : public CObjInfo
	{
	private:
		inline static const char* ms_AssetName = "zdlc02_obj_jumpboard";

	public:
		inline static const char* ms_pName = "ObjYoshiJumpBoardInfo";

		hh::gfx::res::ResModel Model{};
		hh::gfx::res::ResSkeleton Skeleton{};
		animation::AnimationResContainer AnimationContainer{ *m_pAllocator };

		ObjYoshiJumpBoardInfo() { }

	protected:
		void Initialize(GameDocument& in_rDocument) override
		{
			auto packFile = ObjUtil::GetPackFile(ObjUtil::GetStagePackName(in_rDocument));
			Model = ObjUtil::GetModelResource(ms_AssetName, packFile);
			Skeleton = ObjUtil::GetSkeletonResource(ms_AssetName, packFile);

			auto animScript = ObjUtil::GetAnimationScriptResource(ms_AssetName, packFile);
			animation::AnimationResContainer::LoadInfo animLoadInfo{ animScript, Skeleton, nullptr };
			AnimationContainer.LoadFromBuffer(animLoadInfo, packFile);
		}

		const char* GetInfoName() override
		{
			return ms_pName;
		}
	};

	inline CObjInfo* createObjInfo_ObjYoshiJumpBoardBig_ObjYoshiJumpBoardInfo(csl::fnd::IAllocator* in_pAllocator)
	{
		return new(in_pAllocator) ObjYoshiJumpBoardInfo();
	}

	inline CObjInfo* createObjInfo_ObjYoshiJumpBoardSmall_ObjYoshiJumpBoardInfo(csl::fnd::IAllocator* in_pAllocator)
	{
		return new(in_pAllocator) ObjYoshiJumpBoardInfo();
	}
}