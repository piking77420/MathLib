#include <array>
#include <Matrix3x3d.hpp>
#include <Vector4d.hpp>
#include <Vector3d.hpp>
#include <Vector2d.hpp>

namespace MathLib
{
    Vector4<double> Vector4<double>::cross(const Vector4& a, const Vector4& b, const Vector4& c) noexcept
    {
        std::array<double, 4> af;
        std::array<double, 4> bf;
        std::array<double, 4> cf;

        a.storeToUnalignedDouble(af);
        b.storeToUnalignedDouble(bf);
        c.storeToUnalignedDouble(cf);

        // clang-format off
        const Matrix3x3d m0(
            af[1], af[2], af[3],
            bf[1], bf[2], bf[3],
            cf[1], cf[2], cf[3]);

        const Matrix3x3d m1(
            af[0], af[2], af[3],
            bf[0], bf[2], bf[3],
            cf[0], cf[2], cf[3]);

        const Matrix3x3d m2(
            af[0], af[1], af[3],
            bf[0], bf[1], bf[3],
            cf[0], cf[1], cf[3]);

        const Matrix3x3d m3(
            af[0], af[1], af[2],
            bf[0], bf[1], bf[2],
            cf[0], cf[1], cf[2]);
        // clang-format on

        return Vector4<double>(m0.determinant(), -m1.determinant(), m2.determinant(), -m3.determinant());
    }

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
#if defined(SIMD_AVX)
        std::array<double, 4> data;
        storeToAlignedDouble(data);
        return Vector3<double>(data[0], data[1], data[2]);
#else
        return Vector3<double>(m_x, m_y, m_z);
#endif
    }

    Vector4<double>::operator Vector2<double>() const noexcept
    {
#if defined(SIMD_AVX)
        // Vector2<double> stores [x, y] in __m128d
        return Vector2<double>(_mm256_castpd256_pd128(m_data));
#else
        return Vector2<double>(m_x, m_y);
#endif
    }

} // MathLib
