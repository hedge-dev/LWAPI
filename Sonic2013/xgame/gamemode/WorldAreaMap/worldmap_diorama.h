#pragma once

namespace app::worldmap
{
    struct WorldMapObjResource
    {
        hh::gfx::res::ResModel Model{};
        hh::gfx::res::ResSkeleton Skeleton{};
        hh::gfx::res::ResAnimSkeleton Animation{};
        csl::ut::MoveArray<hh::gfx::res::ResAnimSkeleton> Animations{};
        csl::ut::MoveArray<hh::gfx::res::ResAnimMaterial> MaterialAnimations{};
        csl::ut::MoveArray<hh::gfx::res::ResAnimVis> VisAnimations{};
        csl::ut::MoveArray<hh::gfx::res::ResAnimTexSrt> TexSrtAnimations{};
    };

    class CWorldMapDioramaInfo : public CObjInfo
    {
    public:
        csl::ut::FixedString<16> StageName{};
        WorldMapObjResource Resource{};

    private:
        inline static FUNCTION_PTR(void, __thiscall, ms_fpMakeResModel, ASLR(0x0094CE50), CWorldMapDioramaInfo*, WorldMapObjResource*, const char*, const char*, hh::ut::PackFile&, uint, uint);

    public:
        CWorldMapDioramaInfo(const char* in_pStageName) : CObjInfo(), StageName(in_pStageName)
        {

        }

    protected:
        void Initialize(GameDocument& in_rDocument) override
        {
            char packfileNameBuffer[32]{};
            csl::fnd::Snprintf(packfileNameBuffer, sizeof(packfileNameBuffer), "diorama_%s.pac", StageName);

            char assetNameBuffer[32]{};
            csl::fnd::Snprintf(assetNameBuffer, sizeof(assetNameBuffer), "%s_diorama", StageName);

            char scriptNameBuffer[32]{};
            csl::fnd::Snprintf(scriptNameBuffer, sizeof(scriptNameBuffer), "diorama_%s", StageName);

            auto packFile = ObjUtil::GetPackFile(packfileNameBuffer);
            if (!packFile.IsValid())
                return;

            MakeResModel(&Resource, assetNameBuffer, scriptNameBuffer, packFile, 0, 1);
        }

    public:
        const char* GetInfoName() override
        {
            return "CWorldMapDioramaInfo";
        }

        void MakeResModel(WorldMapObjResource* in_pResource, const char* in_pAssetName, const char* in_pScriptName, hh::ut::PackFile& in_rPackfile, uint in_minSkeletonCount, uint in_minAnimationCount)
        {
            ms_fpMakeResModel(this, in_pResource, in_pAssetName, in_pScriptName, in_rPackfile, in_minAnimationCount, in_minAnimationCount);
        }
    };
}