#pragma once

namespace app
{
    class RcHelicopterInfo : public RcInfoBase
    {
    private:
        inline static const char* ms_pPacfileName = "RcHelicopter.pac";
        inline static const char* ms_pModelName = "rc_helicopter";
        inline static const char* ms_pBombModelName = "rc_obj_bomb";
        inline static const char* ms_pSkeletonName = "rc_helicopter";
        inline static const char* ms_pAnimationScriptName = "RcHelicopter";

    public:
        hh::gfx::res::ResModel Model{};
        hh::gfx::res::ResSkeleton Skeleton{};
        animation::AnimationResContainer AnimationContainer{ *m_pAllocator };
        hh::gfx::res::ResModel BombModel{};
        
        RcHelicopterInfo(byte in_variant) : RcInfoBase(in_variant, ms_pPacfileName)
        {

        }

    protected:
        void Initialize(GameDocument& in_rDocument) override
        {
            auto packFile = ObjUtil::GetPackFile(PacfileName.c_str());
            BombModel = ObjUtil::GetModelResource(ms_pBombModelName, packFile);

            Skeleton = ObjUtil::GetSkeletonResource(ms_pSkeletonName, packFile);
            
            auto animScript = ObjUtil::GetAnimationScriptResource(ms_pAnimationScriptName, packFile);
            animation::AnimationResContainer::LoadInfo animLoadInfo{ animScript, Skeleton, nullptr };
            AnimationContainer.LoadFromBuffer(animLoadInfo, packFile);

            packFile = ObjUtil::GetPackFile(VariantPacfileName.c_str());
            Model = ObjUtil::GetModelResource(ms_pModelName, packFile);
        }

    public:
        const char* GetInfoName() override
        {
            return "RcHelicopterInfo";
        }
    };
}