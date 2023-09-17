#pragma once

namespace app::Player
{
    class PhantomAsteroidInfo : public CObjInfo
    {
    private:
        inline static const char* ms_pPackfileName = "PhantomAsteroid.pac";
        inline static const char* ms_pModelName = "chr_pha_Asteroid";
        inline static const char* ms_pSkeletonName = "chr_pha_Asteroid";
        inline static const char* ms_pAnimationScriptName = "phantom_asteroid";
        inline static const char* ms_pTexSrtAnimationName = "pha_aste_body_mat-0000";

    public:
        hh::gfx::res::ResModel Model{};
        hh::gfx::res::ResSkeleton Skeleton{};
        animation::AnimationResContainer AnimationContainer{ *m_pAllocator };
        hh::gfx::res::ResAnimTexSrt TexSrtAnimation{};

        PhantomAsteroidInfo() {}

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

            TexSrtAnimation = ObjUtil::GetTexSrtAnimationResource(ms_pTexSrtAnimationName, packFile);

            auto animScript = ObjUtil::GetAnimationScriptResource(ms_pAnimationScriptName, packFile);
            animation::AnimationResContainer::LoadInfo animLoadInfo{ animScript, Skeleton, nullptr };
            AnimationContainer.LoadFromBuffer(animLoadInfo, packFile);
        }

        const char* GetInfoName() override
        {
            return "PhantomAsteroidInfo";
        }
    };
}