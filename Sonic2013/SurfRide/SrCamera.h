#pragma once

namespace SurfRide
{
    class SrCamera
    {
    public:
        const char* m_pName{};
        int m_ID{};
        Math::Vector3 m_Position{};
        Math::Vector3 m_Target{};
        int m_FieldOfView{};
        float m_NearPlane{};
        float m_FarPlane{};
        INSERT_PADDING(8);
    };
}