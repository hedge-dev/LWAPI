#pragma once

namespace app
{
    class WorldAreaMapInfo : public CObjInfo
    {
    private:
       
    public:
        inline static const char* ms_pName = "ObjBreakFloorInfo";

        hh::gfx::res::ResModel SonicModel{};
        hh::gfx::res::ResSkeleton SonicSkeleton{};
        animation::AnimationResContainer AnimationContainer{ *m_pAllocator };
        csl::ut::FixedArray<hh::gfx::res::ResAnimVis, 2> VisualAnimations{};
        hh::gfx::res::ResModel CursorModel{};
        hh::gfx::res::ResModel DioramaShadow{};
        hh::gfx::res::ResModel RankIcons[5]{};
        WorldAreaMapObjResource DioramaResources[36]{};
        WorldAreaMapObjResource IconResources[8]{};
        WorldAreaMapObjResource RoadResources[7]{};
        WorldAreaMapObjResource RoadEffectResources[7]{};
        WorldAreaMapObjResource WallEffectResources[7]{};
        WorldAreaMapObjResource DioramaSelectionResources[8]{};
        hh::gfx::res::ResModel ItemBoxModel{};
        hh::gfx::res::ResSkeleton Unk1{};
        hh::gfx::res::ResAnimSkeleton Unk2{};
        csl::ut::MoveArray<hh::gfx::res::ResAnimSkeleton> Unk3{};
        csl::ut::MoveArray<hh::gfx::res::ResAnimMaterial> Unk4{};
        csl::ut::MoveArray<hh::gfx::res::ResAnimVis> Unk5{};
        csl::ut::MoveArray<hh::gfx::res::ResAnimTexSrt> Unk6{};
        WorldAreaMapObjResource ItemResources[6]{};
        INSERT_PADDING(1400); //xgame::WorldMapConfig WorldMapConfig{};
        INSERT_PADDING(20); //xgame::DioramaConfigContainer DioramaConfigurations{};
        WorldAreaMapObjResource ExtraDioramaResources[3]{};

    public:
        WorldAreaMapInfo() : CObjInfo()
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