#include <Vector4d.hpp>

namespace MathLib
{
    Vector4d::Vector4<double>(double _x, double _y, double _z, double _w)
        : m_x(_x)
        , m_y(_y)
        , m_z(_z)
        , m_w(_w)
    {

    }

    Vector4d::~Vector4<double>() = default;

    double Vector4d::getX() const noexcept
    {
        return m_x;
    }

    double Vector4d::getY() const noexcept
    {
        return m_y;
    }

    double Vector4d::getZ() const noexcept
    {
        return m_z;
    }

    double Vector4d::getW() const noexcept
    {
        return m_w;
    }

} // MathLib