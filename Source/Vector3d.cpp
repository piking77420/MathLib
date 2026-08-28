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
        return Vector2d(getX(), getZ());
    }

    Vector2<double> Vector3<double>::yx() const noexcept
    {
        return Vector2d(getY(), getX());
    }

    Vector2<double> Vector3<double>::yz() const noexcept
    {
        return Vector2d(getY(), getZ());
    }

    Vector2<double> Vector3<double>::zx() const noexcept
    {
        return Vector2d(getZ(), getX());
    }

    Vector2<double> Vector3<double>::zy() const noexcept
    {
        return Vector2d(getZ(), getY());
    }

    Vector3<double>::operator Vector2<double>() const noexcept
    {
        return Vector2d(getX(), getY());
    }
} // namespace MathLib
