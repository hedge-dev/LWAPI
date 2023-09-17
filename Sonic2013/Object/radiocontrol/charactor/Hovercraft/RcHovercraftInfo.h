#pragma once

namespace app
{
    class RcHovercraftInfo : public RcInfoBase
    {
    private:
        inline static const char* ms_pPacfileName = "RcHovercraft.pac";
        inline static const char* ms_pModelName = "rc_hovercraft";
        inline static const char* ms_pSkeletonName = "rc_hovercraft";
        inline static const char* ms_pLoopAnimationName = "rc_hovercraft_loop";
        inline static const char* ms_pTurnAnimationName = "rc_hovercraft_turn";

    public:
        hh::gfx::res::ResModel Model{};
        hh::gfx::res::ResSkeleton Skeleton{};
        hh::gfx::res::ResAnimSkeleton LoopAnimation{};
        hh::gfx::res::ResAnimSkeleton TurnAnimation{};
        
        RcHovercraftInfo(byte in_variant) : RcInfoBase(in_variant, ms_pPacfileName)
        {

        }

    protected:
        void Initialize(GameDocument& in_rDocument) override
        {
            auto packFile = ObjUtil::GetPackFile(PacfileName.c_str());

            Skeleton = ObjUtil::GetSkeletonResource(ms_pSkeletonName, packFile);
            
            LoopAnimation = ObjUtil::GetAnimationResource(ms_pLoopAnimationName, packFile);
            TurnAnimation = ObjUtil::GetAnimationResource(ms_pTurnAnimationName, packFile);

            packFile = ObjUtil::GetPackFile(VariantPacfileName.c_str());
            Model = ObjUtil::GetModelResource(ms_pModelName, packFile);
        }

    public:
        const char* GetInfoName() override
        {
            return "RcHovercraftInfo";
        }
    };
}