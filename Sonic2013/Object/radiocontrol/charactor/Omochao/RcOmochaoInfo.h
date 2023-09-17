#pragma once

namespace app
{
    class RcOmochaoInfo : public RcInfoBase
    {
    private:
        inline static const char* ms_pPacfileName = "RcOmochao.pac";
        inline static const char* ms_pModelName = "rc_omochao";
        inline static const char* ms_pSkeletonName = "rc_omochao";
        inline static const char* ms_pAnimationScriptName = "RcOmochao";
        inline static const char* ms_pTexSrtAnimationName = "rc_omochao_mouth-0001";
        inline static const char* ms_pMaterialAnimationName = "rc_omochao_eye";

    public:
        hh::gfx::res::ResModel Model{};
        hh::gfx::res::ResSkeleton Skeleton{};
        hh::gfx::res::ResAnimTexSrt TexSrtAnimation{};
        hh::gfx::res::ResAnimMaterial MaterialAnimation{};
        animation::AnimationResContainer AnimationContainer{ *m_pAllocator };
        
        RcOmochaoInfo(byte in_variant) : RcInfoBase(in_variant, ms_pPacfileName)
        {

        }

    protected:
        void Initialize(GameDocument& in_rDocument) override
        {
            auto packFile = ObjUtil::GetPackFile(PacfileName.c_str());
            Skeleton = ObjUtil::GetSkeletonResource(ms_pSkeletonName, packFile);
            TexSrtAnimation = ObjUtil::GetTexSrtAnimationResource(ms_pTexSrtAnimationName, packFile);
            MaterialAnimation = ObjUtil::GetMaterialAnimationResource(ms_pMaterialAnimationName, packFile);

            auto animScript = ObjUtil::GetAnimationScriptResource(ms_pAnimationScriptName, packFile);
            animation::AnimationResContainer::LoadInfo animLoadInfo{ animScript, Skeleton, nullptr };
            AnimationContainer.LoadFromBuffer(animLoadInfo, packFile);

            packFile = ObjUtil::GetPackFile(VariantPacfileName.c_str());
            Model = ObjUtil::GetModelResource(ms_pModelName, packFile);
        }

    public:
        const char* GetInfoName() override
        {
            return "RcOmochaoInfo";
        }
    };
}