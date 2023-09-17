#pragma once

namespace app
{
    class GameOverInfo : public CObjInfo
    {
    private:

    public:
        inline static const char* ms_pName = "GameOverInfo";

        hh::gfx::res::ResModel SonicModel{};
        hh::gfx::res::ResSkeleton SonicSkeleton{};
        animation::AnimationResContainer SonicAnimation{ *m_pAllocator };
        ObjUtil::ResTexSrtAnimFixedContainer<6> TextureAnimations{};
        hh::gfx::res::ResModel SpotlightModel{};

    public:
        GameOverInfo() : CObjInfo()
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