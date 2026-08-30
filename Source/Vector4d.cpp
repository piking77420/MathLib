#include <array>
#include <Matrix3x3d.hpp>
#include <Vector4d.hpp>
#include <Vector3d.hpp>
#include <Vector2.hpp>

namespace MathLib
{
    Vector3<double> Vector4<double>::xyz() const noexcept
    {
        return static_cast<Vector3<double>>(*this);
    };

    Vector3<double> Vector4<double>::xzy() const noexcept
    {
        return static_cast<Vector3<double>>(xzyw());
    }

    Vector3<double> Vector4<double>::yxz() const noexcept
    {
        return static_cast<Vector3<double>>(yxzw());
    }
    Vector3<double> Vector4<double>::yzx() const noexcept
    {
        return static_cast<Vector3<double>>(yzxw());
    }

    Vector3<double> Vector4<double>::zxy() const noexcept
    {
        return static_cast<Vector3<double>>(zxyw());
    }
    Vector3<double> Vector4<double>::zyx() const noexcept
    {
        return static_cast<Vector3<double>>(zyxw());
    }

    Vector2<double> Vector4<double>::xy() const noexcept
    {
        return static_cast<Vector2<double>>(*this);
    }

    Vector2<double> Vector4<double>::xz() const noexcept
    {
        return static_cast<Vector2<double>>(xzwy());
    }

    Vector2<double> Vector4<double>::xw() const noexcept
    {
        return static_cast<Vector2<double>>(xwyz());
    }

    Vector2<double> Vector4<double>::yx() const noexcept
    {
        return static_cast<Vector2<double>>(yxzw());
    }

    Vector2<double> Vector4<double>::yz() const noexcept
    {
        return static_cast<Vector2<double>>(yzxw());
    }

    Vector2<double> Vector4<double>::yw() const noexcept
    {
        return static_cast<Vector2<double>>(ywxz());
    }

    Vector2<double> Vector4<double>::zx() const noexcept
    {
        return static_cast<Vector2<double>>(zxyw());
    }

    Vector2<double> Vector4<double>::zy() const noexcept
    {
        return static_cast<Vector2<double>>(zywx());
    }

    Vector2<double> Vector4<double>::zw() const noexcept
    {
        return static_cast<Vector2<double>>(zwxy());
    }

    Vector2<double> Vector4<double>::wx() const noexcept
    {
        return static_cast<Vector2<double>>(wxyz());
    }

    Vector2<double> Vector4<double>::wy() const noexcept
    {
        return static_cast<Vector2<double>>(wyxz());
    }

    Vector2<double> Vector4<double>::wz() const noexcept
    {
        return static_cast<Vector2<double>>(wzxy());
    }

    Vector4<double>::operator Vector3<double>() const noexcept
    {
        return Vector3<double>(getX(), getY(), getZ());
    }

    Vector4<double>::operator Vector2<double>() const noexcept
    {
        return Vector2<double>(getX(), getY());
    }

} // MathLib
