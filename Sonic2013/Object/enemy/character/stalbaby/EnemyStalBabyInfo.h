#pragma once

namespace app
{
    class EnemyStalBabyInfo : public EnemyInfo
    {
    private:
        inline static const char* ms_pPacfileName = "EnemyStalbaby.pac";
        inline static const char* ms_pModelName = "enm_stalbaby";
        inline static const char* ms_pHeadModelName = "enm_stalbaby_head";
        inline static const char* ms_pSkeletonName = "enm_stalbaby";
        inline static const char* ms_pAnimScriptName = "stalbaby";

    public:
        inline static const char* ms_pName = "EnemyStalBabyInfo";

        hh::gfx::res::ResModel Model{};
        hh::gfx::res::ResModel HeadModel{};
        hh::gfx::res::ResSkeleton Skeleton{};
        animation::AnimationResContainer AnimationContainer{ *m_pAllocator };

        EnemyStalBabyInfo()
        {
            pPacfileName = ms_pPacfileName;
        }

    protected:
        void Initialize(GameDocument& in_rDocument) override
        {
            Model = GetModelResource(ms_pModelName);
            HeadModel = GetModelResource(ms_pHeadModelName);
            
            Skeleton = GetSkeletonResource(ms_pSkeletonName);

            auto animScript = GetAnimationScriptResource(ms_pAnimScriptName);
            animation::AnimationResContainer::LoadInfo animLoadInfo{ animScript, Skeleton, nullptr };
            AnimationContainer.LoadFromBuffer(animLoadInfo, GetEnemyPackfile());
        }

        const char* GetInfoName() override
        {
            return ms_pName;
        }
    };
}