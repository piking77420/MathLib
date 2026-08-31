#ifndef MATH_LIB_VECTOR3_H
#define MATH_LIB_VECTOR3_H

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
    requires(std::is_floating_point_v<T>)
    class Vector2;

    template<typename T>
    requires(std::is_floating_point_v<T>)
    class Vector3
    {
    public:
        explicit Vector3() = default;

        ~Vector3() = default;

        MATH_LIB_FORCE_INLINE explicit Vector3(T x, T y, T z)
            : m_data({x, y, z}){ASSERT_IS_FINITE(*this)}

            MATH_LIB_FORCE_INLINE explicit Vector3(T x)
            : m_data({x, x, x})

        {
            ASSERT_IS_FINITE(*this)
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE T getX() const noexcept
        {
            return m_data[0];
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE T getY() const noexcept
        {
            return m_data[1];
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE T getZ() const noexcept
        {
            return m_data[2];
        }

        MATH_LIB_FORCE_INLINE void setX(T x) noexcept
        {
            m_data[0] = x;
        }

        MATH_LIB_FORCE_INLINE void setY(T y) noexcept
        {
            m_data[1] = y;
        }

        MATH_LIB_FORCE_INLINE void setZ(T z) noexcept
        {
            m_data[2] = z;
        }

        MATH_LIB_FORCE_INLINE Vector3& operator+=(const Vector3& other) noexcept
        {
            m_data[0] += other.m_data[0];
            m_data[1] += other.m_data[1];
            m_data[2] += other.m_data[2];
            ASSERT_IS_FINITE(*this)
            return *this;
        }

        MATH_LIB_FORCE_INLINE Vector3& operator-=(const Vector3& other) noexcept
        {
            m_data[0] -= other.m_data[0];
            m_data[1] -= other.m_data[1];
            m_data[2] -= other.m_data[2];

            ASSERT_IS_FINITE(*this)
            return *this;
        }

        MATH_LIB_FORCE_INLINE Vector3& operator*=(const Vector3& other) noexcept
        {
            m_data[0] *= other.m_data[0];
            m_data[1] *= other.m_data[1];
            m_data[2] *= other.m_data[2];
            ASSERT_IS_FINITE(*this)
            return *this;
        }

        MATH_LIB_FORCE_INLINE Vector3& operator/=(const Vector3& other) noexcept
        {
            m_data[0] /= other.m_data[0];
            m_data[1] /= other.m_data[1];
            m_data[2] /= other.m_data[2];
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

        MATH_LIB_FORCE_INLINE Vector3& operator+=(const T scalar) noexcept
        {
            m_data[0] += scalar;
            m_data[1] += scalar;
            m_data[2] += scalar;

            ASSERT_IS_FINITE(*this)
            return *this;
        }

        MATH_LIB_FORCE_INLINE Vector3& operator-=(const T scalar) noexcept
        {
            m_data[0] -= scalar;
            m_data[1] -= scalar;
            m_data[2] -= scalar;

            ASSERT_IS_FINITE(*this)
            return *this;
        }

        MATH_LIB_FORCE_INLINE Vector3& operator*=(T scalar) noexcept
        {
            m_data[0] *= scalar;
            m_data[1] *= scalar;
            m_data[2] *= scalar;

            ASSERT_IS_FINITE(*this)
            return *this;
        }

        MATH_LIB_FORCE_INLINE Vector3& operator/=(T scalar) noexcept
        {
            m_data[0] /= scalar;
            m_data[1] /= scalar;
            m_data[2] /= scalar;

            ASSERT_IS_FINITE(*this)
            return *this;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector3 operator+(Vector3 lhs, const T scalar) noexcept
        {
            lhs += scalar;
            return lhs;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector3 operator-(Vector3 lhs, const T scalar) noexcept
        {
            lhs -= scalar;
            return lhs;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector3 operator*(Vector3 lhs, const T scalar) noexcept
        {
            lhs *= scalar;
            return lhs;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector3 operator/(Vector3 lhs, const T scalar) noexcept
        {
            lhs /= scalar;
            return lhs;
        }

        [[nodiscard]] bool operator==(const Vector3& other) const
        {
            return fuzzyZero(m_data[0] - other.m_data[0]) && fuzzyZero(m_data[1] - other.m_data[1]) &&
                   fuzzyZero(m_data[2] - other.m_data[2]);
        }

        [[nodiscard]] bool operator!=(const Vector3& other) const
        {
            return !(*this == other);
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector3 operator-() const noexcept
        {
            ASSERT_IS_FINITE(*this)
            return Vector3(-m_data[0], -m_data[1], -m_data[2]);
        }

        [[nodiscard]] static MATH_LIB_FORCE_INLINE T dot(const Vector3& a, const Vector3& b)
        {
            ASSERT_IS_FINITE(a)
            ASSERT_IS_FINITE(b)
            return (a.m_data[0] * b.m_data[0]) + (a.m_data[1] * b.m_data[1]) + (a.m_data[2] * b.m_data[2]);
        }

        [[nodiscard]] static MATH_LIB_FORCE_INLINE Vector3 cross(const Vector3& a, const Vector3& b)
        {
            ASSERT_IS_FINITE(a);
            ASSERT_IS_FINITE(b);
            const T x = a.getY() * b.getZ() - a.getZ() * b.getY();
            const T y = a.getZ() * b.getX() - a.getX() * b.getZ();
            const T z = a.getX() * b.getY() - a.getY() * b.getX();
            return Vector3(x, y, z);
        }

        [[nodiscard]] static MATH_LIB_FORCE_INLINE T mix(const Vector3& a, const Vector3& b, const Vector3& c)
        {
            return Vector3::dot(a, Vector3::cross(b, c));
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE T lengthSquare() const
        {
            ASSERT_IS_FINITE(*this)
            return dot(*this, *this);
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE T length() const
        {
            ASSERT_IS_FINITE(*this)
            return std::sqrt(lengthSquare());
        }

        [[nodiscard]] static MATH_LIB_FORCE_INLINE T distanceSquare(const Vector3& a, const Vector3& b)
        {
            ASSERT_IS_FINITE(a)
            ASSERT_IS_FINITE(b)
            return (b - a).lengthSquare();
        }

        [[nodiscard]] static MATH_LIB_FORCE_INLINE T distance(const Vector3& a, const Vector3& b)
        {
            return std::sqrt(distanceSquare(a, b));
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector3 getNormalize() const
        {
            const T currentLength = length();

            if (fuzzyZero(currentLength))
            {
                return *this;
            }

            return *this / currentLength;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector3 getNormalizeFast() const
        {
            const T currentLength = length();

            if (fuzzyZero(currentLength))
            {
                return *this;
            }

            const T invLength = 1.0 / currentLength;
            return *this * invLength;
        }

        Vector3& normalize()
        {
            const T currentLength = length();

            if (fuzzyZero(currentLength))
            {
                return *this;
            }

            *this /= currentLength;
            return *this;
        }

        Vector3& normalizeFast()
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

        [[nodiscard]] MATH_LIB_FORCE_INLINE static Vector3 min(const Vector3& a, const Vector3& b) noexcept
        {
            ASSERT_IS_FINITE(a)
            ASSERT_IS_FINITE(b)
            return Vector3(std::min(a.getX(), b.getX()), std::min(a.getY(), b.getY()), std::min(a.getZ(), b.getZ()));
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE static Vector3 max(const Vector3& a, const Vector3& b) noexcept
        {
            ASSERT_IS_FINITE(a)
            ASSERT_IS_FINITE(b)
            return Vector3(std::max(a.getX(), b.getX()), std::max(a.getY(), b.getY()), std::max(a.getZ(), b.getZ()));
        }

        [[nodiscard]] Vector3 abs() const
        {
            return Vector3{std::abs(m_data[0]), std::abs(m_data[1]), std::abs(m_data[2])};
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
            return Vector3(0.0, 0.0, 0.0);
        }

        friend MATH_LIB_FORCE_INLINE std::ostream& operator<<(std::ostream& ostream, const Vector3& vec)
        {
            ostream << "x: " << vec.m_data[0] << ", y: " << vec.m_data[1] << ", z: " << vec.m_data[2];

            return ostream;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE bool isFinite() const
        {
            return std::isfinite(m_data[0]) && std::isfinite(m_data[1]) && std::isfinite(m_data[2]);
        }

        [[nodiscard]] Vector3<T> xzy() const noexcept
        {
            return Vector3(getX(), getZ(), getY());
        }

        [[nodiscard]] Vector3<T> yxz() const noexcept
        {
            return Vector3(getY(), getX(), getZ());
        }

        [[nodiscard]] Vector3<T> yzx() const noexcept
        {
            return Vector3(getY(), getZ(), getX());
        }

        [[nodiscard]] Vector3<T> zxy() const noexcept
        {
            return Vector3(getZ(), getX(), getY());
        }

        [[nodiscard]] Vector3<T> zyx() const noexcept
        {
            return Vector3(getZ(), getY(), getX());
        }

        [[nodiscard]] Vector2<T> xy() const noexcept
        {
            return Vector2(getX(), getY());
        }

        [[nodiscard]] Vector2<T> xz() const noexcept
        {
            return Vector2(getX(), getZ());
        }

        [[nodiscard]] Vector2<T> yx() const noexcept
        {
            return Vector2(getY(), getX());
        }

        [[nodiscard]] Vector2<T> yz() const noexcept
        {
            return Vector2(getY(), getZ());
        }

        [[nodiscard]] Vector2<T> zx() const noexcept
        {
            return Vector2(getZ(), getX());
        }

        [[nodiscard]] Vector2<T> zy() const noexcept
        {
            return Vector2(getZ(), getY());
        }

        explicit operator Vector2<T>() const noexcept
        {
            return Vector2<T>(getX(), getY());
        }

    private:
        std::array<T, 3> m_data;
    };

    using Vector3f = Vector3<float>;
    using Vector3d = Vector3<double>;

} // MathLib

// NOLINTEND(clang-analyzer-optin.cplusplus.UninitializedObject)

template<typename T>
struct std::formatter<MathLib::Vector3<T>, char>
{
    constexpr static std::format_parse_context::const_iterator parse(std::format_parse_context& ctx)
    {
        return ctx.begin();
    }

    static std::format_context::iterator format(const MathLib::Vector3<T>& v, std::format_context& ctx)
    {
        return std::format_to(ctx.out(), "x: {}, y: {}, z: {}", v.getX(), v.getY(), v.getZ());
    }
};

#endif // MATH_LIB_VECTOR3_H
