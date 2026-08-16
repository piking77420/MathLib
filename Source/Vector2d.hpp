#ifndef MATH_LIB_VECTOR2D_H
#define MATH_LIB_VECTOR2D_H

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
    class Vector2;

    template<>
    class Vector2<double>
    {
    public:
        explicit Vector2() = default;

        ~Vector2() = default;

#if defined(SIMD_SSE2)
        explicit MATH_LIB_FORCE_INLINE Vector2(__m128d _data) noexcept
            : m_data(_data)
        {
        }
#endif // defined(SIMD_SSE2)

        MATH_LIB_FORCE_INLINE explicit Vector2(double _x, double _y)
#if defined(SIMD_SSE2)
            // reverse order because the highest lane is first
            // or you can use _mm_setr_pd to reverse the order
            : m_data(_mm_set_pd(_y, _x))
#else
            : m_x(_x)
            , m_y(_y)
#endif // defined(SIMD_SSE2)
        {
            ASSERT_IS_FINITE(*this);
        }

        MATH_LIB_FORCE_INLINE explicit Vector2(double _v)
#if defined(SIMD_SSE2)
            : m_data(_mm_set1_pd(_v))
#else
            : m_x(_v)
            , m_y(_v)
#endif // defined(SIMD_SSE2)
        {
            ASSERT_IS_FINITE(*this);
        }

#if defined(SIMD_SSE2)
        operator __m128d() const
        {
            return m_data;
        }
#endif // #if defined(SIMD_SSE2)

        [[nodiscard]] MATH_LIB_FORCE_INLINE double getX() const noexcept
        {
#if defined(SIMD_SSE2)
            // Extract the lowest lane so x
            return _mm_cvtsd_f64(m_data);
#else
            return m_x;
#endif // defined(SIMD_SSE2)
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double getY() const noexcept
        {
#if defined(SIMD_SSE2)
            // unpackhi_pd will merge the 2 high of the packed double pass in parameter to one packed double
            // so we can just get the lowest lane of the result after
            return _mm_cvtsd_f64(_mm_unpackhi_pd(m_data, m_data));
#else
            return m_y;
#endif // defined(SIMD_SSE2)
        }

        MATH_LIB_FORCE_INLINE void setX(double _x) noexcept
        {
#if defined(SIMD_SSE2)
            // create and new packed double with lowest lane x
            m_data = _mm_move_sd(m_data, _mm_set_sd(_x));
#else
            m_x = _x;
#endif // defined(SIMD_SSE2)
            ASSERT_IS_FINITE(*this);
        }

        MATH_LIB_FORCE_INLINE void setY(double _y) noexcept
        {
#if defined(SIMD_SSE2)
            // create and new packed double with lowest lane x
            // merge those to lowest lane to one create a next one
            m_data = _mm_unpacklo_pd(m_data, _mm_set_sd(_y));
#else
            m_y = _y;
#endif // defined(SIMD_SSE2)
            ASSERT_IS_FINITE(*this);
        }

        MATH_LIB_FORCE_INLINE Vector2& operator+=(const Vector2& _other) noexcept
        {
#if defined(SIMD_SSE2)
            m_data = _mm_add_pd(*this, _other);
#else
            m_x += _other.m_x;
            m_y += _other.m_y;
#endif // defined(SIMD_SSE2)
            ASSERT_IS_FINITE(*this);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Vector2& operator-=(const Vector2& _other) noexcept
        {
#if defined(SIMD_SSE2)
            m_data = _mm_sub_pd(*this, _other);
#else
            m_x -= _other.m_x;
            m_y -= _other.m_y;
#endif // defined(SIMD_SSE2)
            ASSERT_IS_FINITE(*this);
            return *this;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector2 operator+(Vector2 _lhs, const Vector2& _rhs) noexcept
        {
            _lhs += _rhs;
            return _lhs;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector2 operator-(Vector2 _lhs, const Vector2& _rhs) noexcept
        {
            _lhs -= _rhs;
            return _lhs;
        }

        MATH_LIB_FORCE_INLINE Vector2& operator+=(const double _scalar) noexcept
        {
#if defined(SIMD_SSE2)
            const __m128d scalarPackedDouble = _mm_set_pd(_scalar, _scalar);
            m_data = _mm_add_pd(m_data, scalarPackedDouble);
#else
            m_x += _scalar;
            m_y += _scalar;
#endif
            ASSERT_IS_FINITE(*this);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Vector2& operator-=(const double _scalar) noexcept
        {
#if defined(SIMD_SSE2)
            const __m128d scalarPackedDouble = _mm_set_pd(_scalar, _scalar);
            m_data = _mm_sub_pd(m_data, scalarPackedDouble);
#else
            m_x -= _scalar;
            m_y -= _scalar;
#endif
            ASSERT_IS_FINITE(*this);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Vector2& operator*=(double _scalar) noexcept
        {
#if defined(SIMD_SSE2)
            const __m128d scalarPackedDouble = _mm_set_pd(_scalar, _scalar);
            m_data = _mm_mul_pd(m_data, scalarPackedDouble);
#else
            m_x *= _scalar;
            m_y *= _scalar;
#endif
            ASSERT_IS_FINITE(*this);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Vector2& operator/=(double _scalar) noexcept
        {
#if defined(SIMD_SSE2)
            const __m128d scalarPackedDouble = _mm_set_pd(_scalar, _scalar);
            m_data = _mm_div_pd(m_data, scalarPackedDouble);
#else
            m_x /= _scalar;
            m_y /= _scalar;
#endif
            ASSERT_IS_FINITE(*this);
            return *this;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector2 operator+(Vector2 _lhs, const double _scalar) noexcept
        {
            _lhs += _scalar;
            return _lhs;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector2 operator-(Vector2 _lhs, const double _scalar) noexcept
        {
            _lhs -= _scalar;
            return _lhs;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector2 operator*(Vector2 _lhs, const double _scalar) noexcept
        {
            _lhs *= _scalar;
            return _lhs;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector2 operator/(Vector2 _lhs, const double _scalar) noexcept
        {
            _lhs /= _scalar;
            return _lhs;
        }

        [[nodiscard]] bool operator==(const Vector2& _other) const
        {
#if defined(SIMD_SSE2)
            const Vector2 absDiff = (*this - _other).abs();
            const Vector2 epsilon = Vector2(DoubleEpsilon);
            const __m128d cmp = _mm_cmple_pd(absDiff, epsilon);

            return _mm_movemask_pd(cmp) == 0b11;
#else
            return fuzzyZero(m_x - _other.m_x) && fuzzyZero(m_y - _other.m_y);
#endif // defined(SIMD_SSE2)
        }

        [[nodiscard]] bool operator!=(const Vector2& _other) const
        {
            return !(*this == _other);
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector2 operator-() const noexcept
        {
#if defined(SIMD_SSE2)
            // -0.0 has only the sign bit set: 0x8000000000000000
            constexpr size_t mask = 0x7FFFFFFFFFFFull;
            return Vector2{_mm_xor_pd(m_data, _mm_set1_pd(-0.0))};
#else
            return Vector2(-m_x, -m_y);
#endif // defined(SIMD_SSE2)
        }

        [[nodiscard]] static MATH_LIB_FORCE_INLINE double dot(const Vector2& _a, const Vector2& _b)
        {
            // TODO may add ext for dot procudt simd SSE4.1
            ASSERT_IS_FINITE(_a);
            ASSERT_IS_FINITE(_b);
#if defined(SIMD_SSE2)
            // make multiplication
            // lane low := a.x * b.x
            // lane high := a.y * b.y
            const __m128d mul = _mm_mul_pd(_a, _b);
            // create new __m128d from the hight lanes of those 2
            // lane low := so a.y * b.y
            // lane high := a.y * b.y
            const __m128d high = _mm_unpackhi_pd(mul, mul);
            // _mm_add_sd adds only the low lanes.
            // addOp's low lane := (a.x * b.x) + (a.y * b.y),
            // high lane := a.y * b.y
            const __m128d addOp = _mm_add_sd(mul, high);

            // return lower lane so (a.x * b.x) + (a.y * b.y)
            return _mm_cvtsd_f64(addOp);
#else
            return (_a.getX() * _b.getX()) + (_a.getY() * _b.getY());
#endif // defined(SIMD_SSE2)
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double lengthSquare() const
        {
            ASSERT_IS_FINITE(*this)
            return dot(*this, *this);
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double length() const
        {
            return std::sqrt(lengthSquare());
        }

        [[nodiscard]] static MATH_LIB_FORCE_INLINE double distanceSquare(const Vector2& _a, const Vector2& _b)
        {
            ASSERT_IS_FINITE(_a);
            ASSERT_IS_FINITE(_b);
            return (_b - _a).lengthSquare();
        }

        [[nodiscard]] static MATH_LIB_FORCE_INLINE double distance(const Vector2& _a, const Vector2& _b)
        {
            return std::sqrt(distanceSquare(_a, _b));
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector2 getNormalize() const
        {
            const double currentLength = length();

            if (fuzzyZero(currentLength))
            {
                return *this;
            }

            return *this / currentLength;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector2 getNormalizeFast() const
        {
            const double currentLength = length();

            if (fuzzyZero(currentLength))
            {
                return *this;
            }

            const double invLength = 1.0 / currentLength;
            return *this * invLength;
        }

        Vector2& normalize()
        {
            const double currentLength = length();

            if (fuzzyZero(currentLength))
            {
                return *this;
            }

            *this /= currentLength;
            return *this;
        }

        Vector2& normalizeFast()
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

        [[nodiscard]] MATH_LIB_FORCE_INLINE static double cross(const Vector2& _a, const Vector2& _b)
        {
            ASSERT_IS_FINITE(_a);
            ASSERT_IS_FINITE(_b);

            return _b.getY() * _a.getX() - _b.getX() * _a.getY();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE static Vector2 min(const Vector2& _a, const Vector2& _b) noexcept
        {
            ASSERT_IS_FINITE(_a);
            ASSERT_IS_FINITE(_b);
#if defined(SIMD_SSE2)
            return Vector2{_mm_min_pd(_a, _b)};
#else
            return Vector2(std::min(_a.getX(), _b.getX()), std::min(_a.getY(), _b.getY()));
#endif // defined(SIMD_SSE2)
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE static Vector2 max(const Vector2& _a, const Vector2& _b) noexcept
        {
            ASSERT_IS_FINITE(_a);
            ASSERT_IS_FINITE(_b);
#if defined(SIMD_SSE2)
            return Vector2{_mm_max_pd(_a, _b)};
#else
            return Vector2(std::max(_a.getX(), _b.getX()), std::max(_a.getY(), _b.getY()));
#endif // defined(SIMD_SSE2)
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector2 abs() const noexcept
        {
            ASSERT_IS_FINITE(*this);
#if defined(SIMD_SSE2)
            // that create an value with only the highest bit to 1
            const __m128d signMask = _mm_set1_pd(-0.0);
            // a  1 0 0 0   1 0 0 0
            // b  1 0 1 0   0 1 1 1
            //    !a & b
            // r  0 0 1 0   0 1 1 1
            return Vector2{_mm_andnot_pd(signMask, m_data)};
#else
            return Vector2(std::abs(m_x), std::abs(m_y));
#endif // defined(SIMD_SSE2)
        }

        static Vector2 unitX()
        {
            return Vector2(1.0, 0.0);
        }

        static Vector2 unitY()
        {
            return Vector2(0.0, 1.0);
        }

        static Vector2 zero()
        {
            return Vector2(0.0, 0.0);
        }

        MATH_LIB_FORCE_INLINE void storeToUnalignedDouble(const std::span<double, 2>& _span) const
        {
            ASSERT_IS_FINITE(*this);
#if defined(SIMD_SSE2)
            _mm_storeu_pd(_span.data(), m_data);
#else
            _span[0] = m_x;
            _span[1] = m_y;
#endif // defined(SIMD_SSE2)
        }

        MATH_LIB_FORCE_INLINE void storeToUnalignedDouble(double* const _ptr) const
        {
            storeToUnalignedDouble(std::span<double, 2>(_ptr, 2));
        }

        MATH_LIB_FORCE_INLINE void storeToUnAlignedFloat(const std::span<float, 2>& _span) const
        {
            ASSERT_IS_FINITE(*this);
#if defined(SIMD_SSE2)

#else
            _span[0] = static_cast<float>(m_x);
            _span[1] = static_cast<float>(m_y);
#endif // defined(SIMD_SSE2)
        }

        MATH_LIB_FORCE_INLINE void storeToUnAlignedFloat(float* const _ptr) const
        {
            storeToUnAlignedFloat(std::span<float, 2>(_ptr, 2));
        }

        MATH_LIB_FORCE_INLINE void storeToAlignedDouble(const std::span<double, 2>& _span) const
        {
            ASSERT_IS_FINITE(*this);
            MATHLIB_ASSERT(isAligned<AVX_AVX2_ALIGNEMENT>(_span.data()));
#if defined(SIMD_SSE2)
            _mm_store_pd(_span.data(), m_data);
#else
            _span[0] = m_x;
            _span[1] = m_y;
#endif // defined(SIMD_SSE2)
        }

        MATH_LIB_FORCE_INLINE void storeToAlignedDouble(double* const _ptr) const
        {
            storeToAlignedDouble(std::span<double, 2>(_ptr, 2));
        }

        MATH_LIB_FORCE_INLINE void storeToAlignedFloat(const std::span<float, 2>& _span) const
        {
            ASSERT_IS_FINITE(*this);
            MATHLIB_ASSERT(isAligned<SSE_ALIGNEMENT>(_span.data()));
#if defined(SIMD_SSE2)

#else
            _span[0] = static_cast<float>(m_x);
            _span[1] = static_cast<float>(m_y);
#endif
        }

        MATH_LIB_FORCE_INLINE void storeToAlignedFloat(float* const _ptr) const
        {
            storeToUnAlignedFloat(std::span<float, 2>(_ptr, 2));
        }

        MATH_LIB_FORCE_INLINE void fromUnalignedDouble(const std::span<const double, 2>& _span)
        {
#if defined(SIMD_SSE2)
            m_data = _mm_loadu_pd(_span.data());
#else
            m_x = _span[0];
            m_y = _span[1];
#endif // #if defined(SIMD_SSE2)
            ASSERT_IS_FINITE(*this);
        }

        MATH_LIB_FORCE_INLINE void fromUnalignedDouble(const double* const _ptr)
        {
            fromUnalignedDouble(std::span<const double, 2>(_ptr, 2));
        }

        MATH_LIB_FORCE_INLINE void fromUnAlignedFloat(const std::span<const float, 2>& _span)
        {
#if defined(SIMD_SSE2)
            // Create 4 packed 32-bit floats: [x, y, 0, 0]
            const __m128 values = _mm_setr_ps(_span[0], _span[1], 0.0f, 0.0f);
            // Convert the lower 2 packed 32-bit floats to 2 packed 64-bit doubles.
            m_data = _mm_cvtps_pd(values);
#else
            m_x = static_cast<double>(_span[0]);
            m_y = static_cast<double>(_span[1]);
#endif // defined(SIMD_SSE2)
            ASSERT_IS_FINITE(*this);
        }

        MATH_LIB_FORCE_INLINE void fromUnAlignedFloat(const float* const _ptr)
        {
            fromUnAlignedFloat(std::span<const float, 2>(_ptr, 2));
        }

        MATH_LIB_FORCE_INLINE void fromAlignedDouble(const std::span<const double, 2>& _span)
        {
            MATHLIB_ASSERT(isAligned<SSE_ALIGNEMENT>(_span.data()));
#if defined(SIMD_SSE2)
            m_data = _mm_cvtps_pd(_mm_setr_ps(_span[0], _span[1], 0.0f, 0.0f));
#else
            m_x = _span[0];
            m_y = _span[1];
#endif // defined(SIMD_SSE2)
            ASSERT_IS_FINITE(*this);
        }

        MATH_LIB_FORCE_INLINE void fromAlignedDouble(const double* const _ptr)
        {
            fromAlignedDouble(std::span<const double, 2>(_ptr, 2));
        }

        MATH_LIB_FORCE_INLINE void fromAlignedFloat(const std::span<const float, 2>& _span)
        {
            MATHLIB_ASSERT(isAligned<SSE_ALIGNEMENT>(_span.data()));
#if defined(SIMD_SSE2)
            // Create 4 packed 32-bit floats: [x, y, 0, 0] but can use load instruction since the data is align
            const __m128 values = _mm_load_ps(_span.data());
            // Convert the lower 2 packed 32-bit floats to 2 packed 64-bit doubles.
            m_data = _mm_cvtps_pd(values);
#else
            m_x = static_cast<double>(_span[0]);
            m_y = static_cast<double>(_span[1]);
#endif // defined(SIMD_SSE2)
            ASSERT_IS_FINITE(*this);
        }

        MATH_LIB_FORCE_INLINE void fromAlignedFloat(const float* const _ptr)
        {
            fromAlignedFloat(std::span<const float, 2>(_ptr, 2));
        }

        friend MATH_LIB_FORCE_INLINE std::ostream& operator<<(std::ostream& _ostream, const Vector2& _vec)
        {
            std::array<double, 2> data;
            _vec.storeToUnalignedDouble(data);
            _ostream << "x: " << data[0] << ", y: " << data[1];

            return _ostream;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE bool isFinite() const
        {
#if defined(SIMD_SSE2)
            const __m128d signMask = _mm_set1_pd(-0.0);
            const __m128d absValue = _mm_andnot_pd(signMask, m_data);

            const __m128d infinity = _mm_set1_pd(std::numeric_limits<double>::infinity());

            const __m128d finite = _mm_cmplt_pd(absValue, infinity);

            return _mm_movemask_pd(finite) == 0b11;
#else
            return std::isfinite(m_x) && std::isfinite(m_y);
#endif // defined(SIMD_SSE2)
        }

    private:
#if defined(SIMD_SSE2)
        __m128d m_data;
#else
        double m_x;
        double m_y;
#endif // defined(SIMD_SSE2)
    };

    using Vector2d = Vector2<double>;

} // MathLib

template<>
struct std::formatter<MathLib::Vector2d>
{
    constexpr static std::format_parse_context::const_iterator parse(std::format_parse_context& _ctx)
    {
        return _ctx.begin();
    }

    static std::format_context::iterator format(const MathLib::Vector2d& _v, std::format_context& _ctx)
    {
        std::array<double, 2> data;

        _v.storeToUnalignedDouble(data);

        return std::format_to(_ctx.out(), "x: {}, y: {}", data[0], data[1]);
    }
};

#endif // MATH_LIB_VECTOR2D_H
