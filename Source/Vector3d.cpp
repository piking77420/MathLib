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
        return static_cast<Vector2d>(xzy());
    }

    Vector2<double> Vector3<double>::yx() const noexcept
    {
#if defined(SIMD_AVX)
        return Vector2d(_mm_permute_pd(_mm256_castpd256_pd128(m_data), 0b01));
#else
        return static_cast<Vector2d>(yxz());
#endif
    }

    Vector2<double> Vector3<double>::yz() const noexcept
    {
        return static_cast<Vector2d>(yzx());
    }

    Vector2<double> Vector3<double>::zx() const noexcept
    {
        return static_cast<Vector2d>(zxy());
    }

    Vector2<double> Vector3<double>::zy() const noexcept
    {
        return static_cast<Vector2d>(zyx());
    }

    Vector3<double>::operator Vector2<double>() const noexcept
    {
#if defined(SIMD_AVX)
        return Vector2<double>(_mm256_castpd256_pd128(m_data));
#else
        return Vector2d(m_x, m_y);
#endif
    }
} // namespace MathLib
