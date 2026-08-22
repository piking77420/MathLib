#ifndef MATH_LIB_VECTOR4D_H
#define MATH_LIB_VECTOR4D_H

#include <array>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <format>
#include <ostream>
#include <span>
#include <MathLibHeader.hpp>

namespace MathLib
{
    template<typename T>
    class Vector4;

    template<>
    class Vector4<double>
    {
    public:
        explicit Vector4() = default;

        ~Vector4() = default;

#if defined(SIMD_AVX)
        MATH_LIB_FORCE_INLINE Vector4(__m256d data) noexcept
            : m_data(data)
        {
        }
#endif // defined(SIMD_AVX)

        MATH_LIB_FORCE_INLINE explicit Vector4(double x, double y, double z, double w)
#if defined(SIMD_AVX)
            : m_data(_mm256_set_pd(w, z, y, x))
#else
            : m_x(x)
            , m_y(y)
            , m_z(z)
            , m_w(w)
#endif // defined(SIMD_AVX)

                  {ASSERT_IS_FINITE(*this)}

            MATH_LIB_FORCE_INLINE explicit Vector4(double x)
#if defined(SIMD_AVX)
            : m_data(_mm256_set1_pd(x))
#else
            : m_x(x)
            , m_y(x)
            , m_z(x)
            , m_w(x)
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

        MATH_LIB_FORCE_INLINE void setW(double w) noexcept
        {
#if defined(SIMD_AVX)
            m_data = _mm256_blend_pd(m_data, _mm256_set1_pd(w), 0b1000);
#else
            m_w = w;
#endif // defined(SIMD_AVX)
            ASSERT_IS_FINITE(*this);
        }

        MATH_LIB_FORCE_INLINE Vector4& operator+=(const Vector4& other) noexcept
        {
#if defined(SIMD_AVX)
            m_data = _mm256_add_pd(*this, other);
#else
            m_x += other.m_x;
            m_y += other.m_y;
            m_z += other.m_z;
            m_w += other.m_w;
#endif // defined(SIMD_AVX)

            ASSERT_IS_FINITE(*this) return *this;
        }

        MATH_LIB_FORCE_INLINE Vector4& operator-=(const Vector4& other) noexcept
        {
#if defined(SIMD_AVX)
            m_data = _mm256_sub_pd(*this, other);
#else
            m_x -= other.m_x;
            m_y -= other.m_y;
            m_z -= other.m_z;
            m_w -= other.m_w;
#endif // defined(SIMD_AVX)
            ASSERT_IS_FINITE(*this)
            return *this;
        }

        MATH_LIB_FORCE_INLINE Vector4& operator*=(const Vector4& other) noexcept
        {
#if defined(SIMD_AVX)
            m_data = _mm256_mul_pd(*this, other);
#else
            m_x *= other.m_x;
            m_y *= other.m_y;
            m_z *= other.m_z;
            m_w *= other.m_w;
#endif // defined(SIMD_AVX)
            ASSERT_IS_FINITE(*this)
            return *this;
        }

        MATH_LIB_FORCE_INLINE Vector4& operator/=(const Vector4& other) noexcept
        {
#if defined(SIMD_AVX)
            m_data = _mm256_div_pd(*this, other);
#else
            m_x /= other.m_x;
            m_y /= other.m_y;
            m_z /= other.m_z;
            m_w /= other.m_w;
#endif // defined(SIMD_AVX)
            ASSERT_IS_FINITE(*this)
            return *this;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector4 operator+(Vector4 lhs, const Vector4& _rhs) noexcept
        {
            lhs += _rhs;
            return lhs;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector4 operator-(Vector4 lhs, const Vector4& _rhs) noexcept
        {
            lhs -= _rhs;
            return lhs;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector4 operator*(Vector4 lhs, const Vector4& _rhs) noexcept
        {
            lhs *= _rhs;
            return lhs;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector4 operator/(Vector4 lhs, const Vector4& _rhs) noexcept
        {
            lhs /= _rhs;
            return lhs;
        }

        MATH_LIB_FORCE_INLINE Vector4& operator+=(const double scalar) noexcept
        {
#if defined(SIMD_AVX)
            m_data = _mm256_add_pd(*this, _mm256_set1_pd(scalar));
#else
            m_x += scalar;
            m_y += scalar;
            m_z += scalar;
            m_w += scalar;
#endif // defined(SIMD_AVX)
            ASSERT_IS_FINITE(*this)
            return *this;
        }

        MATH_LIB_FORCE_INLINE Vector4& operator-=(const double scalar) noexcept
        {
#if defined(SIMD_AVX)
            m_data = _mm256_sub_pd(*this, _mm256_set1_pd(scalar));
#else
            m_x -= scalar;
            m_y -= scalar;
            m_z -= scalar;
            m_w -= scalar;
#endif // defined(SIMD_AVX)
            ASSERT_IS_FINITE(*this)
            return *this;
        }

        MATH_LIB_FORCE_INLINE Vector4& operator*=(double scalar) noexcept
        {
#if defined(SIMD_AVX)
            m_data = _mm256_mul_pd(*this, _mm256_set1_pd(scalar));
#else
            m_x *= scalar;
            m_y *= scalar;
            m_z *= scalar;
            m_w *= scalar;
#endif // defined(SIMD_AVX)
            ASSERT_IS_FINITE(*this)
            return *this;
        }

        MATH_LIB_FORCE_INLINE Vector4& operator/=(double scalar) noexcept
        {
#if defined(SIMD_AVX)
            m_data = _mm256_div_pd(*this, _mm256_set1_pd(scalar));
#else
            m_x /= scalar;
            m_y /= scalar;
            m_z /= scalar;
            m_w /= scalar;
#endif // defined(SIMD_AVX)
            ASSERT_IS_FINITE(*this)
            return *this;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector4 operator+(Vector4 lhs, const double scalar) noexcept
        {
            lhs += scalar;
            return lhs;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector4 operator-(Vector4 lhs, const double scalar) noexcept
        {
            lhs -= scalar;
            return lhs;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector4 operator*(Vector4 lhs, const double scalar) noexcept
        {
            lhs *= scalar;
            return lhs;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector4 operator/(Vector4 lhs, const double scalar) noexcept
        {
            lhs /= scalar;
            return lhs;
        }

        [[nodiscard]] bool operator==(const Vector4& other) const
        {
#if defined(SIMD_AVX)
            const Vector4 absDiff = (*this - other).abs();
            const Vector4 epsilon = Vector4(DoubleEpsilon);
            const __m256d cmp = _mm256_cmp_pd(absDiff.m_data, epsilon.m_data, _CMP_LE_OQ);
            return _mm256_movemask_pd(cmp) == 0b1111;
#else
            return fuzzyZero(m_x - other.m_x) && fuzzyZero(m_y - other.m_y) && fuzzyZero(m_z - other.m_z) &&
                   fuzzyZero(m_w - other.m_w);
#endif
        }

        [[nodiscard]] bool operator!=(const Vector4& other) const
        {
            return !(*this == other);
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 operator-() const noexcept
        {
#if defined(SIMD_AVX)
            // -0.0 has only the sign bit set: 0x8000000000000000
            constexpr size_t mask = 0x7FFFFFFFFFFFull;
            return Vector4{_mm256_xor_pd(m_data, _mm256_set1_pd(-0.0))};
#else
            return Vector4(-m_x, -m_y, -m_z, -m_w);
#endif // defined(SIMD_AVX)
        }

        [[nodiscard]] static MATH_LIB_FORCE_INLINE double dot(const Vector4& a, const Vector4& b)
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
            return (a.m_x * b.m_x) + (a.m_y * b.m_y) + (a.m_z * b.m_z) + (a.m_w * b.m_w);
#endif // defined(SIMD_AVX)
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double lengthSquare() const
        {
            return dot(*this, *this);
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double length() const
        {
            return std::sqrt(lengthSquare());
        }

        [[nodiscard]] static MATH_LIB_FORCE_INLINE double distanceSquare(const Vector4& a, const Vector4& b)
        {
            ASSERT_IS_FINITE(a)
            ASSERT_IS_FINITE(b)
            return (b - a).lengthSquare();
        }

        [[nodiscard]] static MATH_LIB_FORCE_INLINE double distance(const Vector4& a, const Vector4& b)
        {
            return std::sqrt(distanceSquare(a, b));
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 getNormalize() const
        {
            const double currentLength = length();

            if (fuzzyZero(currentLength))
            {
                return *this;
            }

            return *this / currentLength;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 getNormalizeFast() const
        {
            const double currentLength = length();

            if (fuzzyZero(currentLength))
            {
                return *this;
            }

            const double invLength = 1.0 / currentLength;
            return *this * invLength;
        }

        Vector4& normalize()
        {
            const double currentLength = length();

            if (fuzzyZero(currentLength))
            {
                return *this;
            }

            *this /= currentLength;
            return *this;
        }

        Vector4& normalizeFast()
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

        [[nodiscard]] bool isHomogeneous() const
        {
            return fuzzyEqual(getW(), 1.0);
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE static Vector4 min(const Vector4& a, const Vector4& b) noexcept
        {
            ASSERT_IS_FINITE(a)
            ASSERT_IS_FINITE(b)
#if defined(SIMD_AVX)
            return _mm256_min_pd(a, b);
#else
            return Vector4(std::min(a.getX(), b.getX()), std::min(a.getY(), b.getY()), std::min(a.getZ(), b.getZ()),
                           std::min(a.getW(), b.getW()));
#endif // defined(SIMD_AVX)
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE static Vector4 max(const Vector4& a, const Vector4& b) noexcept
        {
            ASSERT_IS_FINITE(a)
            ASSERT_IS_FINITE(b)
#if defined(SIMD_AVX)
            return _mm256_max_pd(a, b);
#else
            return Vector4(std::max(a.getX(), b.getX()), std::max(a.getY(), b.getY()), std::max(a.getZ(), b.getZ()),
                           std::max(a.getW(), b.getW()));
#endif // defined(SIMD_AVX)
        }

        static Vector4 unitX()
        {
            return Vector4(1.0, 0.0, 0.0, 0.0);
        }

        static Vector4 unitY()
        {
            return Vector4(0.0, 1.0, 0.0, 0.0);
        }

        static Vector4 unitZ()
        {
            return Vector4(0.0, 0.0, 1.0, 0.0);
        }

        static Vector4 unitW()
        {
            return Vector4(0.0, 0.0, 0.0, 1.0);
        }

        static Vector4 zero()
        {
#if defined(SIMD_AVX)
            return Vector4{_mm256_setzero_pd()};
#else
            return Vector4(0.0, 0.0, 0.0, 0.0);
#endif // defined(SIMD_AVX)
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 abs() const noexcept
        {
            ASSERT_IS_FINITE(*this);
#if defined(SIMD_AVX)

            // that create an value with only the highest bit to 1
            const __m256d signMask = _mm256_set1_pd(-0.0);
            // a  1 0 0 0   1 0 0 0
            // b  1 0 1 0   0 1 1 1
            //    !a & b
            // r  0 0 1 0   0 1 1 1
            return Vector4{_mm256_andnot_pd(signMask, m_data)};
#else
            return Vector4(std::abs(m_x), std::abs(m_y), std::abs(m_z), std::abs(m_w));
#endif // defined(SIMD_AVX)
        }

        MATH_LIB_FORCE_INLINE void storeToUnalignedDouble(const std::span<double, 4>& span) const noexcept
        {
            ASSERT_IS_FINITE(*this);

#if defined(SIMD_AVX)
            _mm256_storeu_pd(span.data(), m_data);
#else
            span[0] = m_x;
            span[1] = m_y;
            span[2] = m_z;
            span[3] = m_w;
#endif // defined(SIMD_AVX)
        }

        MATH_LIB_FORCE_INLINE void storeToUnalignedDouble(double* const ptr) const noexcept
        {
            storeToUnalignedDouble(std::span<double, 4>(ptr, 4));
        }

        MATH_LIB_FORCE_INLINE void storeToUnAlignedFloat(const std::span<float, 4>& span) const noexcept
        {
            ASSERT_IS_FINITE(*this);

#if defined(SIMD_AVX)
            // Convert 4 doubles -> 4 floats.
            const __m128 values = _mm256_cvtpd_ps(m_data);
            _mm_storeu_ps(span.data(), values);
#else
            span[0] = static_cast<float>(m_x);
            span[1] = static_cast<float>(m_y);
            span[2] = static_cast<float>(m_z);
            span[3] = static_cast<float>(m_w);
#endif // defined(SIMD_AVX)
        }

        MATH_LIB_FORCE_INLINE void storeToUnAlignedFloat(float* const ptr) const noexcept
        {
            storeToUnAlignedFloat(std::span<float, 4>(ptr, 4));
        }

        MATH_LIB_FORCE_INLINE void storeToAlignedDouble(const std::span<double, 4>& span) const noexcept
        {
            MATHLIB_ASSERT(isAligned<AVX_ALIGNEMENT>(span.data()));
            ASSERT_IS_FINITE(*this);

#if defined(SIMD_AVX)
            _mm256_store_pd(span.data(), m_data);
#else
            span[0] = m_x;
            span[1] = m_y;
            span[2] = m_z;
            span[3] = m_w;
#endif // defined(SIMD_AVX)
        }

        MATH_LIB_FORCE_INLINE void storeToAlignedDouble(double* const ptr) const noexcept
        {
            storeToAlignedDouble(std::span<double, 4>(ptr, 4));
        }

        MATH_LIB_FORCE_INLINE void storeToAlignedFloat(const std::span<float, 4>& span) const noexcept
        {
            MATHLIB_ASSERT(isAligned<SSE_ALIGNEMENT>(span.data()));
            ASSERT_IS_FINITE(*this);

#if defined(SIMD_AVX)
            const __m128 values = _mm256_cvtpd_ps(m_data);
            _mm_store_ps(span.data(), values);
#else
            span[0] = static_cast<float>(m_x);
            span[1] = static_cast<float>(m_y);
            span[2] = static_cast<float>(m_z);
            span[3] = static_cast<float>(m_w);
#endif // defined(SIMD_AVX)
        }

        MATH_LIB_FORCE_INLINE void storeToAlignedFloat(float* const ptr) const noexcept
        {
            storeToAlignedFloat(std::span<float, 4>(ptr, 4));
        }

        MATH_LIB_FORCE_INLINE void fromUnalignedDouble(const std::span<const double, 4>& span) noexcept
        {
#if defined(SIMD_AVX)
            m_data = _mm256_loadu_pd(span.data());
#else
            m_x = span[0];
            m_y = span[1];
            m_z = span[2];
            m_w = span[3];
#endif // defined(SIMD_AVX)

            ASSERT_IS_FINITE(*this);
        }

        MATH_LIB_FORCE_INLINE void fromUnalignedDouble(const double* const ptr) noexcept
        {
            fromUnalignedDouble(std::span<const double, 4>(ptr, 4));
        }

        MATH_LIB_FORCE_INLINE void fromUnAlignedFloat(const std::span<const float, 4>& span) noexcept
        {
#if defined(SIMD_AVX)
            // Load 4 floats then convert them to 4 doubles.
            m_data = _mm256_cvtps_pd(_mm_loadu_ps(span.data()));
#else
            m_x = static_cast<double>(span[0]);
            m_y = static_cast<double>(span[1]);
            m_z = static_cast<double>(span[2]);
            m_w = static_cast<double>(span[3]);
#endif // defined(SIMD_AVX)

            ASSERT_IS_FINITE(*this);
        }

        MATH_LIB_FORCE_INLINE void fromUnAlignedFloat(const float* const ptr) noexcept
        {
            fromUnAlignedFloat(std::span<const float, 4>(ptr, 4));
        }

        MATH_LIB_FORCE_INLINE void fromAlignedDouble(const std::span<const double, 4>& span) noexcept
        {
            MATHLIB_ASSERT(isAligned<AVX_ALIGNEMENT>(span.data()));

#if defined(SIMD_AVX)
            m_data = _mm256_load_pd(span.data());
#else
            m_x = span[0];
            m_y = span[1];
            m_z = span[2];
            m_w = span[3];
#endif // defined(SIMD_AVX)

            ASSERT_IS_FINITE(*this);
        }

        MATH_LIB_FORCE_INLINE void fromAlignedDouble(const double* const ptr) noexcept
        {
            fromAlignedDouble(std::span<const double, 4>(ptr, 4));
        }

        MATH_LIB_FORCE_INLINE void fromAlignedFloat(const std::span<const float, 4>& span) noexcept
        {
            MATHLIB_ASSERT(isAligned<SSE_ALIGNEMENT>(span.data()));

#if defined(SIMD_AVX)
            m_data = _mm256_cvtps_pd(_mm_load_ps(span.data()));
#else
            m_x = static_cast<double>(span[0]);
            m_y = static_cast<double>(span[1]);
            m_z = static_cast<double>(span[2]);
            m_w = static_cast<double>(span[3]);
#endif // defined(SIMD_AVX)

            ASSERT_IS_FINITE(*this);
        }

        MATH_LIB_FORCE_INLINE void fromAlignedFloat(const float* const ptr) noexcept
        {
            fromAlignedFloat(std::span<const float, 4>(ptr, 4));
        }

        friend MATH_LIB_FORCE_INLINE std::ostream& operator<<(std::ostream& ostream, const Vector4& vec)
        {
            std::array<double, 4> data;
            vec.storeToUnalignedDouble(data);
            ostream << "x: " << data[0] << ", y: " << data[1] << ", z: " << data[2] << ", w: " << data[3];

            return ostream;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE bool isFinite() const
        {
#if defined(SIMD_AVX)
            const __m256d signMask = _mm256_set1_pd(-0.0);
            const __m256d absValue = _mm256_andnot_pd(signMask, m_data);

            const __m256d infinity = _mm256_set1_pd(std::numeric_limits<double>::infinity());

            const __m256d finite = _mm256_cmp_pd(absValue, infinity, _CMP_LT_OQ);

            return _mm256_movemask_pd(finite) == 0b1111;
#else
            return std::isfinite(m_x) && std::isfinite(m_y) && std::isfinite(m_z) && std::isfinite(m_w);
#endif // defined(SIMD_AVX)
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 xywz() const noexcept
        {
#if defined(SIMD_AVX2)
            return Vector4<double>(_mm256_permute4x64_pd(m_data, _MM_SHUFFLE(2, 3, 1, 0))); // zwyx
#elif defined(SIMD_AVX)
            // [x, y, z, w] -> [x, y, w, z]
            return Vector4<double>(_mm256_permute_pd(m_data, 0b0110));
#else
            return Vector4(m_x, m_y, m_w, m_z);
#endif // defined(SIMD_AVX)
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 xzyw() const noexcept
        {
#if defined(SIMD_AVX2)
            return Vector4<double>(_mm256_permute4x64_pd(m_data, _MM_SHUFFLE(3, 1, 2, 0))); // wyzx
#elif defined(SIMD_AVX)
            // because thee swapping element are outside lane boundary we can't use regular _mm256_permute_pd
            //
            // [x, y, z, w] -> [z, w, x, y]
            const __m256d swapped128 = _mm256_permute2f128_pd(m_data, m_data, 0x01);
            // [z, w, x, y] -> [w, z, y, x]
            const __m256d reversed = _mm256_permute_pd(swapped128, 0b0101);
            // Take lanes 1 and 2 from reversed:
            // [x, y, z, w]
            // [w, z, y, x]
            //      ^  ^
            // => [x, z, y, w]
            return Vector4<double>(_mm256_blend_pd(m_data, reversed, 0b0110));
#else
            return Vector4(m_x, m_z, m_y, m_w);
#endif // defined(SIMD_AVX2)
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 xzwy() const noexcept
        {
#if defined(SIMD_AVX2)
            return Vector4<double>(_mm256_permute4x64_pd(m_data, _MM_SHUFFLE(1, 3, 2, 0))); // ywzx

#elif defined(SIMD_AVX)

#else
            return Vector4(m_x, m_z, m_w, m_y);
#endif // defined(SIMD_AVX2)
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 xwyz() const noexcept
        {
#if defined(SIMD_AVX2)
            return Vector4<double>(_mm256_permute4x64_pd(m_data, _MM_SHUFFLE(2, 1, 3, 0))); // zywx
#elif defined(SIMD_AVX)
#else
            return Vector4(m_x, m_w, m_y, m_z);
#endif // defined(SIMD_AVX2)
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 xwzy() const noexcept
        {
#if defined(SIMD_AVX2)
            return Vector4<double>(_mm256_permute4x64_pd(m_data, _MM_SHUFFLE(1, 2, 3, 0))); // yzwx
#elif defined(SIMD_AVX)

#else
            return Vector4(m_x, m_w, m_z, m_y);
#endif // defined(SIMD_AVX2)
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 yxzw() const noexcept
        {
#if defined(SIMD_AVX2)
            return Vector4<double>(_mm256_permute4x64_pd(m_data, _MM_SHUFFLE(3, 2, 0, 1))); // wzxy
#elif defined(SIMD_AVX)

#else
            return Vector4(m_y, m_x, m_z, m_w);
#endif // defined(SIMD_AVX2)
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 yxwz() const noexcept
        {
#if defined(SIMD_AVX2)
            return Vector4<double>(_mm256_permute4x64_pd(m_data, _MM_SHUFFLE(2, 3, 0, 1))); // zwxy
#elif defined(SIMD_AVX)

#else
            return Vector4(m_y, m_x, m_w, m_z);
#endif // defined(SIMD_AVX2)
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 yzxw() const noexcept
        {
#if defined(SIMD_AVX2)
            return Vector4<double>(_mm256_permute4x64_pd(m_data, _MM_SHUFFLE(3, 0, 2, 1))); // wxzy
#elif defined(SIMD_AVX)
#else
            return Vector4(m_y, m_z, m_x, m_w);
#endif // defined(SIMD_AVX2)
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 yzwx() const noexcept
        {
#if defined(SIMD_AVX2)
            return Vector4<double>(_mm256_permute4x64_pd(m_data, _MM_SHUFFLE(0, 3, 2, 1))); // xwzy
#elif defined(SIMD_AVX)
#else
            return Vector4(m_y, m_z, m_w, m_x);
#endif // defined(SIMD_AVX2)
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 ywxz() const noexcept
        {
#if defined(SIMD_AVX2)
            return Vector4<double>(_mm256_permute4x64_pd(m_data, _MM_SHUFFLE(2, 0, 3, 1))); // zxwy
#elif defined(SIMD_AVX)
#else
            return Vector4(m_y, m_w, m_x, m_z);
#endif // defined(SIMD_AVX2)
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 ywzx() const noexcept
        {
#if defined(SIMD_AVX2)
            return Vector4<double>(_mm256_permute4x64_pd(m_data, _MM_SHUFFLE(0, 2, 3, 1))); // xzwy
#elif defined(SIMD_AVX)
#else
            return Vector4(m_y, m_w, m_z, m_x);
#endif // defined(SIMD_AVX2)
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 zxyw() const noexcept
        {
#if defined(SIMD_AVX2)
            return Vector4<double>(_mm256_permute4x64_pd(m_data, _MM_SHUFFLE(3, 1, 0, 2))); // wyxz
#elif defined(SIMD_AVX)
#else
            return Vector4(m_z, m_x, m_y, m_w);
#endif // defined(SIMD_AVX2)
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 zxwy() const noexcept
        {
#if defined(SIMD_AVX2)
            return Vector4<double>(_mm256_permute4x64_pd(m_data, _MM_SHUFFLE(1, 3, 0, 2))); // ywxz
#elif defined(SIMD_AVX)
#else
            return Vector4(m_z, m_x, m_w, m_y);
#endif // defined(SIMD_AVX2)
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 zyxw() const noexcept
        {
#if defined(SIMD_AVX2)
            return Vector4<double>(_mm256_permute4x64_pd(m_data, _MM_SHUFFLE(3, 0, 1, 2))); // wxyz
#elif defined(SIMD_AVX)
#else
            return Vector4(m_z, m_y, m_x, m_w);
#endif // defined(SIMD_AVX2)
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 zywx() const noexcept
        {
#if defined(SIMD_AVX2)
            return Vector4<double>(_mm256_permute4x64_pd(m_data, _MM_SHUFFLE(0, 3, 1, 2))); // xwyz
#elif defined(SIMD_AVX)
#else
            return Vector4(m_z, m_y, m_w, m_x);
#endif // defined(SIMD_AVX2)
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 zwxy() const noexcept
        {
#if defined(SIMD_AVX2)
            return Vector4<double>(_mm256_permute4x64_pd(m_data, _MM_SHUFFLE(1, 0, 3, 2))); // yxwz
#elif defined(SIMD_AVX)
#else
            return Vector4(m_z, m_w, m_x, m_y);
#endif // defined(SIMD_AVX2)
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 zwyx() const noexcept
        {
#if defined(SIMD_AVX2)
            return Vector4<double>(_mm256_permute4x64_pd(m_data, _MM_SHUFFLE(0, 1, 3, 2))); // xywz
#elif defined(SIMD_AVX)
#else
            return Vector4(m_z, m_w, m_y, m_x);
#endif // defined(SIMD_AVX2)
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 wxyz() const noexcept
        {
#if defined(SIMD_AVX2)
            return Vector4<double>(_mm256_permute4x64_pd(m_data, _MM_SHUFFLE(2, 1, 0, 3))); // zyxw
#elif defined(SIMD_AVX)
#else
            return Vector4(m_w, m_x, m_y, m_z);
#endif // defined(SIMD_AVX2)
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 wxzy() const noexcept
        {
#if defined(SIMD_AVX2)
            return Vector4<double>(_mm256_permute4x64_pd(m_data, _MM_SHUFFLE(1, 2, 0, 3))); // yzxw
#elif defined(SIMD_AVX)
#else
            return Vector4(m_w, m_x, m_z, m_y);
#endif // defined(SIMD_AVX2)
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 wyxz() const noexcept
        {
#if defined(SIMD_AVX2)
            return Vector4<double>(_mm256_permute4x64_pd(m_data, _MM_SHUFFLE(2, 0, 1, 3))); // zxyw
#elif defined(SIMD_AVX)
#else
            return Vector4(m_w, m_y, m_x, m_z);
#endif // defined(SIMD_AVX2)
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 wyzx() const noexcept
        {
#if defined(SIMD_AVX2)
            return Vector4<double>(_mm256_permute4x64_pd(m_data, _MM_SHUFFLE(0, 2, 1, 3))); // xzyw
#elif defined(SIMD_AVX)
#else
            return Vector4(m_w, m_y, m_z, m_x);
#endif // defined(SIMD_AVX2)
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 wzxy() const noexcept
        {
#if defined(SIMD_AVX2)
            return Vector4<double>(_mm256_permute4x64_pd(m_data, _MM_SHUFFLE(1, 0, 2, 3))); // yxzw
#elif defined(SIMD_AVX)
#else
            return Vector4(m_w, m_z, m_x, m_y);
#endif // defined(SIMD_AVX2)
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 wzyx() const noexcept
        {
#if defined(SIMD_AVX2)
            return Vector4<double>(_mm256_permute4x64_pd(m_data, _MM_SHUFFLE(0, 1, 2, 3))); // xyzw
#elif defined(SIMD_AVX)
#else
            return Vector4(m_w, m_z, m_y, m_x);
#endif // defined(SIMD_AVX2)
        }







    private:
#if defined(SIMD_AVX)
        __m256d m_data;
#else
        double m_x;
        double m_y;
        double m_z;
        double m_w;
#endif // defined(MATHLIB_SIMD_LEVEL_AVX)
    };

    using Vector4d = Vector4<double>;

} // MathLib

template<>
struct std::formatter<MathLib::Vector4d>
{
    constexpr static std::format_parse_context::const_iterator parse(std::format_parse_context& ctx)
    {
        return ctx.begin();
    }

    static std::format_context::iterator format(const MathLib::Vector4d& v, std::format_context& ctx)
    {
        std::array<double, 4> data;

        v.storeToUnalignedDouble(data);

        return std::format_to(ctx.out(), "x: {}, y: {}, z: {}, w: {}", data[0], data[1], data[2], data[3]);
    }
};

#endif // MATH_LIB_VECTOR4D_H
