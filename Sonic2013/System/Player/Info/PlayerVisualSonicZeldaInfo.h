#pragma once

namespace app::Player
{
    class SonicZeldaInfo : public CObjInfo
    {
    public:
        inline static const char* ms_pName = "SonicZeldaInfo";

    private:
        inline static const char* ms_pPackfileName = "Linksonic.pac";
        inline static const char* ms_pModelName = "chr_Linksonic";
        inline static const char* ms_pShadowModelName = "chr_Linksonic";

    public:
        hh::gfx::res::ResModel Model{};
        res::ResShadowModel ShadowModel{ nullptr };

        SonicZeldaInfo() {}

    protected:
        void Load(CObjInfoFileLoader& in_rLoader) override
        {
            in_rLoader.Load(ms_pPackfileName, 0x4001);
        }

        void Initialize(GameDocument& in_rDocument) override
        {
            auto packFile = ObjUtil::GetPackFile(ms_pPackfileName);

            Model = ObjUtil::GetModelResource(ms_pModelName, packFile);
            ShadowModel = ObjUtil::GetShadowModel(ms_pShadowModelName, packFile);
        }

    public:
        const char* GetInfoName() override
        {
            return ms_pName;
        }
    };
}