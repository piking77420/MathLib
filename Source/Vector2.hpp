#ifndef MATH_LIB_VECTOR2_H
#define MATH_LIB_VECTOR2_H

#include <array>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <format>
#include <ostream>
#include <type_traits>
#include <span>
#include <MathLibHeader.hpp>

namespace MathLib
{
    template<typename T>
    requires(std::is_floating_point_v<T>)
    class Vector2
    {
    public:
        using _ValueType = T;

        explicit Vector2() = default;

        ~Vector2() = default;

        MATH_LIB_FORCE_INLINE explicit Vector2(T x, T y)
            : m_data({x, y})
        {
            ASSERT_IS_FINITE(*this);
        }

        MATH_LIB_FORCE_INLINE explicit Vector2(T x)
            : m_data({x, x})

        {
            ASSERT_IS_FINITE(*this);
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE T getX() const noexcept
        {
            return m_data[0];
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE T getY() const noexcept
        {
            return m_data[1];
        }

        MATH_LIB_FORCE_INLINE void setX(T x) noexcept
        {
            m_data[0] = x;
        }

        MATH_LIB_FORCE_INLINE void setY(T y) noexcept
        {
            m_data[1] = y;
        }

        MATH_LIB_FORCE_INLINE Vector2& operator+=(const Vector2& other) noexcept
        {
            m_data[0] += other.m_data[0];
            m_data[1] += other.m_data[1];
            ASSERT_IS_FINITE(*this);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Vector2& operator-=(const Vector2& other) noexcept
        {
            m_data[0] -= other.m_data[0];
            m_data[1] -= other.m_data[1];
            ASSERT_IS_FINITE(*this);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Vector2& operator*=(const Vector2& other) noexcept
        {
            m_data[0] *= other.m_data[0];
            m_data[1] *= other.m_data[1];
            ASSERT_IS_FINITE(*this);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Vector2& operator/=(const Vector2& other) noexcept
        {
            m_data[0] /= other.m_data[0];
            m_data[1] /= other.m_data[1];
            ASSERT_IS_FINITE(*this);
            return *this;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector2 operator+(Vector2 lhs, const Vector2& _rhs) noexcept
        {
            lhs += _rhs;
            return lhs;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector2 operator-(Vector2 lhs, const Vector2& _rhs) noexcept
        {
            lhs -= _rhs;
            return lhs;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector2 operator*(Vector2 lhs, const Vector2& _rhs) noexcept
        {
            lhs *= _rhs;
            return lhs;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector2 operator/(Vector2 lhs, const Vector2& _rhs) noexcept
        {
            lhs /= _rhs;
            return lhs;
        }

        MATH_LIB_FORCE_INLINE Vector2& operator+=(const T scalar) noexcept
        {
            m_data[0] += scalar;
            m_data[1] += scalar;
            ASSERT_IS_FINITE(*this);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Vector2& operator-=(const T scalar) noexcept
        {
            m_data[0] -= scalar;
            m_data[1] -= scalar;
            ASSERT_IS_FINITE(*this);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Vector2& operator*=(T scalar) noexcept
        {
            m_data[0] *= scalar;
            m_data[1] *= scalar;
            ASSERT_IS_FINITE(*this);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Vector2& operator/=(T scalar) noexcept
        {
            m_data[0] /= scalar;
            m_data[1] /= scalar;
            ASSERT_IS_FINITE(*this);
            return *this;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector2 operator+(Vector2 lhs, const T scalar) noexcept
        {
            lhs += scalar;
            return lhs;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector2 operator-(Vector2 lhs, const T scalar) noexcept
        {
            lhs -= scalar;
            return lhs;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector2 operator*(Vector2 lhs, const T scalar) noexcept
        {
            lhs *= scalar;
            return lhs;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector2 operator/(Vector2 lhs, const T scalar) noexcept
        {
            lhs /= scalar;
            return lhs;
        }

        [[nodiscard]] bool operator==(const Vector2& other) const
        {
            return fuzzyZero(m_data[0] - other.m_data[0]) && fuzzyZero(m_data[1] - other.m_data[1]);
        }

        [[nodiscard]] bool operator!=(const Vector2& other) const
        {
            return !(*this == other);
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector2 operator-() const noexcept
        {
            return Vector2(-m_data[0], -m_data[1]);
        }

        [[nodiscard]] static MATH_LIB_FORCE_INLINE double dot(const Vector2& a, const Vector2& b) noexcept
        {
            ASSERT_IS_FINITE(a);
            ASSERT_IS_FINITE(b);
            return (a.getX() * b.getX()) + (a.getY() * b.getY());
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

        [[nodiscard]] static MATH_LIB_FORCE_INLINE double distanceSquare(const Vector2& a, const Vector2& b)
        {
            ASSERT_IS_FINITE(a);
            ASSERT_IS_FINITE(b);
            return (b - a).lengthSquare();
        }

        [[nodiscard]] static MATH_LIB_FORCE_INLINE double distance(const Vector2& a, const Vector2& b)
        {
            return std::sqrt(distanceSquare(a, b));
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
            const T currentLength = length();

            if (fuzzyZero(currentLength))
            {
                return *this;
            }

            const T invLength = 1.0 / currentLength;
            *this *= invLength;
            return *this;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE static double cross(const Vector2& a, const Vector2& b)
        {
            ASSERT_IS_FINITE(a);
            ASSERT_IS_FINITE(b);
            return b.getY() * a.getX() - b.getX() * a.getY();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE static Vector2 min(const Vector2& a, const Vector2& b) noexcept
        {
            ASSERT_IS_FINITE(a);
            ASSERT_IS_FINITE(b);
            return Vector2(std::min(a.getX(), b.getX()), std::min(a.getY(), b.getY()));
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE static Vector2 max(const Vector2& a, const Vector2& b) noexcept
        {
            ASSERT_IS_FINITE(a);
            ASSERT_IS_FINITE(b);
            return Vector2(std::max(a.getX(), b.getX()), std::max(a.getY(), b.getY()));
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector2 abs() const noexcept
        {
            ASSERT_IS_FINITE(*this);
            return Vector2(std::abs(m_data[0]), std::abs(m_data[1]));
        }

        static Vector2 unitX()
        {
            return Vector2(static_cast<T>(1.0), static_cast<T>(0.0));
        }

        static Vector2 unitY()
        {
            return Vector2(static_cast<T>(0.0), static_cast<T>(1.0));
        }

        static Vector2 zero()
        {
            return Vector2(static_cast<T>(0.0), static_cast<T>(0.0));
        }

        friend MATH_LIB_FORCE_INLINE std::ostream& operator<<(std::ostream& ostream, const Vector2& vec)
        {
            ostream << "x: " << vec.m_data[0] << ", y: " << vec.m_data[1];

            return ostream;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE bool isFinite() const
        {
            return std::isfinite(getX()) && std::isfinite(getY());
        }

    private:
        std::array<T, 2> m_data;
    };

    using Vector2f = Vector2<float>;
    using Vector2d = Vector2<double>;

} // MathLib

template<typename T>
struct std::formatter<MathLib::Vector2<T>, char>
{
    constexpr auto parse(std::format_parse_context& ctx)
    {
        return ctx.begin();
    }

    auto format(const MathLib::Vector2<T>& v, std::format_context& ctx) const
    {
        return std::format_to(ctx.out(), "x: {}, y: {}", v.getX(), v.getY());
    }
};

#endif // MATH_LIB_VECTOR2_H
