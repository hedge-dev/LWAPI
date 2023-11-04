#pragma once

namespace app::Player
{
    class VehicleSnowBallInfo : public CObjInfo
    {
    public:
        inline static const char* ms_pName = "VehicleSnowBallInfo";

    private:
        inline static const char* ms_pModelName = "w4_obj_snowball";
        inline static const char* ms_pShadowModelName = "w4_obj_snowball";
        inline static const char* ms_pSkeletonName = "w4_obj_snowball";
        inline static const char* ms_pAnimationScriptName = "snowball";
        inline static const char* ms_pMaterialAnimationName = "w4_obj_snowball_01";

    public:
        hh::gfx::res::ResModel Model{};
        hh::gfx::res::ResSkeleton Skeleton{};
        animation::AnimationResContainer AnimationContainer{ *m_pAllocator };
        hh::gfx::res::ResAnimMaterial MaterialAnimation{};
        debris::ResFixPositionDebris Debris{ m_pAllocator };
        res::ResShadowModel ShadowModel{};

        VehicleSnowBallInfo() {}

    protected:
        void Initialize(GameDocument& in_rDocument) override
        {
            auto packFile = ObjUtil::GetPackFile(ObjUtil::GetStagePackName(in_rDocument));

            Model = ObjUtil::GetModelResource(ms_pModelName, packFile);
            Skeleton = ObjUtil::GetSkeletonResource(ms_pSkeletonName, packFile);
            ShadowModel = ObjUtil::GetShadowModel(ms_pShadowModelName, packFile);

            auto animScript = ObjUtil::GetAnimationScriptResource(ms_pAnimationScriptName, packFile);
            animation::AnimationResContainer::LoadInfo animLoadInfo{ animScript, Skeleton, nullptr };
            AnimationContainer.LoadFromBuffer(animLoadInfo, packFile);
        
            MaterialAnimation = ObjUtil::GetMaterialAnimationResource(ms_pMaterialAnimationName, packFile);
            
            debris::ResFixPositionDebris::SDesc debrisDesc{ ms_pSkeletonName, &packFile };
            Debris.Build(debrisDesc);

            auto* pTrackManager = in_rDocument.GetService<SnowBallTrackManager>();
            if (!pTrackManager)
                return;
        
            csl::ut::FixedString<32> stagePackName = ObjUtil::GetStagePackName(in_rDocument);
            csl::ut::FixedString<32> snowlineName[3]{};

            snowlineName[0] = "w4_obj_snowline002_nrm";

            pTrackManager->SetupResources({ stagePackName, snowlineName[0] });
        }

        const char* GetInfoName() override
        {
            return ms_pName;
        }
    };
}