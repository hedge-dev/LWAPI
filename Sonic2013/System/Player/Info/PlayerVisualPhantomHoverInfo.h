#pragma once

namespace app::Player
{
    class PhantomHoverInfo : public CObjInfo
    {
    private:
        inline static const char* ms_pPackfileName = "PhantomHover.pac";
        inline static const char* ms_pModelName = "chr_pha_Hover";
        inline static const char* ms_pSkeletonName = "chr_pha_Hover";
        inline static const char* ms_pAnimationScriptName = "phantom_hover";

    public:
        hh::gfx::res::ResModel Model{};
        hh::gfx::res::ResSkeleton Skeleton{};
        animation::AnimationResContainer AnimationContainer{ *m_pAllocator };

        PhantomHoverInfo() {}

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
            return "PhantomHoverInfo";
        }
    };
}