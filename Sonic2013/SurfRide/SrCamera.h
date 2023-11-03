#pragma once

namespace SurfRide
{
    class SrCamera
    {
    public:
        const char* pName{};
        int ID{};
        Math::Vector3 Position{};
        Math::Vector3 Target{};
        int FieldOfView{};
        float NearPlane{};
        float FarPlane{};
        INSERT_PADDING(8);
    };
}