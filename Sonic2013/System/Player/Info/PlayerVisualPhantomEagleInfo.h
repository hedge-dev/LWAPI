#pragma once

namespace app::Player
{
    class PhantomEagleInfo : public CObjInfo
    {
    public:
        inline static const char* ms_pName = "PhantomEagleInfo";

    private:
        inline static const char* ms_pPackfileName = "PhantomEagle.pac";
        inline static const char* ms_pModelName = "chr_pha_Eagle";
        inline static const char* ms_pSkeletonName = "chr_pha_Eagle";
        inline static const char* ms_pAnimationScriptName = "phantom_eagle";

    public:
        hh::gfx::res::ResModel Model{};
        hh::gfx::res::ResSkeleton Skeleton{};
        animation::AnimationResContainer AnimationContainer{ *m_pAllocator };

        PhantomEagleInfo() {}

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
        }

        const char* GetInfoName() override
        {
            return ms_pName;
        }
    };
}