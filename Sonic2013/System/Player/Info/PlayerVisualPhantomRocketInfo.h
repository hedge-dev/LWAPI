#pragma once

namespace app::Player
{
    class PhantomRocketInfo : public CObjInfo
    {
    private:
        inline static const char* ms_pPackfileName = "PhantomRocket.pac";
        inline static const char* ms_pModelName = "chr_pha_Rocket";

    public:
        hh::gfx::res::ResModel Model{};

        PhantomRocketInfo() {}

    protected:
        void Load(CObjInfoFileLoader& in_rLoader) override
        {
            in_rLoader.Load(ms_pPackfileName, 0x4001);
        }

        void Initialize(GameDocument& in_rDocument) override
        {
            auto packFile = ObjUtil::GetPackFile(ms_pPackfileName);

            Model = ObjUtil::GetModelResource(ms_pModelName, packFile);
        }

        const char* GetInfoName() override
        {
            return "PhantomRocketInfo";
        }
    };
}