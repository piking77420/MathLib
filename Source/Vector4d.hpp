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
#include <AVX.hpp>

namespace MathLib
{
    template<typename T>
    class Vector4;

    template<typename T>
    class Vector3;

    template<>
    class Vector3<double>;

    template<typename T>
    class Vector2;

    template<>
    class Vector2<double>;

    template<>
    class alignas(VECTOR4D_ALIGNEMENT) Vector4<double>
    {
    public:
        explicit Vector4() = default;

        ~Vector4() = default;

        MATH_LIB_FORCE_INLINE explicit Vector4(double x, double y, double z, double w)
            : m_data({x, y, z, w})

                  {ASSERT_IS_FINITE(*this)}

            MATH_LIB_FORCE_INLINE explicit Vector4(double x)
            : m_data({x, x, x, x})

        {
            ASSERT_IS_FINITE(*this)
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE const double* data() const noexcept
        {
            return m_data.data();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double* data() noexcept
        {
            return m_data.data();
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

        [[nodiscard]] MATH_LIB_FORCE_INLINE double getW() const noexcept
        {
            return m_data[3];
        }

        MATH_LIB_FORCE_INLINE void setX(double x) noexcept
        {
            m_data[0] = x;
            ASSERT_IS_FINITE(*this);
        }

        MATH_LIB_FORCE_INLINE void setY(double y) noexcept
        {
            m_data[1] = y;
            ASSERT_IS_FINITE(*this);
        }

        MATH_LIB_FORCE_INLINE void setZ(double z) noexcept
        {
            m_data[2] = z;
            ASSERT_IS_FINITE(*this);
        }

        MATH_LIB_FORCE_INLINE void setW(double w) noexcept
        {
            m_data[3] = w;
            ASSERT_IS_FINITE(*this);
        }

        MATH_LIB_FORCE_INLINE Vector4& operator+=(const Vector4& other) noexcept
        {
#if defined(MATH_LIB_INTRINSIC)
            *this = Vector4(Simd::add(*this, other));
#else
            m_data[0] += other.m_data[0];
            m_data[1] += other.m_data[1];
            m_data[2] += other.m_data[2];
            m_data[3] += other.m_data[3];
#endif // defined(MATH_LIB_INTRINSIC)

            ASSERT_IS_FINITE(*this) return *this;
        }

        MATH_LIB_FORCE_INLINE Vector4& operator-=(const Vector4& other) noexcept
        {
#if defined(MATH_LIB_INTRINSIC)
            *this = Vector4(Simd::sub(*this, other));
#else
            m_data[0] -= other.m_data[0];
            m_data[1] -= other.m_data[1];
            m_data[2] -= other.m_data[2];
            m_data[3] -= other.m_data[3];
#endif // defined(MATH_LIB_INTRINSIC)
            ASSERT_IS_FINITE(*this)
            return *this;
        }

        MATH_LIB_FORCE_INLINE Vector4& operator*=(const Vector4& other) noexcept
        {
#if defined(MATH_LIB_INTRINSIC)
            *this = Vector4(Simd::mul(*this, other));
#else
            m_data[0] *= other.m_data[0];
            m_data[1] *= other.m_data[1];
            m_data[2] *= other.m_data[2];
            m_data[3] *= other.m_data[3];
#endif // defined(MATH_LIB_INTRINSIC)
            ASSERT_IS_FINITE(*this)
            return *this;
        }

        MATH_LIB_FORCE_INLINE Vector4& operator/=(const Vector4& other) noexcept
        {
#if defined(MATH_LIB_INTRINSIC)
            *this = Vector4(Simd::div(*this, other));
#else
            m_data[0] /= other.m_data[0];
            m_data[1] /= other.m_data[1];
            m_data[2] /= other.m_data[2];
            m_data[3] /= other.m_data[3];
#endif // defined(MATH_LIB_INTRINSIC)
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
#if defined(MATH_LIB_INTRINSIC)
            *this = Vector4(Simd::add(*this, Simd::makeVector4D(scalar)));
#else
            m_data[0] += scalar;
            m_data[1] += scalar;
            m_data[2] += scalar;
            m_data[3] += scalar;
#endif // defined(MATH_LIB_INTRINSIC)
            ASSERT_IS_FINITE(*this)
            return *this;
        }

        MATH_LIB_FORCE_INLINE Vector4& operator-=(const double scalar) noexcept
        {
#if defined(MATH_LIB_INTRINSIC)
            *this = Vector4(Simd::sub(*this, Simd::makeVector4D(scalar)));
#else
            m_data[0] -= scalar;
            m_data[1] -= scalar;
            m_data[2] -= scalar;
            m_data[3] -= scalar;
#endif // defined(MATH_LIB_INTRINSIC)
            ASSERT_IS_FINITE(*this)
            return *this;
        }

        MATH_LIB_FORCE_INLINE Vector4& operator*=(double scalar) noexcept
        {
#if defined(MATH_LIB_INTRINSIC)
            *this = Vector4(Simd::mul(*this, Simd::makeVector4D(scalar)));
#else
            m_data[0] *= scalar;
            m_data[1] *= scalar;
            m_data[2] *= scalar;
            m_data[3] *= scalar;
#endif // defined(MATH_LIB_INTRINSIC)
            ASSERT_IS_FINITE(*this)
            return *this;
        }

        MATH_LIB_FORCE_INLINE Vector4& operator/=(double scalar) noexcept
        {
#if defined(MATH_LIB_INTRINSIC)
            *this = Vector4(Simd::div(*this, Simd::makeVector4D(scalar)));
#else
            m_data[0] /= scalar;
            m_data[1] /= scalar;
            m_data[2] /= scalar;
            m_data[3] /= scalar;
#endif // defined(MATH_LIB_INTRINSIC)
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
            return fuzzyZero(m_data[0] - other.m_data[0]) && fuzzyZero(m_data[1] - other.m_data[1]) &&
                   fuzzyZero(m_data[2] - other.m_data[2]) && fuzzyZero(m_data[3] - other.m_data[3]);
        }

        [[nodiscard]] bool operator!=(const Vector4& other) const
        {
            return !(*this == other);
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 operator-() const noexcept
        {
            return Vector4(-m_data[0], -m_data[1], -m_data[2], -m_data[3]);
        }

        [[nodiscard]] static MATH_LIB_FORCE_INLINE double dot(const Vector4& a, const Vector4& b)
        {
            ASSERT_IS_FINITE(a)
            ASSERT_IS_FINITE(b)

            const double x2 = a.getX() * b.getX();
            const double y2 = a.getY() * b.getY();
            const double z2 = a.getZ() * b.getZ();
            const double w2 = a.getW() * b.getW();
            return x2 + y2 + z2 + w2;
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

        [[nodiscard]] MATH_LIB_FORCE_INLINE static Vector4 cross(const Vector4& a, const Vector4& b,
                                                                 const Vector4& c) noexcept
        {
            // Get all scalar
            const double ax = a.getX();
            const double ay = a.getY();
            const double az = a.getZ();
            const double aw = a.getW();

            const double bx = b.getX();
            const double by = b.getY();
            const double bz = b.getZ();
            const double bw = b.getW();

            const double cx = c.getX();
            const double cy = c.getY();
            const double cz = c.getZ();
            const double cw = c.getW();

            // manually do the cors product or determinant
            const double mYZ = by * cz - bz * cy;
            const double mYW = by * cw - bw * cy;
            const double mZW = bz * cw - bw * cz;

            const double mXZ = bx * cz - bz * cx;
            const double mXW = bx * cw - bw * cx;

            const double mXY = bx * cy - by * cx;

            // manuall dot
            return Vector4(ay * mZW - az * mYW + aw * mYZ, -(ax * mZW - az * mXW + aw * mXZ),
                           ax * mYW - ay * mXW + aw * mXY, -(ax * mYZ - ay * mXZ + az * mXY));
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE static Vector4 min(const Vector4& a, const Vector4& b) noexcept
        {
            ASSERT_IS_FINITE(a)
            ASSERT_IS_FINITE(b)
#if defined(MATH_LIB_INTRINSIC)
            return Vector4(Simd::min(a, b));
#else
            return Vector4(std::min(a.getX(), b.getX()), std::min(a.getY(), b.getY()), std::min(a.getZ(), b.getZ()),
                           std::min(a.getW(), b.getW()));
#endif // defined(MATH_LIB_INTRINSIC)
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE static Vector4 max(const Vector4& a, const Vector4& b) noexcept
        {
            ASSERT_IS_FINITE(a)
            ASSERT_IS_FINITE(b)
#if defined(MATH_LIB_INTRINSIC)
            return Vector4(Simd::max(a, b));
#else
            return Vector4(std::max(a.getX(), b.getX()), std::max(a.getY(), b.getY()), std::max(a.getZ(), b.getZ()),
                           std::max(a.getW(), b.getW()));
#endif // defined(MATH_LIB_INTRINSIC)
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
            return Vector4(0.0, 0.0, 0.0, 0.0);
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 abs() const noexcept
        {
            ASSERT_IS_FINITE(*this);
            return Vector4(std::abs(getX()), std::abs(m_data[1]), std::abs(m_data[2]), std::abs(m_data[3]));
        }

        friend MATH_LIB_FORCE_INLINE std::ostream& operator<<(std::ostream& ostream, const Vector4& vec)
        {
            ostream << "x: " << vec.m_data[0] << ", y: " << vec.m_data[1] << ", z: " << vec.m_data[2]
                    << ", w: " << vec.m_data[3];

            return ostream;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE bool isFinite() const
        {
            return std::isfinite(getX()) && std::isfinite(m_data[1]) && std::isfinite(m_data[2]) &&
                   std::isfinite(m_data[3]);
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 xywz() const noexcept
        {
            return Vector4(getX(), getY(), getW(), getZ());
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 xzyw() const noexcept
        {
            return Vector4(getX(), getZ(), getY(), getW());
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 xzwy() const noexcept
        {
            return Vector4(getX(), getZ(), getW(), getY());
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 xwyz() const noexcept
        {
            return Vector4(getX(), getW(), getY(), getZ());
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 xwzy() const noexcept
        {
            return Vector4(getX(), getW(), getZ(), getY());
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 yxzw() const noexcept
        {
            return Vector4(getY(), getX(), getZ(), getW());
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 yxwz() const noexcept
        {
            return Vector4(getY(), getX(), getW(), getZ());
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 yzxw() const noexcept
        {
            return Vector4(getY(), getZ(), getX(), getW());
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 yzwx() const noexcept
        {
            return Vector4(getY(), getZ(), getW(), getX());
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 ywxz() const noexcept
        {
            return Vector4(getY(), getW(), getX(), getZ());
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 ywzx() const noexcept
        {
            return Vector4(getY(), getW(), getZ(), getX());
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 zxyw() const noexcept
        {
            return Vector4(getZ(), getX(), getY(), getW());
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 zxwy() const noexcept
        {
            return Vector4(getZ(), getX(), getW(), getY());
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 zyxw() const noexcept
        {
            return Vector4(getZ(), getY(), getX(), getW());
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 zywx() const noexcept
        {
            return Vector4(getZ(), getY(), getW(), getX());
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 zwxy() const noexcept
        {
            return Vector4(getZ(), getW(), getX(), getY());
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 zwyx() const noexcept
        {
            return Vector4(getZ(), getW(), getY(), getX());
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 wxyz() const noexcept
        {
            return Vector4(getW(), getX(), getY(), getZ());
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 wxzy() const noexcept
        {

            return Vector4(getW(), getX(), getZ(), getY());
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 wyxz() const noexcept
        {
            return Vector4(getW(), getY(), getX(), getZ());
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 wyzx() const noexcept
        {
            return Vector4(getW(), getY(), getZ(), getX());
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 wzxy() const noexcept
        {
            return Vector4(getW(), getZ(), getX(), getY());
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 wzyx() const noexcept
        {
            return Vector4(getW(), getZ(), getY(), getX());
        }

        [[nodiscard]] Vector3<double> xyz() const noexcept;

        [[nodiscard]] Vector3<double> xzy() const noexcept;

        [[nodiscard]] Vector3<double> yxz() const noexcept;

        [[nodiscard]] Vector3<double> yzx() const noexcept;

        [[nodiscard]] Vector3<double> zxy() const noexcept;

        [[nodiscard]] Vector3<double> zyx() const noexcept;

        [[nodiscard]] Vector2<double> xy() const noexcept;

        [[nodiscard]] Vector2<double> xz() const noexcept;

        [[nodiscard]] Vector2<double> xw() const noexcept;

        [[nodiscard]] Vector2<double> yx() const noexcept;

        [[nodiscard]] Vector2<double> yz() const noexcept;

        [[nodiscard]] Vector2<double> yw() const noexcept;

        [[nodiscard]] Vector2<double> zx() const noexcept;

        [[nodiscard]] Vector2<double> zy() const noexcept;

        [[nodiscard]] Vector2<double> zw() const noexcept;

        [[nodiscard]] Vector2<double> wx() const noexcept;

        [[nodiscard]] Vector2<double> wy() const noexcept;

        [[nodiscard]] Vector2<double> wz() const noexcept;

        explicit operator Vector3<double>() const noexcept;

        explicit operator Vector2<double>() const noexcept;

    private:
        std::array<double, 4> m_data;

#if defined(MATH_LIB_INTRINSIC)
        MATH_LIB_FORCE_INLINE Vector4(const Simd::VectorRegister4Double& reg) noexcept
        {
            Simd::storeUnaligned(reg, m_data.data());
        }
#endif // defined(MATH_LIB_INTRINSIC)

#if defined(MATH_LIB_INTRINSIC)
        operator Simd::VectorRegister4Double() const noexcept
        {
            return Simd::makeVector4DUnaligned(m_data.data());
        }
#endif // defined(MATH_LIB_INTRINSIC)
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
        return std::format_to(ctx.out(), "x: {}, y: {}, z: {}, w: {}", v.getX(), v.getY(), v.getZ(), v.getW());
    }
};

#endif // MATH_LIB_VECTOR4D_H
