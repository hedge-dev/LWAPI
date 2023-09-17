#pragma once

namespace app
{
    class EnemyPiranhaPlantInfo : public EnemyInfo
    {
    private:
        inline static const char* ms_pPacfileName = "EnemyPackunFlower.pac";
        inline static const char* ms_pModelName = "enm_packunflower";
        inline static const char* ms_pTexSrtAnimName = "enm_packunflower_head-0000";
        inline static const char* ms_pAnimScriptName = "piranhaplant";

    public:
        inline static const char* ms_pName = "EnemyPiranhaPlantInfo";

        hh::gfx::res::ResModel Model{};
        hh::gfx::res::ResSkeleton Skeleton{};
        animation::AnimationResContainer AnimationContainer{ *m_pAllocator };
        hh::gfx::res::ResAnimTexSrt TextureAnimation{};
        
        EnemyPiranhaPlantInfo()
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

            TextureAnimation = GetTexSrtAnimationResource(ms_pTexSrtAnimName);
        }

        const char* GetInfoName() override
        {
            return ms_pName;
        }
    };
}