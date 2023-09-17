#pragma once

namespace app
{
    class RcBalloonInfo : public RcInfoBase
    {
    private:
        inline static const char* ms_pPacfileName = "RcBalloon.pac";
        inline static const char* ms_pModelName = "rc_balloon";
        inline static const char* ms_pSkeletonName = "rc_balloon";
        inline static const char* ms_pAnimationNames[] = { "rc_balloon_open", "rc_balloon_close" };

    public:
        inline static const size_t ms_AnimationCount = ARRAYSIZE(ms_pAnimationNames);

        hh::gfx::res::ResModel Model{};
        hh::gfx::res::ResSkeleton Skeleton{};
        ObjUtil::ResCharAnimFixedContainer<ms_AnimationCount> AnimationContainer{};
        
        RcBalloonInfo(byte in_variant) : RcInfoBase(in_variant, ms_pPacfileName)
        {

        }

    protected:
        void Initialize(GameDocument& in_rDocument) override
        {
            auto packFile = ObjUtil::GetPackFile(PacfileName.c_str());
            Skeleton = ObjUtil::GetSkeletonResource(ms_pSkeletonName, packFile);

            for (size_t i = 0; i < AnimationContainer.Animations.size(); i++)
                AnimationContainer.Animations[i] = ObjUtil::GetAnimationResource(ms_pAnimationNames[i], packFile);

            packFile = ObjUtil::GetPackFile(VariantPacfileName.c_str());
            Model = ObjUtil::GetModelResource(ms_pModelName, packFile);
        }

    public:
        const char* GetInfoName() override
        {
            return "RcBalloonInfo";
        }
    };
}