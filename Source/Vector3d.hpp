#ifndef MATH_LIB_VECTOR3D_H
#define MATH_LIB_VECTOR3D_H

#include <array>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <format>
#include <ostream>
#include <span>
#include <MathLibHeader.hpp>

// NOLINTBEGIN(clang-analyzer-optin.cplusplus.UninitializedObject)

namespace MathLib
{
    template<typename T>
    class Vector3;

    template<>
    class Vector3<double>
    {
    public:
        explicit Vector3() = default;

        ~Vector3() = default;

#if defined(SIMD_AVX)
        MATH_LIB_FORCE_INLINE Vector3(__m256d data) noexcept
            : m_data(data)
        {
        }
#endif // defined(SIMD_AVX)

        MATH_LIB_FORCE_INLINE explicit Vector3(double x, double y, double z)
#if defined(SIMD_AVX)
            : m_data(_mm256_set_pd(0.0, z, y, x))
#else
            : m_x(x)
            , m_y(y)
            , m_z(z)
#endif // defined(SIMD_AVX)

                  {ASSERT_IS_FINITE(*this)}

            MATH_LIB_FORCE_INLINE explicit Vector3(double x)
#if defined(SIMD_AVX)
            : m_data(_mm256_set_pd(0.0, x, x, x))
#else
            : m_x(x)
            , m_y(x)
            , m_z(x)
#endif // defined(SIMD_AVX)

        {
            ASSERT_IS_FINITE(*this)
        }

#if defined(SIMD_AVX)
        operator __m256d() const
        {
            return m_data;
        }
#endif // #if defined(SIMD_AVX)

        [[nodiscard]] MATH_LIB_FORCE_INLINE double getX() const noexcept
        {
#if defined(SIMD_AVX)
            return _mm_cvtsd_f64(_mm256_castpd256_pd128(m_data));
#else
            return m_x;
#endif // defined(SIMD_AVX)
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double getY() const noexcept
        {
#if defined(SIMD_AVX)
            const __m128d xy = _mm256_castpd256_pd128(m_data);
            return _mm_cvtsd_f64(_mm_unpackhi_pd(xy, xy));
#else
            return m_y;
#endif // defined(SIMD_AVX)
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double getZ() const noexcept
        {
#if defined(SIMD_AVX)
            const __m128d zw = _mm256_extractf128_pd(m_data, 1);
            return _mm_cvtsd_f64(zw);
#else
            return m_z;
#endif
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double getW() const noexcept
        {
#if defined(SIMD_AVX)
            const __m128d zw = _mm256_extractf128_pd(m_data, 1);
            return _mm_cvtsd_f64(_mm_unpackhi_pd(zw, zw));
#else
            return m_w;
#endif
        }

        MATH_LIB_FORCE_INLINE void setX(double x) noexcept
        {
#if defined(SIMD_AVX)
            m_data = _mm256_blend_pd(m_data, _mm256_set1_pd(x), 0b0001);
#else
            m_x = x;
#endif // defined(SIMD_AVX)
            ASSERT_IS_FINITE(*this);
        }

        MATH_LIB_FORCE_INLINE void setY(double y) noexcept
        {
#if defined(SIMD_AVX)
            m_data = _mm256_blend_pd(m_data, _mm256_set1_pd(y), 0b0010);
#else
            m_y = y;
#endif // defined(SIMD_AVX)
            ASSERT_IS_FINITE(*this);
        }

        MATH_LIB_FORCE_INLINE void setZ(double z) noexcept
        {
#if defined(SIMD_AVX)
            m_data = _mm256_blend_pd(m_data, _mm256_set1_pd(z), 0b0100);
#else
            m_z = z;
#endif // defined(SIMD_AVX)
            ASSERT_IS_FINITE(*this);
        }

        MATH_LIB_FORCE_INLINE Vector3& operator+=(const Vector3& other) noexcept
        {
#if defined(SIMD_AVX)
            m_data = _mm256_add_pd(*this, other);
#else
            m_x += other.m_x;
            m_y += other.m_y;
            m_z += other.m_z;
#endif // defined(SIMD_AVX)
            ASSERT_IS_FINITE(*this) return *this;
        }

        MATH_LIB_FORCE_INLINE Vector3& operator-=(const Vector3& other) noexcept
        {
#if defined(SIMD_AVX)
            m_data = _mm256_sub_pd(*this, other);
#else
            m_x -= other.m_x;
            m_y -= other.m_y;
            m_z -= other.m_z;
#endif // defined(SIMD_AVX)
            ASSERT_IS_FINITE(*this)
            return *this;
        }

        MATH_LIB_FORCE_INLINE Vector3& operator*=(const Vector3& other) noexcept
        {
#if defined(SIMD_AVX)
            m_data = _mm256_mul_pd(*this, other);
#else
            m_x *= other.m_x;
            m_y *= other.m_y;
            m_z *= other.m_z;
#endif // defined(SIMD_AVX)
            ASSERT_IS_FINITE(*this)
            return *this;
        }

        MATH_LIB_FORCE_INLINE Vector3& operator/=(const Vector3& other) noexcept
        {
#if defined(SIMD_AVX)
            const __m256d divisor = _mm256_blend_pd(other, _mm256_set1_pd(1.0), 0b1000);
            m_data = _mm256_div_pd(m_data, divisor);
            m_data = _mm256_blend_pd(m_data, _mm256_setzero_pd(), 0b1000);
#else
            m_x /= other.m_x;
            m_y /= other.m_y;
            m_z /= other.m_z;
#endif // defined(SIMD_AVX)
            ASSERT_IS_FINITE(*this)
            return *this;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector3 operator+(Vector3 lhs, const Vector3& _rhs) noexcept
        {
            lhs += _rhs;
            return lhs;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector3 operator-(Vector3 lhs, const Vector3& _rhs) noexcept
        {
            lhs -= _rhs;
            return lhs;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector3 operator*(Vector3 lhs, const Vector3& _rhs) noexcept
        {
            lhs *= _rhs;
            return lhs;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector3 operator/(Vector3 lhs, const Vector3& _rhs) noexcept
        {
            lhs /= _rhs;
            return lhs;
        }

        MATH_LIB_FORCE_INLINE Vector3& operator+=(const double scalar) noexcept
        {
#if defined(SIMD_AVX)
            m_data = _mm256_add_pd(m_data, _mm256_set_pd(0.0, scalar, scalar, scalar));
#else
            m_x += scalar;
            m_y += scalar;
            m_z += scalar;
#endif // defined(SIMD_AVX)

            ASSERT_IS_FINITE(*this)
            return *this;
        }

        MATH_LIB_FORCE_INLINE Vector3& operator-=(const double scalar) noexcept
        {
#if defined(SIMD_AVX)
            m_data = _mm256_sub_pd(m_data, _mm256_set_pd(0.0, scalar, scalar, scalar));
#else
            m_x -= scalar;
            m_y -= scalar;
            m_z -= scalar;
#endif // defined(SIMD_AVX)
            ASSERT_IS_FINITE(*this)
            return *this;
        }

        MATH_LIB_FORCE_INLINE Vector3& operator*=(double scalar) noexcept
        {
#if defined(SIMD_AVX)
            m_data = _mm256_mul_pd(m_data, _mm256_set_pd(1.0, scalar, scalar, scalar));
#else
            m_x *= scalar;
            m_y *= scalar;
            m_z *= scalar;
#endif // defined(SIMD_AVX)
            ASSERT_IS_FINITE(*this)
            return *this;
        }

        MATH_LIB_FORCE_INLINE Vector3& operator/=(double scalar) noexcept
        {
#if defined(SIMD_AVX)
            m_data = _mm256_div_pd(m_data, _mm256_set_pd(1.0, scalar, scalar, scalar));
#else
            m_x /= scalar;
            m_y /= scalar;
            m_z /= scalar;
#endif // defined(SIMD_AVX)
            ASSERT_IS_FINITE(*this)
            return *this;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector3 operator+(Vector3 lhs, const double scalar) noexcept
        {
            lhs += scalar;
            return lhs;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector3 operator-(Vector3 lhs, const double scalar) noexcept
        {
            lhs -= scalar;
            return lhs;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector3 operator*(Vector3 lhs, const double scalar) noexcept
        {
            lhs *= scalar;
            return lhs;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector3 operator/(Vector3 lhs, const double scalar) noexcept
        {
            lhs /= scalar;
            return lhs;
        }

        [[nodiscard]] bool operator==(const Vector3& other) const
        {
#if defined(SIMD_AVX)
            const Vector3 absDiff = (*this - other).abs();
            const Vector3 epsilon = Vector3(DoubleEpsilon);
            const __m256d cmp = _mm256_cmp_pd(absDiff.m_data, epsilon.m_data, _CMP_LE_OQ);
            // mask w
            return (_mm256_movemask_pd(cmp) & 0b0111) == 0b0111; // we ignore w
#else
            return fuzzyZero(m_x - other.m_x) && fuzzyZero(m_y - other.m_y) && fuzzyZero(m_z - other.m_z);
#endif
        }

        [[nodiscard]] bool operator!=(const Vector3& other) const
        {
            return !(*this == other);
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector3 operator-() const noexcept
        {
            ASSERT_IS_FINITE(*this)
#if defined(SIMD_AVX)
            // -0.0 has only the sign bit set: 0x8000000000000000
            constexpr size_t mask = 0x7FFFFFFFFFFFull;
            return Vector3{_mm256_xor_pd(m_data, _mm256_set1_pd(-0.0))}; // we can ignore w = -0.0
#else
            return Vector3(-m_x, -m_y, -m_z);
#endif // defined(SIMD_AVX)
        }

        [[nodiscard]] static MATH_LIB_FORCE_INLINE double dot(const Vector3& a, const Vector3& b)
        {
            ASSERT_IS_FINITE(a)
            ASSERT_IS_FINITE(b)
#if defined(SIMD_AVX)
            // [ax*bx, ay*by, az*bz, aw*bw]
            const __m256d mul = _mm256_mul_pd(a, b);

            // [ax*bx, ay*by]
            const __m128d low = _mm256_castpd256_pd128(mul);

            // [az*bz, aw*bw]
            const __m128d high = _mm256_extractf128_pd(mul, 1);
            // [ax*bx + az*bz, ay*by + aw*bw]
            const __m128d sum = _mm_add_pd(low, high);

            // Move high lane into low lane.
            const __m128d highSum = _mm_unpackhi_pd(sum, sum);

            // (ax*bx + az*bz) + (ay*by + aw*bw)
            return _mm_cvtsd_f64(_mm_add_sd(sum, highSum));
#else
            return (a.m_x * b.m_x) + (a.m_y * b.m_y) + (a.m_z * b.m_z);
#endif // defined(SIMD_AVX)
        }

        [[nodiscard]] static MATH_LIB_FORCE_INLINE Vector3 cross(const Vector3& a, const Vector3& b)
        {
            ASSERT_IS_FINITE(a);
            ASSERT_IS_FINITE(b);
            // TODO add test for correctness and winding order

#if defined(SIMD_AVX)
            // [y, z, x, w]
            const __m256d aYZX = _mm256_permute4x64_pd(a.m_data, _MM_SHUFFLE(3, 0, 2, 1));

            const __m256d bYZX = _mm256_permute4x64_pd(b.m_data, _MM_SHUFFLE(3, 0, 2, 1));

            // [z, x, y, w]
            const __m256d aZXY = _mm256_permute4x64_pd(a.m_data, _MM_SHUFFLE(3, 1, 0, 2));

            const __m256d bZXY = _mm256_permute4x64_pd(b.m_data, _MM_SHUFFLE(3, 1, 0, 2));

            return Vector3(_mm256_sub_pd(_mm256_mul_pd(aYZX, bZXY), _mm256_mul_pd(aZXY, bYZX)));
#else
            const double x = a.getY() * b.getZ() - a.getZ() * b.getY();
            const double y = a.getZ() * b.getX() - a.getX() * b.getZ();
            const double z = a.getX() * b.getY() - a.getY() * b.getX();

            return Vector3(x, y, z);
#endif
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double lengthSquare() const
        {
            ASSERT_IS_FINITE(*this)
            return dot(*this, *this);
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double length() const
        {
            ASSERT_IS_FINITE(*this)
            return std::sqrt(lengthSquare());
        }

        [[nodiscard]] static MATH_LIB_FORCE_INLINE double distanceSquare(const Vector3& a, const Vector3& b)
        {
            ASSERT_IS_FINITE(a)
            ASSERT_IS_FINITE(b)
            return (b - a).lengthSquare();
        }

        [[nodiscard]] static MATH_LIB_FORCE_INLINE double distance(const Vector3& a, const Vector3& b)
        {
            return std::sqrt(distanceSquare(a, b));
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector3 getNormalize() const
        {
            const double currentLength = length();

            if (fuzzyZero(currentLength))
            {
                return *this;
            }

            return *this / currentLength;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector3 getNormalizeFast() const
        {
            const double currentLength = length();

            if (fuzzyZero(currentLength))
            {
                return *this;
            }

            const double invLength = 1.0 / currentLength;
            return *this * invLength;
        }

        Vector3& normalize()
        {
            const double currentLength = length();

            if (fuzzyZero(currentLength))
            {
                return *this;
            }

            *this /= currentLength;
            return *this;
        }

        Vector3& normalizeFast()
        {
            const double currentLength = length();

            if (fuzzyZero(currentLength))
            {
                return *this;
            }

            const double invLength = 1.0 / currentLength;
            *this *= invLength;
            return *this;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE static Vector3 min(const Vector3& a, const Vector3& b) noexcept
        {
            ASSERT_IS_FINITE(a)
            ASSERT_IS_FINITE(b)
#if defined(SIMD_AVX)
            return Vector3(_mm256_min_pd(a, b));
#else
            return Vector3(std::min(a.getX(), b.getX()), std::min(a.getY(), b.getY()), std::min(a.getZ(), b.getZ()));
#endif
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE static Vector3 max(const Vector3& a, const Vector3& b) noexcept
        {
            ASSERT_IS_FINITE(a)
            ASSERT_IS_FINITE(b)
#if defined(SIMD_AVX)
            return Vector3(_mm256_max_pd(a, b));
#else
            return Vector3(std::max(a.getX(), b.getX()), std::max(a.getY(), b.getY()), std::max(a.getZ(), b.getZ()));
#endif
        }

        [[nodiscard]] Vector3 abs() const
        {
#if defined(SIMD_AVX)
            // that create an value with only the highest bit to 1
            const __m256d signMask = _mm256_set1_pd(-0.0);
            // a  1 0 0 0   1 0 0 0
            // b  1 0 1 0   0 1 1 1
            //    !a & b
            // r  0 0 1 0   0 1 1 1
            return Vector3{_mm256_andnot_pd(signMask, m_data)};
#else
            return Vector3{std::abs(m_x), std::abs(m_y), std::abs(m_z)};
#endif // defined(SIMD_AVX)
        }

        static Vector3 unitX()
        {
            return Vector3(1.0, 0.0, 0.0);
        }

        static Vector3 unitY()
        {
            return Vector3(0.0, 1.0, 0.0);
        }

        static Vector3 unitZ()
        {
            return Vector3(0.0, 0.0, 1.0);
        }

        static Vector3 zero()
        {
#if defined(SIMD_AVX)
            return Vector3(_mm256_setzero_pd());
#else
            return Vector3(0.0, 0.0, 0.0);
#endif // defined(SIMD_AVX)
        }

        MATH_LIB_FORCE_INLINE void storeToUnalignedDouble(const std::span<double, 3>& span) const noexcept
        {
            ASSERT_IS_FINITE(*this);

#if defined(SIMD_AVX)
            const __m256i mask = _mm256_set_epi64x(0, -1, -1, -1);
            _mm256_maskstore_pd(span.data(), mask, m_data);
#else
            span[0] = m_x;
            span[1] = m_y;
            span[2] = m_z;
#endif // defined(SIMD_AVX)
        }

        MATH_LIB_FORCE_INLINE void storeToUnalignedDouble(double* const ptr) const noexcept
        {
            storeToUnalignedDouble(std::span<double, 3>(ptr, 3));
        }

        MATH_LIB_FORCE_INLINE void storeToUnAlignedFloat(const std::span<float, 3>& span) const noexcept
        {
            ASSERT_IS_FINITE(*this);

#if defined(SIMD_AVX)
            const __m128 dataf = _mm256_cvtpd_ps(m_data);
            const __m128i mask = _mm_set_epi32(0, -1, -1, -1);
            _mm_maskstore_ps(span.data(), mask, dataf);
#else
            span[0] = static_cast<float>(m_x);
            span[1] = static_cast<float>(m_y);
            span[2] = static_cast<float>(m_z);
#endif // defined(SIMD_AVX)
        }

        MATH_LIB_FORCE_INLINE void storeToUnAlignedFloat(float* const ptr) const noexcept
        {
            storeToUnAlignedFloat(std::span<float, 3>(ptr, 3));
        }

        MATH_LIB_FORCE_INLINE void storeToAlignedDouble(const std::span<double, 3>& span) const noexcept
        {
            MATHLIB_ASSERT(isAligned<AVX_ALIGNEMENT>(span.data()));
            storeToUnalignedDouble(span);
        }

        MATH_LIB_FORCE_INLINE void storeToAlignedDouble(double* const ptr) const noexcept
        {
            storeToAlignedDouble(std::span<double, 3>(ptr, 3));
        }

        MATH_LIB_FORCE_INLINE void storeToAlignedFloat(const std::span<float, 3>& span) const noexcept
        {
            MATHLIB_ASSERT(isAligned<SSE_ALIGNEMENT>(span.data()));
            storeToUnAlignedFloat(span);
        }

        MATH_LIB_FORCE_INLINE void storeToAlignedFloat(float* const ptr) const noexcept
        {
            storeToAlignedFloat(std::span<float, 3>(ptr, 3));
        }

        MATH_LIB_FORCE_INLINE void fromUnalignedDouble(const std::span<const double, 3>& span) noexcept
        {
#if defined(SIMD_AVX)
            const __m256i mask = _mm256_set_epi64x(0, -1, -1, -1);
            m_data = _mm256_maskload_pd(span.data(), mask);
#else
            m_x = span[0];
            m_y = span[1];
            m_z = span[2];
            m_w = 0.0;
#endif // defined(SIMD_AVX)

            ASSERT_IS_FINITE(*this);
        }

        MATH_LIB_FORCE_INLINE void fromUnalignedDouble(const double* const ptr) noexcept
        {
            fromUnalignedDouble(std::span<const double, 3>(ptr, 3));
        }

        MATH_LIB_FORCE_INLINE void fromUnAlignedFloat(const std::span<const float, 3>& span) noexcept
        {
#if defined(SIMD_AVX)
            const __m128i mask = _mm_set_epi32(0, -1, -1, -1);
            const __m128 values = _mm_maskload_ps(span.data(), mask);
            m_data = _mm256_cvtps_pd(values);
#else
            m_x = static_cast<double>(span[0]);
            m_y = static_cast<double>(span[1]);
            m_z = static_cast<double>(span[2]);
            m_w = 0.0;
#endif // defined(SIMD_AVX)

            ASSERT_IS_FINITE(*this);
        }

        MATH_LIB_FORCE_INLINE void fromUnAlignedFloat(const float* const ptr) noexcept
        {
            fromUnAlignedFloat(std::span<const float, 3>(ptr, 3));
        }

        MATH_LIB_FORCE_INLINE void fromAlignedDouble(const std::span<const double, 3>& span) noexcept
        {
            MATHLIB_ASSERT(isAligned<AVX_ALIGNEMENT>(span.data()));
            fromUnalignedDouble(span);
        }

        MATH_LIB_FORCE_INLINE void fromAlignedDouble(const double* const ptr) noexcept
        {
            fromAlignedDouble(std::span<const double, 3>(ptr, 3));
        }

        MATH_LIB_FORCE_INLINE void fromAlignedFloat(const std::span<const float, 3>& span) noexcept
        {
            MATHLIB_ASSERT(isAligned<SSE_ALIGNEMENT>(span.data()));
            fromUnAlignedFloat(span);
            ASSERT_IS_FINITE(*this);
        }

        MATH_LIB_FORCE_INLINE void fromAlignedFloat(const float* const ptr) noexcept
        {
            fromAlignedFloat(std::span<const float, 3>(ptr, 3));
        }

        friend MATH_LIB_FORCE_INLINE std::ostream& operator<<(std::ostream& ostream, const Vector3& vec)
        {
            std::array<double, 3> data;
            vec.storeToUnalignedDouble(data);
            ostream << "x: " << data[0] << ", y: " << data[1] << ", z: " << data[2];

            return ostream;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE bool isFinite() const
        {
#if defined(SIMD_AVX)
            const __m256d signMask = _mm256_set1_pd(-0.0);
            const __m256d absValue = _mm256_andnot_pd(signMask, m_data);

            const __m256d infinity = _mm256_set1_pd(std::numeric_limits<double>::infinity());

            const __m256d finite = _mm256_cmp_pd(absValue, infinity, _CMP_LT_OQ);
            return (_mm256_movemask_pd(finite) & 0b0111) == 0b0111; // we ignore w
#else
            return std::isfinite(m_x) && std::isfinite(m_y) && std::isfinite(m_z);
#endif // defined(SIMD_AVX)
        }

    private:
#if defined(SIMD_AVX)
        __m256d m_data;
#else
        double m_x;
        double m_y;
        double m_z;
        [[maybe_unused]] double m_w; // not used deliberately
#endif // SIMD_AVX
    };

    using Vector3d = Vector3<double>;

} // MathLib

// NOLINTEND(clang-analyzer-optin.cplusplus.UninitializedObject)

template<>
struct std::formatter<MathLib::Vector3d>
{
    constexpr static std::format_parse_context::const_iterator parse(std::format_parse_context& ctx)
    {
        return ctx.begin();
    }

    static std::format_context::iterator format(const MathLib::Vector3d& v, std::format_context& ctx)
    {
        std::array<double, 3> data;

        v.storeToUnalignedDouble(data);

        return std::format_to(ctx.out(), "x: {}, y: {}, z: {}", data[0], data[1], data[2]);
    }
};

#endif // MATH_LIB_VECTOR3D_H
