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

    template<typename T>
    class Vector2;

    template<>
    class Vector2<double>;

    template<>
    class Vector3<double>
    {
    public:
        explicit Vector3() = default;

        ~Vector3() = default;

        MATH_LIB_FORCE_INLINE explicit Vector3(double x, double y, double z)
            : m_data({x, y, z}){ASSERT_IS_FINITE(*this)}

            MATH_LIB_FORCE_INLINE explicit Vector3(double x)
            : m_data({x, x, x})

        {
            ASSERT_IS_FINITE(*this)
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double getX() const noexcept
        {
            return m_data[0];
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double getY() const noexcept
        {
            return m_data[1];
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double getZ() const noexcept
        {
            return m_data[2];
        }

        MATH_LIB_FORCE_INLINE void setX(double x) noexcept
        {
            m_data[0] = x;
        }

        MATH_LIB_FORCE_INLINE void setY(double y) noexcept
        {
            m_data[1] = y;
        }

        MATH_LIB_FORCE_INLINE void setZ(double z) noexcept
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

        MATH_LIB_FORCE_INLINE Vector3& operator+=(const double scalar) noexcept
        {
            m_data[0] += scalar;
            m_data[1] += scalar;
            m_data[2] += scalar;

            ASSERT_IS_FINITE(*this)
            return *this;
        }

        MATH_LIB_FORCE_INLINE Vector3& operator-=(const double scalar) noexcept
        {
            m_data[0] -= scalar;
            m_data[1] -= scalar;
            m_data[2] -= scalar;

            ASSERT_IS_FINITE(*this)
            return *this;
        }

        MATH_LIB_FORCE_INLINE Vector3& operator*=(double scalar) noexcept
        {
            m_data[0] *= scalar;
            m_data[1] *= scalar;
            m_data[2] *= scalar;

            ASSERT_IS_FINITE(*this)
            return *this;
        }

        MATH_LIB_FORCE_INLINE Vector3& operator/=(double scalar) noexcept
        {
            m_data[0] /= scalar;
            m_data[1] /= scalar;
            m_data[2] /= scalar;

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

        [[nodiscard]] static MATH_LIB_FORCE_INLINE double dot(const Vector3& a, const Vector3& b)
        {
            ASSERT_IS_FINITE(a)
            ASSERT_IS_FINITE(b)
            return (a.m_data[0] * b.m_data[0]) + (a.m_data[1] * b.m_data[1]) + (a.m_data[2] * b.m_data[2]);
        }

        [[nodiscard]] static MATH_LIB_FORCE_INLINE Vector3 cross(const Vector3& a, const Vector3& b)
        {
            ASSERT_IS_FINITE(a);
            ASSERT_IS_FINITE(b);
            const double x = a.getY() * b.getZ() - a.getZ() * b.getY();
            const double y = a.getZ() * b.getX() - a.getX() * b.getZ();
            const double z = a.getX() * b.getY() - a.getY() * b.getX();
            return Vector3(x, y, z);
        }

        [[nodiscard]] static MATH_LIB_FORCE_INLINE double mix(const Vector3& a, const Vector3& b, const Vector3& c)
        {
            return Vector3::dot(a, Vector3::cross(b, c));
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

        [[nodiscard]] Vector3<double> xzy() const noexcept
        {
            return Vector3(getX(), getZ(), getY());
        }

        [[nodiscard]] Vector3<double> yxz() const noexcept
        {
            return Vector3(getY(), getX(), getZ());
        }

        [[nodiscard]] Vector3<double> yzx() const noexcept
        {
            return Vector3(getY(), getZ(), getX());
        }

        [[nodiscard]] Vector3<double> zxy() const noexcept
        {
            return Vector3(getZ(), getX(), getY());
        }

        [[nodiscard]] Vector3<double> zyx() const noexcept
        {
            return Vector3(getZ(), getY(), getX());
        }

        [[nodiscard]] Vector2<double> xy() const noexcept;

        [[nodiscard]] Vector2<double> xz() const noexcept;

        [[nodiscard]] Vector2<double> yx() const noexcept;

        [[nodiscard]] Vector2<double> yz() const noexcept;

        [[nodiscard]] Vector2<double> zx() const noexcept;

        [[nodiscard]] Vector2<double> zy() const noexcept;

        explicit operator Vector2<double>() const noexcept;

    private:
        std::array<double, 3> m_data;
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
        return std::format_to(ctx.out(), "x: {}, y: {}, z: {}", v.getX(), v.getY(), v.getZ());
    }
};

#endif // MATH_LIB_VECTOR3D_H
