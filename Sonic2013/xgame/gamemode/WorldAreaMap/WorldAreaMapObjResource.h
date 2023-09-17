#pragma once

namespace app
{
    class WorldAreaMapObjResource
    {
    public:
        hh::gfx::res::ResModel Model{};
        hh::gfx::res::ResSkeleton Skeleton{};
        hh::gfx::res::ResAnimSkeleton Animation{};
        csl::ut::MoveArray<hh::gfx::res::ResAnimSkeleton> ExtraAnimations{};
        csl::ut::MoveArray<hh::gfx::res::ResAnimMaterial> MaterialAnimations{};
        csl::ut::MoveArray<hh::gfx::res::ResAnimVis> VisualAnimations{};
        csl::ut::MoveArray<hh::gfx::res::ResAnimTexSrt> TextureAnimations{};
    };
}