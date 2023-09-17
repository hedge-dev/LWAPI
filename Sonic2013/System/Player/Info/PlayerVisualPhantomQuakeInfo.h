#pragma once

namespace app::Player
{
    class PhantomQuakeInfo : public CObjInfo
    {
    private:
        inline static const char* ms_pPackfileName = "PhantomQuake.pac";
        inline static const char* ms_pModelName = "chr_pha_Quake";

    public:
        hh::gfx::res::ResModel Model{};

        PhantomQuakeInfo() {}

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
            return "PhantomQuakeInfo";
        }
    };
}