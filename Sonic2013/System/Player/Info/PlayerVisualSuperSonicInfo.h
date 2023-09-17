#pragma once

namespace app::Player
{
    class SuperSonicInfo : public CObjInfo
    {
    private:
        inline static const char* ms_pPackfileName = "Supersonic.pac";
        inline static const char* ms_pModelName = "chr_supersonic";
        inline static const char* ms_pSpinModelName = "chr_supersonic_spin";
        inline static const char* ms_pEmeraldModelName = "chr_obj_emerald";
        inline static const char* ms_pShadowModelName = "chr_supersonic";
        inline static const char* ms_pSkeletonName = "chr_supersonic";
        inline static const char* ms_pSpinSkeletonName = "chr_supersonic_spin";
        inline static const char* ms_pEmeraldSkeletonName = "chr_obj_emerald";
        inline static const char* ms_pAnimationScriptName = "player_supersonic";
        inline static const char* ms_pSpinTexSrtAnimationName = "chr_Supersonic_spin";
        inline static const char* ms_pEmeraldAnimationNames[] = { "chr_obj_emerald_start", "chr_obj_emerald_end" };

    public:
        inline static const size_t ms_EmeraldAnimationCount = ARRAYSIZE(ms_pEmeraldAnimationNames);

        hh::gfx::res::ResModel Model{};
        hh::gfx::res::ResSkeleton Skeleton{};
        animation::AnimationResContainer AnimationContainer{ *m_pAllocator };
        hh::gfx::res::ResModel SpinModel{};
        hh::gfx::res::ResSkeleton SpinSkeleton{};
        hh::gfx::res::ResAnimTexSrt SpinTexSrtAnimation{};
        res::ResShadowModel ShadowModel{};
        hh::gfx::res::ResModel EmeraldModel{};
        hh::gfx::res::ResSkeleton EmeraldSkeleton{};
        ObjUtil::ResCharAnimFixedContainer<ms_EmeraldAnimationCount> EmeraldAnimations{};

        SuperSonicInfo() {}

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

            csl::ut::InplaceMoveArray<animation::MirrorBindData, 8> bindData{ m_pAllocator };
            bindData.push_back_unchecked({ "MouthReference_L", "MouthReference" });
            bindData.push_back_unchecked({ "MouthPosition_L", "MouthPosition" });
            bindData.push_back_unchecked({ "Jaw_L", "Jaw" });
            bindData.push_back_unchecked({ "Teeth_Low_L", "Teeth_Low" });
            bindData.push_back_unchecked({ "Teeth_Up_L", "Teeth_Up" });
            bindData.push_back_unchecked({ "Lip_C_L", "Lip_C" });
            bindData.push_back_unchecked({ "Lip_L", "Lip_L_L" });
            bindData.push_back_unchecked({ "Lip_R", "Lip_R_L" });

            animation::AnimationResContainer::LoadInfo animLoadInfo{ animScript, Skeleton, &bindData };
            AnimationContainer.LoadFromBuffer(animLoadInfo, packFile);

            SpinModel = ObjUtil::GetModelResource(ms_pSpinModelName, packFile);
            SpinSkeleton = ObjUtil::GetSkeletonResource(ms_pSpinSkeletonName, packFile);
            SpinTexSrtAnimation = ObjUtil::GetTexSrtAnimationResource(ms_pSpinTexSrtAnimationName, packFile);

            ShadowModel = ObjUtil::GetShadowModel(ms_pShadowModelName, packFile);

            EmeraldModel = ObjUtil::GetModelResource(ms_pEmeraldModelName, packFile);
            EmeraldSkeleton = ObjUtil::GetSkeletonResource(ms_pEmeraldSkeletonName, packFile);

            for (size_t i = 0; i < EmeraldAnimations.Animations.size(); i++)
                EmeraldAnimations.Animations[i] = ObjUtil::GetAnimationResource(ms_pEmeraldAnimationNames[i], packFile);
        }

        const char* GetInfoName() override
        {
            return "SuperSonicInfo";
        }
    };
}