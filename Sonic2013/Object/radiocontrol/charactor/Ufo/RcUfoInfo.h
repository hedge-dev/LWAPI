#pragma once

namespace app
{
    class RcUfoInfo : public RcInfoBase
    {
    private:
        inline static const char* ms_pPacfileName = "RcUfo.pac";
        inline static const char* ms_pModelName = "rc_ufo";
        inline static const char* ms_pSkeletonName = "rc_ufo";
        inline static const char* ms_pAnimationName = "rc_ufo_loop";

    public:
        hh::gfx::res::ResModel Model{};
        hh::gfx::res::ResSkeleton Skeleton{};
        hh::gfx::res::ResAnimSkeleton Animation{};
        
        RcUfoInfo(byte in_variant) : RcInfoBase(in_variant, ms_pPacfileName)
        {

        }

    protected:
        void Initialize(GameDocument& in_rDocument) override
        {
            auto packFile = ObjUtil::GetPackFile(PacfileName.c_str());
            Skeleton = ObjUtil::GetSkeletonResource(ms_pSkeletonName, packFile);
            Animation = ObjUtil::GetAnimationResource(ms_pAnimationName, packFile);

            packFile = ObjUtil::GetPackFile(VariantPacfileName.c_str());
            Model = ObjUtil::GetModelResource(ms_pModelName, packFile);
        }

    public:
        const char* GetInfoName() override
        {
            return "RcUfoInfo";
        }
    };
}