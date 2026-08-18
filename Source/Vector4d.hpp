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
        MATH_LIB_FORCE_INLINE Vector4(__m256d _data) noexcept
            : m_data(_data)
        {
        }
#endif // defined(SIMD_AVX)

        MATH_LIB_FORCE_INLINE explicit Vector4(double _x, double _y, double _z, double _w)
#if defined(SIMD_AVX)
            : m_data(_mm256_set_pd(_w, _z, _y, _x))
#else
            : m_x(_x)
            , m_y(_y)
            , m_z(_z)
            , m_w(_w)
#endif // defined(SIMD_AVX)

                  {ASSERT_IS_FINITE(*this)}

            MATH_LIB_FORCE_INLINE explicit Vector4(double _x)
#if defined(SIMD_AVX)
            : m_data(_mm256_set1_pd(_x))
#else
            : m_x(_x)
            , m_y(_x)
            , m_z(_x)
            , m_w(_x)
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

        MATH_LIB_FORCE_INLINE void setX(double _x) noexcept
        {
#if defined(SIMD_AVX)
            m_data = _mm256_blend_pd(m_data, _mm256_set1_pd(_x), 0b0001);
#else
            m_x = _x;
#endif // defined(SIMD_AVX)
            ASSERT_IS_FINITE(*this);
        }

        MATH_LIB_FORCE_INLINE void setY(double _y) noexcept
        {
#if defined(SIMD_AVX)
            m_data = _mm256_blend_pd(m_data, _mm256_set1_pd(_y), 0b0010);
#else
            m_y = _y;
#endif // defined(SIMD_AVX)
            ASSERT_IS_FINITE(*this);
        }

        MATH_LIB_FORCE_INLINE void setZ(double _z) noexcept
        {
#if defined(SIMD_AVX)
            m_data = _mm256_blend_pd(m_data, _mm256_set1_pd(_z), 0b0100);
#else
            m_z = _z;
#endif // defined(SIMD_AVX)
            ASSERT_IS_FINITE(*this);
        }

        MATH_LIB_FORCE_INLINE void setW(double _w) noexcept
        {
#if defined(SIMD_AVX)
            m_data = _mm256_blend_pd(m_data, _mm256_set1_pd(_w), 0b1000);
#else
            m_w = _w;
#endif // defined(SIMD_AVX)
            ASSERT_IS_FINITE(*this);
        }

        MATH_LIB_FORCE_INLINE Vector4& operator+=(const Vector4& _other) noexcept
        {
#if defined(SIMD_AVX)
            m_data = _mm256_add_pd(*this, _other);
#else
            m_x += _other.m_x;
            m_y += _other.m_y;
            m_z += _other.m_z;
            m_w += _other.m_w;
#endif // defined(SIMD_AVX)

            ASSERT_IS_FINITE(*this) return *this;
        }

        MATH_LIB_FORCE_INLINE Vector4& operator-=(const Vector4& _other) noexcept
        {
#if defined(SIMD_AVX)
            m_data = _mm256_sub_pd(*this, _other);
#else
            m_x -= _other.m_x;
            m_y -= _other.m_y;
            m_z -= _other.m_z;
            m_w -= _other.m_w;
#endif // defined(SIMD_AVX)
            ASSERT_IS_FINITE(*this)
            return *this;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector4 operator+(Vector4 _lhs, const Vector4& _rhs) noexcept
        {
            _lhs += _rhs;
            return _lhs;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector4 operator-(Vector4 _lhs, const Vector4& _rhs) noexcept
        {
            _lhs -= _rhs;
            return _lhs;
        }

        MATH_LIB_FORCE_INLINE Vector4& operator+=(const double _scalar) noexcept
        {
#if defined(SIMD_AVX)
            m_data = _mm256_add_pd(*this, _mm256_set1_pd(_scalar));
#else
            m_x += _scalar;
            m_y += _scalar;
            m_z += _scalar;
            m_w += _scalar;
#endif // defined(SIMD_AVX)
            ASSERT_IS_FINITE(*this)
            return *this;
        }

        MATH_LIB_FORCE_INLINE Vector4& operator-=(const double _scalar) noexcept
        {
#if defined(SIMD_AVX)
            m_data = _mm256_sub_pd(*this, _mm256_set1_pd(_scalar));
#else
            m_x -= _scalar;
            m_y -= _scalar;
            m_z -= _scalar;
            m_w -= _scalar;
#endif // defined(SIMD_AVX)
            ASSERT_IS_FINITE(*this)
            return *this;
        }

        MATH_LIB_FORCE_INLINE Vector4& operator*=(double _scalar) noexcept
        {
#if defined(SIMD_AVX)
            m_data = _mm256_mul_pd(*this, _mm256_set1_pd(_scalar));
#else
            m_x *= _scalar;
            m_y *= _scalar;
            m_z *= _scalar;
            m_w *= _scalar;
#endif // defined(SIMD_AVX)
            ASSERT_IS_FINITE(*this)
            return *this;
        }

        MATH_LIB_FORCE_INLINE Vector4& operator/=(double _scalar) noexcept
        {
#if defined(SIMD_AVX)
            m_data = _mm256_div_pd(*this, _mm256_set1_pd(_scalar));
#else
            m_x /= _scalar;
            m_y /= _scalar;
            m_z /= _scalar;
            m_w /= _scalar;
#endif // defined(SIMD_AVX)
            ASSERT_IS_FINITE(*this)
            return *this;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector4 operator+(Vector4 _lhs, const double _scalar) noexcept
        {
            _lhs += _scalar;
            return _lhs;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector4 operator-(Vector4 _lhs, const double _scalar) noexcept
        {
            _lhs -= _scalar;
            return _lhs;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector4 operator*(Vector4 _lhs, const double _scalar) noexcept
        {
            _lhs *= _scalar;
            return _lhs;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector4 operator/(Vector4 _lhs, const double _scalar) noexcept
        {
            _lhs /= _scalar;
            return _lhs;
        }

        [[nodiscard]] bool operator==(const Vector4& _other) const
        {
#if defined(SIMD_AVX)
            const Vector4 absDiff = (*this - _other).abs();
            const Vector4 epsilon = Vector4(DoubleEpsilon);
            const __m256d cmp = _mm256_cmp_pd(absDiff.m_data, epsilon.m_data, _CMP_LE_OQ);
            return _mm256_movemask_pd(cmp) == 0b1111;
#else
            return fuzzyZero(m_x - _other.m_x) && fuzzyZero(m_y - _other.m_y) && fuzzyZero(m_z - _other.m_z) &&
                   fuzzyZero(m_w - _other.m_w);
#endif
        }

        [[nodiscard]] bool operator!=(const Vector4& _other) const
        {
            return !(*this == _other);
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

        [[nodiscard]] static MATH_LIB_FORCE_INLINE double dot(const Vector4& _a, const Vector4& _b)
        {
            ASSERT_IS_FINITE(_a)
            ASSERT_IS_FINITE(_b)
#if defined(SIMD_AVX)
            // [ax*bx, ay*by, az*bz, aw*bw]
            const __m256d mul = _mm256_mul_pd(_a, _b);

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
            return (_a.m_x * _b.m_x) + (_a.m_y * _b.m_y) + (_a.m_z * _b.m_z) + (_a.m_w * _b.m_w);
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

        [[nodiscard]] static MATH_LIB_FORCE_INLINE double distanceSquare(const Vector4& _a, const Vector4& _b)
        {
            ASSERT_IS_FINITE(_a)
            ASSERT_IS_FINITE(_b)
            return (_b - _a).lengthSquare();
        }

        [[nodiscard]] static MATH_LIB_FORCE_INLINE double distance(const Vector4& _a, const Vector4& _b)
        {
            return std::sqrt(distanceSquare(_a, _b));
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

        [[nodiscard]] MATH_LIB_FORCE_INLINE static Vector4 min(const Vector4& _a, const Vector4& _b) noexcept
        {
            ASSERT_IS_FINITE(_a)
            ASSERT_IS_FINITE(_b)
#if defined(SIMD_AVX)
            return _mm256_min_pd(_a, _b);
#else
            return Vector4(std::min(_a.getX(), _b.getX()), std::min(_a.getY(), _b.getY()),
                           std::min(_a.getZ(), _b.getZ()), std::min(_a.getW(), _b.getW()));
#endif // defined(SIMD_AVX)
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE static Vector4 max(const Vector4& _a, const Vector4& _b) noexcept
        {
            ASSERT_IS_FINITE(_a)
            ASSERT_IS_FINITE(_b)
#if defined(SIMD_AVX)
            return _mm256_max_pd(_a, _b);
#else
            return Vector4(std::max(_a.getX(), _b.getX()), std::max(_a.getY(), _b.getY()),
                           std::max(_a.getZ(), _b.getZ()), std::max(_a.getW(), _b.getW()));
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

        MATH_LIB_FORCE_INLINE void storeToUnalignedDouble(const std::span<double, 4>& _span) const noexcept
        {
            ASSERT_IS_FINITE(*this);

#if defined(SIMD_AVX)
            _mm256_storeu_pd(_span.data(), m_data);
#else
            _span[0] = m_x;
            _span[1] = m_y;
            _span[2] = m_z;
            _span[3] = m_w;
#endif // defined(SIMD_AVX)
        }

        MATH_LIB_FORCE_INLINE void storeToUnalignedDouble(double* const _ptr) const noexcept
        {
            storeToUnalignedDouble(std::span<double, 4>(_ptr, 4));
        }

        MATH_LIB_FORCE_INLINE void storeToUnAlignedFloat(const std::span<float, 4>& _span) const noexcept
        {
            ASSERT_IS_FINITE(*this);

#if defined(SIMD_AVX)
            // Convert 4 doubles -> 4 floats.
            const __m128 values = _mm256_cvtpd_ps(m_data);
            _mm_storeu_ps(_span.data(), values);
#else
            _span[0] = static_cast<float>(m_x);
            _span[1] = static_cast<float>(m_y);
            _span[2] = static_cast<float>(m_z);
            _span[3] = static_cast<float>(m_w);
#endif // defined(SIMD_AVX)
        }

        MATH_LIB_FORCE_INLINE void storeToUnAlignedFloat(float* const _ptr) const noexcept
        {
            storeToUnAlignedFloat(std::span<float, 4>(_ptr, 4));
        }

        MATH_LIB_FORCE_INLINE void storeToAlignedDouble(const std::span<double, 4>& _span) const noexcept
        {
            MATHLIB_ASSERT(isAligned<AVX_ALIGNEMENT>(_span.data()));
            ASSERT_IS_FINITE(*this);

#if defined(SIMD_AVX)
            _mm256_store_pd(_span.data(), m_data);
#else
            _span[0] = m_x;
            _span[1] = m_y;
            _span[2] = m_z;
            _span[3] = m_w;
#endif // defined(SIMD_AVX)
        }

        MATH_LIB_FORCE_INLINE void storeToAlignedDouble(double* const _ptr) const noexcept
        {
            storeToAlignedDouble(std::span<double, 4>(_ptr, 4));
        }

        MATH_LIB_FORCE_INLINE void storeToAlignedFloat(const std::span<float, 4>& _span) const noexcept
        {
            MATHLIB_ASSERT(isAligned<SSE_ALIGNEMENT>(_span.data()));
            ASSERT_IS_FINITE(*this);

#if defined(SIMD_AVX)
            const __m128 values = _mm256_cvtpd_ps(m_data);
            _mm_store_ps(_span.data(), values);
#else
            _span[0] = static_cast<float>(m_x);
            _span[1] = static_cast<float>(m_y);
            _span[2] = static_cast<float>(m_z);
            _span[3] = static_cast<float>(m_w);
#endif // defined(SIMD_AVX)
        }

        MATH_LIB_FORCE_INLINE void storeToAlignedFloat(float* const _ptr) const noexcept
        {
            storeToAlignedFloat(std::span<float, 4>(_ptr, 4));
        }

        MATH_LIB_FORCE_INLINE void fromUnalignedDouble(const std::span<const double, 4>& _span) noexcept
        {
#if defined(SIMD_AVX)
            m_data = _mm256_loadu_pd(_span.data());
#else
            m_x = _span[0];
            m_y = _span[1];
            m_z = _span[2];
            m_w = _span[3];
#endif // defined(SIMD_AVX)

            ASSERT_IS_FINITE(*this);
        }

        MATH_LIB_FORCE_INLINE void fromUnalignedDouble(const double* const _ptr) noexcept
        {
            fromUnalignedDouble(std::span<const double, 4>(_ptr, 4));
        }

        MATH_LIB_FORCE_INLINE void fromUnAlignedFloat(const std::span<const float, 4>& _span) noexcept
        {
#if defined(SIMD_AVX)
            // Load 4 floats then convert them to 4 doubles.
            m_data = _mm256_cvtps_pd(_mm_loadu_ps(_span.data()));
#else
            m_x = static_cast<double>(_span[0]);
            m_y = static_cast<double>(_span[1]);
            m_z = static_cast<double>(_span[2]);
            m_w = static_cast<double>(_span[3]);
#endif // defined(SIMD_AVX)

            ASSERT_IS_FINITE(*this);
        }

        MATH_LIB_FORCE_INLINE void fromUnAlignedFloat(const float* const _ptr) noexcept
        {
            fromUnAlignedFloat(std::span<const float, 4>(_ptr, 4));
        }

        MATH_LIB_FORCE_INLINE void fromAlignedDouble(const std::span<const double, 4>& _span) noexcept
        {
            MATHLIB_ASSERT(isAligned<AVX_ALIGNEMENT>(_span.data()));

#if defined(SIMD_AVX)
            m_data = _mm256_load_pd(_span.data());
#else
            m_x = _span[0];
            m_y = _span[1];
            m_z = _span[2];
            m_w = _span[3];
#endif // defined(SIMD_AVX)

            ASSERT_IS_FINITE(*this);
        }

        MATH_LIB_FORCE_INLINE void fromAlignedDouble(const double* const _ptr) noexcept
        {
            fromAlignedDouble(std::span<const double, 4>(_ptr, 4));
        }

        MATH_LIB_FORCE_INLINE void fromAlignedFloat(const std::span<const float, 4>& _span) noexcept
        {
            MATHLIB_ASSERT(isAligned<SSE_ALIGNEMENT>(_span.data()));

#if defined(SIMD_AVX)
            m_data = _mm256_cvtps_pd(_mm_load_ps(_span.data()));
#else
            m_x = static_cast<double>(_span[0]);
            m_y = static_cast<double>(_span[1]);
            m_z = static_cast<double>(_span[2]);
            m_w = static_cast<double>(_span[3]);
#endif // defined(SIMD_AVX)

            ASSERT_IS_FINITE(*this);
        }

        MATH_LIB_FORCE_INLINE void fromAlignedFloat(const float* const _ptr) noexcept
        {
            fromAlignedFloat(std::span<const float, 4>(_ptr, 4));
        }

        friend MATH_LIB_FORCE_INLINE std::ostream& operator<<(std::ostream& _ostream, const Vector4& _vec)
        {
            std::array<double, 4> data;
            _vec.storeToUnalignedDouble(data);
            _ostream << "x: " << data[0] << ", y: " << data[1] << ", z: " << data[2] << ", w: " << data[3];

            return _ostream;
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
    constexpr static std::format_parse_context::const_iterator parse(std::format_parse_context& _ctx)
    {
        return _ctx.begin();
    }

    static std::format_context::iterator format(const MathLib::Vector4d& _v, std::format_context& _ctx)
    {
        std::array<double, 4> data;

        _v.storeToUnalignedDouble(data);

        return std::format_to(_ctx.out(), "x: {}, y: {}, z: {}, w: {}", data[0], data[1], data[2], data[3]);
    }
};

#endif // MATH_LIB_VECTOR4D_H
