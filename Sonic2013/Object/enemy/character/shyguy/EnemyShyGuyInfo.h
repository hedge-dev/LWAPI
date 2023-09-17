#pragma once

namespace app
{
    class EnemyShyGuyInfo : public EnemyInfo
    {
    private:
        inline static const char* ms_pPacfileName = "EnemyHeyho.pac";
        inline static const char* ms_pAnimScriptName = "shyguy";
        inline static const char* ms_pAnimNames[] = { "hey_walk_left_loop", "hey_walk_right_loop" };
        inline static const char* ms_pModelName = "enm_heyho";

    public:
        inline static const char* ms_pName = "EnemyShyGuyInfo";

        inline static size_t ms_AnimCount = ARRAYSIZE(ms_pAnimNames);

        hh::gfx::res::ResModel Model{};
        hh::gfx::res::ResSkeleton Skeleton{};
        animation::AnimationResContainer AnimationContainer{ *m_pAllocator };
        hh::gfx::res::ResAnimSkeleton Animations[ARRAYSIZE(ms_pAnimNames)]{};
        
        EnemyShyGuyInfo()
        {
            pPacfileName = ms_pPacfileName;
        }

    protected:
        void Initialize(GameDocument& in_rDocument) override
        {
            Model = GetModelResource(ms_pModelName);
            Skeleton = GetSkeletonResource(ms_pModelName);
            
            auto animScript = GetAnimationScriptResource(ms_pAnimScriptName);
            animation::AnimationResContainer::LoadInfo animLoadInfo{ animScript, Skeleton, nullptr };
            AnimationContainer.LoadFromBuffer(animLoadInfo, GetEnemyPackfile());

            for (size_t i = 0; i < ms_AnimCount; i++)
                Animations[i] = GetAnimationResource(ms_pAnimNames[i]);
        }

        const char* GetInfoName() override
        {
            return ms_pName;
        }
    };
}