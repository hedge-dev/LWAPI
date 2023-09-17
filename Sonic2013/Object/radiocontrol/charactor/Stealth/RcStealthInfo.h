#pragma once

namespace app
{
    class RcStealthInfo : public RcInfoBase
    {
    private:
        inline static const char* ms_pPacfileName = "RcStealth.pac";
        inline static const char* ms_pModelName = "rc_stealth";
        inline static const char* ms_pSkeletonName = "rc_stealth";

    public:
        hh::gfx::res::ResModel Model{};
        hh::gfx::res::ResSkeleton Skeleton{};
        
        RcStealthInfo(byte in_variant) : RcInfoBase(in_variant, ms_pPacfileName)
        {

        }

    protected:
        void Initialize(GameDocument& in_rDocument) override
        {
            auto packFile = ObjUtil::GetPackFile(PacfileName.c_str());
            Skeleton = ObjUtil::GetSkeletonResource(ms_pSkeletonName, packFile);
            
            packFile = ObjUtil::GetPackFile(VariantPacfileName.c_str());
            Model = ObjUtil::GetModelResource(ms_pModelName, packFile);
        }

    public:
        const char* GetInfoName() override
        {
            return "RcStealthInfo";
        }
    };
}