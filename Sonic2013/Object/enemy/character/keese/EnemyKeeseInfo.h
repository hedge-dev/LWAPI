#pragma once

namespace app
{
    class EnemyKeeseInfo : public EnemyInfo
    {
    private:
        inline static const char* ms_pPacfileName = "EnemyKeese.pac";
        inline static const char* ms_pModelName = "enm_keese";
        inline static const char* ms_pSkeletonName = "enm_keese";
        inline static const char* ms_pAnimationScriptName = "keese";
        inline static const char* ms_pFlyAnimationName = "kes_fly_loop";

    public:
        inline static const char* ms_pName = "EnemyKeeseInfo";

        hh::gfx::res::ResModel Model{};
        hh::gfx::res::ResSkeleton Skeleton{};
        animation::AnimationResContainer AnimationContainer { *m_pAllocator };
        hh::gfx::res::ResAnimSkeleton FlyAnimation{};

        EnemyKeeseInfo()
        {
            pPacfileName = ms_pPacfileName;
        }

    protected:
        void Initialize(GameDocument& in_rDocument) override
        {
            Model = GetModelResource(ms_pModelName);
            Skeleton = GetSkeletonResource(ms_pSkeletonName);
            
            auto animScript = GetAnimationScriptResource(ms_pAnimationScriptName);
            animation::AnimationResContainer::LoadInfo animLoadInfo{ animScript, Skeleton, nullptr };
            AnimationContainer.LoadFromBuffer(animLoadInfo, GetEnemyPackfile());
            
            FlyAnimation = GetAnimationResource(ms_pFlyAnimationName);
        }

        const char* GetInfoName() override
        {
            return ms_pName;
        }
    };
}