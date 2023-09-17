#pragma once

namespace SurfRide::Math
{
    class Vector2 : Eigen::Vector2f
    {
    public:
        static const Vector2* Zero;

        Vector2() : Eigen::Vector2f()
        {

        }

        Vector2(float x, float y) : Eigen::Vector2f(x, y)
        {

        }

        Vector2(const Eigen::Vector2f& vec) : Eigen::Vector2f(vec.x(), vec.y())
        {

        }

        float GetX() const { return x(); }
        float GetY() const { return y(); }
    };

    class Vector3 : Eigen::Vector3f
    {
    public:
        static const Vector3* Zero;

        Vector3() : Eigen::Vector3f()
        {

        }

        Vector3(float x, float y, float z) : Eigen::Vector3f(x, y, z)
        {

        }

        Vector3(const Eigen::Vector3f& vec) : Eigen::Vector3f(vec.x(), vec.y(), vec.z())
        {

        }

        float GetX() const { return x(); }
        void SetX(float in_x) { x() = in_x; }
        float GetY() const { return y(); }
        void SetY(float in_y) { y() = in_y; }
        float GetZ() const { return z(); }
        void SetZ(float in_z) { z() = in_z; }
    };
}