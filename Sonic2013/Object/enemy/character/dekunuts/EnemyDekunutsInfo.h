#pragma once

namespace app
{
    class EnemyDekunutsInfo : public EnemyInfo
    {
    private:
        inline static const char* ms_pPacfileName = "EnemyDekunuts.pac";
        inline static const char* ms_pCueSheetName = "sound/se_enemy_kokeko_fv.acb";
        inline static const char* ms_pModelNames[] = { "enm_dekunuts_base", "enm_dekunuts" };
        inline static const char* ms_pSkeletonNames[] = { "enm_dekunuts_base", "enm_dekunuts" };
        inline static const char* ms_pAnimScriptNames[] = { "dekunutsbase", "dekunuts" };
        inline static const char* ms_pShotModelName = "enm_dekunuts_bullet";

    public:
        inline static const size_t ms_ModelCount = ARRAYSIZE(ms_pModelNames);
        inline static const size_t ms_SkeletonCount = ARRAYSIZE(ms_pSkeletonNames);

        inline static const char* ms_pName = "EnemyDekunutsInfo";

        ObjUtil::ResModelFixedContainer<ms_ModelCount> ModelContainer{};
        ObjUtil::ResSkeletonFixedContainer<ms_SkeletonCount> SkeletonContainer{};
        animation::AnimationResContainer AnimationContainer{ *m_pAllocator };
        animation::AnimationResContainer BaseAnimationContainer { *m_pAllocator };
        hh::gfx::res::ResModel ShotModel{};

        EnemyDekunutsInfo()
        {
            pPacfileName = ms_pPacfileName;
            pCueSheetName = ms_pCueSheetName;
        }

    protected:
        void Initialize(GameDocument& in_rDocument) override
        {
            for (size_t i = 0; i < ModelContainer.Models.size(); i++)
            {
                ModelContainer.Models[i] = GetModelResource(ms_pModelNames[i]);
                SkeletonContainer.Skeletons[i] = GetSkeletonResource(ms_pSkeletonNames[i]);
            }
            
            auto animScript = GetAnimationScriptResource(ms_pAnimScriptNames[0]);
            animation::AnimationResContainer::LoadInfo animLoadInfo{ animScript, SkeletonContainer.Skeletons[0], nullptr };
            BaseAnimationContainer.LoadFromBuffer(animLoadInfo, GetEnemyPackfile());
            
            animScript = GetAnimationScriptResource(ms_pAnimScriptNames[1]);
            animLoadInfo = { animScript, SkeletonContainer.Skeletons[1], nullptr };
            AnimationContainer.LoadFromBuffer(animLoadInfo, GetEnemyPackfile());

            ShotModel = GetModelResource(ms_pShotModelName);
        }

        const char* GetInfoName() override
        {
            return ms_pName;
        }
    };
}