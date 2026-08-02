#include <Vector4d.hpp>

namespace MathLib
{
    Vector4<double>::Vector4(double _x, double _y, double _z, double _w)
        : m_x(_x)
        , m_y(_y)
        , m_z(_z)
        , m_w(_w)
    {
    }

    double Vector4<double>::getX() const noexcept
    {
        return m_x;
    }

    double Vector4<double>::getY() const noexcept
    {
        return m_y;
    }

    double Vector4<double>::getZ() const noexcept
    {
        return m_z;
    }

    double Vector4<double>::getW() const noexcept
    {
        return m_w;
    }

    void Vector4<double>::setX(double _x) noexcept
    {
        m_x = _x;
    }

    void Vector4<double>::setY(double _y) noexcept
    {
        m_y = _y;
    }

    void Vector4<double>::setZ(double _z) noexcept
    {
        m_z = _z;
    }

    void Vector4<double>::setW(double _w) noexcept
    {
        m_w = _w;
    }

} // MathLib