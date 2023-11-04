#pragma once

namespace app::Player
{
    class PhantomLaserInfo : public CObjInfo
    {
    public:
        inline static const char* ms_pName = "PhantomLaserInfo";

    private:
        inline static const char* ms_pPackfileName = "PhantomLaser.pac";
        inline static const char* ms_pModelName = "chr_pha_Laser";
        inline static const char* ms_pSpinModelName = "chr_pha_laserspin";
        inline static const char* ms_pSkeletonName = "chr_pha_Laser";
        inline static const char* ms_pSpinSkeletonName = "chr_pha_laserspin";
        inline static const char* ms_pAnimationScriptName = "phantom_laser";
        inline static const char* ms_pSpinAnimationScriptName = "phantom_laserspin";
        inline static const char* ms_pSpinTexSrtAnimationName = "chr_pha_laserspin-0000";

    public:
        hh::gfx::res::ResModel Model{};
        hh::gfx::res::ResSkeleton Skeleton{};
        animation::AnimationResContainer AnimationContainer{ *m_pAllocator };
        hh::gfx::res::ResModel SpinModel{};
        hh::gfx::res::ResSkeleton SpinSkeleton{};
        animation::AnimationResContainer SpinAnimationContainer{ *m_pAllocator };
        hh::gfx::res::ResAnimTexSrt SpinTexSrtAnimation{};

        PhantomLaserInfo() {}

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

            SpinModel = ObjUtil::GetModelResource(ms_pSpinModelName, packFile);
            SpinSkeleton = ObjUtil::GetSkeletonResource(ms_pSpinSkeletonName, packFile);

            animScript = ObjUtil::GetAnimationScriptResource(ms_pSpinAnimationScriptName, packFile);
            animLoadInfo = { animScript, SpinSkeleton, nullptr };
            AnimationContainer.LoadFromBuffer(animLoadInfo, packFile);

            SpinTexSrtAnimation = ObjUtil::GetTexSrtAnimationResource(ms_pSpinTexSrtAnimationName, packFile);
        }

        const char* GetInfoName() override
        {
            return ms_pName;
        }
    };
}