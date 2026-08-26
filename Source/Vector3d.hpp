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
            : m_x(x)
            , m_y(y)
            , m_z(z){ASSERT_IS_FINITE(*this)}

            MATH_LIB_FORCE_INLINE explicit Vector3(double x)
            : m_x(x)
            , m_y(x)
            , m_z(x)

        {
            ASSERT_IS_FINITE(*this)
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double getX() const noexcept
        {
            return m_x;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double getY() const noexcept
        {
            return m_y;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double getZ() const noexcept
        {
            return m_z;
        }

        MATH_LIB_FORCE_INLINE void setX(double x) noexcept
        {
            m_x = x;
            ASSERT_IS_FINITE(*this);
        }

        MATH_LIB_FORCE_INLINE void setY(double y) noexcept
        {
            m_y = y;
            ASSERT_IS_FINITE(*this);
        }

        MATH_LIB_FORCE_INLINE void setZ(double z) noexcept
        {
            m_z = z;
            ASSERT_IS_FINITE(*this);
        }

        MATH_LIB_FORCE_INLINE Vector3& operator+=(const Vector3& other) noexcept
        {
            m_x += other.m_x;
            m_y += other.m_y;
            m_z += other.m_z;
            ASSERT_IS_FINITE(*this) return *this;
        }

        MATH_LIB_FORCE_INLINE Vector3& operator-=(const Vector3& other) noexcept
        {
            m_x -= other.m_x;
            m_y -= other.m_y;
            m_z -= other.m_z;

            ASSERT_IS_FINITE(*this)
            return *this;
        }

        MATH_LIB_FORCE_INLINE Vector3& operator*=(const Vector3& other) noexcept
        {
            m_x *= other.m_x;
            m_y *= other.m_y;
            m_z *= other.m_z;
            ASSERT_IS_FINITE(*this)
            return *this;
        }

        MATH_LIB_FORCE_INLINE Vector3& operator/=(const Vector3& other) noexcept
        {
            m_x /= other.m_x;
            m_y /= other.m_y;
            m_z /= other.m_z;
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
            m_x += scalar;
            m_y += scalar;
            m_z += scalar;

            ASSERT_IS_FINITE(*this)
            return *this;
        }

        MATH_LIB_FORCE_INLINE Vector3& operator-=(const double scalar) noexcept
        {
            m_x -= scalar;
            m_y -= scalar;
            m_z -= scalar;

            ASSERT_IS_FINITE(*this)
            return *this;
        }

        MATH_LIB_FORCE_INLINE Vector3& operator*=(double scalar) noexcept
        {
            m_x *= scalar;
            m_y *= scalar;
            m_z *= scalar;

            ASSERT_IS_FINITE(*this)
            return *this;
        }

        MATH_LIB_FORCE_INLINE Vector3& operator/=(double scalar) noexcept
        {
            m_x /= scalar;
            m_y /= scalar;
            m_z /= scalar;

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
            return fuzzyZero(m_x - other.m_x) && fuzzyZero(m_y - other.m_y) && fuzzyZero(m_z - other.m_z);
        }

        [[nodiscard]] bool operator!=(const Vector3& other) const
        {
            return !(*this == other);
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector3 operator-() const noexcept
        {
            ASSERT_IS_FINITE(*this)
            return Vector3(-m_x, -m_y, -m_z);
        }

        [[nodiscard]] static MATH_LIB_FORCE_INLINE double dot(const Vector3& a, const Vector3& b)
        {
            ASSERT_IS_FINITE(a)
            ASSERT_IS_FINITE(b)
            return (a.m_x * b.m_x) + (a.m_y * b.m_y) + (a.m_z * b.m_z);
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
            return Vector3{std::abs(m_x), std::abs(m_y), std::abs(m_z)};
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

        MATH_LIB_FORCE_INLINE void storeToUnalignedDouble(const std::span<double, 3>& span) const noexcept
        {
            ASSERT_IS_FINITE(*this);
            span[0] = m_x;
            span[1] = m_y;
            span[2] = m_z;
        }

        MATH_LIB_FORCE_INLINE void storeToUnalignedDouble(double* const ptr) const noexcept
        {
            storeToUnalignedDouble(std::span<double, 3>(ptr, 3));
        }

        MATH_LIB_FORCE_INLINE void storeToUnAlignedFloat(const std::span<float, 3>& span) const noexcept
        {
            ASSERT_IS_FINITE(*this);
            span[0] = static_cast<float>(m_x);
            span[1] = static_cast<float>(m_y);
            span[2] = static_cast<float>(m_z);
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
            m_x = span[0];
            m_y = span[1];
            m_z = span[2];

            ASSERT_IS_FINITE(*this);
        }

        MATH_LIB_FORCE_INLINE void fromUnalignedDouble(const double* const ptr) noexcept
        {
            fromUnalignedDouble(std::span<const double, 3>(ptr, 3));
        }

        MATH_LIB_FORCE_INLINE void fromUnAlignedFloat(const std::span<const float, 3>& span) noexcept
        {
            m_x = static_cast<double>(span[0]);
            m_y = static_cast<double>(span[1]);
            m_z = static_cast<double>(span[2]);
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
            return std::isfinite(m_x) && std::isfinite(m_y) && std::isfinite(m_z);
        }

        [[nodiscard]] Vector3<double> xzy() const noexcept
        {
            return Vector3(m_x, m_z, m_y);
        }

        [[nodiscard]] Vector3<double> yxz() const noexcept
        {
            return Vector3(m_y, m_x, m_z);
        }

        [[nodiscard]] Vector3<double> yzx() const noexcept
        {
            return Vector3(m_y, m_z, m_x);
        }

        [[nodiscard]] Vector3<double> zxy() const noexcept
        {
            return Vector3(m_z, m_x, m_y);
        }

        [[nodiscard]] Vector3<double> zyx() const noexcept
        {
            return Vector3(m_z, m_y, m_x);
        }

        [[nodiscard]] Vector2<double> xy() const noexcept;

        [[nodiscard]] Vector2<double> xz() const noexcept;

        [[nodiscard]] Vector2<double> yx() const noexcept;

        [[nodiscard]] Vector2<double> yz() const noexcept;

        [[nodiscard]] Vector2<double> zx() const noexcept;

        [[nodiscard]] Vector2<double> zy() const noexcept;

        explicit operator Vector2<double>() const noexcept;

    private:
        double m_x;
        double m_y;
        double m_z;
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
