#include <Vector4d.hpp>
#include <Vector3d.hpp>

namespace MathLib
{
    Vector3<double> Vector4<double>::xyz() const noexcept
    {
#if defined(SIMD_AVX)
#else
#endif // defined(SIMD_AVX)
    }
    Vector3<double> Vector4<double>::xzy() const noexcept
    {
#if defined(SIMD_AVX)
#else
        return Vector3d(m_x, m_z, m_y);
#endif // defined(SIMD_AVX)
    }

    Vector3<double> Vector4<double>::yxz() const noexcept
    {
#if defined(SIMD_AVX)
#else
        return Vector3d(m_y, m_x, m_z);
#endif // defined(SIMD_AVX)
    }
    Vector3<double> Vector4<double>::yzx() const noexcept
    {
#if defined(SIMD_AVX)
#else
        return Vector3d(m_y, m_z, m_x);
#endif // defined(SIMD_AVX)
    }

    Vector3<double> Vector4<double>::zxy() const noexcept
    {
#if defined(SIMD_AVX)
#else
        return Vector3d(m_z, m_x, m_y);
#endif // defined(SIMD_AVX)
    }
    Vector3<double> Vector4<double>::zyx() const noexcept
    {
#if defined(SIMD_AVX)
#else
        return Vector3d(m_z, m_y, m_x);
#endif // defined(SIMD_AVX)
    }

} // MathLib
