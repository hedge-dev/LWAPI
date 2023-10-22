#pragma once

namespace app
{
    namespace mg_character
    {
        enum CharacterType
        {
            eCharacterType_Sonic,
            eCharacterType_SonicSpin,
            eCharacterType_Tails,
            eCharacterType_TailsSpin,
            eCharacterType_Orbot,
            eCharacterType_Cubot
        };
    }

    class MinigameCharacterInfo : public CObjInfo
    {
    private:

    public:
        inline static const char* ms_pName = "MinigameCharacterInfo";
        inline static const char* ms_pPacfileNames[] = { "Sonic.pac", "Sonic.pac" , "Tails.pac", "Tails.pac", "Orbot.pac", "Cubot.pac" };
        inline static const char* ms_pModelNames[] = { "chr_Sonic", "chr_sonic_spin", "chr_tails", "chr_tails_spin", "chr_Orbot_ball", "chr_CubotHead" };
        inline static const char* ms_pSkeletonNames[] = { "chr_Sonic", "chr_sonic_spin", "chr_tails", "chr_tails_spin", "chr_Orbot_ball", "chr_CubotHead" };
        inline static const char* ms_pAnimationScriptNames[] = { "player_sonic", "player_sonic_spin", "tails", "chr_tails_spin", "orbot", "cubot" };

        ObjUtil::ResModelFixedContainer<6> ModelContainer{};
        ObjUtil::ResSkeletonFixedContainer<6> SkeletonContainer{};
        animation::AnimationResContainer SonicAnimationContainer{ *m_pAllocator };
        animation::AnimationResContainer SonicSpinAnimationContainer{ *m_pAllocator };
        animation::AnimationResContainer TailsAnimationContainer{ *m_pAllocator };
        animation::AnimationResContainer TailsSpinAnimationContainer{ *m_pAllocator };
        animation::AnimationResContainer OrbotAnimationContainer{ *m_pAllocator };
        animation::AnimationResContainer CubotAnimationContainer{ *m_pAllocator };

    public:
        MinigameCharacterInfo() : CObjInfo()
        {

        }

    protected:
        void Initialize(GameDocument& in_rDocument) override
        {
            for (size_t i = 0; i < ModelContainer.Models.size(); i++)
                InitializeCharacter((mg_character::CharacterType)i);
        }

    public:
        const char* GetInfoName() override
        {
            return ms_pName;
        }

        void InitializeCharacter(mg_character::CharacterType in_characterType)
        {
            if (auto* pPacfileName = ms_pPacfileNames[in_characterType])
            {
                auto packFile = ObjUtil::GetPackFile(pPacfileName);

                if (auto* pModelName = ms_pModelNames[in_characterType])
                {
                    ModelContainer.Models[in_characterType] = ObjUtil::GetModelResource(pModelName, packFile);
                }

                if (auto* pSkeletonName = ms_pSkeletonNames[in_characterType])
                {
                    SkeletonContainer.Skeletons[in_characterType] = ObjUtil::GetSkeletonResource(pSkeletonName, packFile);
                }

                if (auto* pAnimationScriptName = ms_pAnimationScriptNames[in_characterType])
                {
                    auto animScript = ObjUtil::GetAnimationScriptResource(pAnimationScriptName, packFile);
                    animation::AnimationResContainer::LoadInfo animLoadInfo{ animScript, SkeletonContainer.Skeletons[in_characterType], nullptr };
                    GetAnimationResContainer(in_characterType)->LoadFromBuffer(animLoadInfo, packFile);
                }
            }
        }

        animation::AnimationResContainer* GetAnimationResContainer(mg_character::CharacterType in_characterType)
        {
            switch (in_characterType)
            {
            case app::mg_character::CharacterType::eCharacterType_Sonic:
            {
                return &SonicAnimationContainer;
            }
            case app::mg_character::CharacterType::eCharacterType_SonicSpin:
            {
                return &SonicSpinAnimationContainer;
            }
            case app::mg_character::CharacterType::eCharacterType_Tails:
            {
                return &TailsAnimationContainer;
            }
            case app::mg_character::CharacterType::eCharacterType_TailsSpin:
            {
                return &TailsAnimationContainer;
            }
            case app::mg_character::CharacterType::eCharacterType_Orbot:
            {
                return &OrbotAnimationContainer;
            }
            case app::mg_character::CharacterType::eCharacterType_Cubot:
            {
                return &CubotAnimationContainer;
            }
            default:
            {
                return { nullptr };
            }
            }
        }

        const animation::AnimationResContainer* GetAnimationResContainer(mg_character::CharacterType in_characterType) const
        {
            switch (in_characterType)
            {
            case app::mg_character::CharacterType::eCharacterType_Sonic:
            {
                return &SonicAnimationContainer;
            }
            case app::mg_character::CharacterType::eCharacterType_SonicSpin:
            {
                return &SonicSpinAnimationContainer;
            }
            case app::mg_character::CharacterType::eCharacterType_Tails:
            {
                return &TailsAnimationContainer;
            }
            case app::mg_character::CharacterType::eCharacterType_TailsSpin:
            {
                return &TailsAnimationContainer;
            }
            case app::mg_character::CharacterType::eCharacterType_Orbot:
            {
                return &OrbotAnimationContainer;
            }
            case app::mg_character::CharacterType::eCharacterType_Cubot:
            {
                return &CubotAnimationContainer;
            }
            default:
            {
                return { nullptr };
            }
            }
        }
    };
}