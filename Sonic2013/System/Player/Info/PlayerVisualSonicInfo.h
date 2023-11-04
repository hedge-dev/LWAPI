#pragma once

namespace app::Player
{
    class SonicInfo : public CObjInfo
    {
    public:
        inline static const char* ms_pName = "SonicInfo";

    private:
        inline static const char* ms_pPackfileName = "Sonic.pac";
        inline static const char* ms_pModelName = "chr_Sonic";
        inline static const char* ms_pSpinModelName = "chr_sonic_spin";
        inline static const char* ms_pShadowModelName = "chr_Sonic";
        inline static const char* ms_pSkeletonName = "chr_Sonic";
        inline static const char* ms_pSpinSkeletonName = "chr_sonic_spin";
        inline static const char* ms_pAnimationScriptName = "player_sonic";
        inline static const char* ms_pSpinAnimationScriptName = "player_sonic_spin";
        inline static const char* ms_pSpinTexSrtAnimationName = "chr_Sonic_spin";
        inline static const char* ms_pVisAnimationNames[] = { "sn_idle_l_loop", "sn_idle_r_loop" };
        inline static const char* ms_pFootprintNames[] = { "sonic_footprint01", "sonic_footprint02" };
        inline static const char* ms_pMirrorBindDataNames[] = { "MouthReference_L", "MouthReference", "MouthPosition_L", "MouthPosition", "Jaw_L", "Jaw", "Teeth_Low_L", "Teeth_Low",
            "Teeth_Up_L", "Teeth_Up", "Lip_C_L", "Lip_C", "Lip_L", "Lip_L_L", "Lip_R", "Lip_R_L",};

    public:
        inline static const size_t ms_VisAnimationCount = ARRAYSIZE(ms_pVisAnimationNames);

        hh::gfx::res::ResModel Model{};
        hh::gfx::res::ResSkeleton Skeleton{};
        animation::AnimationResContainer AnimationContainer{ *m_pAllocator };
        csl::ut::FixedArray<hh::gfx::res::ResAnimVis, ms_VisAnimationCount> VisualAnimations{};
        hh::gfx::res::ResModel SpinModel{};
        hh::gfx::res::ResSkeleton SpinSkeleton{};
        animation::AnimationResContainer SpinAnimationContainer{ *m_pAllocator };
        hh::gfx::res::ResAnimTexSrt SpinTexSrtAnimation{};
        res::ResShadowModel ShadowModel{ nullptr };

        SonicInfo() { }

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

            VisualAnimations[0] = ObjUtil::GetVisAnimationResource(ms_pVisAnimationNames[0], packFile);
            VisualAnimations[1] = ObjUtil::GetVisAnimationResource(ms_pVisAnimationNames[1], packFile);

            auto animScript = ObjUtil::GetAnimationScriptResource(ms_pAnimationScriptName, packFile);
            csl::ut::InplaceMoveArray<app::animation::MirrorBindData, 8> bindData{ m_pAllocator };
            bindData.push_back_unchecked({ ms_pMirrorBindDataNames[0], ms_pMirrorBindDataNames[1] });
            bindData.push_back_unchecked({ ms_pMirrorBindDataNames[2], ms_pMirrorBindDataNames[3] });
            bindData.push_back_unchecked({ ms_pMirrorBindDataNames[4], ms_pMirrorBindDataNames[5] });
            bindData.push_back_unchecked({ ms_pMirrorBindDataNames[6], ms_pMirrorBindDataNames[7] });
            bindData.push_back_unchecked({ ms_pMirrorBindDataNames[8], ms_pMirrorBindDataNames[9] });
            bindData.push_back_unchecked({ ms_pMirrorBindDataNames[10], ms_pMirrorBindDataNames[11] });
            bindData.push_back_unchecked({ ms_pMirrorBindDataNames[12], ms_pMirrorBindDataNames[13] });
            bindData.push_back_unchecked({ ms_pMirrorBindDataNames[14], ms_pMirrorBindDataNames[15] });
            
            app::animation::AnimationResContainer::LoadInfo loadInfo{ animScript, Skeleton, &bindData };
            AnimationContainer.LoadFromBuffer(loadInfo, packFile);

            SpinModel = ObjUtil::GetModelResource(ms_pSpinModelName, packFile);
            SpinSkeleton = ObjUtil::GetSkeletonResource(ms_pSpinSkeletonName, packFile);

            SpinTexSrtAnimation = ObjUtil::GetTexSrtAnimationResource(ms_pSpinTexSrtAnimationName, packFile);

            animScript = ObjUtil::GetAnimationScriptResource(ms_pSpinAnimationScriptName, packFile);
            loadInfo = app::animation::AnimationResContainer::LoadInfo{ animScript, SpinSkeleton, nullptr };
            SpinAnimationContainer.LoadFromBuffer(loadInfo, packFile);

            ShadowModel = ObjUtil::GetShadowModel(ms_pShadowModelName, packFile);

            auto* fpManager = in_rDocument.GetService<FootPrintManager>();
            if (!fpManager)
                return;
        
            fpManager->SetupResources({ ms_pPackfileName, { ms_pFootprintNames[0], ms_pFootprintNames[1] } });
        }

    public:
        const char* GetInfoName() override
        {
            return ms_pName;
        }
    };
}
