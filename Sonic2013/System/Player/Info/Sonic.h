#pragma once

namespace app::Player
{
    class SonicInfo : public CObjInfo
    {
    public:
        hh::gfx::res::ResModel m_Model{};
        hh::gfx::res::ResSkeleton m_Skeleton{};
        animation::AnimationResContainer m_AnimContainer{ *m_pAllocator };
        csl::ut::FixedArray<hh::gfx::res::ResAnimVis, 2> m_VisualAnims{};
        hh::gfx::res::ResModel m_SpinModel{};
        hh::gfx::res::ResSkeleton m_SpinSkeleton{};
        animation::AnimationResContainer m_SpinAnimContainer{ *m_pAllocator };
        hh::gfx::res::ResAnimTexSrt m_TextureAnim{};
        res::ResShadowModel m_ShadowModel{};

        SonicInfo() {}
        ~SonicInfo() {}

    protected:
        void Load(CObjInfoFileLoader& loader) override
        {
            loader.Load("Sonic.pac", 0x4001);
        }

        void Initialize(GameDocument& document) override
        {
            auto packFile = ObjUtil::GetPackFile("Sonic.pac");

            m_Model = ObjUtil::GetModelResource("chr_Sonic", packFile);
            m_Skeleton = ObjUtil::GetSkeletonResource("chr_Sonic", packFile);

            m_VisualAnims[0] = ObjUtil::GetVisAnimationResource("sn_idle_l_loop", packFile);
            m_VisualAnims[1] = ObjUtil::GetVisAnimationResource("sn_idle_r_loop", packFile);

            auto animScript = ObjUtil::GetAnimationScriptResource("player_sonic", packFile);
            csl::ut::InplaceMoveArray<app::animation::MirrorBindData, 8> bindData{ m_pAllocator };
            bindData.push_back_unchecked({ "MouthReference_L", "MouthReference" });
            bindData.push_back_unchecked({ "MouthPosition_L", "MouthPosition" });
            bindData.push_back_unchecked({ "Jaw_L", "Jaw" });
            bindData.push_back_unchecked({ "Teeth_Low_L", "Teeth_Low" });
            bindData.push_back_unchecked({ "Teeth_Up_L", "Teeth_Up" });
            bindData.push_back_unchecked({ "Lip_C_L", "Lip_C" });
            bindData.push_back_unchecked({ "Lip_L", "Lip_L_L" });
            bindData.push_back_unchecked({ "Lip_R", "Lip_R_L" });

            app::animation::AnimationResContainer::LoadInfo loadInfo{ animScript, m_Skeleton, &bindData };
            m_AnimContainer.LoadFromBuffer(loadInfo, packFile);

            m_SpinModel = ObjUtil::GetModelResource("chr_sonic_spin", packFile);
            m_SpinSkeleton = ObjUtil::GetSkeletonResource("chr_sonic_spin", packFile);

            m_TextureAnim = ObjUtil::GetTexSrtAnimationResource("chr_Sonic_spin", packFile);

            animScript = ObjUtil::GetAnimationScriptResource("player_sonic_spin", packFile);
            loadInfo = app::animation::AnimationResContainer::LoadInfo(animScript, m_SpinSkeleton, nullptr);
            m_SpinAnimContainer.LoadFromBuffer(loadInfo, packFile);

            m_ShadowModel = ObjUtil::GetShadowModel("chr_Sonic", packFile);

            auto* fpManager = document.GetService<FootPrintManager>();
            if (!fpManager)
                return;
        
            fpManager->SetupResources({ "Sonic.pac", { "sonic_footprint01", "sonic_footprint02" } });
        }

        const char* GetInfoName() override
        {
            return "SonicInfo";
        }
    };
}
