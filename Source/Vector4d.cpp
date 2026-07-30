#include <Vector4d.hpp>

namespace MathLib
{
    Vector4<double>::Vector4<double>(double _x, double _y, double _z, double _w)
        : m_x(_x)
        , m_y(_y)
        , m_z(_z)
        , m_w(_w)
    {

    }

    Vector4<double>::~Vector4<double>() = default;

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

} // MathLib