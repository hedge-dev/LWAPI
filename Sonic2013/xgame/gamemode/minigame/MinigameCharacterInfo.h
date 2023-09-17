#pragma once

namespace app
{
    class MinigameCharacterInfo : public CObjInfo
    {
    private:

    public:
        inline static const char* ms_pName = "MinigameCharacterInfo";

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

        }

    public:
        const char* GetInfoName() override
        {
            return ms_pName;
        }
    };
}