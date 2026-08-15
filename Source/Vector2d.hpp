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

        MATH_LIB_FORCE_INLINE explicit Vector2(double _x, double _y)
            : m_x(_x)
            , m_y(_y)
        {
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double getX() const noexcept
        {
            return m_x;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double getY() const noexcept
        {
            return m_y;
        }

        MATH_LIB_FORCE_INLINE void setX(double _x) noexcept
        {
            m_x = _x;
        }

        MATH_LIB_FORCE_INLINE void setY(double _y) noexcept
        {
            m_y = _y;
        }

        MATH_LIB_FORCE_INLINE Vector2& operator+=(const Vector2& _other) noexcept
        {
            m_x += _other.m_x;
            m_y += _other.m_y;
            return *this;
        }

        MATH_LIB_FORCE_INLINE Vector2& operator-=(const Vector2& _other) noexcept
        {
            m_x -= _other.m_x;
            m_y -= _other.m_y;
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
            m_x += _scalar;
            m_y += _scalar;
            return *this;
        }

        MATH_LIB_FORCE_INLINE Vector2& operator-=(const double _scalar) noexcept
        {
            m_x -= _scalar;
            m_y -= _scalar;
            return *this;
        }

        MATH_LIB_FORCE_INLINE Vector2& operator*=(double _scalar) noexcept
        {
            m_x *= _scalar;
            m_y *= _scalar;
            return *this;
        }

        MATH_LIB_FORCE_INLINE Vector2& operator/=(double _scalar) noexcept
        {
            m_x /= _scalar;
            m_y /= _scalar;
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
            return FuzzyZero(m_x - _other.m_x) && FuzzyZero(m_y - _other.m_y);
        }

        [[nodiscard]] bool operator!=(const Vector2& _other) const
        {
            return !(*this == _other);
        }

        [[nodiscard]] static MATH_LIB_FORCE_INLINE double dot(const Vector2& _a, const Vector2& _b)
        {
            return (_a.m_x * _b.m_x) + (_a.m_y * _b.m_y);
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double lengthSquare() const
        {
            return dot(*this, *this);
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double length() const
        {
            return std::sqrt(lengthSquare());
        }

        [[nodiscard]] static MATH_LIB_FORCE_INLINE double distanceSquare(const Vector2& _a, const Vector2& _b)
        {
            return (_b - _a).lengthSquare();
        }

        [[nodiscard]] static MATH_LIB_FORCE_INLINE double distance(const Vector2& _a, const Vector2& _b)
        {
            return std::sqrt(distanceSquare(_a, _b));
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector2 getNormalize() const
        {
            const double currentLength = length();

            if (FuzzyZero(currentLength))
            {
                return *this;
            }

            return *this / currentLength;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector2 getNormalizeFast() const
        {
            const double currentLength = length();

            if (FuzzyZero(currentLength))
            {
                return *this;
            }

            const double invLength = 1.0 / currentLength;
            return *this * invLength;
        }

        Vector2& normalize()
        {
            const double currentLength = length();

            if (FuzzyZero(currentLength))
            {
                return *this;
            }

            *this /= currentLength;
            return *this;
        }

        Vector2& normalizeFast()
        {
            const double currentLength = length();

            if (FuzzyZero(currentLength))
            {
                return *this;
            }

            const double invLength = 1.0 / currentLength;
            *this *= invLength;
            return *this;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE static double cross(const Vector2& _a, const Vector2& _b)
        {
            return _b.getY() * _a.getX() - _b.getX() * _a.getY();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE static Vector2 min(const Vector2& _a, const Vector2& _b) noexcept
        {
            return Vector2(std::min(_a.getX(), _b.getX()), std::min(_a.getY(), _b.getY()));
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE static Vector2 max(const Vector2& _a, const Vector2& _b) noexcept
        {
            return Vector2(std::max(_a.getX(), _b.getX()), std::max(_a.getY(), _b.getY()));
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

        MATH_LIB_FORCE_INLINE void streamToUnalignedDouble(const std::span<double, 2>& _span) const
        {
            _span[0] = m_x;
            _span[1] = m_y;
        }

        MATH_LIB_FORCE_INLINE void streamToUnalignedDouble(double* const _ptr) const
        {
            streamToUnalignedDouble(std::span<double, 2>(_ptr, 2));
        }

        MATH_LIB_FORCE_INLINE void streamToUnAlignedFloat(const std::span<float, 2>& _span) const
        {
            _span[0] = static_cast<float>(m_x);
            _span[1] = static_cast<float>(m_y);
        }

        MATH_LIB_FORCE_INLINE void streamToUnAlignedFloat(float* const _ptr) const
        {
            streamToUnAlignedFloat(std::span<float, 2>(_ptr, 2));
        }

        MATH_LIB_FORCE_INLINE void streamToAlignedDouble(const std::span<double, 2>& _span) const
        {
            assert(isAligned<AVX_AVX2_ALIGNEMENT>(_span.data()));

            _span[0] = m_x;
            _span[1] = m_y;
        }

        MATH_LIB_FORCE_INLINE void streamToAlignedDouble(double* const _ptr) const
        {
            streamToAlignedDouble(std::span<double, 2>(_ptr, 2));
        }

        MATH_LIB_FORCE_INLINE void streamToAlignedFloat(const std::span<float, 2>& _span) const
        {
            assert(isAligned<SSE_ALIGNEMENT>(_span.data()));

            _span[0] = static_cast<float>(m_x);
            _span[1] = static_cast<float>(m_y);
        }

        MATH_LIB_FORCE_INLINE void streamToAlignedFloat(float* const _ptr) const
        {
            streamToUnAlignedFloat(std::span<float, 2>(_ptr, 2));
        }

        MATH_LIB_FORCE_INLINE void fromUnalignedDouble(const std::span<const double, 2>& _span)
        {
            m_x = _span[0];
            m_y = _span[1];
        }

        MATH_LIB_FORCE_INLINE void fromUnalignedDouble(double* const _ptr)
        {
            fromUnalignedDouble(std::span<double, 2>(_ptr, 2));
        }

        MATH_LIB_FORCE_INLINE void fromUnAlignedFloat(const std::span<const float, 2>& _span)
        {
            m_x = static_cast<double>(_span[0]);
            m_y = static_cast<double>(_span[1]);
        }

        MATH_LIB_FORCE_INLINE void fromUnAlignedFloat(float* const _ptr)
        {
            fromUnAlignedFloat(std::span<float, 2>(_ptr, 2));
        }

        MATH_LIB_FORCE_INLINE void fromAlignedDouble(const std::span<const double, 2>& _span)
        {
            assert(isAligned<AVX_AVX2_ALIGNEMENT>(_span.data()));

            m_x = _span[0];
            m_y = _span[1];
        }

        MATH_LIB_FORCE_INLINE void fromAlignedDouble(const double* const _ptr)
        {
            fromAlignedDouble(std::span<const double, 2>(_ptr, 2));
        }

        MATH_LIB_FORCE_INLINE void fromAlignedFloat(const std::span<const float, 2>& _span)
        {
            assert(isAligned<SSE_ALIGNEMENT>(_span.data()));

            m_x = static_cast<double>(_span[0]);
            m_y = static_cast<double>(_span[1]);
        }

        MATH_LIB_FORCE_INLINE void fromAlignedFloat(const float* const _ptr)
        {
            fromAlignedFloat(std::span<const float, 2>(_ptr, 2));
        }

        friend MATH_LIB_FORCE_INLINE std::ostream& operator<<(std::ostream& _ostream, const Vector2& _vec)
        {
            alignas(AVX_AVX2_ALIGNEMENT) std::array<double, 2> data;
            _vec.streamToUnalignedDouble(data);
            _ostream << "x: " << data[0] << ", y: " << data[1];

            return _ostream;
        }

    private:
        double m_x;
        double m_y;
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

        _v.streamToUnalignedDouble(data);

        return std::format_to(_ctx.out(), "x: {}, y: {}", data[0], data[1]);
    }
};

#endif // MATH_LIB_VECTOR2D_H
