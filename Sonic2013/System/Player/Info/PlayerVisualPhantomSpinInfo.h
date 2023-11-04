#pragma once

namespace app::Player
{
    class PhantomSpinInfo : public CObjInfo
    {
    public:
        inline static const char* ms_pName = "PhantomSpinInfo";

    private:
        inline static const char* ms_pPackfileName = "PhantomSpin.pac";
        inline static const char* ms_pModelName = "chr_pha_Spin";
        inline static const char* ms_pSkeletonName = "chr_pha_Spin";
        inline static const char* ms_pAnimationScriptName = "phantom_spin";
        inline static const char* ms_pSoilTextureName = "w2_obj_soil051_dif";

    public:
        hh::gfx::res::ResModel Model{};
        hh::gfx::res::ResSkeleton Skeleton{};
        animation::AnimationResContainer AnimationContainer{ *m_pAllocator };
        hh::gfx::res::ResTexture SoilTexture{};

        PhantomSpinInfo() {}

    protected:
        void Load(CObjInfoFileLoader& in_rLoader) override
        {
            in_rLoader.Load(ms_pPackfileName, 0x4001);
        }

        void Initialize(GameDocument& in_rDocument) override
        {
            auto packFile = ObjUtil::GetPackFile(ms_pPackfileName);

            Model = ObjUtil::GetModelResource(ms_pModelName, packFile);
            Skeleton = ObjUtil::GetSkeletonResource(ms_pSkeletonName, packFile);

            auto animScript = ObjUtil::GetAnimationScriptResource(ms_pAnimationScriptName, packFile);
            animation::AnimationResContainer::LoadInfo animLoadInfo{ animScript, Skeleton, nullptr };
            AnimationContainer.LoadFromBuffer(animLoadInfo, packFile);

            auto stagePackFile = ObjUtil::GetPackFile(ObjUtil::GetStagePackName(in_rDocument));
            if (stagePackFile.IsValid())
                SoilTexture = ObjUtil::GetResTexture(ms_pSoilTextureName, stagePackFile);
        }

        const char* GetInfoName() override
        {
            return ms_pName;
        }
    };
}