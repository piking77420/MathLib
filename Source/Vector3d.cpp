#include <Vector3d.hpp>
#include <Vector2d.hpp>

namespace MathLib
{
    Vector2<double> Vector3<double>::xy() const noexcept
    {
        return static_cast<Vector2d>(*this);
    }

    Vector2<double> Vector3<double>::xz() const noexcept
    {
        return Vector2d(m_x, m_z);
    }

    Vector2<double> Vector3<double>::yx() const noexcept
    {
        return Vector2d(m_y, m_x);
    }

    Vector2<double> Vector3<double>::yz() const noexcept
    {
        return Vector2d(m_y, m_z);
    }

    Vector2<double> Vector3<double>::zx() const noexcept
    {
        return Vector2d(m_z, m_x);
    }

    Vector2<double> Vector3<double>::zy() const noexcept
    {
        return Vector2d(m_z, m_y);
    }

    Vector3<double>::operator Vector2<double>() const noexcept
    {
        return Vector2d(m_x, m_y);
    }
} // namespace MathLib
